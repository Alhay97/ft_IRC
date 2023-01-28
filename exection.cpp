#include "server.hpp"


// create an atoi for cpp 98 standard for the port
	//should be less than 65535 and greater than 0 (done)
	//should not be part of reserverd ports
	//
//


int stringToInt(std::string str)
{
	int num = 0;
	int i  = 0;
	int size = str.length();
	while (i < size)
	{
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}


int portChecker(int port)
{
	try
	{
		if(port <= 65535 && port >= 0)
			return (port);
		else
			throw std::invalid_argument("not in port range");
	}

	catch(const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}

int main(int counter, char **str)
{
	try
	{
		if(counter == 3)
		{
			portChecker(stringToInt(str[1]));
			std::cout << str[1] << std::endl;
			std::cout << str[2] << std::endl;
		}
		else
			throw std::invalid_argument("invalid arguments");
	}
	catch(const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}




