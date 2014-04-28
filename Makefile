STATIC_LIB = libsclib.a
DYNAMIC_LIB = libsclib.so

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test
INCLUDE_DIR = include

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.c=.o)))

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(subst .c,.o,$(TEST_SRCS))
TEST_EXES := $(subst .c,.exe,$(TEST_SRCS))

CC = gcc
INCLUDES = -I $(INCLUDE_DIR)
CFLAGS = -g -Wall -std=c99 $(INCLUDES)

all: $(STATIC_LIB) $(DYNAMIC_LIB)

alltest: $(TEST_EXES)
		for exe in $(TEST_EXES); \
		do $$exe; \
		done

$(STATIC_LIB): $(OBJS)
		$(AR) r $(BIN_DIR)/$@ $^

$(DYNAMIC_LIB):
		$(CC) -shared $(CFLAGS) -o $(BIN_DIR)/$@ $(SRCS)

compile: $(OBJS)

%_test: $(TEST_DIR)/%_test.o $(OBJS)
		$(CC) -o $(TEST_DIR)/$@.exe $^
		$(TEST_DIR)/$@.exe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		$(CC) -c $(CFLAGS) -o $@ $<

$(TEST_DIR)/%_test.o: $(TEST_DIR)/%_test.c
		$(CC) -c $(CFLAGS) -o $@ $<

clean:
		rm $(STATIC_LIB) $(DYNAMIC_LIB) $(OBJS)

cleantest:
		rm $(TEST_EXES)
