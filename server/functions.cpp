#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "functions.h"
#include "universe.h"
#include "exceptions.h"

using namespace std;


bool is_address(std::string address, universe* map)
{
	int count = 0;
	for (int i = 0; i < address.size(); i++) {
		if (address[i] == ',') {
			count++;
		}
	}
	if (count != 1) {
		return false;
	}

	string delimiter = ",";
	string source_galaxy = address.substr(0, address.find(delimiter));
	string source_planet = address.substr(address.find(delimiter) + 1, address.size());
	int index1 = map->find_galaxy(source_galaxy);
	int index2 = map->get_galaxy()[index1]->find_planet(source_planet);

	return true;
}

string get_command() {
	string input;
	getline(cin, input);
	return input;
}

string print_estimate_trip(int cost, int distance) {
	stringstream ss;
	string result = "";
	ss << cost << " " << distance << endl;
	result += ss.str();
	return result;
}

std::vector<int> date_analyse(std::string date)
{
	vector<int> date_time;
	string delimiter1 = "-";
	string day;
	day = date.substr(0, date.find(delimiter1));
	int day_int = atoi(day.c_str());
	date = date.substr(date.find(delimiter1) + 1, date.size());
	string delimiter2 = ":";
	string hour;
	hour = date.substr(0, date.find(delimiter2));
	int hour_int = atoi(hour.c_str());
	date = date.substr(date.find(delimiter2) + 1, date.size());
	string minute;
	minute = date.substr(0, date.find(delimiter2));
	int minute_int = atoi(minute.c_str());
	date = date.substr(date.find(delimiter2) + 1, date.size());
	string second;
	second = date.substr(0, date.find(delimiter2));
	int second_int = atoi(second.c_str());
	date = date.substr(date.find(delimiter2) + 1, date.size());
	date_time.push_back(day_int);
	date_time.push_back(hour_int);
	date_time.push_back(minute_int);
	date_time.push_back(second_int);
	return date_time;
}

bool is_date(std::string date)
{
	vector<int> date_time;
	date_time = date_analyse(date);
	if (date_time.size() != 4)
		return false;
	if (date_time[0] > 31 && date_time[0] < 1)
		return false;
	if (date_time[1] > 23 && date_time[1] < 0)
		return false;
	if (date_time[2] > 59 && date_time[2] < 0)
		return false;
	if (date_time[3] > 59 && date_time[3] < 0)
		return false;
	return true;
}

bool is_date_bigger(std::string date1, std::string date2)
{
	vector<int> date_time1;
	date_time1 = date_analyse(date1);
	vector<int> date_time2;
	date_time2 = date_analyse(date2);
	if (date_time1[0] > date_time2[0])
		return true;
	if (date_time1[0] < date_time2[0])
		return false;
	if (date_time1[1] > date_time2[1])
		return true;
	if (date_time1[1] < date_time2[1])
		return false;
	if (date_time1[2] > date_time2[2])
		return true;
	if (date_time1[2] < date_time2[2])
		return false;
	if (date_time1[3] > date_time2[3])
		return true;
	if (date_time1[3] < date_time2[3])
		return false;
	return false;
}

bool is_date_equal(std::string date1, std::string date2)
{
	vector<int> date_time1;
	date_time1 = date_analyse(date1);
	vector<int> date_time2;
	date_time2 = date_analyse(date2);
	if (date_time1 == date_time2)
		return true;
	return false;
}

int diff_time(std::string date1, std::string date2)
{
	if (is_date(date1) && is_date(date2)) {
		vector<int> date_time1;
		date_time1 = date_analyse(date1);
		vector<int> date_time2;
		date_time2 = date_analyse(date2);
		vector<int> date_time3;
		for (int i = 0; i < date_time1.size(); i++) {
			date_time3.push_back(date_time1[i] - date_time2[i]);
		}
		int diff_time;
		diff_time = (date_time3[0] * 3600 * 24) + (date_time3[1] * 3600) + (date_time3[2] * 60) + (date_time3[3] * 1);
		return diff_time;
	}
	else {
		throw not_a_date();
	}
}
