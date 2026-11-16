CC = gcc
CFLAGS ?= -std=c11 -O2

PROGRAMS = coursework records search search-old 3.1-trees 3.1-trees-100 3.2-isdp 3.2-isdp-iterative 3.3-sdp 3.3-sdp-iterative 3.3-sdp-repeat 3.3-sdp-repeat-iterative 3.4-sdp-delete 3.5-avl 3.6-avl-delete 3.7-dbd 3.8-dop 3.9-a1-a2
VIEWER = labs/lab-viewer.c
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

.PHONY: all clean $(addprefix run-,$(PROGRAMS))
all: $(addprefix build/,$(PROGRAMS))

build:
	mkdir -p build

COURSEWORK_SOURCES = coursework/src/main.c coursework/src/sort.c coursework/src/search.c coursework/src/a2.c coursework/src/tree.c coursework/src/svg.c

build/coursework: $(COURSEWORK_SOURCES) $(wildcard coursework/src/*.h) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(COURSEWORK_SOURCES) $(LDFLAGS) $(LDLIBS) -o $@

build/records: labs/records/main.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

build/search: labs/substring-search/saod.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

build/search-old: labs/substring-search/saod-old.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

run-coursework: build/coursework
	cd coursework/src && ../../build/coursework

run-records: build/records
	./build/records

run-search: build/search
	cd labs/substring-search && ../../build/search

run-search-old: build/search-old
	cd labs/substring-search && ../../build/search-old

clean:
	rm -rf build

LAB_3_1_TREES = labs/3.1-trees/3.1-main.c labs/3.1-trees/3.1-trees.c labs/3.1-trees/3.1-svg.c labs/3.1-trees/3.1-preview.c $(VIEWER)
build/3.1-trees: $(LAB_3_1_TREES) $(wildcard labs/3.1-trees/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_1_TREES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.1-trees: build/3.1-trees
	./build/3.1-trees

LAB_3_1_TREES_100 = labs/3.1-trees/3.1-main-100.c labs/3.1-trees/3.1-insert.c labs/3.1-trees/3.1-trees.c labs/3.1-trees/3.1-svg.c labs/3.1-trees/3.1-preview.c $(VIEWER)
build/3.1-trees-100: $(LAB_3_1_TREES_100) $(wildcard labs/3.1-trees/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_1_TREES_100) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.1-trees-100: build/3.1-trees-100
	./build/3.1-trees-100

LAB_3_2_ISDP = labs/3.2-isdp/3.2-main.c labs/3.2-isdp/3.2-isdp.c labs/3.2-isdp/3.2-common.c labs/3.2-isdp/3.2-compare.c labs/3.2-isdp/3.2-svg.c labs/3.2-isdp/3.2-search.c $(VIEWER)
build/3.2-isdp: $(LAB_3_2_ISDP) $(wildcard labs/3.2-isdp/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_2_ISDP) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.2-isdp: build/3.2-isdp
	./build/3.2-isdp

LAB_3_2_ISDP_ITERATIVE = labs/3.2-isdp/3.2-main.c labs/3.2-isdp/3.2-isdp.c labs/3.2-isdp/3.2-common.c labs/3.2-isdp/3.2-compare.c labs/3.2-isdp/3.2-svg.c labs/3.2-isdp/3.2-search-iterative.c $(VIEWER)
build/3.2-isdp-iterative: $(LAB_3_2_ISDP_ITERATIVE) $(wildcard labs/3.2-isdp/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_2_ISDP_ITERATIVE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.2-isdp-iterative: build/3.2-isdp-iterative
	./build/3.2-isdp-iterative

LAB_3_3_SDP = labs/3.3-sdp/3.3-main.c labs/3.3-sdp/3.3-sdp.c labs/3.3-sdp/3.3-common.c labs/3.3-sdp/3.3-compare.c labs/3.3-sdp/3.3-svg.c labs/3.3-sdp/3.3-search.c $(VIEWER)
build/3.3-sdp: $(LAB_3_3_SDP) $(wildcard labs/3.3-sdp/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_3_SDP) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.3-sdp: build/3.3-sdp
	./build/3.3-sdp

LAB_3_3_SDP_ITERATIVE = labs/3.3-sdp/3.3-main.c labs/3.3-sdp/3.3-sdp.c labs/3.3-sdp/3.3-common.c labs/3.3-sdp/3.3-compare.c labs/3.3-sdp/3.3-svg.c labs/3.3-sdp/3.3-search-iterative.c $(VIEWER)
build/3.3-sdp-iterative: $(LAB_3_3_SDP_ITERATIVE) $(wildcard labs/3.3-sdp/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_3_SDP_ITERATIVE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.3-sdp-iterative: build/3.3-sdp-iterative
	./build/3.3-sdp-iterative

LAB_3_3_SDP_REPEAT = labs/3.3-sdp/3.3-main-repeat.c labs/3.3-sdp/3.3-sdp-repeat.c labs/3.3-sdp/3.3-common.c labs/3.3-sdp/3.3-compare.c labs/3.3-sdp/3.3-svg.c labs/3.3-sdp/3.3-search.c $(VIEWER)
build/3.3-sdp-repeat: $(LAB_3_3_SDP_REPEAT) $(wildcard labs/3.3-sdp/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_3_SDP_REPEAT) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.3-sdp-repeat: build/3.3-sdp-repeat
	./build/3.3-sdp-repeat

LAB_3_3_SDP_REPEAT_ITERATIVE = labs/3.3-sdp/3.3-main-repeat.c labs/3.3-sdp/3.3-sdp-repeat.c labs/3.3-sdp/3.3-common.c labs/3.3-sdp/3.3-compare.c labs/3.3-sdp/3.3-svg.c labs/3.3-sdp/3.3-search-iterative.c $(VIEWER)
build/3.3-sdp-repeat-iterative: $(LAB_3_3_SDP_REPEAT_ITERATIVE) $(wildcard labs/3.3-sdp/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_3_SDP_REPEAT_ITERATIVE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.3-sdp-repeat-iterative: build/3.3-sdp-repeat-iterative
	./build/3.3-sdp-repeat-iterative

LAB_3_4_SDP_DELETE = labs/3.4-sdp-delete/3.4-main.c labs/3.4-sdp-delete/3.4-sdp-delete.c labs/3.4-sdp-delete/3.4-input.c labs/3.4-sdp-delete/3.4-preview.c labs/3.3-sdp/3.3-sdp.c labs/3.3-sdp/3.3-common.c labs/3.3-sdp/3.3-svg.c $(VIEWER)
build/3.4-sdp-delete: $(LAB_3_4_SDP_DELETE) $(wildcard labs/3.4-sdp-delete/*.h) $(wildcard labs/3.3-sdp/*.h) labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LAB_3_4_SDP_DELETE) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.4-sdp-delete: build/3.4-sdp-delete
	./build/3.4-sdp-delete

# 3.5 — АВЛ: включение вершины
AVL_CORE = labs/3.5-avl/3.5-avl.c labs/3.5-avl/3.5-common.c
AVL_SVG = labs/3.5-avl/3.5-svg.c
AVL_SOURCES = labs/3.5-avl/3.5-main.c $(AVL_CORE) labs/3.5-avl/3.5-compare.c labs/3.5-avl/3.5-search.c $(AVL_SVG) labs/3.5-avl/3.5-preview.c $(VIEWER)

build/3.5-avl: $(AVL_SOURCES) labs/3.5-avl/3.5-avl.h labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(AVL_SOURCES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.5-avl: build/3.5-avl
	./build/3.5-avl

# 3.6 — удаление из АВЛ
AVL_DELETE_SOURCES = labs/3.6-avl-delete/3.6-main.c labs/3.6-avl-delete/3.6-avl-delete.c labs/3.6-avl-delete/3.6-preview.c $(AVL_CORE) $(AVL_SVG) $(VIEWER)

build/3.6-avl-delete: $(AVL_DELETE_SOURCES) labs/3.6-avl-delete/3.6-avl-delete.h labs/3.5-avl/3.5-avl.h labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(AVL_DELETE_SOURCES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.6-avl-delete: build/3.6-avl-delete
	./build/3.6-avl-delete

# 3.7 — двоичное Б-дерево
DBD_SOURCES = labs/3.7-dbd/3.7-main.c labs/3.7-dbd/3.7-dbd.c labs/3.7-dbd/3.7-compare.c labs/3.7-dbd/3.7-svg.c $(AVL_CORE) $(VIEWER)

build/3.7-dbd: $(DBD_SOURCES) labs/3.7-dbd/3.7-dbd.h labs/3.5-avl/3.5-avl.h labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DBD_SOURCES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.7-dbd: build/3.7-dbd
	./build/3.7-dbd

# 3.8 — точный ДОП
DOP_CORE = labs/3.8-dop/3.8-dop.c labs/3.8-dop/3.8-common.c labs/3.8-dop/3.8-tree.c labs/3.8-dop/3.8-svg.c
DOP_SOURCES = labs/3.8-dop/3.8-main.c labs/3.8-dop/3.8-compare.c $(DOP_CORE) $(VIEWER)

build/3.8-dop: $(DOP_SOURCES) labs/3.8-dop/3.8-dop.h labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DOP_SOURCES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.8-dop: build/3.8-dop
	./build/3.8-dop

# 3.9 — приближённые А1 и А2
A1A2_SOURCES = labs/3.9-a1-a2/3.9-main.c labs/3.9-a1-a2/3.9-a1-a2.c labs/3.9-a1-a2/3.9-compare.c $(DOP_CORE) $(VIEWER)

build/3.9-a1-a2: $(A1A2_SOURCES) labs/3.9-a1-a2/3.9-a1-a2.h labs/3.8-dop/3.8-dop.h labs/lab-viewer.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(A1A2_SOURCES) $(LDFLAGS) $(LDLIBS) $(VIEWER_LIBS) -o $@

run-3.9-a1-a2: build/3.9-a1-a2
	./build/3.9-a1-a2
