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
		~Server();
		Server(std::string host, std::string port, std::string password);
		void close_server();
		void run();
		bool is_running();
		bool has_password();
		std::string get_password();
		std::string get_server_name();

	public:
		std::vector< Client *> getr_related_clients(Clients * client);
		std::map < std::string, Client *> get_realted_Channels(Client * client);
		Client * getClient( std::string const &name);
		void deleteClient(int fd);
		size_t get_client_index(std::string &name);

	public:
		Channel * getChannel (std::string &name);
		std::vector<Channel *>  getChannels ();
		Channel * 	createChannel (std::string &name, std::string &password);
		Command * 	getCommand (std::string &name);

	public:
		std::map< size_t, Client * > 	_clients;
		std::map< std::string, Command * > 	_commands;
		std::map< std::string, Channel * > 	_channels;
		enum Server::Status 	_status;






};


bool validate_arguments(int argc, char **argv);


#endif
