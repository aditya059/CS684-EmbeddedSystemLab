/*
 * eBot_Sandbox.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */


//---------------------------------- INCLUDES -----------------------------------

#include "eBot_Sandbox.h"
#include <stdlib.h>


//------------------------------ GLOBAL VARIABLES -------------------------------

// To store 8-bit data of left, center and right white line sensors
unsigned char left_wl_sensor_data, center_wl_sensor_data, right_wl_sensor_data;

// To store 8-bit data of 5th IR proximity sensors
unsigned char ir_prox_5_sensor_data;

// To store the eBot's current and Goal location
typedef struct
{
	int x, y;
}tuple;
tuple curr_loc = {4,0}, goal_loc = {4,5};

// To store the direction in which eBot is currently facing
char dir_flag = 'n';


//---------------------------------- FUNCTIONS ----------------------------------


/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
//
void forward_wls(unsigned char node)
{

	for (int i = 0; i < node; i++)
	{

	}

}

/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls();
*
*/
void left_turn_wls(void)
{

}


/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls();
*
*/
void right_turn_wls(void)
{

}

/**
 * @brief      Executes the logic to achieve the aim of Lab 4
 */
void traverse_line_to_goal(void)
{

}

