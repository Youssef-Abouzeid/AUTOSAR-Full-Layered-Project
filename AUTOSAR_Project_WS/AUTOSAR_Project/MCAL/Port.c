/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Youssef Khaled
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Service_Layer/Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigType *Port_Pins = NULL_PTR;
STATIC volatile uint8 Port_Status = PORT_NOT_INITIALIZED;
STATIC Port_PinType index = 0;

/************************************************************************************
 * Service Name: Port_Init
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module:
 *              - Setup the Pin mode (e.g. PORT, ADC, SPI …)
 *              - Setup the  Pin direction (input, output)
 *              - Provide Pin level initial value for o/p pin
 *              - Setup the internal resistor for i/p pin
 ************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                        PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        /*
         * Set the module state to initialized and point to the PB configuration structure using a global pointer.
         * This global pointer is global to be used by other functions to read the PB configuration structures
         */
        Port_Status = PORT_INITIALIZED;
        Port_Pins = ConfigPtr; /* address of the first Channels structure --> Channels[0] */
    }

    for(index = 0 ; index < PORT_CONFIGURED_PINS ; index++)
    {
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_Pins->Pin_ConfigType[index].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        if( ((Port_Pins->Pin_ConfigType[index].port_num == 3) && (Port_Pins->Pin_ConfigType[index].pin_num == 7)) || ((Port_Pins->Pin_ConfigType[index].port_num == 5) && (Port_Pins->Pin_ConfigType[index].pin_num == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if( (Port_Pins->Pin_ConfigType[index].port_num == 2) && (Port_Pins->Pin_ConfigType[index].pin_num <= 3) ) /* PC0 to PC3 */
        {
            /* Do Nothing ...  this is the JTAG pins */
            continue;
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        if(Port_Pins->Pin_ConfigType[index].pin_mode == PORT_PIN_MODE_DIO)
        {
            /* Setup the pin mode as Dio */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins->Pin_ConfigType[index].pin_num * 4));     /* Clear the PMCx bits for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
        else if(Port_Pins->Pin_ConfigType[index].pin_mode == PORT_PIN_MODE_ANLOG)
        {
            /* Setup the pin mode as Analog pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);        /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins->Pin_ConfigType[index].pin_num * 4));     /* Clear the PMCx bits for this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);         /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */


        }
        else
        {
            /* Setup the pin mode as Alternative pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);               /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((0x0000000F) & ((uint32)(Port_Pins->Pin_ConfigType[index].pin_mode)) << (Port_Pins->Pin_ConfigType[index].pin_num * 4));     /* Set the corresponding Alternative function bits in the PMCx for this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


        }


        if(Port_Pins->Pin_ConfigType[index].direction == PORT_PIN_OUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

            if(Port_Pins->Pin_ConfigType[index].initial_value == STD_HIGH)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
            }
        }
        else if(Port_Pins->Pin_ConfigType[index].direction == PORT_PIN_IN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

            if(Port_Pins->Pin_ConfigType[index].resistor == PULL_UP)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
            }
            else if(Port_Pins->Pin_ConfigType[index].resistor == PULL_DOWN)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
            }
        }
        else
        {
            /* Do Nothing */
        }

    }
}

/************************************************************************************
 * Service Name: Port_SetpinDirection
 * Service ID[hex]:0x01
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Pin: Port Pin ID number, Direction: Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction
 ************************************************************************************/
#if (PortSetPinDirection == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if API service called prior to module initialization */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
    /* Check if Port Pin not configured as changeable */
    if (Port_Pins->Pin_ConfigType[Pin].Pin_Dir_Changeable != STD_ON)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE);
    }    /* Check if Incorrect Port Pin ID passed */
    if(PORT_CONFIGURED_PINS <= Pin)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_PARAM_PIN);
    }
    else
    {
        /* Do Nothing */

    }
