/*
 * eBot_MCU_Predef.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */


#include "eBot_MCU_Predef.h"


//---------------------------------- FUNCTIONS ----------------------------------

/**
 * @brief      Makes **ONLY** 2nd, 6th and 8th Bar-graph LED pins as output and initially sets **ONLY** 2nd Bar-graph LED as high (ON)
 */
void bar_graph_led_pins_config(void)
{
	// << NOTE >> : Use Masking and Shift Operators here

	// Make **ONLY** 2nd, 6th and 8th Bar-graph LED pins as output
	bar_graph_led_ddr_reg	|= ( 1 << bar_graph_led_2_pin ) | ( 1 << bar_graph_led_6_pin ) | ( 1 << bar_graph_led_8_pin ) ;

	// Set **ONLY** 2nd Bar-graph LED as high (ON)
	bar_graph_led_port_reg	|= (1 << bar_graph_led_2_pin );
}


/**
 * @brief      Makes **ONLY** Interrupt Switch pin as input and pulls it up internally
 */
void interrupt_sw_pin_config(void)
{
	// << NOTE >> : Use Masking and Shift Operators here

	// Makes **ONLY** Interrupt Switch pin as input
	interrupt_sw_ddr_reg	&= ~(1 << interrupt_sw_pin);

	// Makes **ONLY** Interrupt Switch pin internally pull-up
	interrupt_sw_port_reg	|= (1 << interrupt_sw_pin);
}


/**
 * @brief      Checks if Interrupt Switch is pressed or not
 *
 * @return     boolean true if Interrupt Switch is pressed, else false.
 */
bool interrupt_switch_pressed(void)
{
	/*
	<< TODO >> :
		1. Write an if-else statement with a condition which checks whether the Interrupt Switch is pressed or not.
		2. If the Interrupt Switch is pressed return true, else return false
	*/
	if( interrupt_sw_pin_reg & (1 << interrupt_sw_pin) )
		return true;
	else
		return false;
}


/**
 * @brief      Sets **ONLY** a particular Bar-graph LED pin as high (ON)
 *
 * @param[in]  led_pin   Pin number of Bar-graph LED
 */
void turn_on_bar_graph_led(unsigned char led_pin)
{
	// << NOTE >> : Use Masking and Shift Operators here

	// Set **ONLY** a particular Bar-graph LED pin as high (ON)
	bar_graph_led_port_reg	|= ( 1 << led_pin );
}


/**
 * @brief      Sets **ONLY** a particular Bar-graph LED pin as low (OFF)
 *
 * @param[in]  led_pin   Pin number of Bar-graph LED
 */
void turn_off_bar_graph_led(unsigned char led_pin)
{
	// << NOTE >> : Use Masking and Shift Operators here

	// Set **ONLY** a particular Bar-graph LED pin as low (OFF)
	bar_graph_led_port_reg	&= ~( 1 << led_pin );
}


/**
 * @brief      Initializes the setup by configuring all the required devices
 */
int init_setup(void)
{
	// Initialize the 2nd, 6th and 8th Bar-graph LEDs
	bar_graph_led_pins_config();

	// Initialize the Interrupt Switch
	interrupt_sw_pin_config();

	// Turn ON 6th Bar-graph LED
	turn_on_bar_graph_led(bar_graph_led_6_pin);

	return 1;
}

