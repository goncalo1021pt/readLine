NAME = readline

SRCS = $(wildcard srcs/*.c)

RM = rm -f
CFLAGS = -Wall -Wextra -Werror 
SFLAGS = -fsanitize=address
CC = cc
INCLUDES = -I includes
HDRS = $(includes/*.h)
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:srcs/%.c=%.o))
SOBJS = $(addprefix $(OBJS_DIR_S)/,$(SRCS:srcs/%.c=%.o))

OBJS_DIR = objs
OBJS_DIR_S = s_objs

# Color codes
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m 
ORANGE = \033[0;33m
NC = \033[0m 

CN = DefaultClass

all: $(NAME)

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_S)
	@echo "$(RED)$(NAME)$(NC)OBJS cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@echo "$(RED)$(NAME)$(NC)cleaned!"

re: fclean all

$(OBJS_DIR)/%.o: srcs/%.c $(HDRS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR_S)/%.o: srcs/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(SFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)$(NAME)$(NC) compiling..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@echo "$(GREEN)$(NAME)$(NC) ready!"

s: fclean $(SOBJS)
	@echo "$(GREEN)$(NAME)$(NC) compiling..."
	@$(CC) $(CFLAGS) $(SFLAGS) -o $(NAME) $(SOBJS) 
	@echo "$(GREEN)$(NAME)$(NC) ready!"

v: 
	make re && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

fcount:
	@echo "you wrote $(RED)$(shell cat $(SRCS) | wc -l)$(NC)lines of code"

send:
	@git add . && git commit -m "auto" && git push

run: all
	./$(NAME) 

.PHONY: all fclean clean re v s fcount send run