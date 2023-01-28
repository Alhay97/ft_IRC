#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

class Server
{
	private:

	public:
	Server();// default constructor
	Server();//constructor
	Server(Server &copy);
	Server &operator=(Server &source);
	~Server();

};

#endif
