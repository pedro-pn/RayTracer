SOURCES = Vec.cpp Point.cpp
NAME = raytracer
SRCS_PATH = ./srcs
OBJS_PATH = ./objects
MY_SRCS = ${addprefix ${SRCS_PATH}/, ${notdir ${MY_SOURCES}}}
SRCS = ${addprefix ${SRCS_PATH}/, ${SOURCES}}
OBJS = ${addprefix ${OBJS_PATH}/, ${notdir ${SOURCES:.cpp=.o}}}
VPATH :=	${SRCS_PATH} ${SRCS_PATH}/main ${SRCS_PATH}/file
CC = g++
FLAGS =  -g -Wextra -Wextra -Wall -O3
INCLUDE = -I include ${addprefix -I , ${wildcard srcs/*}}

NAME_WILD = raytracer
NAME_ARCHIVE = raytracer.a
MAIN_W = main.cpp
MAIN_TEST = tests/test.cpp
MAIN_TEST_OBJ = ${OBJS_PATH}/test.o
TEST = tests/test
MAIN_OBJ = ${OBJS_PATH}/main.o
SOURCES_W = $(wildcard $(SRCS_PATH)/**/*.cpp) $(wildcard $(SRCS_PATH)/*.cpp) \
			$(wildcard $(SRCS_PATH)/**/**/*.cpp)
OBJECTS_W = $(patsubst $(SRCS_PATH)/%.cpp, $(OBJS_PATH)/%.o, $(SOURCES_W))
OBJECTS_W_PATH = ${dir ${OBJECTS_W}}

${OBJS_PATH}/%.o: ${SRCS_PATH}/%.cpp
		@ mkdir -p ${OBJS_PATH}
		 ${CC} ${INCLUDE}  ${FLAGS} -c $< -o $@

m: ${NAME_WILD}

${NAME_WILD}: ${NAME_ARCHIVE} ${MAIN_OBJ}
				${CC} ${INCLUDE} ${MAIN_OBJ} ${NAME_ARCHIVE} ${FLAGS} -o ${NAME_WILD}

${MAIN_OBJ}: ${MAIN_W}
		 @ ${CC} ${FLAGS} ${INCLUDE} -c $< -o $@
			
${NAME_ARCHIVE}: ${OBJECTS_W}
				ar -rcs ${NAME_ARCHIVE} ${OBJECTS_W}

run: m
	./${NAME_WILD}

val: m
	 valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./${NAME_WILD}

${MAIN_TEST_OBJ}: ${MAIN_TEST}
				@ ${CC} ${FLAGS} ${INCLUDE} -c $< -o $@

tests: test
		./${TEST}

valtests: test
		valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./${TEST}

test: fclean dirs ${NAME_ARCHIVE} ${MAIN_TEST_OBJ}
		@ ${CC} ${INCLUDE} ${MAIN_TEST_OBJ} ${NAME_ARCHIVE} ${FLAGS} -lUnitTest++  -o ${TEST}
		rm objects/test.o

dirs:
		mkdir -p ${OBJECTS_W_PATH} ${OBJECTS_T_PATH}

clean:
		rm -rf objects

fclean: clean
		rm -rf ${NAME_ARCHIVE} ${TEST}
		rm -rf ${NAME_WILD}

show:
	echo ${INCLUDE}