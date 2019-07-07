all: main.o driver.o passenger.o admin_system.o functions.o repository.o trip.o universe.o server_socket.o server.o tools.o
	g++ -o server main.o driver.o passenger.o admin_system.o functions.o repository.o trip.o universe.o server_socket.o server.o tools.o
main.o: main.cpp driver.o passenger.o admin_system.o functions.o repository.o trip.o universe.o server_socket.o server.o tools.o
	g++ -c main.cpp
driver.o: driver.h driver.cpp
	g++ -c driver.cpp
passenger.o: passenger.h passenger.cpp
	g++ -c passenger.cpp
admin_system.o: admin_system.h admin_system.cpp
	g++ -c admin_system.cpp
functions.o: functions.h functions.cpp exceptions.h universe.h
	g++ -c functions.cpp
repository.o: repository.h repository.cpp universe.h trip.h functions.h admin_system.h passenger.h driver.h exceptions.h
	g++ -c repository.cpp
trip.o: trip.h trip.cpp
	g++ -c trip.cpp
universe.o: universe.h universe.cpp functions.h exceptions.h
	g++ -c universe.cpp
server.o: server.cpp server.h
	g++ -c server.cpp
	
server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
clean:
	rm -rf *.o
