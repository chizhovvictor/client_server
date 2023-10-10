NAME = webserv

SRCS =	./main.cpp

HEADER = ./include/cub3d.h

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = -Werror -Wextra -Wall -std=c++98
CPP = c++

all: $(NAME)


%.o : %.cpp 
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CPP) $(OBJS) -o $(NAME)


clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus