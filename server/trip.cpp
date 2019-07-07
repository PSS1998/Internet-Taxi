#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "trip.h"

using namespace std;


string order::print_status(bool accepted)
{	
	stringstream ss;
	string result = "";
	if (!accepted) {
		ss << "waiting" << endl;
		return "";
	}
	else {
		ss << "accepted" << " " << get_driver_name() << " ";

	}
	return get_driver_name();
}

string order::print()
{
	string destinations;
	for (int i = 0; i < destination.size(); i++) {
		destinations += destination[i];
	}
	stringstream ss;
	ss << user << " " << source << " " << destinations << " " << cost << " " << distance << endl;
	string result = ss.str();
	return result;
}
