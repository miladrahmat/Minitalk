CLIENT := client

SERVER := server

CC := cc

CFLAGS := -Wall -Wextra -Werror

WAIT_TIME ?= 500

SRC_DIR := ./sources/

INC_DIR := ./includes/

LIBFT := $(INC_DIR)Libft/libft.a

HEADERS := -I $(INC_DIR)Libft -I $(INC_DIR)

CLIENT_SRCS := $(SRC_DIR)client.c \
				$(SRC_DIR)utils.c

SERVER_SRCS := $(SRC_DIR)server.c \
				$(SRC_DIR)utils.c

CLIENT_OBJS := $(CLIENT_SRCS:%.c=%.o)

SERVER_OBJS := $(SERVER_SRCS:%.c=%.o)

all: $(CLIENT) $(SERVER)

%.o: %.c
	@$(CC) $(CFLAGS) -g -D WAIT_TIME=$(WAIT_TIME) $(HEADERS) -o $@ -c $<

$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	@echo "\e[1;93m Preparing Client ⏳ \e[0m"
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) $(HEADERS) -o $(CLIENT)
	@echo "\e[1;92m Client ready! 🗣 \e[0m"

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	@echo "\e[1;93m Preparing Server ⏳ \e[0m"
	@$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) $(HEADERS) -o $(SERVER)
	@echo "\e[1;92m Server ready! 💻 \e[0m"

$(LIBFT):
	@echo "\e[1;93m Compiling Libft ⏳ \e[0m"
	@make -s -C $(INC_DIR)Libft
	@echo "\e[1;92m Libft compiled! 📚 \e[0m"

clean:
	@make clean -s -C $(INC_DIR)Libft && rm -fr $(CLIENT_OBJS) \
		&& rm -fr $(SERVER_OBJS) && echo "\e[1;96m Removing all object files 🧹 \e[0m"

fclean: clean
	@make fclean -s -C $(INC_DIR)Libft && rm -fr $(CLIENT) \
		&& rm -fr $(SERVER) && echo "\e[1;96m Removing all executables 🧹 \e[0m"

re: fclean all

.PHONY: all, clean, fclean, re