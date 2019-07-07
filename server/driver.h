#include <vector>
#include <string>


class order;

class spaceship {
public:
	spaceship(std::string _spaceship_number, std::string _spaceship_model, std::string _production_year, std::string _spaceship_color) : spaceship_number(_spaceship_number), spaceship_model(_spaceship_model), production_year(_production_year), spaceship_color(_spaceship_color) {}
	std::string print();
	std::string print_spaceship();
	std::string get_spaceship_number() { return spaceship_number; }
private:
	std::string spaceship_number;
	std::string spaceship_model;
	std::string production_year;
	std::string spaceship_color;


};
//list_trips
class driver {
public:
	driver(std::string _username, std::string _password, std::string _spaceship_number, std::string _spaceship_model, std::string _production_year, std::string _spaceship_color, bool _VIP, std::string _date) : vehicle(new spaceship(_spaceship_number, _spaceship_model, _production_year, _spaceship_color)), username(_username), password(_password), VIP(_VIP), accepted(0), rate(0), num_rate(0), account_value(0), date(_date), logged_in(0) {}
	~driver() { delete vehicle; }
	std::string get_name() { return username; }
	std::string get_password() { return password; }
	spaceship* get_spaceship() { return vehicle; }
	std::string get_address() { return address; }
	std::string get_status() { return status; }
	int get_rating() { if (num_rate != 0) return (rate / num_rate); return 5; }
	void get_paid(float amount) { account_value += amount; }
	std::vector<order*> get_list_trips() { return list_trips; }
	bool is_VIP() { return VIP; }
	void login() { logged_in = true; }
	void logout() { logged_in = false; }
	void set_status(bool _status, std::string _address) { if (_status) status = "available"; else status = "unavailable"; if (_address != "") address = _address; }
	std::string print();
	std::string print_address();
	void in_trip() { status = "in trip"; }
	void rate_trip(int rating) { num_rate++; rate += rating; }
	void add_trip(order* Order) { list_trips.push_back(Order); }
	bool allowed_command();
	std::string get_date() { return date; }

	bool accepted;
private:

	std::string username;
	std::string password;
	spaceship* vehicle;
	bool VIP;
	std::string status;
	std::string address;
	int rate;
	int num_rate;
	float account_value;
	std::string date;
	bool logged_in;
	std::vector<order*> list_trips;


};
