SRC_DIR = src
INCLUDE_DIR = ./include

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS = $(subst .c,.o,$(SRCS))

CC = gcc
INCLUDES = -I$(INCLUDE_DIR)
CFLAGS = -g -Wall -std=c99 $(INCLUDES)

all: compile

compile: $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
		$(CC) -c $(CFLAGS) -o $@ $<

clean:
		rm $(OBJS)
