#include "irc_user.hpp"

User::User(int _fd)
{
    this->fd = _fd;
    this->nickname = "";
    this->userName = "";
    this->fullname = "";
    this->isAuth = false;
}

User::~User()
{

}

//setters
void User::setNick(std::string _nickname)
{
    this->nickname = _nickname;
}
void User::setFullname(std::string _fullname)
{
    this->fullname = _fullname;
}
void User::setUsername(std::string _userName)
{
    this->userName = _userName;
}

void User::setAuth(bool _auth)
{
    this->isAuth = _auth;
}

    //getters
std::string  User::getNick()
{
    return(nickname);
}
std::string  User::getFullname()
{
    return(fullname);
}
std::string  User::getUsername()
{
    return (userName);
}

bool User::getAuth()
{
    return (isAuth);
}

int User::getFd()
{
    return (fd);
}