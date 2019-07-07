#include "server.h"

#include "exceptions.h"
#include "universe.h"
#include "admin_system.h"
#include "trip.h"
#include "passenger.h"
#include "driver.h"
#include "repository.h"
#include "functions.h"

#include <cstdlib>
#include <map>

using namespace std;


struct ID {
  int id_num;
  string id_name;
};


// 'Server' is an abstract class, so define your own server class inheriting from the 'Server'
class MyServer : public Server {
public:
  MyServer(int port) : Server(port), username("admin"), logged_in(false) {}
  void on_standard_input(string line);
  void on_new_connection(int identifier);
  void on_new_message(int identifier, string message);
  void on_terminated_connection(int identifier);

	repository control;
private:
  void check_id_duplicate();
  vector<ID> id;
  string username;
  bool logged_in;
  
};

void MyServer::on_standard_input(string line)
{
  cout << "STDIN: " << line << endl;
  if (line == ":q")
    stop();
  string totem;
  string delimiter = " "; 
  totem = line.substr(0, line.find(delimiter));
  if(totem == "login"){
    if(line == "login admin s3cret"){
      logged_in = true;
      line = "login s3cret";
    }
    else{
      cout << "wrong username or password" << endl;
    }
  }
  if(logged_in){
    line = username + " " + line;
    control.command.get_command(line);
  }
  else{
    cout << "not logged in" << endl;
  }
}

void MyServer::on_new_connection(int identifier) {
  cout << "NEW CONNECTION: " << identifier << endl;
}

void MyServer::check_id_duplicate() {
  for(int i=0; i<id.size(); i++){
    for(int j=i+1; j<id.size(); j++){
      if(id[i].id_num == id[j].id_num && id[i].id_name == id[j].id_name){
        id.erase(id.begin() + i);
        i--;
        break;
      }
    }
  }

}

void MyServer::on_new_message(int identifier, string message) {
  cout << "NEW MESSAGE FROM " << identifier <<": " << message << endl;
  
  message = control.command.get_command(message);
  if(control.command.command == "register_passenger" || control.command.command == "register_driver" || control.command.command == "login"){
    ID temp;
    temp.id_name = control.command.username;
    temp.id_num = identifier;
    id.push_back(temp);
    check_id_duplicate();
  }
  send(identifier, message);
}

void MyServer::on_terminated_connection(int identifier) {
  cout << "TERMINATED CONNECTION: " << identifier << endl;
  for(int i=0; i<id.size(); i++){
    if(id[i].id_num == identifier){
      id.erase(id.begin() + i);
    }
  }
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "valid operation: " << argv[0] << " [port number]\n";
    exit(-1);
  }

  
  
  MyServer server(Tools::mystoi(argv[1]));

  server.control.map = new universe;
	server.control.adminstrator = new admin_system;
	server.control.map->get_topology();
	server.control.adminstrator->get_vehicles();
	server.control.command.command_owner = &server.control;
	server.control.server = &server;
  

  server.run();
  
  return 0;
}
