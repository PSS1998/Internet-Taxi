#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "admin_system.h"

using namespace std;


void admin_system::get_vehicles()
{
	ifstream vehicles;
	vehicles.open("vehicles.cfg");
	stringstream sstr;
	sstr << vehicles.rdbuf();
	string vehicles_string;
	vehicles_string = sstr.str();

	char c;
	int line = 0;
	while (sstr.get(c))
		if (c == '\n')
			line++;

	sstr.clear();
	sstr.seekg(0, sstr.beg);

	for (int i = 0; i < line; i++) {
		string vehicle_name;
		sstr >> vehicle_name;
		list_vehicles.push_back(vehicle_name);
		sstr.seekg(1, sstr.cur);
	}
}

bool admin_system::allowed_command()
{
	if (!logged_in) {
		return false;
	}
	return true;
}