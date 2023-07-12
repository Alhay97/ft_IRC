#ifndef _IRC_SERVER_HPP__
# define _IRC_SERVER_HPP__


# define HOST "127.0.0.1"
# define MAX_CLIENT 17
# define DEFAULT_BUFLEN 512
# define LISTEN_BACKLOG 50
# define END "\r\n"
# define TIMEOUT (50 * 60 * 1000)
# define DIE_PASS "partiu"

// Libraries Used
// #include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <cerrno>
#include <vector>
#include <algorithm>
#include <cctype>
#include <signal.h>
#include <stdexcept>
#include "Utils.hpp"
#include "irc_user.hpp"


// Our Other Needed Classes
class	Client;
// class	Channel;
class   User;

/** REFERENCES
 *  about fcntl:
 * https://man7.org/linux/man-pages/man2/fcntl.2.html
 * https://www.geeksforgeeks.org/non-blocking-io-with-pipes-in-c/
 * about poll:
 * https://man7.org/linux/man-pages/man2/poll.2.html
 * about getaddrinfo:
 *  https://www.man7.org/linux/man-pages/man3/getaddrinfo.3.html
 * about setsockopt:
 * https://man7.org/linux/man-pages/man3/setsockopt.3p.html
 * https://stackoverflow.com/questions/21515946/what-is-sol-socket-used-for
 * about bind:
 * https://man7.org/linux/man-pages/man2/bind.2.html
 * about listen:
 *  https://man7.org/linux/man-pages/man2/listen.2.html
 *  * About accept:
 * https://man7.org/linux/man-pages/man2/accept4.2.html
 *  * About recv:
 * https://man7.org/linux/man-pages/man2/recv.2.html
 * 
 */

// Validating Tests

// IRC Int_Main 
extern bool	loop;

class Irc_Server 
{
    // server connections parameters    
    private:

		std::string				host;
		std::string				port;
		std::string				_password;
		int						socketFd;
		std::vector<pollfd>		Vpollfds;
		// std::vector<Channel*>	Vchannels;
		std::vector<User *> 	Users;

	public:

		Irc_Server( std::string host, std::string port, std::string password );
		~Irc_Server( void );

	private:
    // within or to the server  
		void				checkPol( void );
		void				createUsr( void );
		void				msgRcvd( int fd );
        
    // between server and other classes
	public:
		void					initPoll( void );
        int						getSocketFd( void );
		void					setSocketFd( void );
        std::string				getPassword( void );
		bool					Operators( void );
        void					deleteU( int fd );
        void					msgallUs( std::string msg );
		void					msgServ( std::string msg, int userFd );
		std::vector<User *>		getUsers( void );
		User					*getUserByNick( std::string nick );
		User					*getUserByFd( int fd );
		void					_checkPoll( void );
		void					_createUser( void );
		void					_messageReceived( int fd );
        // void					addChannel( Channel *channel );
		// std::vector<Channel *>	getChannels( void );
		// Channel*				getChannelByName( std::string name );
};

//socket status
// enum    status
// {
//     ONLINE,
//     OFFLINE,
//     CLOSED
// }   _status;



#endif