CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.5-avl
COMMON = 3.5-main.c 3.5-avl.c 3.5-common.c 3.5-compare.c 3.5-search.c 3.5-svg.c 3.5-preview.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../*.h)
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

SOURCES_3_5_AVL = $(COMMON)
$(BUILD)/3.5-avl: $(SOURCES_3_5_AVL) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_5_AVL) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.5-avl
	$(BUILD)/3.5-avl

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
