CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.2-isdp 3.2-isdp-iterative
COMMON = 3.2-main.c 3.2-isdp.c 3.2-common.c 3.2-compare.c 3.2-svg.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../*.h)
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean run-iterative

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_3_2_ISDP = $(COMMON) 3.2-search.c
$(BUILD)/3.2-isdp: $(SOURCES_3_2_ISDP) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_2_ISDP) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.2-isdp
	$(BUILD)/3.2-isdp

SOURCES_3_2_ISDP_ITERATIVE = $(COMMON) 3.2-search-iterative.c
$(BUILD)/3.2-isdp-iterative: $(SOURCES_3_2_ISDP_ITERATIVE) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_2_ISDP_ITERATIVE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-iterative: $(BUILD)/3.2-isdp-iterative
	$(BUILD)/3.2-isdp-iterative

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
	rm -f ../../3.2-*.svg
