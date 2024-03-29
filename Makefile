NAME	=	ircserv
COMPILER=	c++ 
FLAGS	=	-std=c++98 -Wall -Wextra -Werror
SRC		=	 irc_socket.cpp Utils.cpp irc_server.cpp irc_user.cpp

OBJ		=	$(SRC:.cpp=.o)
INC		=	

DEFAULT	=	'\033[0m'
GREEN	=	'\033[1;32m'
ORANGE 	=	'\033[1;33m'

.PHONY: all clean fclean re

all: compiling $(NAME) compiled

irssi: rm_irssi
	docker run -it --name my-running-irssi -e TERM -u $(id -u):$(id -g) \
	--log-driver=none \
    -v ${HOME}/.irssi:/home/user/.irssi:ro \
    irssi

rm_irssi:
	@docker rm -f my-running-irssi 2> /dev/null || exit 0

%.o: %.cpp $(INC)
	$(COMPILER) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@rm -f */*.out
	@rm -f *.out
	@rm -f */*.gch
	@rm -f *.gch
	@rm -rf *.dSYM
	@rm -rf */*.dSYM
	@find . -name ".DS_Store" -type f -delete
	@echo ${ORANGE}"Cleaning up refuse"$(DEFAULT)

fclean: clean
	@rm -f $(NAME)
	@echo ${GREEN}"All Clean"$(DEFAULT)

re: fclean all

compiling:
	@echo $(ORANGE)"Ft_IRC is being compiled"$(DEFAULT)

compiled:
	@echo $(GREEN)"Ft_IRC is ready"$(DEFAULT)
	@echo ""
	@echo "  .'.     '."
	@echo " /'         '\ "
	@echo "|             ;"
	@echo "|             ;"
	@echo " '.         .'"
	@echo "   `'-----'`"
	@echo "Straw Hat Pirates"
	@echo "Welcome to our IRC server!\033[0m"
