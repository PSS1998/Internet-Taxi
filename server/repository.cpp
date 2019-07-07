#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "exceptions.h"
#include "universe.h"
#include "admin_system.h"
#include "trip.h"
#include "passenger.h"
#include "driver.h"
#include "repository.h"
#include "functions.h"

using namespace std;






string repository::commands::get_command(string input)
{	
	string result = "";
	parameters.clear();
	stringstream ss;
	ss.str(input);
	ss >> username;
	ss.seekg(1, ss.cur);
	ss >> command;
	ss.seekg(1, ss.cur);
	string parameter;
	int c;
	do {
		ss >> parameter;
		ss.seekg(1, ss.cur);
		parameters.push_back(parameter);
		c = ss.peek();
	} while (c != EOF);
	if (parameters.size() == 1)
		if (parameters[0] == "")
			parameters.clear();
	if (cin.eof()) {
		return result;
	}	
	result = check_command();
	return result;
}

string repository::commands::check_command()
{
	string result = "";
	try {
		if (command == "register_passenger") {
			result += register_passenger();
		}
		if (command == "register_driver") {
			result += register_driver();
		}
		if (command == "accept_registration") {
			result += accept_registration();
		}
		if (command == "reject_registration") {
			result += reject_registration();
		}
		if (command == "show_registration_requests") {
			result += show_registration_requests();
		}
		if (command == "get_discount_code") {
			result += get_discount_code();
		}
		if (command == "login") {
			result += login();
		}
		if (command == "logout") {
			result += logout();
		}
		if (command == "set_status") {
			result += set_status();
		}
		if (command == "estimate_trip") {
			result += estimate_trip();
		}
		if (command == "request_trip") {
			result += request_trip();
		}
		if (command == "cancel_trip_request") {
			result += cancel_trip_request();
		}
		if (command == "show_trip_requests") {
			result += show_trip_requests();
		}
		if (command == "accept_trip_request") {
			result += accept_trip_request();
		}
		if (command == "trip_status") {
			result += trip_status();
		}
		if (command == "arrived") {
			result += arrived();
		}
		if (command == "end_trip") {
			result += end_trip();
		}
		if (command == "rate_driver") {
			result += rate_driver();
		}
		if (command == "charge_account") {
			result += charge_account();
		}
		if (command == "get_credit") {
			result += get_credit();
		}
		if (command == "driver_report") {
			if (username == "admin") {
				driver_report();
			}
			else {
				cout << "user doesnt have access" << endl;
				return result;
			}
		}
		if (command == "passenger_report") {
			if (username == "admin") {
				passenger_report();
			}
			else {
				cout << "user doesnt have access" << endl;
				return result;
			}
		}
		if (command == "system_report") {
			if (username == "admin") {
				system_report();
			}
			else {
				cout << "user doesnt have access" << endl;
				return result;
			}
		}
		if (command == "set_time") {
			if (username == "admin") {
				set_time();
			}
			else {
				cout << "user doesnt have access" << endl;
				return result;
			}
		}
		if (command == "system_time"){
			result += system_time();
		}
		if (command == "must_rate"){
			result += must_rate();
		}
	}
	catch (wrong_parameter_exception exception) {
		string r = "wrong parameters";
		r += "\n";
		result += r;
	}
	catch (not_allowed_command exception) {
		string r = "command is not allowed";
		r += "\n";
		result += r;
	}
	catch (not_a_username exception) {
		string r = "not a username";
		r += "\n";
		result += r;
	}
}

string repository::commands::must_rate()
{
	string result = "";
	result += command_owner->passengers[command_owner->find_passenger(username)]->must_rate();
	return result;
}

string repository::commands::system_time()
{
	string result = "";
	result += command_owner->adminstrator->get_date();
	return result;
}

