CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../build
PROGRAMS = coursework
COMMON = src/main.c src/input.c src/sort.c src/search.c src/queue.c src/search-main.c src/a2.c src/tree.c src/tree-search.c src/svg.c src/preview.c ../labs/lab-viewer.c
HEADERS = $(wildcard src/*.h) ../labs/lab-viewer.h
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_COURSEWORK = $(COMMON)
$(BUILD)/coursework: $(SOURCES_COURSEWORK) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_COURSEWORK) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/coursework
	$(BUILD)/coursework

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
