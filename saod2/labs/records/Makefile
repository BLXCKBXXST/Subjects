CC = gcc
CFLAGS ?= -std=c11 -O2
BUILD = ../../build
PROGRAMS = records
COMMON = main.c
HEADERS =

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.PHONY: all run clean

all: $(addprefix $(BUILD)/,$(PROGRAMS))

$(BUILD):
	mkdir -p "$(BUILD)"

SOURCES_RECORDS = $(COMMON)
$(BUILD)/records: $(SOURCES_RECORDS) $(HEADERS) Makefile | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES_RECORDS) $(LDFLAGS) $(LDLIBS) -o "$@"

run: $(BUILD)/records
	cd ../.. && build/records

clean:
	rm -f $(addprefix $(BUILD)/,$(PROGRAMS))
