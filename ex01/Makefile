COMPILER = c++
SRCS = main.cpp RPN.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = RPN
CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
