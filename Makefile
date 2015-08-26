LIB_NAME = sclib
STATIC_LIB = lib$(LIB_NAME).a
DYNAMIC_LIB = lib$(LIB_NAME).so

ifeq ($(DEBUG),true)
  DST_DIR = build/debug
  CFLAGS += -g3 -O0
else
  DST_DIR = build/release
endif

SRC_DIR = src
TEST_SRC_DIR = test
EXAMPLE_SRC_DIR = example
INCLUDE_DIR = include

OBJ_DIR = $(DST_DIR)/$(SRC_DIR)
BIN_DIR = $(DST_DIR)/bin
TEST_OBJ_DIR = $(DST_DIR)/$(TEST_SRC_DIR)
EXAMPLE_OBJ_DIR = $(DST_DIR)/$(EXAMPLE_SRC_DIR)

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(addprefix $(DST_DIR)/, $(SRCS:.c=.o))
TEST_SRCS := $(wildcard $(TEST_SRC_DIR)/*.c)
TEST_OBJS := $(addprefix $(DST_DIR)/, $(TEST_SRCS:.c=.o))
TEST_EXES := $(addprefix $(DST_DIR)/, $(TEST_SRCS:.c=.exe))

CC = gcc
CFLAGS += -Wall -std=c99 -I$(INCLUDE_DIR)

all: $(STATIC_LIB) $(DYNAMIC_LIB)

$(STATIC_LIB): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(AR) r $(BIN_DIR)/$@ $^

$(DYNAMIC_LIB):
	@mkdir -p $(BIN_DIR)
	$(CC) -shared $(CFLAGS) -o $(BIN_DIR)/$@ $(SRCS)

compile: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

test: $(TEST_EXES)
	@for exe in $(TEST_EXES) ; do $$exe ; done

%_test: $(TEST_OBJ_DIR)/%_test.exe
	$<

$(TEST_OBJ_DIR)/%_test.exe: $(TEST_OBJ_DIR)/%_test.o $(OBJS)
	$(CC) -o $@ $^

$(TEST_OBJ_DIR)/%_test.o: $(TEST_SRC_DIR)/%_test.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

%_example: $(EXAMPLE_OBJ_DIR)/%_example.exe
	$<

$(EXAMPLE_OBJ_DIR)/%_example.exe: $(EXAMPLE_SRC_DIR)/%_example.c $(STATIC_LIB)
	@mkdir -p $(EXAMPLE_OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(BIN_DIR)/$(STATIC_LIB)

clean:
	rm -rf $(DST_DIR)