#endif


    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

    switch(Port_Pins->Pin_ConfigType[Pin].port_num)
    {
    case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    break;
    case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    break;
    case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    break;
    case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    break;
    case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    break;
    case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    break;
    }

    if(Direction == PORT_PIN_OUT)
    {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        if(Port_Pins->Pin_ConfigType[Pin].initial_value == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if (Direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        if(Port_Pins->Pin_ConfigType[Pin].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(Port_Pins->Pin_ConfigType[Pin].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }


}
#endif


/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]:0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Refreshes port direction
 ************************************************************************************/
void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if API service called prior to module initialization */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
    else
    {
        /* Do Nothing */
    }
#endif

    for(index = 0 ; index < PORT_CONFIGURED_PINS ; index++)
    {
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

        switch(Port_Pins->Pin_ConfigType[index].port_num)
        {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        break;
        case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        break;
        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        break;
        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        break;
        }

        /*
         * Exclude those port pins from refreshing that are
         * configured as "pin direction changeable during runtime".
         *
         * */
        if(Port_Pins->Pin_ConfigType[index].Pin_Dir_Changeable != STD_ON){

            if( ((Port_Pins->Pin_ConfigType[index].port_num == 3) && (Port_Pins->Pin_ConfigType[index].pin_num == 7)) || ((Port_Pins->Pin_ConfigType[index].port_num == 5) && (Port_Pins->Pin_ConfigType[index].pin_num == 0)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (Port_Pins->Pin_ConfigType[index].port_num == 2) && (Port_Pins->Pin_ConfigType[index].pin_num <= 3) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
                continue;
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            if(Port_Pins->Pin_ConfigType[index].direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(Port_Pins->Pin_ConfigType[index].initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(Port_Pins->Pin_ConfigType[index].direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(Port_Pins->Pin_ConfigType[index].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(Port_Pins->Pin_ConfigType[index].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins->Pin_ConfigType[index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* Do Nothing */
        }

    }
}

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void PORT_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if API service called prior to module initialization */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
                        PORT_E_UNINIT);
    }
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin: Port Pin ID number, Mode: New Port Pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if API service called prior to module initialization */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                        PORT_E_UNINIT);
    }
    /* Check if Incorrect Port Pin ID passed*/
    if(PORT_CONFIGURED_PINS <= Pin)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_PIN);
    }
    /* Check if Port Pin Mode passed not valid */
    if((Mode != PORT_PIN_MODE_DIO)  && (Mode != PORT_PIN_MODE_ALT1) && (Mode != PORT_PIN_MODE_ALT2) &&
            (Mode != PORT_PIN_MODE_ALT2) && (Mode != PORT_PIN_MODE_ALT3) && (Mode != PORT_PIN_MODE_ALT4) &&
            (Mode != PORT_PIN_MODE_ALT5) && (Mode != PORT_PIN_MODE_ALT6) && (Mode != PORT_PIN_MODE_ALT7) &&
            (Mode != PORT_PIN_MODE_ALT8) && (Mode != PORT_PIN_MODE_ALT9) && (Mode != PORT_PIN_MODE_ALT14)&&
            (Mode != PORT_PIN_MODE_ANLOG))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_PARAM_INVALID_MODE);
    }
    /* Check if Port_SetPinMode service called when the mode is unchangeable */
    if(Port_Pins->Pin_ConfigType[Pin].Pin_Mode_Changeable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                        PORT_E_MODE_UNCHANGEABLE);
    }
    else
    {
        /* Do Nothing */
    }
#endif
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

    switch(Port_Pins->Pin_ConfigType[Pin].port_num)
    {
    case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    break;
    case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    break;
    case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    break;
    case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    break;
    case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    break;
    case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    break;
    }

    if( ((Port_Pins->Pin_ConfigType[Pin].port_num == 3) && (Port_Pins->Pin_ConfigType[Pin].pin_num == 7)) || ((Port_Pins->Pin_ConfigType[Pin].port_num == 5) && (Port_Pins->Pin_ConfigType[Pin].pin_num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (Port_Pins->Pin_ConfigType[Pin].port_num == 2) && (Port_Pins->Pin_ConfigType[Pin].pin_num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
        return ;
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }

    if(Port_Pins->Pin_ConfigType[Pin].pin_mode == PORT_PIN_MODE_DIO)
    {
        /* Setup the pin mode as Dio */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins->Pin_ConfigType[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

    }
    else if(Port_Pins->Pin_ConfigType[Pin].pin_mode == PORT_PIN_MODE_ANLOG)
    {
        /* Setup the pin mode as Analog pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);        /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins->Pin_ConfigType[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);         /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */


    }
    else
    {
        /* Setup the pin mode as Alternative pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);                                                             /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);                                                                      /* Enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((0x0000000F) & ((uint32)(Port_Pins->Pin_ConfigType[Pin].pin_mode)) << (Port_Pins->Pin_ConfigType[Pin].pin_num * 4));     /* Set the corresponding Alternative function bits in the PMCx for this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins->Pin_ConfigType[Pin].pin_num);                                                                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


    }


}




