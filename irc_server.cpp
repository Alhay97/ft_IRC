#include "irc_server.hpp"


Irc_Server::Irc_Server( std::string host, std::string port, std::string password )
	: host(host), port(port), _password(password) {
	this->setSocketFd();
	return ;
}

Irc_Server::~Irc_Server( void ) {
//change format
	std::vector<User *>::iterator	user_i = this->Users.begin();
	// std::vector<Channel *>::iterator	channel_i = this->Vchannels.begin();
	// std::vector<pollfd>::iterator	poll_i = this->VpollFdV.begin();

	// for ( ; channel_i != this->Vchannels.end(); channel_i++) {
	// 	delete *channel_i;
	// }
	// this->Vchannels.clear();

	// for ( ; poll_i != this->Vpollfds.end(); poll_i++) {
	// 	close((*poll_i).fd);
	// }

	for ( ; user_i != this->Users.end(); user_i++) {
			delete *user_i;
	}
	this->Users.clear();

	return ;
}

// function to send message to all users, has to be through server cuz its like main admin
void	Irc_Server::msgallUs( std::string msg ) {

	std::vector<User *>::iterator	it = this->Users.begin();

	if (msg.find(END) == std::string::npos)
		msg +=END;

	for( ; it != this->Users.end(); it++)
		if (send((*it)->getFd(), msg.c_str(), strlen(msg.c_str()), 0) < 0)
			ft::errorMessage("msgallUs: send:", strerror(errno));

	return ;

}

// to get messages accross to the server 
void	Irc_Server::msgServ( std::string msg, int userFd ) {

	std::vector<User *>::iterator	it = this->Users.begin();

	if (msg.find(END) == std::string::npos)
		msg +=END;

	for( ; it != this->Users.end(); it++)
		if ((*it)->getFd() != userFd)
			if (send((*it)->getFd(), msg.c_str(), strlen(msg.c_str()), 0) < 0)
				ft::errorMessage("msgServ: send:", strerror(errno));

	return ;

}

// void	Irc_Server::deleteU( int fd ) {
// 	std::vector<User *>::iterator	user_i = this->Users.begin();
// 	std::vector<Channel *>::iterator	channel_i = this->Vchannels.begin();
// 	std::vector<pollfd>::iterator	poll_i = this->Vpollfds.begin();

// 	for ( ; channel_i != this->Vchannels.end(); channel_i++)
// 		(*channel_i)->removeUser(getUserByFd(fd));

// 	for ( ; poll_i != this->Vpollfds.end(); poll_i++) {
// 		if ((*poll_i).fd == fd) {
// 			this->Vpollfds.erase(poll_i);
// 			close(fd);
// 			break ;
// 		}
// 	}

// 	for ( ; user_i != this->Users.end(); user_i++) {
// 		if ((*user_i)->getFd() == fd) {
// 			delete *user_i;
// 			this->Users.erase(user_i);
// 			break ;
// 		}
// 	}


// }

// void	Irc_Server::addChannel( Channel *channel ) {
// 	this->Vchannels.push_back(channel);
// }


User	*Irc_Server::getUserByFd( int fd ) {

	std::vector<User *>::iterator	it = this->Users.begin();

	for ( ; it != this->Users.end(); it++)
		if ((*it)->getFd() == fd)
			return (*it);

	return (NULL);

}

User	*Irc_Server::getUserByNick( std::string nick ) {

	std::vector<User *>::iterator	it = this->Users.begin();

	for ( ; it != this->Users.end(); it++)
		if ((*it)->getNick() == nick)
			return (*it);

	return (NULL);

}

std::string	Irc_Server::getPassword( void ) {
	return (this->_password);
}

std::vector<User *>	Irc_Server::getUsers( void ) {
	return (this->Users);
}


void	Irc_Server::_createUser( void ) 
{

	int					userFd;
	User				*newUser;
	struct sockaddr_in	cli_addr;
	socklen_t			len;

	len = sizeof(cli_addr);
	// we create a new User(connection)passing fd by the accept function
	userFd = accept(this->socketFd, (struct sockaddr *)&cli_addr, &len);
	if (userFd < 0)
		ft::errorMessage("accept:", strerror(errno));
	// new user poll fd will be set to o_nonblock using fcntl.
	pollfd	userPollFd = { userFd, POLLIN, 0 };
	if (fcntl(userFd, F_SETFL, O_NONBLOCK) == -1)
		ft::errorMessage("createUser: fcntl:", strerror(errno));
	//The new User is created
	newUser = new User(userFd);
	// add new pollfd and new user fd to their respective vector.
	this->Users.push_back(newUser);
	this->Vpollfds.push_back(userPollFd);
	std::cout << "New User: " << userFd << std::endl;
	return ;

}


void	Irc_Server::_messageReceived( int fd ) {

	char		buff;
	std::string	str;
	int			a = 0;

	while (str.find("\n")) 
	{
		// read the fd and get the buffer(message)
		if (recv(fd, &buff, 1, 0) < 0) {
			continue;
		} 
		else 
		{
		// here these all messages are read into str
			str += buff;
			if (a > 500)
				str = "/Quit not today!\r\n";
		// if we find a command we call the command function to excute that command
			if (str.find("\n") != std::string::npos) {
				if (str.size() == 1)
					str = "/Quit not today!\r\n";
				// Command command(str, fd, *this);
				break ;
			}
		}
		a++;
	}
	User * current_user = this->getUserByFd(fd);
	if(current_user->getAuth() == false)
	{
		std::cout << "got : " << str.substr(0, 4)  << std::endl;
		if(str.substr(0, 4) == "NICK")
		{
			current_user->setNick(str.substr(5, str.length()));
			std::cout << "set the nick\n";
		}
		else if(str.substr(0, 4) == "USER")
		{
			current_user->setUsername(str.substr(5, str.length()));
			std::cout << "set the userName\n";
		}
		else if(str.substr(0, 4) == "PASS")
		{
			std::cout << "nick: " << current_user->getNick() << std::endl;
			std::cout << "user: " << current_user->getUsername() << std::endl;
			std::cout << "ready to auth\n";
			// current_user->set(str.substr(5, str.length()));
		}
	}
	str.clear();
}


// creating pointers to channel vector on server
// std::vector<Channel *>	Irc_Server::getChannels( void ) {
// 	return (this->Vchannels);
// }

// we create the name of the channels for easier lookup later 
// Channel*	Irc_Server::getChannelByName( std::string name ) 
// {

// 	std::vector<Channel *>::iterator	it = this->Vchannels.begin();
// 	if (name[0] != '#')
// 		name = "#" + name;
// 	for ( ; it != this->Vchannels.end(); it++)
// 		if ((*it)->getName() == name)
// 			return (*it);
// 	return (NULL);
// }



bool	loop;

void	handle_ctrl_c( int sig ) {

	(void)sig;

	std::cout << std::endl;
	std::cout << BGRN << "/ ***************************************** \\" << std::endl;
	std::cout <<         "|         😎  Thanks for User!!  😎         |" << std::endl;
	std::cout <<         "\\ ***************************************** /" << RESET <<std::endl;

	throw std::runtime_error("");

}


//STEP1- our server starts running here 
int	main( int argc, char **argv ) {

	if (argc != 3) {
		std::cerr << "usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
    //STEP 2 - Loop will start by initializing our IRC server poll
	loop = true;
	signal(SIGINT, handle_ctrl_c);
	try {
		Irc_Server	server(HOST, argv[1], argv[2]);

		server.initPoll();
	} catch ( std::exception & e ) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}