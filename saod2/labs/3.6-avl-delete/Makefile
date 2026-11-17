CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.6-avl-delete
COMMON = 3.6-main.c 3.6-avl-delete.c 3.6-preview.c ../3.5-avl/3.5-avl.c ../3.5-avl/3.5-common.c ../3.5-avl/3.5-svg.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../3.5-avl/*.h ../*.h)
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

SOURCES_3_6_AVL_DELETE = $(COMMON)
$(BUILD)/3.6-avl-delete: $(SOURCES_3_6_AVL_DELETE) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_6_AVL_DELETE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.6-avl-delete
	$(BUILD)/3.6-avl-delete

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
