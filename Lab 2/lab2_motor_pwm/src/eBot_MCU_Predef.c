/*
 * eBot_MCU_Predef.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */
//---------------------------------- INCLUDES ----------------------------------
#include "eBot_MCU_Predef.h"
//---------------------------------- FUNCTIONS ----------------------------------
/**
 * @brief      Function to configure pins of micro-controller to which pins of L293D Motor Driver IC is connected
 */
void motors_pin_config(void)
{
	motors_dir_ddr_reg |= ((1 << motors_RB_pin) | (1 << motors_RF_pin) | (1 << motors_LF_pin) | (1 << motors_LB_pin));			// motor pins as output
	motors_dir_port_reg &= ~((1 << motors_RB_pin) | (1 << motors_RF_pin) | (1 << motors_LF_pin) | (1 << motors_LB_pin));		// stop motors initially
}
/**
 * @brief      Function to configure left and right channel pins of the L293D Motor Driver IC for PWM
 */
void pwm_pin_config(void)
{
	motors_pwm_ddr_reg |= ((1 << motors_pwm_L_pin) | (1 << motors_pwm_R_pin));	// left and right channel pin as output
	motors_pwm_port_reg |= ((1 << motors_pwm_L_pin) | (1 << motors_pwm_R_pin));	// enable left and right channel
}
/**
 * @brief      Function to initialize Timer in Phase Correct PWM mode for speed control of motors of the robot
 */
void timer_pwm_init(void)
{
	// Make values in both Output Compare Registers as 0
	OCRAH_reg = 0x00;
	OCRAL_reg = 0x00;
	OCRBH_reg = 0x00;
	OCRBL_reg = 0x00;
	// Clear on Compare
	TCCRA_reg |= (1 << COMA1_bit) | (1 << COMB1_bit);
	TCCRA_reg &= ~((1 << COMA0_bit) | (1 << COMB0_bit));
	// Configure for Phase Correct PWM
	TCCRA_reg |=  (1 << WGM0_bit);
	TCCRA_reg &= ~(1 << WGM1_bit);
	TCCRB_reg &= ~(1 << WGM2_bit);
	TCCRB_reg &= ~(1 << WGM3_bit);
	// Set Prescalar to 64
	TCCRB_reg |= (1 << CS1_bit) | (1 << CS0_bit);
	TCCRB_reg &= ~(1 << CS2_bit);
}
/**
 * @brief      Function to make the robot move forward.
 */
void forward(void)
{
	motors_dir_port_reg &= ~((1 << motors_LF_pin) | (1 << motors_LB_pin) | (1 << motors_RF_pin) | (1 << motors_RB_pin));	// Make LF, LB, RF, RB LOW
	motors_dir_port_reg |= ((1 << motors_LF_pin) | (1 << motors_RF_pin));	// Make LF and RF HIGH
}
/**
 * @brief      Function to control the speed of both the motors of robot
 *
 * @param[in]  left_motor_speed   Left motor speed 0 to 255
 * @param[in]  right_motor_speed  Right motor speed 0 to 255
 */
void velocity(unsigned char left_motor_speed, unsigned char right_motor_speed)
{
	OCRAL_reg = (unsigned char)left_motor_speed;
	OCRBL_reg = (unsigned char)right_motor_speed;
}
/**
 * @brief      Initializes the setup by configuring all the required devices
 */
int init_setup(void)
{
	// Initialize motor pins
	motors_pin_config();
	// Initialize PWM pins as output
	pwm_pin_config();
	// Initialize Timer in Phase Correct PWM mode
	timer_pwm_init();
	return 1;
}
