#include <vector>
#include <string>


class wrong_parameter_exception;
class not_a_phone_number;
class wrong_password;
class not_a_username;
class not_a_date;
class not_an_address;
class not_allowed_command;


class admin_system;
class passenger;
class driver;
class spaceship;
class order;
class universe;
class galaxy;
class planet;
class MyServer;

class repository {
public:

	~repository() {
		for (int i = 0; i < passengers.size(); i++)
			delete passengers[i];
		for (int i = 0; i < drivers.size(); i++)
			delete drivers[i];
		for (int i = 0; i < orders.size(); i++)
			delete orders[i];
		delete adminstrator;
		delete map;
	}

	class commands {
	public:
		std::string get_command(std::string input);
		std::string check_command();
		std::string register_passenger();
		std::string register_driver();
		std::string accept_registration();
		std::string reject_registration();
		std::string show_registration_requests();
		std::string get_discount_code();
		std::string login();
		std::string logout();
		std::string set_status();
		std::string estimate_trip();
		std::string request_trip();
		std::string cancel_trip_request();
		std::string show_trip_requests();
		std::string accept_trip_request();
		std::string trip_status();
		std::string arrived();
		std::string end_trip();
		std::string rate_driver();
		std::string charge_account();
		std::string get_credit();
		std::string driver_report();
		std::string passenger_report();
		std::string system_report();
		std::string set_time();
		std::string system_time();
		std::string must_rate();

		std::string username;
		std::string command;
		std::vector<std::string> parameters;

		repository* command_owner;
	};



	void add_passenger(std::string username, std::string password, std::string phone);
	void add_driver(std::string username, std::string password, std::string spaceship_number, std::string spaceship_model, std::string production_year, std::string spaceship_color, bool VIP);

	int find_driver(std::string username);
	int find_passenger(std::string username);
	std::string not_accepted_drivers();
	void get_discount(std::string username, std::string discount_code);
	void login(std::string username, std::string password);
	void logout(std::string username);
	void set_status(std::string username, std::string status);
	void set_status(std::string username, std::string status, std::string address);
	std::vector<int> estimate_trip(std::string username, bool VIP, std::string source, std::string destinations);
	std::string request_trip(std::string username, bool VIP, std::string source, std::string destinations);
	void cancel_trip_request(std::string username);
	std::string show_trip_requests(std::string username);
	std::vector<order*>::iterator find_order(std::string username, bool accepted);
	std::vector<int> find_trips(bool VIP, bool accepted);
	void accept_trip_request(std::string username, std::string passenger_username);
	std::string trip_status(std::string username);
	int find_trips(std::string username, bool end_trip);
	void arrived(std::string username);
	void end_trip(std::string username);
	int find_trip_driver(std::string username);
	std::vector<int> find_trips_driver(std::string username);
	std::vector<int> find_trips_driver(std::string username, std::string date1, std::string date2);
	int find_order_rate(std::string username);
	void rate_driver(std::string username, std::string rate);
	void charge_account(std::string username, std::string amount);
	std::string get_credit(std::string username);
	void driver_report(std::string username, std::string driver_username, std::string start_date, std::string end_date);
	void print_driver_report(int trips_count, float total_income, int total_rate);
	void passenger_report(std::string username, std::string passenger_username);
	void print_credit(int credit);
	std::vector<int> find_trips_date(std::string date1, std::string date2);
	void print_system_report(float system_credit, int trips_count, int drivers_count, int passengers_count);
	void system_report(std::string username, std::string date1, std::string date2);
	void system_report(std::string username);
	std::vector<int> trips_ended();
	std::vector<int> drivers_accepted();
	std::vector<int> drivers_accepted(std::string date1, std::string date2);
	std::vector<int> passengers_date(std::string date1, std::string date2);
	void set_time(std::string username, std::string date);
	void pay_wages(std::string date1, std::string date2);
	void driver_algorithm(bool VIP, std::string source);
	std::vector<int> find_drivers(bool VIP);
	std::vector<int> find_trips_passenger(std::string username);
	bool is_frequent_traveler(std::string username);
	bool is_not_frequent_traveler(std::string username);
	void check_frequent_traveler();
	void check_not_frequent_traveler();

	commands command;

	std::vector<passenger*> passengers;
	std::vector<driver*> drivers;
	admin_system* adminstrator;
	universe* map;
	std::vector<order*> orders;
	MyServer* server;
};
