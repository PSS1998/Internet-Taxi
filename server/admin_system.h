#include <vector>
#include <string>


class wrong_parameter_exception;
class not_a_phone_number;
class wrong_password;
class not_a_username;
class not_a_date;
class not_an_address;
class not_allowed_command;

class repository;

class admin_system {
public:
	admin_system() : date_time("1-00:00:00"), account_value(0), logged_in(0) {}
	void get_vehicles();
	std::string get_date() { return date_time; }
	void set_date(std::string date) { date_time = date; }
	float get_credit() { return account_value; }
	void charge_account(float amount) { account_value += amount; }
	void pay_wage(float amount) { account_value -= amount; }
	void login() { logged_in = true; }
	void logout() { logged_in = false; }
	bool allowed_command();
	std::vector<std::string> get_list_vehicles() { return list_vehicles; }

	repository* repository_control;

private:
	std::string date_time;
	float account_value;
	std::vector<std::string> list_vehicles;
	bool logged_in;

};
