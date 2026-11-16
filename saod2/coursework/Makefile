CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../build
PROGRAMS = coursework
COMMON = src/main.c src/sort.c src/search.c src/a2.c src/tree.c src/svg.c
HEADERS = $(wildcard src/*.h)

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean run-coursework

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_COURSEWORK = $(COMMON)
$(BUILD)/coursework: $(SOURCES_COURSEWORK) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_COURSEWORK) $(LDFLAGS) $(LDLIBS) -o "$@"

run-coursework: $(BUILD)/coursework
	cd src && ../../build/coursework

run: run-coursework

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
