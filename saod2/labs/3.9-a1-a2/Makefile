CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.9-a1-a2
COMMON = 3.9-main.c 3.9-a1-a2.c 3.9-compare.c ../3.8-dop/3.8-dop.c ../3.8-dop/3.8-common.c ../3.8-dop/3.8-tree.c ../3.8-dop/3.8-svg.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../3.8-dop/*.h ../*.h)
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean run-3.9-a1-a2

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_3_9_A1_A2 = $(COMMON)
$(BUILD)/3.9-a1-a2: $(SOURCES_3_9_A1_A2) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_9_A1_A2) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-3.9-a1-a2: $(BUILD)/3.9-a1-a2
	$(BUILD)/3.9-a1-a2

run: run-3.9-a1-a2

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