string repository::commands::set_time()
{
	if (parameters.size() == 1) {
		try {
			command_owner->set_time(username, parameters[0]);
		}
		catch (not_a_date exception) {
			cout << "not a date" << endl;
		}
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::system_report()
{
	if (parameters.size() == 2) {
		command_owner->system_report(username, parameters[0], parameters[1]);
	}
	else if (parameters.size() == 0) {
		command_owner->system_report(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::passenger_report()
{
	if (parameters.size() == 1) {
		command_owner->passenger_report(username, parameters[0]);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::driver_report()
{
	if (parameters.size() == 3) {
		command_owner->driver_report(username, parameters[0], parameters[1], parameters[2]);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::get_credit()
{
	string result = "";
	if (parameters.size() == 0) {
		result += command_owner->get_credit(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

string repository::commands::charge_account()
{
	if (parameters.size() == 1) {
		command_owner->charge_account(username, parameters[0]);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::rate_driver()
{
	if (parameters.size() == 1) {
		command_owner->rate_driver(username, parameters[0]);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::end_trip()
{
	if (parameters.size() == 0) {
		command_owner->end_trip(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::arrived()
{
	if (parameters.size() == 0) {
		command_owner->arrived(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::trip_status()
{
	string result = "";
	if (parameters.size() == 0) {
		result += command_owner->trip_status(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	if(result == ""){
		result = "waiting";
		result += "\n";
	}
	else{
		stringstream ss;
		ss << "accepted" << " " << result << " ";
		result = ss.str();
	}
	return result;
}

string repository::commands::accept_trip_request()
{
	if (parameters.size() == 1) {
		command_owner->accept_trip_request(username, parameters[0]);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::show_trip_requests()
{
	string result = "";
	if (parameters.size() == 0) {
		result += command_owner->show_trip_requests(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

string repository::commands::cancel_trip_request()
{
	if (parameters.size() == 0) {
		command_owner->cancel_trip_request(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::request_trip() {
	string result = "";
	if (parameters[0] == "VIP") {
		string destinations;
		for (int i = 2; i < parameters.size(); i++) {
			destinations += parameters[i] + " ";
		}
		result += command_owner->request_trip(username, 1, parameters[1], destinations);
	}
	else {
		string destinations;
		for (int i = 1; i < parameters.size(); i++) {
			destinations += parameters[i] + " ";
		}
		result += command_owner->request_trip(username, 0, parameters[0], destinations);
	}
	
	return result;
}

string repository::commands::estimate_trip()
{
	vector<int> results;
	if(parameters.size() == 1){
		return "";
	}
	if(parameters[0] == "" || parameters[1] == ""){
		return "";
	}
	if (parameters[0] == "VIP") {
		string destinations;
		for (int i = 2; i < parameters.size(); i++) {
			destinations += parameters[i] + " ";
		}
		results = command_owner->estimate_trip(username, 1, parameters[0], destinations);
	}
	else {
		string destinations;
		for (int i = 1; i < parameters.size(); i++) {
			destinations += parameters[i] + " ";
		}
		results = command_owner->estimate_trip(username, 0, parameters[0], destinations);
	}
	if(results.size() == 0){
		string not_result = "";
		return not_result;
	}
	stringstream ss;
	ss << results[0] << " ";
	stringstream ss2;
	ss2 << results[1];
	string r1 = ss.str();
	string r2 = ss2.str();
	string result;
	result = r1 + r2;
	return result;	
}

string repository::commands::set_status()
{
	string result = "";
	if (parameters.size() == 2) {
		try {
			command_owner->set_status(username, parameters[0], parameters[1]);
		}
		catch (not_an_address exception) {
			result += "not an address";
			result += "\n";
		}
		catch (not_a_username exception) {
			result += "not a username";
			result += "\n";
		}
	}
	else if (parameters.size() == 1) {
		try {
			command_owner->set_status(username, parameters[0]);
		}
		catch (not_an_address exception) {
			result += "not an address";
			result += "\n";
		}
		catch (not_a_username exception) {
			result += "not a username";
			result += "\n";
		}
	}
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

string repository::commands::logout()
{
	if (parameters.size() == 0) {
		command_owner->logout(username);
	}
	else {
		throw wrong_parameter_exception();
	}
	string result = "";
	return result;
}

string repository::commands::login()
{
	string result = "1";
	if (parameters.size() == 1) {
		try {
			command_owner->login(username, parameters[0]);
		}
		catch (wrong_password exception) {
			cout << "wrong password" << endl;
			result = "0";
		}
		catch (not_a_username exception) {
			cout << "not a username" << endl;
			result = "0";
		}
	}
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

string repository::commands::get_discount_code()
{
	string result = "";
	if (parameters.size() == 0) {
		int index = command_owner->find_passenger(username);
		result += command_owner->passengers[index]->get_discount_code();
	}
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

string repository::commands::show_registration_requests()
{
	string result = "";
	if (parameters.size() == 0) {
		command_owner->not_accepted_drivers();
	}
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

string repository::commands::accept_registration()
{
	string result = "";
	int index = command_owner->find_driver(parameters[0]);
	if (index != -1) {
		if (command_owner->adminstrator->allowed_command()) {
			if (parameters.size() == 1) {
				int index = command_owner->find_driver(parameters[0]);
				command_owner->drivers[index]->accepted = true;
			}
			else {
				throw wrong_parameter_exception();
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
	
	return result;
}

string repository::commands::reject_registration()
{
	int index = command_owner->find_driver(parameters[0]);
	if (index != -1) {
		if (command_owner->adminstrator->allowed_command()) {
			if (parameters.size() == 1) {
				int index = command_owner->find_driver(parameters[0]);
				if (!command_owner->drivers[index]->accepted) {
					command_owner->drivers.erase(command_owner->drivers.begin() + index);
				}
			}
			else {
				throw wrong_parameter_exception();
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
	string result = "";
	return result;
}

string repository::commands::register_passenger()
{
	string result = "";
	for (int i = 0; i < command_owner->passengers.size(); i++) {
		if (command_owner->passengers[i]->get_name() == username) {
			result += "username already exists";
			result += "\n";
			return result;
		}
	}
	for (int i = 0; i < command_owner->passengers.size(); i++) {
		if (command_owner->passengers[i]->get_phone() == parameters[1]) {
			result += "phone already exists";
			result += "\n";
			return result;
		}
	}

	if (parameters.size() <= 3) {
		try {
			if (parameters.size() == 3)
				command_owner->get_discount(username, parameters[2]);
			command_owner->add_passenger(username, parameters[0], parameters[1]);
		}
		catch (not_a_phone_number exception) {
			result += "entered phone number is not a phone number";
			result += "\n";
		}
	}
	else {
		throw wrong_parameter_exception();
	}
	
	return result;
}

void repository::add_passenger(std::string username, std::string password, std::string phone)
{
	for (int i = 0; i < phone.size(); i++) {
		if (phone[i] > '9' || phone[i] < '0') {
			throw not_a_phone_number();
		}
	}
	passengers.push_back(new passenger(username, password, phone, adminstrator->get_date()));
}

string repository::commands::register_driver() {
	string result = "";
	for (int i = 0; i < command_owner->drivers.size(); i++) {
		if (command_owner->drivers[i]->get_name() == username) {
			result += "username already exists";
			result += "\n";
			return result;
		}
	}
	for (int i = 0; i < command_owner->drivers.size(); i++) {
		if (command_owner->drivers[i]->get_spaceship()->get_spaceship_number() == parameters[1]) {
			result += "spaceship number already exists";
			result += "\n";
			return result;
		}
	}
	bool vehicle_exists = 0;
	for (int i = 0; i < command_owner->adminstrator->get_list_vehicles().size(); i++) {
		if (command_owner->adminstrator->get_list_vehicles()[i] == parameters[2]) {
			vehicle_exists = true;
		}
	}
	if (!vehicle_exists) {
		result += "spaceship model doesnt exists";
		result += "\n";
		return result;
	}

	if (parameters.size() == 5)
		command_owner->add_driver(username, parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], 0);
	else if (parameters.size() == 6)
		command_owner->add_driver(username, parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], 1);
	else {
		throw wrong_parameter_exception();
	}
	return result;
}

void repository::add_driver(std::string username, std::string password, std::string spaceship_number, std::string spaceship_model, std::string production_year, std::string spaceship_color, bool VIP)
{
	drivers.push_back(new driver(username, password, spaceship_number, spaceship_model, production_year, spaceship_color, VIP, adminstrator->get_date()));
}

int repository::find_driver(std::string username)
{
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i]->get_name() == username) {
			return i;
		}
	}
	return -1;
}

string repository::not_accepted_drivers()
{
	string result = "";
	for (int i = 0; i < drivers.size(); i++) {
		if (!drivers[i]->accepted) {
			result = drivers[i]->print();
		}
	}
	return result;
}

int repository::find_passenger(std::string username)
{
	for (int i = 0; i < passengers.size(); i++) {
		if (passengers[i]->get_name() == username) {
			return i;
		}
	}
	return -1;
}

void repository::get_discount(string username, string discount_code)
{
	string discount_user;
	for (int i = 0; i < discount_code.size(); i++) {
		discount_user.push_back((char)discount_code[i]);
	}
	int index = find_passenger(discount_user);
	if (index != -1) {
		passengers[index]->get_discount();
		index = find_passenger(username);
		passengers[index]->get_discount();
	}
}

void repository::login(string username, string password)
{
	if (username == "admin") {
		if (password == "s3cret") {
			adminstrator->login();
		}
		else {
			throw wrong_password();
		}
	}
	int index1 = find_driver(username);
	int index2 = find_passenger(username);
	if (index1 != -1) {
		if (drivers[index1]->accepted) {
			if (drivers[index1]->get_password() == password) {
				drivers[index1]->login();
			}
			else {
				throw wrong_password();
			}
		}
		else {
			cout << "command not allowed" << endl;
			return;
		}
	}
	if (index2 != -1) {
		if (passengers[index2]->get_password() == password) {
			passengers[index2]->login();
		}
		else {
			throw wrong_password();
		}
	}
	if ((index2 == -1) && (index1 == -1) && username != "admin") {
		throw not_a_username();
	}
}

void repository::logout(std::string username)
{
	int index1 = find_driver(username);
	int index2 = find_passenger(username);
	if (index1 != -1) {
		if (drivers[index1]->allowed_command())
			drivers[index1]->logout();
		else
			throw not_allowed_command();
	}
	if (index2 != -1) {
		if (passengers[index2]->allowed_command())
			passengers[index2]->logout();
		else
			throw not_allowed_command();
	}
	if (username == "admin") {
		if (adminstrator->allowed_command()) {
			adminstrator->logout();
		}
		else {
			throw not_allowed_command();
		}
	}
	if ((index2 == -1) && (index1 == -1)) {
		throw not_a_username();
	}
}

void repository::set_status(std::string username, std::string status)
{
	if (status == "unavailable") {
		int index = find_driver(username);
		if (index != -1) {
			if (drivers[index]->allowed_command())
				drivers[index]->set_status(0, "");
			else
				throw not_allowed_command();
		}
		else {
			throw not_a_username();
		}
	}
	else if (status == "available") {
		int index = find_driver(username);
		if (index != -1) {
			if (drivers[index]->allowed_command())
				drivers[index]->set_status(1, "");
			else
				throw not_allowed_command();
		}
		else {
			throw not_a_username();
		}
	}
	else {
		cout << "not a status" << endl;
	}
}

void repository::set_status(std::string username, std::string status, std::string address)
{
	if (status == "available") {
		int index = find_driver(username);
		if (index != -1) {
			if (drivers[index]->allowed_command()) {
				if (is_address(address, map)) {
					drivers[index]->set_status(1, address);
				}
				else {
					throw not_an_address();
				}
			}
			else {
				throw not_allowed_command();
			}
		}
		else {
			throw not_a_username();
		}
	}
	else {
		cout << "not a status" << endl;
	}
}

vector<int> repository::estimate_trip(std::string username, bool VIP, std::string source, std::string destinations)
{
	vector<string> destination;
	string delimiter = " ";
	while (destinations != "") {
		destination.push_back(destinations.substr(0, destinations.find(delimiter)));
		destinations = destinations.substr(destinations.find(delimiter) + 1, destinations.size());
	}
	int total_destination = 0;
	try {
		total_destination = map->get_distance(source, destination[0]);
		for (int i = 0; i < destination.size() - 1; i++) {
			total_destination += map->get_distance(destination[i], destination[i + 1]);
		}
	}
	catch (not_an_address exception) {
		cout << "not an address" << endl;
		vector<int> a;
		return a;
	}
	int total_charge = 0;
	total_charge = total_destination * (VIP + 1);
	if (is_frequent_traveler(username))
		passengers[find_passenger(username)]->set_frequent_traveler(1);
	if (is_not_frequent_traveler(username))
		passengers[find_passenger(username)]->set_frequent_traveler(0);
	if (passengers[find_passenger(username)]->is_frequent_traveler()) {
		total_charge = total_charge / 2;
	}
	print_estimate_trip(total_charge, total_destination);
	vector<int> results;
	results.push_back(total_charge);
	results.push_back(total_destination);
	return results;
}

std::vector<int> repository::find_drivers(bool VIP)
{
	vector<int> index;
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i]->is_VIP() == VIP) {
			if (drivers[i]->get_status() == "available")
				index.push_back(i);
		}
	}
	return index;
}

struct driver_score {
	int index;
	float score;
};
bool custom_compare(const driver_score &a, const driver_score &b)
{
	return a.score < b.score;
}

void repository::driver_algorithm(bool VIP, std::string source)
{
	vector<int> drivers_distance;
	vector<int> drivers_ratings;
	vector<driver_score> driver_list;
	vector<float> drivers_score;
	vector<float> drivers_score_backup;
	vector<int> index;
	index = find_drivers(VIP);
	driver_list.resize(index.size());
	for (int i = 0; i < index.size(); i++) {
		driver_list[i].index = index[i];
	}
	try {
		for (int i = 0; i < index.size(); i++) {
			drivers_distance.push_back(map->get_distance(source, drivers[index[i]]->get_address()));
		}
	}
	catch (not_an_address exception) {
		cout << "not an address" << endl;
		return;
	}
	for (int i = 0; i < index.size(); i++) {
		drivers_ratings.push_back(drivers[index[i]]->get_rating());
	}
	for (int i = 0; i < index.size(); i++) {
		drivers_score.push_back(((float)drivers_distance[i] / (float)drivers_ratings[i]));
	}
	for (int i = 0; i < drivers_score.size(); i++) {
		driver_list[i].score = drivers_score[i];
	}
	sort(driver_list.begin(), driver_list.end(), custom_compare);
	vector<int> selected_drivers;
	int size = driver_list.size();
	for (int i = 0; i < min(4, size); i++) {
		selected_drivers.push_back(driver_list[i].index);
	}
	/*for (int i = 0; i < min(4, size); i++) {
	float score = drivers_score[i];
	for (int j = 0; j < drivers_score_backup.size(); j++) {
	if (drivers_score_backup[j] == score) {
	selected_drivers.push_back(index[j]);
	break;
	}
	}
	}*/
	size = selected_drivers.size();
	for (int i = 0; i < min(4, size); i++) {
		drivers[selected_drivers[i]]->add_trip(orders[orders.size() - 1]);
	}
}

string repository::request_trip(std::string username, bool VIP, std::string source, std::string destinations)
{
	string result = "";
	vector<int> results;
	int index = find_passenger(username);
	if (index != -1) {
		if (passengers[index]->allowed_command() && passengers[index]->is_account_enough() && !passengers[index]->get_rate()) {
			string destinations_backup = destinations;
			vector<string> destination;
			string delimiter = " ";
			while (destinations != "") {
				destination.push_back(destinations.substr(0, destinations.find(delimiter)));
				destinations = destinations.substr(destinations.find(delimiter) + 1, destinations.size());
			}
			results = estimate_trip(username, VIP, source, destinations_backup);
			if (results.size() == 0)
				return result;
			orders.push_back(new order(username, source, destination, results[0], results[1], VIP, adminstrator->get_date()));
			driver_algorithm(VIP, source);
		}
		else {
			if (!passengers[index]->is_account_enough()) {
				cout << "not enough money in account" << endl;
			}
			else {
				throw not_allowed_command();
			}
		}
	}
	else {
		throw not_a_username();
	}
	stringstream ss;
	ss << results[0] << " ";
	stringstream ss2;
	ss2 << results[1];
	string r1 = ss.str();
	string r2 = ss2.str();
	result = r1 + r2;
	return result;	
}

vector<order*>::iterator repository::find_order(std::string username, bool accepted)
{
	vector<order*>::iterator it;
	for (it = orders.begin(); it < orders.end(); it++) {
		if ((*it)->get_name() == username) {
			if ((*it)->is_accepted() == accepted) {
				return it;
			}
		}
	}
	return orders.begin() - 1;
}

void repository::cancel_trip_request(std::string username)
{
	int index = find_passenger(username);
	if (index != -1) {
		if (passengers[index]->allowed_command()) {
			vector<order*>::iterator it = find_order(username, 0);
			if (it >= orders.begin()) {
				(*it)->trip_ended();
				orders.erase(it);
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
}



vector<int> repository::find_trips(bool VIP, bool accepted)
{
	vector<int> index;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->is_accepted() == accepted) {
			if (orders[i]->is_VIP() == VIP) {
				index.push_back(i);
			}
		}
	}
	return index;
}

string repository::show_trip_requests(std::string username)
{
	int index = find_driver(username);
	string result = "";
	if (index != -1) {
		if (drivers[index]->allowed_command()) {
			for (int i = 0; i < drivers[index]->get_list_trips().size(); i++) {
				if (!drivers[index]->get_list_trips()[i]->is_ended())
					result += drivers[index]->get_list_trips()[i]->print();
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
	return result;
}

void repository::accept_trip_request(std::string username, std::string passenger_username)
{
	bool flag_passenger_exists=0;
	int index = find_driver(username);
	if (index != -1) {
		if (drivers[index]->allowed_command()) {
			for (int i = 0; i < drivers[index]->get_list_trips().size(); i++) {
				if (drivers[index]->get_list_trips()[i]->get_name() == passenger_username) {
					if (drivers[index]->get_list_trips()[i]->is_accepted() == 0) {
						drivers[index]->get_list_trips()[i]->accept_trip(username);
						drivers[index]->in_trip();
						flag_passenger_exists = 1;
					}
				}
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
	if(!flag_passenger_exists){
		throw not_a_username();
	}
}

int repository::find_trips(std::string username, bool end_trip)
{
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->get_name() == username) {
			if (orders[i]->is_ended() == end_trip) {
				return i;
			}
		}
	}
}

string repository::trip_status(std::string username)
{
	string result = "";
	int index = find_passenger(username);
	if (index != -1) {
		if (passengers[index]->allowed_command()) {
			int index = find_trips(username, 0);
			string driver_name = orders[index]->print_status(orders[index]->is_accepted());
			if (driver_name != "") {
				int driver_index = find_driver(driver_name);
				result += drivers[driver_index]->print_address();
				result += drivers[driver_index]->get_spaceship()->print_spaceship();
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
	return result;
}

int repository::find_trip_driver(std::string username)
{
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->get_driver_name() == username) {
			if (orders[i]->is_ended() == 0) {
				return i;
			}
		}
	}
	return -1;
}

std::vector<int> repository::find_trips_driver(std::string username)
{
	vector<int> index;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->get_driver_name() == username) {
			if (orders[i]->is_ended() == 1) {
				if (orders[i]->is_arrived() == 1)
					index.push_back(i);
			}
		}
	}
	return index;
}

void repository::arrived(std::string username)
{
	int index = find_driver(username);
	if (index != -1) {
		if (drivers[index]->allowed_command()) {
			int index = find_trip_driver(username);
			orders[index]->trip_arrived();
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
}

void repository::end_trip(std::string username)
{
	int index = find_driver(username);
	if (index != -1) {
		if (drivers[index]->allowed_command()) {
			int index = find_trip_driver(username);
			orders[index]->trip_ended();
			orders[index]->set_end_date(adminstrator->get_date());
			set_status(username, "available", orders[index]->get_last_destination());
			int index2 = find_passenger(orders[index]->get_name());
			int amount = orders[index]->get_cost();
			passengers[index2]->pay_credit(amount);
			adminstrator->charge_account(amount);
			passengers[index2]->rate_trip(1);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
}

int repository::find_order_rate(std::string username)
{
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->get_name() == username) {
			if (orders[i]->is_rated() == 0) {
				return i;
			}
		}
	}
	return -1;
}


void repository::rate_driver(std::string username, std::string rate)
{
	int index = find_passenger(username);
	if (index != -1) {
		if (passengers[index]->allowed_command_rate()) {
			int index = find_order_rate(username);
			orders[index]->rate_trip();
			int index2 = find_passenger(username);
			passengers[index2]->rate_trip(0);
			int rating = atoi(rate.c_str());
			drivers[find_driver(orders[index]->get_driver_name())]->rate_trip(rating);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
}

void repository::charge_account(std::string username, std::string amount)
{
	int index = find_passenger(username);
	if (index != -1) {
		if (passengers[index]->allowed_command()) {
			int index = find_passenger(username);
			int amount_int = atoi(amount.c_str());
			passengers[index]->charge_account(amount_int);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		throw not_a_username();
	}
}

string repository::get_credit(std::string username)
{
	string result = "";
	int index = find_passenger(username);
	result += passengers[index]->print_credit();
	return result;
}

std::vector<int> repository::find_trips_driver(std::string username, std::string date1, std::string date2)
{
	vector<int> index;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->get_driver_name() == username) {
			if (orders[i]->is_ended() == 1) {
				if (orders[i]->is_arrived() == 1) {
					string start_date = orders[i]->get_start_date();
					string end_date = orders[i]->get_end_date();
					if (is_date_bigger(start_date, date1) || is_date_equal(start_date, date1)) {
						if (is_date_bigger(date2, end_date) || is_date_equal(date2, end_date)) {
							index.push_back(i);
						}
					}
				}
			}
		}
	}
	return index;
}

void repository::print_driver_report(int trips_count, float total_income, int total_rate)
{
	cout << trips_count << " " << total_income << " " << total_rate << endl;
}

void repository::driver_report(std::string username, std::string driver_username, std::string start_date, std::string end_date)
{
	if (username == "admin") {
		if (adminstrator->allowed_command()) {
			vector<int> index;
			index = find_trips_driver(driver_username, start_date, end_date);
			int trips_count = index.size();
			int driver_index = find_driver(driver_username);
			int total_rate = drivers[driver_index]->get_rating();
			float total_income = 0;
			for (int i = 0; i < index.size(); i++) {
				total_income += (float)orders[index[i]]->get_cost() * 0.8;
			}
			print_driver_report(trips_count, total_income, total_rate);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		cout << "user doesnt have access" << endl;
	}
}

void repository::print_credit(int credit)
{
	cout << credit << endl;
}

void repository::passenger_report(std::string username, std::string passenger_username)
{
	if (username == "admin") {
		if (adminstrator->allowed_command()) {
			int index = find_passenger(passenger_username);
			int credit = passengers[index]->get_credit();
			print_credit(credit);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		cout << "user doesnt have access" << endl;
	}
}

std::vector<int> repository::find_trips_date(std::string date1, std::string date2)
{
	vector<int> index;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->is_ended() == 1) {
			if (orders[i]->is_arrived() == 1) {
				string start_date = orders[i]->get_start_date();
				string end_date = orders[i]->get_end_date();
				if (is_date_bigger(start_date, date1) || is_date_equal(start_date, date1)) {
					if (is_date_bigger(date2, end_date) || is_date_equal(date2, end_date)) {
						index.push_back(i);
					}
				}
			}
		}
	}
	return index;
}

vector<int> repository::trips_ended()
{
	vector<int> index;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->is_ended() == 1) {
			if (orders[i]->is_arrived() == 1)
				index.push_back(i);
		}
	}
	return index;
}

std::vector<int> repository::drivers_accepted()
{
	vector<int> index;
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i]->accepted == 1) {
			index.push_back(i);
		}
	}
	return index;
}

void repository::print_system_report(float system_credit, int trips_count, int drivers_count, int passengers_count)
{
	cout << system_credit << " " << trips_count << " " << drivers_count << " " << passengers_count << endl;
}

std::vector<int> repository::drivers_accepted(std::string date1, std::string date2)
{
	vector<int> index;
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i]->accepted == 1) {
			string date = drivers[i]->get_date();
			if (is_date_bigger(date, date1) || is_date_equal(date, date1)) {
				if (is_date_bigger(date2, date) || is_date_equal(date2, date)) {
					index.push_back(i);
				}
			}
		}
	}
	return index;
}

std::vector<int> repository::passengers_date(std::string date1, std::string date2)
{
	vector<int> index;
	for (int i = 0; i < passengers.size(); i++) {
		string date = passengers[i]->get_date();
		if (is_date_bigger(date, date1) || is_date_equal(date, date1)) {
			if (is_date_bigger(date2, date) || is_date_equal(date2, date)) {
				index.push_back(i);
			}
		}
	}
	return index;
}

void repository::system_report(std::string username, std::string date1, std::string date2)
{
	if (username == "admin") {
		if (adminstrator->allowed_command()) {
			vector<int> index_orders;
			index_orders = find_trips_date(date1, date2);
			int system_credit = 0;
			int trips_count = 0;
			int drivers_count = 0;
			int passengers_count = 0;
			trips_count = index_orders.size();
			system_credit = adminstrator->get_credit();
			vector<int> index_drivers;
			index_drivers = drivers_accepted(date1, date2);
			drivers_count = index_drivers.size();
			vector<int> index_passengers;
			index_passengers = passengers_date(date1, date2);
			passengers_count = index_passengers.size();
			print_system_report(system_credit, trips_count, drivers_count, passengers_count);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		cout << "user doesnt have access" << endl;
	}
}

void repository::system_report(std::string username)
{
	if (username == "admin") {
		if (adminstrator->allowed_command()) {
			int system_credit = 0;
			int trips_count = 0;
			int drivers_count = 0;
			int passengers_count = 0;
			system_credit = adminstrator->get_credit();
			vector<int> index_orders;
			index_orders = trips_ended();
			trips_count = index_orders.size();
			vector<int> index_drivers;
			index_drivers = drivers_accepted();
			drivers_count = index_drivers.size();
			passengers_count = passengers.size();
			print_system_report(system_credit, trips_count, drivers_count, passengers_count);
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		cout << "user doesnt have access" << endl;
	}
}

void repository::set_time(std::string username, std::string date)
{
	if (username == "admin") {
		if (adminstrator->allowed_command()) {
			if (!is_date(date)) {
				throw not_a_date();
			}
			else {
				if (is_date_bigger(date, adminstrator->get_date())) {
					pay_wages(adminstrator->get_date(), date);
					adminstrator->set_date(date);
					check_frequent_traveler();
					check_not_frequent_traveler();
				}
				else {
					cout << "date not acceptable" << endl;
				}
			}
		}
		else {
			throw not_allowed_command();
		}
	}
	else {
		cout << "user doesnt have access" << endl;
	}
}

void repository::pay_wages(std::string date1, std::string date2)
{
	vector<int> date_time1;
	vector<int> date_time2;
	date_time1 = date_analyse(date1);
	date_time2 = date_analyse(date2);
	if (date_time1[0] == date_time2[0])
		return;
	for (int i = 0; i < orders.size(); i++) {
		if (!orders[i]->is_driver_paid()) {
			int index = find_driver(orders[i]->get_driver_name());
			float amount = (float)orders[i]->get_cost() * 0.2;
			adminstrator->pay_wage(amount);
			drivers[index]->get_paid(amount);
			orders[i]->pay();
		}
	}
}

std::vector<int> repository::find_trips_passenger(std::string username)
{
	vector<int> index;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i]->get_name() == username) {
			if (orders[i]->is_ended() == 1)
				if (orders[i]->is_arrived() == 1)
					index.push_back(i);
		}
	}
	return index;
}

void repository::check_frequent_traveler()
{
	for (int i = 0; i < passengers.size(); i++) {
		if (is_frequent_traveler(passengers[i]->get_name())) {
			passengers[i]->set_frequent_traveler(1);
		}
	}
}

void repository::check_not_frequent_traveler()
{
	for (int i = 0; i < passengers.size(); i++) {
		if (is_not_frequent_traveler(passengers[i]->get_name())) {
			passengers[i]->set_frequent_traveler(0);
		}
	}
}

bool repository::is_frequent_traveler(std::string username) {
	try {
		vector<int> index;
		index = find_trips_passenger(username);
		if (index.size() >= 3) {
			int i = index.size() - 1;
			string date4 = orders[i]->get_start_date();
			string date2 = orders[i - 1]->get_start_date();
			string date3 = orders[i - 1]->get_end_date();
			string date1 = orders[i - 2]->get_end_date();
			int time_between = 0;
			time_between += diff_time(date2, date1);
			time_between += diff_time(date4, date3);
			if (time_between < 24 * 60 * 60) {
				return true;
			}
		}
		return false;
	}
	catch (not_a_date exception) {
		cout << "not a date" << endl;
	}
}

bool repository::is_not_frequent_traveler(std::string username)
{
	vector<int> index;
	index = find_trips_passenger(username);
	if (index.size() >= 3) {
		string date2 = adminstrator->get_date();
		string date1 = orders[index.size() - 1]->get_end_date();
		int time_between = 0;
		time_between += diff_time(date2, date1);
		if (time_between > 48 * 60 * 60) {
			return true;
		}
	}
	return false;
}
