#include <vector>
#include <string>


class universe;

std::string get_command();

std::string print_estimate_trip(int cost, int distance);

std::vector<int> date_analyse(std::string date);

bool is_date(std::string date);

bool is_date_bigger(std::string date1, std::string date2);

bool is_date_equal(std::string date1, std::string date2);

int diff_time(std::string date1, std::string date2);

bool is_address(std::string address, universe* map);
