//==================================================================================
// Name        : lab4_line_follower_robot.cpp
// Author      : TAs of CS 684 Spring 2020
// Description : To make robot reach the GOAL while traversing the line from START
//==================================================================================


#include "eBot_Sandbox.h"


// Main Function
int main(int argc, char* argv[])
{
	int init_setup_success = 0;

	init_setup_success = init_setup();

	if (init_setup_success)
	{
		#ifdef NON_MATLAB_PARSING
			std::thread t_1(thread_calls);
			_delay_ms(4000);
		#endif

		traverse_line_to_goal();

		#ifdef NON_MATLAB_PARSING
			clean_up();
			t_1.detach();
		#endif
	}
	else
	{
		printf("\n\tInitialization did not succeed! Try again.");
	}
}
