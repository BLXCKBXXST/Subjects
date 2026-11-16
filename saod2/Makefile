CC = gcc
CFLAGS ?= -std=c11 -O2

PROGRAMS = coursework records tree tree100 isdp isdp-iterative search search-old sdp sdp-iterative sdp-repeat sdp-repeat-iterative sdp-delete 3.5-avl 3.6-avl-delete 3.7-dbd 3.8-dop 3.9-a1-a2
ISDP_COMMON = labs/isdp/main.c labs/isdp/compare.c labs/isdp/treeprint.c

.PHONY: all clean $(addprefix run-,$(PROGRAMS))
all: $(addprefix build/,$(PROGRAMS))

build:
	mkdir -p build

COURSEWORK_SOURCES = coursework/src/main.c coursework/src/sort.c coursework/src/search.c coursework/src/a2.c coursework/src/tree.c coursework/src/svg.c

build/coursework: $(COURSEWORK_SOURCES) $(wildcard coursework/src/*.h) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(COURSEWORK_SOURCES) $(LDFLAGS) $(LDLIBS) -o $@

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

# СДП: как в 3.2, поиск выбирается при компиляции
SDP_COMMON = labs/sdp/main.c labs/sdp/common.c labs/sdp/compare.c labs/sdp/treeprint.c

build/sdp: $(SDP_COMMON) labs/sdp/search.c labs/sdp/sdp.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

build/sdp-iterative: $(SDP_COMMON) labs/sdp/search_iterative.c labs/sdp/sdp.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

run-sdp: build/sdp
	./build/sdp

run-sdp-iterative: build/sdp-iterative
	./build/sdp-iterative


# СДП с повторяющимися ключами: равные элементы идут вправо
SDP_REPEAT_COMMON = labs/sdp/main_repeat.c labs/sdp/common.c labs/sdp/compare.c labs/sdp/treeprint.c

build/sdp-repeat: $(SDP_REPEAT_COMMON) labs/sdp/search.c labs/sdp/sdp.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

build/sdp-repeat-iterative: $(SDP_REPEAT_COMMON) labs/sdp/search_iterative.c labs/sdp/sdp.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

run-sdp-repeat: build/sdp-repeat
	./build/sdp-repeat

run-sdp-repeat-iterative: build/sdp-repeat-iterative
	./build/sdp-repeat-iterative

# 3.4 — удаление введённых ключей из СДП
build/sdp-delete: labs/sdp/main_delete.c labs/sdp/delete.c labs/sdp/delete_input.c labs/sdp/delete_preview.c labs/sdp/common.c labs/sdp/treeprint.c $(wildcard labs/sdp/*.h) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) -o $@

run-sdp-delete: build/sdp-delete
	./build/sdp-delete


# 3.5 — АВЛ: включение вершины
VIEWER = labs/lab-viewer.c
VIEWER_LIBS =
ifeq ($(OS),Windows_NT)
VIEWER_LIBS = -lshell32
endif

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
