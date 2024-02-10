/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Youssef Khaled
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H


/* Id for the company in the AUTOSAR
 * for example Youssef Khaled's ID = 1337 */
#define PORT_VENDOR_ID   (1337U)

/* Port Module Id */
#define PORT_MODULE_ID  (140U)

/* Port Instance Id */
#define PORT_INSTANCE_ID (0U)

/*
 * Module Version 3.2.0
 */
#define PORT_SW_MAJOR_VERSION       (3U)
#define PORT_SW_MINOR_VERSION       (2U)
#define PORT_SW_PATCH_VERSION       (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include <Common/Std_Types.h>

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Mcu.h"
#include <Common/Common_Macros.h>

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT initialization API  */
#define PORT_INIT_SID                      (uint8)0x00

/* Service ID for PORT set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID         (uint8)0x01

/* Service ID for PORT refresh Port direction  */
#define PORT_REFRESH_PORT_DIRECTION_SID    (uint8)0x02

/* Service ID for PORT SET Pin mode */
#define PORT_SET_PIN_MODE_SID              (uint8)0x04

/* Service ID for PORT GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID          (uint8)0x03

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN               (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE  (uint8)0x0B

/* API Port_Init service called with wrong parameter. */
#define PORT_E_PARAM_CONFIG            (uint8)0x0C

/* API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE      (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE       (uint8)0x0E

/* API service called without module initialization */
#define PORT_E_UNINIT                  (uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER           (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Description: Enum to hold PORTS ID'S */
typedef enum
{
    PORTA_ID,
    PORTB_ID,
    PORTC_ID,
    PORTD_ID,
    PORTE_ID,
    PORTF_ID
}Port_PortID;

typedef enum
{
    PORT_PIN_0,
    PORT_PIN_1,
    PORT_PIN_2,
    PORT_PIN_3,
    PORT_PIN_4,
    PORT_PIN_5,
    PORT_PIN_6,
    PORT_PIN_7
}Port_PinID;

/* Description: Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Description: Different port pin modes. */
typedef enum
{
    PORT_PIN_MODE_DIO,
    PORT_PIN_MODE_ALT1,
    PORT_PIN_MODE_ALT2,
    PORT_PIN_MODE_ALT3,
    PORT_PIN_MODE_ALT4,
    PORT_PIN_MODE_ALT5,
    PORT_PIN_MODE_ALT6,
    PORT_PIN_MODE_ALT7,
    PORT_PIN_MODE_ALT8,
    PORT_PIN_MODE_ALT9,
    PORT_PIN_MODE_ALT14 = 14,
    PORT_PIN_MODE_ANLOG,
}Port_PinModeType;

/* Description: Enum to hold Possible directions of a Port PIN */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *  3. the different port pin modes
 *  4. the direction of pin --> INPUT or OUTPUT
 *  5. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct
{
    Port_PortID port_num;
    Port_PinID pin_num;
    Port_PinModeType pin_mode;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    uint8 Pin_Dir_Changeable;           /* STD_ON,STD_OFF */
    uint8 Pin_Mode_Changeable;          /* STD_ON,STD_OFF*/
}Port_PinConfigType;

/* Data Structure required for initializing the PORT Driver */
typedef struct
{
    Port_PinConfigType Pin_ConfigType[PORT_CONFIGURED_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Port_Init
 * Service ID[hex]:0x00
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module:
 *              - Setup the Pin mode (e.g. DIO, ADC, SPI …)
 *              - Setup the  Pin direction (input, output)
 *              - Provide Pin level initial value for o/p pin
 *              - Setup the internal resistor for i/p pin
 ************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr );

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
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

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
void Port_RefreshPortDirection(void);

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
void PORT_GetVersionInfo(Std_VersionInfoType *versioninfo);

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
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
