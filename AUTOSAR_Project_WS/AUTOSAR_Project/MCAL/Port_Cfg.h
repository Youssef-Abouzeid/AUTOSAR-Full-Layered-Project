 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef Khaled
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 3.2.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (3U)
#define PORT_CFG_SW_MINOR_VERSION              (2U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/*Pre-compile option for Port_SetPinDirection*/
#define PortSetPinDirection                  (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Number of the configured Ports */
#define PORT_CONFIGURED_PORTS                (6U)

/* Number of the configured Port Pins */
#define PORT_CONFIGURED_PINS                 (43U)

/* Symbolic names for the individual port pins */
/************************* PORTA *****************************/
#define PORT_A_PIN_0                         (Port_PinType)0
#define PORT_A_PIN_1                         (Port_PinType)1
#define PORT_A_PIN_2                         (Port_PinType)2
#define PORT_A_PIN_3                         (Port_PinType)3
#define PORT_A_PIN_4                         (Port_PinType)4
#define PORT_A_PIN_5                         (Port_PinType)5
#define PORT_A_PIN_6                         (Port_PinType)6
#define PORT_A_PIN_7                         (Port_PinType)7

/************************* PORTB *****************************/
#define PORT_B_PIN_0                         (Port_PinType)8
#define PORT_B_PIN_1                         (Port_PinType)9
#define PORT_B_PIN_2                         (Port_PinType)10
#define PORT_B_PIN_3                         (Port_PinType)11
#define PORT_B_PIN_4                         (Port_PinType)12
#define PORT_B_PIN_5                         (Port_PinType)13
#define PORT_B_PIN_6                         (Port_PinType)14
#define PORT_B_PIN_7                         (Port_PinType)15

/************************* PORTC *****************************/
#define PORT_C_PIN_0                         (Port_PinType)16
#define PORT_C_PIN_1                         (Port_PinType)17
#define PORT_C_PIN_2                         (Port_PinType)18
#define PORT_C_PIN_3                         (Port_PinType)19
#define PORT_C_PIN_4                         (Port_PinType)20
#define PORT_C_PIN_5                         (Port_PinType)21
#define PORT_C_PIN_6                         (Port_PinType)22
#define PORT_C_PIN_7                         (Port_PinType)23

/************************* PORTD *****************************/
#define PORT_D_PIN_0                         (Port_PinType)24
#define PORT_D_PIN_1                         (Port_PinType)25
#define PORT_D_PIN_2                         (Port_PinType)26
#define PORT_D_PIN_3                         (Port_PinType)27
#define PORT_D_PIN_4                         (Port_PinType)28
#define PORT_D_PIN_5                         (Port_PinType)29
#define PORT_D_PIN_6                         (Port_PinType)30
#define PORT_D_PIN_7                         (Port_PinType)31

/************************* PORTE *****************************/
#define PORT_E_PIN_0                         (Port_PinType)32
#define PORT_E_PIN_1                         (Port_PinType)33
#define PORT_E_PIN_2                         (Port_PinType)34
#define PORT_E_PIN_3                         (Port_PinType)35
#define PORT_E_PIN_4                         (Port_PinType)36
#define PORT_E_PIN_5                         (Port_PinType)37

/************************* PORTF *****************************/
#define PORT_F_PIN_0                         (Port_PinType)38
#define PORT_F_PIN_1                         (Port_PinType)39
#define PORT_F_PIN_2                         (Port_PinType)40
#define PORT_F_PIN_3                         (Port_PinType)41
#define PORT_F_PIN_4                         (Port_PinType)42


#endif /* PORT_CFG_H_ */
