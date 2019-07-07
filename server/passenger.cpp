#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "passenger.h"

using namespace std;


bool passenger::allowed_command()
{
	if (!logged_in) {
		return false;
	}
	return true;
}

bool passenger::allowed_command_rate()
{
	if (!logged_in) {
		return false;
	}
	return true;
}

void passenger::cal_discount_code()
{
	int code;
	stringstream ss;
	for (int i = 0; i < username.size(); i++) {
		code = (int)username[i];
		ss << code;
		discount_code += ss.str();
	}
	discount_code_count = 5;
}

string passenger::get_discount_code()
{
	stringstream ss;
	ss << discount_code << " " << discount_code_count << endl;
	string result = ss.str();
	return result;
}

void passenger::get_discount()
{
	discount_code_count--;
	account_value += 10;
}

void passenger::pay_credit(int amount)
{
	account_value -= amount;
}

string passenger::print_credit()
{
	stringstream ss;
	ss << account_value << endl;
	string result = ss.str();
	return result;
}
