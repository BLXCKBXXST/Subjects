CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = 3.4-sdp-delete
COMMON = 3.4-main.c 3.4-sdp-delete.c 3.4-input.c 3.4-preview.c ../3.3-sdp/3.3-sdp.c ../3.3-sdp/3.3-common.c ../3.3-sdp/3.3-svg.c ../lab-viewer.c
HEADERS = $(wildcard ./*.h ../3.3-sdp/*.h ../*.h)
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

SOURCES_3_4_SDP_DELETE = $(COMMON)
$(BUILD)/3.4-sdp-delete: $(SOURCES_3_4_SDP_DELETE) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_3_4_SDP_DELETE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o "$@"

run: $(BUILD)/3.4-sdp-delete
	$(BUILD)/3.4-sdp-delete

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
	rm -f ../../3.4-*.svg ../../3.4-sdp-delete-steps.js ../../3.4-sdp-delete-steps.tmp.js
