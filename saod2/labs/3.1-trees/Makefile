CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.1-trees 3.1-trees-100
COMMON = 3.1-trees.c 3.1-svg.c 3.1-preview.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../*.h)
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean run-100

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_3_1_TREES = $(COMMON) 3.1-main.c
$(BUILD)/3.1-trees: $(SOURCES_3_1_TREES) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_1_TREES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.1-trees
	$(BUILD)/3.1-trees

SOURCES_3_1_TREES_100 = $(COMMON) 3.1-main-100.c 3.1-insert.c
$(BUILD)/3.1-trees-100: $(SOURCES_3_1_TREES_100) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_1_TREES_100) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-100: $(BUILD)/3.1-trees-100
	$(BUILD)/3.1-trees-100

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
	rm -f ../../3.1-*.svg
