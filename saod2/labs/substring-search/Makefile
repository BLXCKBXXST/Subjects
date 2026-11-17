CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = search search-old
COMMON =
HEADERS =

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean run-old

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_SEARCH = $(COMMON) saod.c
$(BUILD)/search: $(SOURCES_SEARCH) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_SEARCH) $(LDFLAGS) $(LDLIBS) -o "$@"

run: $(BUILD)/search
	$(BUILD)/search

SOURCES_SEARCH_OLD = $(COMMON) saod-old.c
$(BUILD)/search-old: $(SOURCES_SEARCH_OLD) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_SEARCH_OLD) $(LDFLAGS) $(LDLIBS) -o "$@"

run-old: $(BUILD)/search-old
	$(BUILD)/search-old

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
