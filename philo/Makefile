NAME := philo

CFLAGS ?= -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS := -g $(CFLAGS)
endif
OBJECTS := philosophers.o
OBJECTS := $(addprefix obj/,$(OBJECTS))
INCLUDE := headers
INCLUDE := $(addprefix -I,$(INCLUDE))
HEADER_FILES := philosophers.h
HEADER_FILES := $(addprefix headers/,$(HEADER_FILES))

PHIL_COUNT ?= 2
TIME_TO_DIE ?= 310
TIME_TO_EAT ?= 200
TIME_TO_SLEEP ?= 200

all: $(NAME)

$(NAME): $(OBJECTS)
	$(info [philosophers] compiling $(NAME))
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

obj/%.o: src/%.c $(HEADER_FILES)
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(info [philosophers] cleaning $(NAME))
	@rm -f $(OBJECTS)
	@rm -rf obj

fclean: clean
	$(info [philosophers] fully cleaning $(NAME))
	@rm -f $(NAME)

re: fclean all

bonus: all

run: all
	$(info [philosophers] running $(NAME))
	./$(NAME) $(PHIL_COUNT) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP) \
		$(EAT_COUNT)

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re bonus run debug
