CC      = i686-w64-mingw32-gcc
SDL     = third_party/SDL3-3.4.18/i686-w64-mingw32
OUT     = build/pc

GAME_CFLAGS = -std=gnu89 -O0 -g -fcommon -fno-strict-aliasing -fwrapv -Igame/include -include port/port.h \
              -w
PORT_CFLAGS = -std=gnu11 -O2 -g -fno-omit-frame-pointer -Wall -Wno-unused -I$(SDL)/include -Iport
LDFLAGS     = -L$(SDL)/lib -lSDL3 -lwinmm -mconsole -Wl,--disable-dynamicbase

GAME_SRC = $(wildcard game/src/*.c)
PORT_SRC = $(wildcard port/*.c)
GAME_OBJ = $(patsubst game/src/%.c,$(OUT)/game/%.o,$(GAME_SRC))
PORT_OBJ = $(patsubst port/%.c,$(OUT)/port/%.o,$(PORT_SRC))
GEN_OBJ  = $(OUT)/gen/a5globals.o $(OUT)/gen/a5swap.o $(OUT)/port/link_res.o

all: $(OUT)/link.exe $(OUT)/SDL3.dll

build/gen/a5globals.s build/gen/a5swap.c: tools/gen_globals.py config/symbols.txt $(wildcard game/include/*.h) $(GAME_SRC)
	python3 tools/gen_globals.py

$(OUT)/game/%.o: game/src/%.c game/include/game.h game/include/version.h port/port.h
	@mkdir -p $(dir $@)
	$(CC) $(GAME_CFLAGS) -c $< -o $@

$(OUT)/port/%.o: port/%.c $(wildcard port/*.h)
	@mkdir -p $(dir $@)
	$(CC) $(PORT_CFLAGS) -c $< -o $@

$(OUT)/gen/a5globals.o: build/gen/a5globals.s
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@

$(OUT)/port/link_res.o: port/link.rc port/link.ico
	@mkdir -p $(dir $@)
	i686-w64-mingw32-windres -I port $< -o $@

$(OUT)/gen/a5swap.o: build/gen/a5swap.c
	@mkdir -p $(dir $@)
	$(CC) -O2 -c $< -o $@

$(OUT)/link.exe: $(GAME_OBJ) $(PORT_OBJ) $(GEN_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OUT)/SDL3.dll: $(SDL)/bin/SDL3.dll
	cp $< $@

REL := build/release/link-faces-of-evil-pc

release: all
	rm -rf build/release
	mkdir -p $(REL)
	i686-w64-mingw32-strip -o $(REL)/link.exe $(OUT)/link.exe
	cp $(OUT)/SDL3.dll README.md $(REL)/
	cp $(SDL)/../LICENSE.txt $(REL)/SDL3-LICENSE.txt
	cd build/release && python3 -c "import shutil; shutil.make_archive('link-faces-of-evil-pc', 'zip', '.', 'link-faces-of-evil-pc')"

clean:
	rm -rf build/pc build/gen build/release

.PHONY: all clean release
