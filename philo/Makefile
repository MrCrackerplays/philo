NAME := philo

CFLAGS ?= -Wall -Werror -Wextra -pthread
ifdef DEBUG
CFLAGS := -g $(CFLAGS)
endif
OBJECTS := philosophers.o philo_setup.o philo_thread_utils.o sleep_utils.o \
	philo_print.o time_utils.o phil_behavior.o philo_mutex.o
OBJECTS := $(addprefix obj/,$(OBJECTS))
INCLUDE := headers
INCLUDE := $(addprefix -I,$(INCLUDE))
HEADER_FILES := philosophers.h pl_threads.h pl_sleep.h pl_print.h pl_time.h \
	phil_behavior.h philo_mutex.h
HEADER_FILES := $(addprefix headers/,$(HEADER_FILES))

PHIL_COUNT ?= 2
DIE_TIME ?= 310
EAT_TIME ?= 200
SLEEP_TIME ?= 200

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
	./$(NAME) $(PHIL_COUNT) $(DIE_TIME) $(EAT_TIME) $(SLEEP_TIME) $(EAT_COUNT)

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re bonus run debug
