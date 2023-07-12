#include <iostream>

class User
{
    public:

    User(int _fd);
    //setters
    void setNick(std::string _nickname);
    void setFullname(std::string _fullname);
    void setUsername(std::string _userName);
    void setAuth(bool _auth);

    //getters
    int         getFd();
    std::string getNick();
    std::string  getFullname();
    std::string  getUsername();
    bool getAuth();
    ~User();

    private:
    std::string nickname;
    std::string userName;
    std::string fullname;
    int fd;
    bool isAuth;


};