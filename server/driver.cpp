#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "driver.h"

using namespace std;


bool driver::allowed_command()
{
	if (!logged_in || !accepted) {
		return false;
	}
	return true;
}

string driver::print()
{
	stringstream ss;
	string result;
	ss << username << " ";
	string print = vehicle->print();
	ss << print;
	if (VIP) {
		ss << "VIP" << endl;
	}
	else {
		ss << endl;
	}
	result = ss.str();
	return result;
}

string spaceship::print()
{
	stringstream ss;
	ss << spaceship_number << " " << spaceship_model << " " << production_year << " " << spaceship_color;
	string result = ss.str();
	return result;
}

string spaceship::print_spaceship()
{
	stringstream ss;
	ss << spaceship_model << " " << spaceship_color << endl;
	string result = ss.str();
	return result;
}

string driver::print_address()
{
	stringstream ss;
	ss << address << " ";
	string result = ss.str();
	return result;
}
