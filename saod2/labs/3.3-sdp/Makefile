CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.3-sdp 3.3-sdp-iterative 3.3-sdp-repeat 3.3-sdp-repeat-iterative
COMMON = 3.3-common.c 3.3-compare.c 3.3-svg.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../*.h)
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean run-3.3-sdp run-3.3-sdp-iterative run-3.3-sdp-repeat run-3.3-sdp-repeat-iterative run-iterative run-repeat run-repeat-iterative

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_3_3_SDP = $(COMMON) 3.3-main.c 3.3-sdp.c 3.3-search.c
$(BUILD)/3.3-sdp: $(SOURCES_3_3_SDP) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_3_SDP) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-3.3-sdp: $(BUILD)/3.3-sdp
	$(BUILD)/3.3-sdp

SOURCES_3_3_SDP_ITERATIVE = $(COMMON) 3.3-main.c 3.3-sdp.c 3.3-search-iterative.c
$(BUILD)/3.3-sdp-iterative: $(SOURCES_3_3_SDP_ITERATIVE) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_3_SDP_ITERATIVE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-3.3-sdp-iterative: $(BUILD)/3.3-sdp-iterative
	$(BUILD)/3.3-sdp-iterative

SOURCES_3_3_SDP_REPEAT = $(COMMON) 3.3-main-repeat.c 3.3-sdp-repeat.c 3.3-search.c
$(BUILD)/3.3-sdp-repeat: $(SOURCES_3_3_SDP_REPEAT) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_3_SDP_REPEAT) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-3.3-sdp-repeat: $(BUILD)/3.3-sdp-repeat
	$(BUILD)/3.3-sdp-repeat

SOURCES_3_3_SDP_REPEAT_ITERATIVE = $(COMMON) 3.3-main-repeat.c 3.3-sdp-repeat.c 3.3-search-iterative.c
$(BUILD)/3.3-sdp-repeat-iterative: $(SOURCES_3_3_SDP_REPEAT_ITERATIVE) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_3_SDP_REPEAT_ITERATIVE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run-3.3-sdp-repeat-iterative: $(BUILD)/3.3-sdp-repeat-iterative
	$(BUILD)/3.3-sdp-repeat-iterative

run: run-3.3-sdp

run-iterative: run-3.3-sdp-iterative

run-repeat: run-3.3-sdp-repeat

run-repeat-iterative: run-3.3-sdp-repeat-iterative

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
