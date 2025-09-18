COMPILER = c++
SRCS = main.cpp BitcoinExchange.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = btc
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
