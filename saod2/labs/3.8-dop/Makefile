CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.8-dop
COMMON = 3.8-main.c 3.8-compare.c 3.8-dop.c 3.8-common.c 3.8-tree.c 3.8-svg.c ../lab-viewer.c
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

SOURCES_3_8_DOP = $(COMMON)
$(BUILD)/3.8-dop: $(SOURCES_3_8_DOP) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_8_DOP) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.8-dop
	$(BUILD)/3.8-dop

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
