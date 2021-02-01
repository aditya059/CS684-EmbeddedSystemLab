//============================================================================
// Name        : lab1_sw_led.cpp
// Author      : TAs of CS 684 Spring 2020
// Description : Toggle status of two Bar-graph LEDs depending on whether
//				 the Interrupt Switch is pressed or released
//============================================================================


#include "eBot_Sandbox.h"


// Main Function
int main(int argc, char* argv[])
{
	int init_setup_success = 0;

	init_setup_success = init_setup();

	if (init_setup_success)
	{
		toggle_leds_on_sw_press();
	}
	else
	{
	}
}
