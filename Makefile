NAME := philosophers

CFLAGS ?= -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS := -g $(CFLAGS)
endif
OBJECTS := 
OBJECTS := $(addprefix obj/,$(OBJECTS))
INCLUDE := headers
HEADER_FILES := 
HEADER_FILES := $(addprefix $(INCLUDE)/,$(HEADER_FILES))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) bonus -C ./ft_printf
	@echo "[philosophers] compiling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJECTS) ft_printf/libftprintf.a -o $(NAME)

obj/%.o: src/%.c $(HEADER_FILES)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@echo "[philosophers] cleaning $(NAME)"
	$(MAKE) clean -C ./ft_printf
	@rm -f $(OBJECTS)
	@rm -rf obj

fclean: clean
	@echo "[philosophers] fully cleaning $(NAME)"
	$(MAKE) fclean -C ./ft_printf
	@rm -f $(NAME)

re: fclean all

bonus: all

run: all
	@echo "[philosophers] running $(NAME)"
	./$(NAME)

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re bonus run debug
