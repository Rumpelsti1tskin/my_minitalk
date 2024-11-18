CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC) #-g3 -fsanitize=address

INC = minitalk.h

SRC = server.c client.c
OBJ = $(SRC:.c=.o)

CNAME = client
SNAME = server

.PHONY = NAME, all, clean, fclean, re, bonus

all: $(CNAME) $(SNAME)

$(SNAME) : $(OBJ) Makefile minitalk.h
		$(CC) $(CFLAGS) server.c -o server

$(CNAME) : $(OBJ) Makefile minitalk.h
		$(CC) $(CFLAGS) client.c -o client

%.o : %.c $(INC)
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
		rm -f $(SNAME) $(CNAME)

re : fclean all
