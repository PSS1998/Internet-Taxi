#include <vector>
#include <string>


class wrong_parameter_exception;
class not_a_phone_number;
class wrong_password;
class not_a_username;
class not_a_date;
class not_an_address;
class not_allowed_command;

class passenger {
public:
	passenger(std::string _username, std::string _password, std::string _phone, std::string _date) : username(_username), password(_password), phone(_phone), date(_date) { cal_discount_code(); logged_in = false; account_value = 0; account_value = 0; rate = 0; frequent_traveler = 0; }
	std::string get_name() { return username; }
	std::string get_password() { return password; }
	std::string get_phone() { return phone; }
	int get_credit() { return account_value; }
	bool get_rate() { return rate; }
	std::string get_date() { return date; }
	void rate_trip(bool _rate) { rate = _rate; }
	void cal_discount_code();
	std::string get_discount_code();
	void get_discount();
	void pay_credit(int amount);
	void login() { logged_in = true; }
	void logout() { logged_in = false; }
	void set_frequent_traveler(bool _frequent_traveler) { frequent_traveler = _frequent_traveler; }
	bool is_frequent_traveler() { return frequent_traveler; }
	void charge_account(int amount) { account_value += amount; }
	std::string print_credit();
	bool allowed_command();
	bool allowed_command_rate();
	bool is_account_enough() { if (account_value < -10) return false; return true; }
	std::string must_rate() {if(rate) return "1"; return ""; }
private:
	std::string username;
	std::string password;
	std::string phone;
	bool logged_in;
	int account_value;
	std::string discount_code;
	int discount_code_count;
	std::string date;
	bool frequent_traveler;
	bool rate;
};
