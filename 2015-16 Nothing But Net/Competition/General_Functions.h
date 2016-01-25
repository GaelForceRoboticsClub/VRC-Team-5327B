//This header file contains useful functions that can be used for calculations and processes throughout the robot code

/*
Function that can be used to determine if a value is "close enough" to the desired value. Takes 3 parameters:
@current_value : The current value
@desired_value : The desired value
@tolerance : How much above or below the desired value we can be and still be satisfied
*/
bool closeEnough(int current_value, int desired_value, int tolerance)
{
	return (abs(current_value - desired_value) <= tolerance);
}
