/******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button_Cfg.h
 *
 * Description: Header file for Pre-Compiler configuration used by Button Module
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef ECUAL_BUTTON_CFG_H_
#define ECUAL_BUTTON_CFG_H_

/* Button State according to its configuration PULL UP/Down */
#define BUTTON_PRESSED  STD_LOW
#define BUTTON_RELEASED STD_HIGH

/* Set the Button Port */
#define BUTTON_PORT DioConf_SW1_PORT_NUM

/* Set the Button Pin Number */
#define BUTTON_PIN_NUM DioConf_SW1_CHANNEL_NUM


#endif /* ECUAL_BUTTON_CFG_H_ */
