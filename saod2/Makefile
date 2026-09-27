CC = gcc
CFLAGS ?= -std=c11 -O2

PROGRAMS = coursework records tree tree100 isdp isdp-iterative search search-old sdp-recursive sdp-double
ISDP_COMMON = labs/isdp/main.c labs/isdp/compare.c labs/isdp/treeprint.c

.PHONY: all clean $(addprefix run-,$(PROGRAMS))
all: $(addprefix build/,$(PROGRAMS))

build:
	mkdir -p build

build/coursework: coursework/src/main.c $(wildcard coursework/src/*.h) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

build/records: labs/records/main.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

build/tree: labs/trees/derevya.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

build/tree100: labs/trees/derevya100.c labs/trees/treeprint.c labs/trees/treeprint.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

build/isdp: $(ISDP_COMMON) labs/isdp/search.c $(wildcard labs/isdp/*.h) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

build/isdp-iterative: $(ISDP_COMMON) labs/isdp/search_iterative.c $(wildcard labs/isdp/*.h) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

build/search: labs/substring-search/saod.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

build/search-old: labs/substring-search/saod-old.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

run-coursework: build/coursework
	cd coursework/src && ../../build/coursework

run-records: build/records
	./build/records

run-tree: build/tree
	./build/tree

run-tree100: build/tree100
	./build/tree100

run-isdp: build/isdp
	./build/isdp

run-isdp-iterative: build/isdp-iterative
	./build/isdp-iterative

run-search: build/search
	cd labs/substring-search && ../../build/search

run-search-old: build/search-old
	cd labs/substring-search && ../../build/search-old

clean:
	rm -rf build

# СДП: две реализации с одним main.c
SDP_SOURCES = labs/sdp/main.c labs/sdp/recursive.c labs/sdp/double.c labs/sdp/common.c labs/sdp/compare.c labs/sdp/treeprint.c

build/sdp-recursive: $(SDP_SOURCES) labs/sdp/sdp.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

build/sdp-double: $(SDP_SOURCES) labs/sdp/sdp.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -DUSE_DOUBLE $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

run-sdp-recursive: build/sdp-recursive
	./build/sdp-recursive

run-sdp-double: build/sdp-double
	./build/sdp-double
