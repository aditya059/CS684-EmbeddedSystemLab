/*
 * eBot_Sandbox.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */


//---------------------------------- INCLUDES -----------------------------------

#include "eBot_Sandbox.h"


//------------------------------ GLOBAL VARIABLES -------------------------------

unsigned char speed = 0;


//---------------------------------- FUNCTIONS ----------------------------------


/**
 * @brief      Executes the logic to achieve the aim of Lab 2
 */
void traverse_s_shape(void)
{
	forward();								// Move the robot in forward direction

	while (1)
	{
		velocity(255 - speed , speed);		// Take turn using velocity difference (use speed variable in complement for two motors)
		speed++;							// Increase the value of speed by one
		_delay_ms(10);						// Provide delay of 10ms
	}
}

