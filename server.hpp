#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <fcntl.h>
#include <poll.h>

class Server
{
	private:
		std::string host;
		std::string port; // the port to listen to
		std::string password; // the password to use

	public:
		enum status
		{
			OFFLINE,
			ONLINE,
			CLOSED,
		}_status;
		int _fd;
		std::vector<pollfd> _pfds;

	public:
		Server(std::string host, std::string port, std::string password);
		~Server();
		void close_server();
		void run();
		bool is_running();
		bool has_password();
		std::string get_password();
		std::string get_server_name();
};


bool validate_arguments(int argc, char **argv);


#endif
