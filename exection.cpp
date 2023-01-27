#include "server.hpp"


// create an atoi for cpp 98 standard for the port

//



int main(int counter, char **str)
{
	try
	{
		if(counter == 3)
		{
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

