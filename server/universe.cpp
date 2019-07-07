#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

#include "universe.h"
#include "functions.h"
#include "exceptions.h"

using namespace std;


void universe::get_topology()
{
	ifstream topology;
	topology.open("topology.cfg");
	stringstream sstr;
	sstr << topology.rdbuf();
	string topology_string;
	topology_string = sstr.str();
	int num_glaxy;
	sstr >> num_glaxy;
	sstr.seekg(/*num_glaxy / 10 + 1 +*/ 1, sstr.beg);
	for (int i = 0; i < num_glaxy; i++) {
		string galaxy_name;
		sstr >> galaxy_name;
		galaxies.push_back(new galaxy(galaxy_name));
		sstr.seekg(/*galaxy_name.size() +*/ 1, sstr.cur);
		int num_planet;
		sstr >> num_planet;
		sstr.seekg(/*num_planet / 10 + 1 +*/ 1, sstr.cur);
		for (int j = 0; j < num_planet; j++) {
			string planet_name;
			sstr >> planet_name;
			galaxies[i]->add_planet(planet_name);
			sstr.seekg(/*planet_name.size() +*/ 1, sstr.cur);
			int num_planet_near;
			sstr >> num_planet_near;
			sstr.seekg(/*num_planet_near / 10 + 1 +*/ 1, sstr.cur);
			for (int k = 0; k < num_planet_near; k++) {
				string planet_name;
				sstr >> planet_name;
				galaxies[i]->add_near_planet(planet_name, j);
				sstr.seekg(/*planet_name.size() +*/ 1, sstr.cur);
			}
		}
	}
	near_V();
}


void  universe::near_V() {
	string planet_name;
	for (int i = 0; i < galaxies.size(); i++) {
		for (int j = 0; j < galaxies[i]->get_planets().size(); j++) {
			for (int k = 0; k < galaxies[i]->get_planets()[j]->get_near_planets().size(); k++) {
				planet_name = galaxies[i]->get_planets()[j]->get_near_planets()[k];
				for (int m = 0; m < galaxies[i]->get_planets().size(); m++) {
					if (planet_name == galaxies[i]->get_planets()[m]->get_name()) {
						galaxies[i]->get_planets()[j]->add_near_index(m);
					}
				}
			}
		}
	}
}

void galaxy::DFSUtil(int v, vector<bool>& visited, vector<int>& level, int lev)
{
	visited[v] = true;
	level[v] = lev;
	for (int i = 0; i < planets[v]->get_near_planets_index().size(); i++) {
		if (!visited[planets[v]->get_near_planets_index()[i]]) {
			DFSUtil(planets[v]->get_near_planets_index()[i], visited, level, lev + 1);
		}
	}
}

void galaxy::DFS(int index, vector<int>& level)
{
	level.resize(planets.size());
	vector<bool> visited;
	visited.resize(planets.size());
	for (int i = 0; i < visited.size(); i++)
		visited[i] = false;
	int lev = 0;
	DFSUtil(index, visited, level, lev);
}

int universe::get_distance(std::string source, std::string destination)
{
	if (is_address(source, this) && is_address(destination, this)) {
		string delimiter, source_galaxy, source_planet, destination_galaxy, destination_planet;
		delimiter = ",";
		source_galaxy = source.substr(0, source.find(delimiter));
		source_planet = source.substr(source.find(delimiter) + 1, source.size());
		destination_galaxy = destination.substr(0, destination.find(delimiter));
		destination_planet = destination.substr(destination.find(delimiter) + 1, destination.size());
		if (source_galaxy == destination_galaxy) {
			int index1 = find_galaxy(source_galaxy);
			int index2 = galaxies[index1]->find_planet(source_planet);
			int index3 = galaxies[index1]->find_planet(destination_planet);
			vector<int> level;
			galaxies[index1]->DFS(index2, level);
			return level[index3];
		}
		else {
			int index1 = find_galaxy(source_galaxy);
			int index2 = find_galaxy(destination_galaxy);
			int index3 = galaxies[index1]->find_planet(source_planet);
			int index4 = galaxies[index2]->find_planet(destination_planet);
			vector<int> level1;
			galaxies[index1]->DFS(0, level1);
			vector<int> level2;
			galaxies[index2]->DFS(0, level2);
			return level1[index3] + level2[index4];
		}
	}
	else {
		throw not_an_address();
	}
}
