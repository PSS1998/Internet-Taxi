#include <vector>
#include <string>

class wrong_parameter_exception;
class not_a_phone_number;
class wrong_password;
class not_a_username;
class not_a_date;
class not_an_address;
class not_allowed_command;


class planet {
public:
	planet(std::string _name) : name(_name) {}
	std::string get_name() { return name; }
	std::vector<std::string> get_near_planets() { return near_planets; }
	std::vector<int> get_near_planets_index() { return near_planets_index; }
	void add_near(std::string _name) { near_planets.push_back(_name); }
	void add_near_index(int _name) { near_planets_index.push_back(_name); }
private:
	std::string name;
	std::vector<std::string> near_planets;
	std::vector<int> near_planets_index;
};

class galaxy {
public:
	galaxy(std::string _name) : name(_name) {}
	~galaxy() { for (int i = 0; i<planets.size(); i++) delete planets[i]; }
	std::string get_name() { return name; }
	std::vector<planet*> get_planets() { return planets; }
	void add_planet(std::string _name) { planets.push_back(new planet(_name)); }
	void add_near_planet(std::string _name, int j) { planets[j]->add_near(_name); }
	int find_planet(std::string _name) { for (int i = 0; i < planets.size(); i++) if (planets[i]->get_name() == _name) return i; return -1; }
	void DFSUtil(int v, std::vector<bool>& visited, std::vector<int>& level, int lev);
	void DFS(int index, std::vector<int>& level);
private:
	std::string name;
	std::vector<planet*> planets;
};

class universe {
public:
	~universe() { for (int i = 0; i<galaxies.size(); i++) delete galaxies[i]; }
	void get_topology();
	void near_V();

	std::vector<galaxy*> get_galaxy() { return galaxies; }

	int get_distance(std::string source, std::string destination);
	int find_galaxy(std::string _name) { for (int i = 0; i < galaxies.size(); i++) if (galaxies[i]->get_name() == _name) return i; return -1; }
private:
	std::vector<galaxy*> galaxies;
};