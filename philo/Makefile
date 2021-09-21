NAME := philo

CFLAGS ?= -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS := -g $(CFLAGS)
endif
OBJECTS := philosophers.o
OBJECTS := $(addprefix obj/,$(OBJECTS))
INCLUDE := headers libft
INCLUDE := $(addprefix -I,$(INCLUDE))
HEADER_FILES := philosophers.h
HEADER_FILES := $(addprefix headers/,$(HEADER_FILES))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) bonus -C ./libft
	@echo "[philosophers] compiling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJECTS) libft/libft.a -o $(NAME)

obj/%.o: src/%.c $(HEADER_FILES)
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "[philosophers] cleaning $(NAME)"
	$(MAKE) clean -C ./libft
	@rm -f $(OBJECTS)
	@rm -rf obj

fclean: clean
	@echo "[philosophers] fully cleaning $(NAME)"
	$(MAKE) fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

bonus: all

run: all
	@echo "[philosophers] running $(NAME)"
	./$(NAME)

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re bonus run debug
