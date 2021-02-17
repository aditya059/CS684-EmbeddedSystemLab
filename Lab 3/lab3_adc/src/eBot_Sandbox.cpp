/*
 * eBot_Sandbox.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */


//---------------------------------- INCLUDES -----------------------------------

#include "eBot_Sandbox.h"


//------------------------------ GLOBAL VARIABLES -------------------------------

// To store 8-bit data of left, center and right white line sensors
unsigned char left_wl_sensor_data, center_wl_sensor_data, right_wl_sensor_data;

// To store 8-bit data of 5th IR proximity sensors
unsigned char ir_prox_5_sensor_data;


//---------------------------------- FUNCTIONS ----------------------------------


/**
 * @brief      Executes the logic to achieve the aim of Lab 3
 */
void send_sensor_data(void)
{
	int return_code;

	while (1)
	{
		// get the ADC converted data of three white line sensors and
		// 5th IR Proximity sensor sensor from their appropriate channel numbers

		// print the data on the terminal


		_delay_ms(500);
	}
}

