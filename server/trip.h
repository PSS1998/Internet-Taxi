#include <vector>
#include <string>


class wrong_parameter_exception;
class not_a_phone_number;
class wrong_password;
class not_a_username;
class not_a_date;
class not_an_address;
class not_allowed_command;

class order {
public:
	order(std::string username, std::string _source, std::vector<std::string> _destination, int _cost, int _distance, bool _VIP, std::string _date) : user(username), source(_source), destination(_destination), cost(_cost), distance(_distance), VIP(_VIP), start_date(_date), end_trip(0), arrived(0), accepted(0), paid_driver(0), rated(0) {}
	std::string get_name() { return user; }
	std::string get_driver_name() { return accepted_driver; }
	std::string get_last_destination() { return destination[destination.size() - 1]; }
	std::string get_start_date() { return start_date; }
	std::string get_end_date() { return end_date; }
	void set_end_date(std::string date) { end_date = date; }
	int get_cost() { return cost; }
	bool is_VIP() { return VIP; }
	bool is_accepted() { return accepted; }
	bool is_ended() { return end_trip; }
	bool is_arrived() { return arrived; }
	bool is_rated() { return rated; }
	bool is_driver_paid() { return paid_driver; }
	void pay() { paid_driver = 1; }
	void rate_trip() { rated = 1; }
	void accept_trip(std::string username) { accepted = true; accepted_driver = username; }
	void trip_arrived() { arrived = true; }
	void trip_ended() { end_trip = true; }
	std::string print();
	std::string print_status(bool accepted);
private:
	std::string user;
	std::string source;
	std::vector<std::string> destination;
	std::string accepted_driver;
	int cost;
	int distance;
	bool VIP;
	bool end_trip;
	bool arrived;
	std::string start_date;
	std::string end_date;
	bool accepted;
	bool rated;
	bool paid_driver;

};
