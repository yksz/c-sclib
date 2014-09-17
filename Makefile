LIB_NAME = sclib
STATIC_LIB = lib$(LIB_NAME).a
DYNAMIC_LIB = lib$(LIB_NAME).so

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test
EXAMPLES_DIR = examples
INCLUDE_DIR = include

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.c=.o)))

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(subst .c,.o,$(TEST_SRCS))
TEST_EXES := $(subst .c,.exe,$(TEST_SRCS))

CC = gcc
CFLAGS = -g -Wall -std=c99 -I$(INCLUDE_DIR)

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		$(CC) -c $(CFLAGS) -o $@ $<

%_test: $(TEST_DIR)/%_test.exe
		$(TEST_DIR)/$@.exe

$(TEST_DIR)/%_test.exe: $(TEST_DIR)/%_test.o $(OBJS)
		$(CC) -o $@ $^

$(TEST_DIR)/%_test.o: $(TEST_DIR)/%_test.c
		$(CC) -c $(CFLAGS) -o $@ $<

%_example: $(EXAMPLES_DIR)/%_example.exe
		$(EXAMPLES_DIR)/$@.exe

$(EXAMPLES_DIR)/%_example.exe: $(EXAMPLES_DIR)/%_example.c $(STATIC_LIB)
		$(CC) $(CFLAGS) -o $@ $< $(BIN_DIR)/$(STATIC_LIB)

clean:
		rm $(BIN_DIR)/$(STATIC_LIB) $(BIN_DIR)/$(DYNAMIC_LIB) $(OBJS)

cleantest:
		rm $(TEST_EXES)
