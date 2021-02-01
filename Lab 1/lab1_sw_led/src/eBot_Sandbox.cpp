/*
 * eBot_Sandbox.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */


//---------------------------------- INCLUDES ----------------------------------

#include "eBot_Sandbox.h"


//---------------------------------- FUNCTIONS ----------------------------------


/**
 * @brief      Executes the logic to achieve the aim of Lab 1
 */
void toggle_leds_on_sw_press(void)
{
	while (1)
	{
		if ( interrupt_switch_pressed () )							// Check condition of switch press
		{
			turn_off_bar_graph_led (bar_graph_led_2_pin);			// Turn OFF 2nd Bar-graph LED
			turn_on_bar_graph_led (bar_graph_led_8_pin);   			// Turn ON 8th Bar-graph LED

			_delay_ms(50);											// Waiting for a while for the Interrupt Switch to settle

			/*
			Why did we include this delay?

			The reason is that mechanical switches like the Interrupt Switch have a limitation called switch bounce.
			You can read more about it here: http://www.labbookpages.co.uk/electronics/debounce.html , https://electrosome.com/switch-debouncing/
			The bar_graph_led_2_on and bar_graph_led_2_off functions execute in a few microseconds, but the switch itself needs time to settle after a press.
			Typically this time is in the order of a few milliseconds.
			Introducing a delay is the simplest way of mitigating for switch bounce and this process is called de-bouncing.
			*/
		}
		else
		{
			turn_on_bar_graph_led (bar_graph_led_2_pin); 			// Turn ON 2nd Bar-graph LED
			turn_off_bar_graph_led (bar_graph_led_8_pin);			// Turn OFF 8th Bar-graph LED
		}
	}
}

