/*
 * eBot_Sandbox.cpp
 *
 * Created on: 11-Jan-2021
 * Author: TAs of CS 684 Spring 2020
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

char reverse = 0;
char turn = 0;

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

void readSensor()
{
	left_wl_sensor_data = convert_analog_channel_data(left_wl_sensor_channel);
	center_wl_sensor_data = convert_analog_channel_data(center_wl_sensor_channel);
	right_wl_sensor_data = convert_analog_channel_data(right_wl_sensor_channel);
	ir_prox_5_sensor_data = convert_analog_channel_data(ir_prox_5_sensor_channel);
	if((curr_loc.y == goal_loc.y - 1) && (reverse == 0) && (center_wl_sensor_data > 200 && (left_wl_sensor_data > 200 || right_wl_sensor_data > 200))) {
		left_wl_sensor_data = 255 - left_wl_sensor_data;
		center_wl_sensor_data = 255 - center_wl_sensor_data;
		right_wl_sensor_data = 255 - right_wl_sensor_data;
		turn = 1;
	}
	else if(turn == 1) {
		if(left_wl_sensor_data < 50 && center_wl_sensor_data < 50 && right_wl_sensor_data < 50)
			reverse = 1;
		if(left_wl_sensor_data > 200 && center_wl_sensor_data < 50 && right_wl_sensor_data < 50)
			reverse = 1;
		if(left_wl_sensor_data < 50 && center_wl_sensor_data > 200 && right_wl_sensor_data < 50)
			reverse = 1;
		if(left_wl_sensor_data < 50 && center_wl_sensor_data < 50 && right_wl_sensor_data > 200)
			reverse = 1;
	}
	_delay_ms(10);
}

void forward_wls(unsigned char node)
{
	unsigned char t = 0;
	unsigned char s = 1;
	for (int i = 0; i < node; i++)
	{
		while(1) {
			readSensor();
			forward();                    // WBW & BWB
			velocity(200,200);
			if(left_wl_sensor_data < 50 && right_wl_sensor_data > 200) {     // WWB & WBB
				right();
				velocity(100,100);
			}
			if(left_wl_sensor_data > 200 && right_wl_sensor_data < 50) {    // BWW & BBW
				left();
				velocity(100,100);
			}
			if(left_wl_sensor_data < 50 && center_wl_sensor_data < 50 && right_wl_sensor_data < 50){  // WWW
				if(t % 4 == 0){
					left();
					velocity(48,50);
					_delay_ms(s * 10);
				}
				else if(t % 4 == 1){
					right();
					velocity(50,48);
					_delay_ms(s * 10);
				}
				else if(t % 4 == 2){
					right();
					velocity(48, 50);
					_delay_ms(s * 10);
				}
				else {
					left();
					velocity(50,48);
					_delay_ms(s * 10);
					s *= 2;
				}
				t++;
			}
			else {
				t = 0;
				s = 1;
			}
			if(left_wl_sensor_data > 200 && center_wl_sensor_data > 200 && right_wl_sensor_data > 200) {  // BBB
				printf("Intersection Reached %d\n", i+1);
				_delay_ms(350);
				velocity(0,0);
				if(dir_flag == 'n') curr_loc.y++;
				else if(dir_flag == 's') curr_loc.y--;
				else if(dir_flag == 'w') curr_loc.x--;
				else curr_loc.x++;
				printf("Curr.y: %d\nGoal.y: %d\n", curr_loc.y, goal_loc.y);
				break;
			}
		}
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
	left();
	_delay_ms(450);
	velocity(30,30);
	while(1) {
		readSensor();
		if(left_wl_sensor_data < 50 && center_wl_sensor_data > 200 && right_wl_sensor_data < 50)
		{
			velocity(0,0);
			break;
		}
	}
	if(dir_flag == 'n') dir_flag = 'w';
	else if(dir_flag == 'w') dir_flag = 's';
	else if(dir_flag == 's') dir_flag = 'e';
	else dir_flag = 'n';
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
	right();
	_delay_ms(450);
	velocity(30,30);
	while(1) {
		readSensor();
		if(left_wl_sensor_data < 50 && center_wl_sensor_data > 200 && right_wl_sensor_data < 50)
		{
			velocity(0,0);
			break;
		}
	}
	if(dir_flag == 'n') dir_flag = 'e';
	else if(dir_flag == 'w') dir_flag = 'n';
	else if(dir_flag == 's') dir_flag = 'w';
	else dir_flag = 's';
}

/**
 * @brief      Executes the logic to achieve the aim of Lab 4
 */
void traverse_line_to_goal(void)
{
	unsigned char step = 0;
	forward_wls(1);
	curr_loc.y--;
	left_turn_wls();
	if(ir_prox_5_sensor_data == 200){
		forward_wls(1);
	}
	else{
		right_turn_wls();
		dir_flag = 'e';
		forward_wls(1);
	}
	while(curr_loc.y != goal_loc.y){
		if(ir_prox_5_sensor_data == 200){
			if(step == 1){
				forward_wls(1);
				step = 0;
			}
			else{
				if(dir_flag == 'w'){
					right_turn_wls();
				}
				else if(dir_flag == 'e'){
					left_turn_wls();
				}
				else if(dir_flag == 'n'){
					forward_wls(1);
				}
				else {
					right_turn_wls();
				}
			}
		}
		else{
			//printf("Curr.x: %d\nGoal.x: %d\n", curr_loc.x, goal_loc.x);
			if(curr_loc.x < goal_loc.x){
				if(dir_flag == 'w'){
					right_turn_wls();
					step = 1;
				}
				else if(dir_flag == 'e'){
					left_turn_wls();
					step = 1;
				}
				else if(dir_flag == 'n'){
					left_turn_wls();
					step = 1;
				}
				else {
					right_turn_wls();
					step = 1;
				}
			}
			else {
				if(dir_flag == 'w'){
					right_turn_wls();
					step = 1;
				}
				else if(dir_flag == 'e'){
					left_turn_wls();
					step = 1;
				}
				else if(dir_flag == 'n'){
					left_turn_wls();
					step = 1;
				}
				else{
					left_turn_wls();
					step = 1;
				}
			}
		}
	}
	while(curr_loc.x != goal_loc.x){
		if(curr_loc.x < goal_loc.x){
			if(dir_flag == 'w'){
				right_turn_wls();
				dir_flag = 'e';
			}
			else if(dir_flag == 'e'){
				forward_wls(1);
			}
			else if(dir_flag == 'n'){
				right_turn_wls();
			}
			else {
				left_turn_wls();
			}
		}
		else {
			if(dir_flag == 'w'){
				forward_wls(1);
			}
			else if(dir_flag == 'e'){
				left_turn_wls();
				dir_flag = 'w';
			}
			else if(dir_flag == 'n'){
				left_turn_wls();
			}
			else{
				right_turn_wls();
			}
		}
	}

//	forward_wls(1);
//	left_turn_wls();
//	forward_wls(1);
//	right_turn_wls();
//	forward_wls(4);
//	forward_wls(1);
//	right_turn_wls();
//	forward_wls(1);
//	left_turn_wls();
//	forward_wls(1);
}

