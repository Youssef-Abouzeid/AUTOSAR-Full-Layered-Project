/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef Khaled
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 3.2.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (3U)
#define PORT_PBCFG_SW_MINOR_VERSION              (2U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with PORT_Init API */
const Port_ConfigType Port_Configuration = {
                                            /************************* PORTA *****************************/
                                            PORTA_ID,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTA_ID,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,

                                            /************************* PORTB *****************************/
                                            PORTB_ID,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTB_ID,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,

                                            /************************* PORTC *****************************/
                                            PORTC_ID,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTC_ID,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,

                                            /************************* PORTD *****************************/
                                            PORTD_ID,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_6,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTD_ID,PORT_PIN_7,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,

                                            /************************* PORTE *****************************/
                                            PORTE_ID,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTE_ID,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTE_ID,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTE_ID,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTE_ID,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTE_ID,PORT_PIN_5,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,

                                            /************************* PORTF *****************************/
                                            PORTF_ID,PORT_PIN_0,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTF_ID,PORT_PIN_1,PORT_PIN_MODE_DIO,PORT_PIN_OUT,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTF_ID,PORT_PIN_2,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTF_ID,PORT_PIN_3,PORT_PIN_MODE_DIO,PORT_PIN_IN,OFF,STD_LOW,STD_ON,STD_ON,
                                            PORTF_ID,PORT_PIN_4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PULL_UP,STD_LOW,STD_ON,STD_ON,

};



