#include "irc_server.hpp"


//initialaize the poll to start receiving sockets ips as fds 
void	Irc_Server::initPoll( void ) {

	struct pollfd					pollFd = { this->socketFd, POLLIN, 0 };
	std::vector<pollfd>::iterator	pi;

//Setting the socket fds to o_nonblock
	if (fcntl(this->socketFd, F_SETFL, O_NONBLOCK) == -1)
		ft::errorMessage("fcntl:", strerror(errno));
// we are saving the socket fds into pointer to vector Vpollfds 
	this->Vpollfds.push_back(pollFd);

	std::cout << BGRN << "/ ***************************************** \\" << std::endl;
	std::cout << "|    Irc_Server Listen at: " << this->host << ":" << this->port << "    |" << std::endl;
	std::cout << "\\ ***************************************** /" << RESET <<std::endl;

	while (loop) {
		pi = this->Vpollfds.begin();
		if (poll(&(*pi), this->Vpollfds.size(), 5000) == -1)
			ft::errorMessage("poll:", strerror(errno));
		this->_checkPoll();
	}

}


// creating pointers to users vector on server 
bool	Irc_Server::Operators( void ) 
{
	// std::vector<User *>::iterator	it = this->Users.begin();
	// for(; it != this->Users.end(); it++)
	// 	if ((*it)->isOper())
	// 		return true;
	return false;
}


int	Irc_Server::getSocketFd( void ) {
	return (this->socketFd);
}

// validate all fds from poll, users, and POLLIN, to know new & existing users
void	Irc_Server::_checkPoll( void ) 
{
	std::vector<pollfd>::iterator	it;

	for (it = this->Vpollfds.begin(); it != this->Vpollfds.end(); it++) 
    {
        //checking the if poll fd vector and POLLIN is true
		if (it->revents && POLLIN) {
            //fd off the poll is equal the server socket fd
			if (it->fd == this->socketFd)
            // create new connection(User)
				this->_createUser();
			else
            // get(command) from exiting user 
				this->_messageReceived(it->fd);
			break ;
		}
	}

}


// This function main job is binding all parameters into the socket 
void	Irc_Server::setSocketFd( void ) {

	struct addrinfo	*resultList;
	struct addrinfo	*lst;
	struct addrinfo 	hints;
	int				exitCode;
	int				serverFd;
	int				value = 1;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	// here we get the address from the host & port of our server
	exitCode = getaddrinfo(this->host.c_str(), this->port.c_str(), &hints, &resultList);
	if (exitCode != 0)
		ft::errorMessage("getaddrinfo:", gai_strerror(exitCode));

	lst = resultList;
	while (lst) 
	{
		//Creates socket fd
		serverFd = socket(lst->ai_family, lst->ai_socktype, lst->ai_protocol);
		if (serverFd == -1)
			continue ;
		// , configure it to be reused 
		exitCode = setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
		if (exitCode != 0) {
			close(serverFd);
			freeaddrinfo(resultList);
			ft::errorMessage("setsockopt:", gai_strerror(exitCode));
		}
		// binding the configured socket fd with the address from exit code above
		exitCode = bind(serverFd, lst->ai_addr, lst->ai_addrlen);
		if (exitCode == 0)
			break ;
		close(serverFd);
		lst = lst->ai_next;
	}
	freeaddrinfo(resultList);
	if (lst == NULL)
		ft::errorMessage("bind:", gai_strerror(exitCode));


	// we are making the socket now listen to the server
	exitCode = listen(serverFd, LISTEN_BACKLOG);
	if (exitCode == -1)
		ft::errorMessage("listen:", gai_strerror(exitCode));
	// passing server fd to the socket 
	this->socketFd = serverFd;
	return ;
}
