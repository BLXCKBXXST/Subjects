CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.7-dbd
COMMON = 3.7-main.c 3.7-dbd.c 3.7-compare.c 3.7-svg.c ../3.5-avl/3.5-avl.c ../3.5-avl/3.5-common.c ../lab-viewer.c
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

SOURCES_3_7_DBD = $(COMMON)
$(BUILD)/3.7-dbd: $(SOURCES_3_7_DBD) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_7_DBD) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.7-dbd
	$(BUILD)/3.7-dbd

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
