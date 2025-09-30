SOURCES =	main.cpp
NAME = rayTracer
SRCS_PATH = ./srcs
OBJS_PATH = ./objects
MY_SRCS = ${addprefix ${SRCS_PATH}/, ${notdir ${MY_SOURCES}}}
SRCS = ${addprefix ${SRCS_PATH}/, ${SOURCES}}
OBJS = ${addprefix ${OBJS_PATH}/, ${notdir ${SOURCES:.cpp=.o}}}
INCLUDE = -I include ${addprefix -I , ${wildcard srcs/*}}
CC = g++
FLAGS = -Werror -Wextra -Wall -O3

# Colors
GREEN = \33[1;32m
L_CYAN = \33[1;36m
L_BLUE = \33[1;34m
L_GREEN = \33[1;92m
L_PURPLE = \33[1;35m
NC = \033[0m

all: ${NAME}

bonus: ${BONUS}

${OBJS_PATH}/%.o: ${SRCS_PATH}/%.cpp
		@ mkdir -p ${OBJS_PATH}
		 ${CC} ${INCLUDE} ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME} 
		@ echo "\12${GREEN}${NAME} successfully compiled!${NC}"

# ***********************WILDCARD COMPILATION******************* # 
NAME_WILD = raytracer
NAME_ARCHIVE = raytracer.a
MAIN_W = main.cpp
MAIN_OBJ = ${OBJS_PATH}/main.o
SOURCES_W = $(wildcard $(SRCS_PATH)/**/*.cpp) $(wildcard $(SRCS_PATH)/*.cpp) \
			$(wildcard $(SRCS_PATH)/**/**/*.cpp)
OBJECTS_W = $(patsubst $(SRCS_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(SOURCES_W))
OBJECTS_W_PATH = ${dir ${OBJECTS_W}}

m: ${NAME_WILD}


${NAME_WILD}: ${LIBFT} ${NAME_ARCHIVE} ${MAIN_OBJ}
				${CC} ${MAIN_OBJ} ${NAME_ARCHIVE} ${INCLUDE} ${FLAGS} -o ${NAME_WILD}

${MAIN_OBJ}: ${MAIN_W}
		 @ ${CC} ${INCLUDE} ${FLAGS} -c $< -o $@
			
${NAME_ARCHIVE}: ${OBJECTS_W}
				ar -rcs ${NAME_ARCHIVE} ${OBJECTS_W}

run: m
	./${NAME_WILD}


# ============================================================ #

# ***********************TESTS******************* # 

TEST_PATH = ./tests
TEST = tests/test
SOURCES_T = $(wildcard $(TEST_PATH)/*.cpp) $(wildcard ${TEST_PATH}/**/*.cpp)
MAIN_TEST = tests/test.cpp
MAIN_TEST_OBJ = ${OBJS_PATH}/test.o
TESTS     = $(patsubst $(TEST_PATH)/%.cpp, $(TEST_PATH)/%.out,   $(SOURCES_T))
VGTESTS   = $(patsubst $(TEST_PATH)/%.cpp, $(TEST_PATH)/%vg.out, $(SOURCES_T))

${MAIN_TEST_OBJ}: ${MAIN_TEST}
				@ ${CC} ${FLAGS} ${INCLUDE} -c $< -o $@

tests: test
		./${TEST}

val: m
	 valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./${NAME_WILD}

valtests: test
		valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./${TEST}

test: fclean dirs ${NAME_ARCHIVE} ${MAIN_TEST_OBJ}
		@ ${CC} ${INCLUDE} ${MAIN_TEST_OBJ} ${NAME_ARCHIVE} ${FLAGS} -lUnitTest++  -o ${TEST}
		rm objects/test.o


# ============================================================ #

clean:
	@ rm -rf ${OBJS_PATH}
	@ echo "${L_CYAN}Objects deleted!${NC}"

fclean: clean
	@ rm -rf ${NAME} ${NAME_ARCHIVE} ${NAME_WILD}
	@ echo "${L_BLUE}Raytracer deleted!${NC}"

re: fclean dirs m

dirs:
		mkdir -p ${OBJECTS_W_PATH} ${OBJECTS_T_PATH}

.PHONY: clean re all fclean
