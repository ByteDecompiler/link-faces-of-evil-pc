# Link: The Faces of Evil PC Port

```diff
- WARNING! -
This repository doesn't include any game data. To play you need your own copy of the game, as a disc image.
```

This is a **PC port** of ***Link: The Faces of Evil*** ((Philips CD-i, 1993)), built from the [Link: The Faces of Evil decompilation](https://github.com/ByteDecompiler/link-faces-of-evil). The game's own C code runs natively on Windows, and the CD-i's hardware ((video planes, sound, disc playback, the pointer)) is rewritten on top of SDL3. It's not an emulator: there is no CD-i BIOS and no 68000 CPU, except for a tiny interpreter for the enemy graphics, which are stored on the disc as 68000 code.

Its still early. It plays the Philips logo, the title, the menu, the cutscenes and the world map, and you can walk around the rooms and fight. Expect bugs.

## Playing

1. Build it ((see below)) or get `link.exe` and `SDL3.dll`.
2. Put your disc image next to `link.exe` or in a `disc` folder beside it. It has to be a raw image with 2352-byte sectors, the usual `.bin`/`.cue` rip. You can also drag the `.bin` onto `link.exe`.
3. Run `link.exe`.

Controls:

- Move: arrow keys or WASD, a gamepad's d-pad or left stick, or the mouse
- Button 1 ((sword, select)): Z, Space, J or Enter, gamepad A, left mouse button
- Button 2 ((item)): X, Ctrl or K, gamepad B or X, right mouse button
- Esc ((or Start)): the settings menu, the game pauses while its open
- P: pause
- Tab ((or the right shoulder button)): hold to fast-forward
- F5: quick save, F9: quick load, F6 and F7: pick the quick save slot ((1 to 9))
- F12: screenshot

Every key and gamepad button can be changed in the menu, under Controls.

Display:

- F2: pixels. Sharp ((crisp pixels that all come out the same size, the default)), nearest ((plain blocky pixels)) or smooth ((blurred, like a TV))
- F3: shape. TV ((4:3, like on a CD-i, where the pixels are a bit taller than wide)) or square pixels
- F4: whole-number scaling. With square pixels and this on, every pixel is exactly the same size on screen
- F11 or Alt+Enter: fullscreen

The menu also has vsync ((on by default, it stops the picture tearing. The game still runs at the CD-i's speed of 59.94 frames a second, on any screen)), scanlines, a CRT look ((a curved screen that gets darker at the edges, and the red, green and blue stripes of a TV, each can be turned on seperately)), the music, effects and voice volumes, pausing when the window isn't in front, and filling the 2 black lines the CD-i leaves at the top of the screen. All settings are saved in `link_port.ini` next to `link.exe`, and the window remembers its size and place. The mouse pointer hides itself when you're not using the mouse.

Saves go in a `saves` folder next to `link.exe`: the game's own saves, and the quick saves ((`quick1.state` to `quick9.state`)). The menu shows the slot and when it was saved. A quick save only loads into the same build of `link.exe`.

Screenshots go in a `screenshots` folder, as PNGs of the picture the way you see it ((with the scanlines and CRT look if they're on)).

## Cutscene colour fix

In a bunch of cutscenes Link's hair is plain brown instead of the yellow-brown he has everywhere else, and his belt is grey-black or brown instead of the dark green from the intro and the ending. Turn on "Fix cutscene colours" in the menu and he looks the same in all of them. Its off by default so you see the cutscenes as they were.

## Play as Zelda

If you also have *Zelda: The Wand of Gamelon*, you can play Link's game as Zelda. Put her disc image next to `link.exe` or in the `disc` folder too ((any version works: English, French, German or Dutch)), or write where it is in `link_port.ini` as `zelda_disc = <path to the .bin>`. Then pick "Hero: Zelda" in the menu. You can switch back and forth at any time.

Both games run on the same engine and the heroes are made the same way: 24 pictures in the same order for the same poses, with the same animations and the same colours. So the port reads Zelda's pictures and her hit areas off her disc and swaps them in for Link's. Nothing else changes: the cutscenes, the voices and the story are still Link's.

## Building

You need WSL ((or Linux)) with:

1. `make` and Python 3
2. The 32-bit MinGW compiler: `sudo apt install gcc-mingw-w64-i686`
3. SDL3's MinGW files ((`SDL3-devel-<version>-mingw.tar.gz` from the SDL releases)) unpacked into `third_party/`, so that `third_party/SDL3-3.4.18/i686-w64-mingw32` exists.

Then run `make`. If all goes well you get `build/pc/link.exe` and `build/pc/SDL3.dll`.

`make release` makes `build/release/link-faces-of-evil-pc.zip` to share: `link.exe` without its debug info, `SDL3.dll`, this README and SDL's license.

The port is 32-bit on purpose: the game keeps addresses in 32-bit longs all over the place, just like it did on the CD-i.

## How it works

- `game/` has the decomp's C code with a few changes for the PC.
- `port/` is the stand-in for the CD-i:
  - `main.c` runs the game in its own thread and sends it signals, like the CD-i's interrupts
  - `mem.c` sets up the game's memory and its globals, with their starting values taken from the program on your disc
  - `video.c` does what the CD-i's video chip does with the game's display tables ((two planes, CLUT7, RL7 and DYUV pictures, fades))
  - `play.c` streams the game's real-time files off the disc, `disc.c` reads the image
  - `audio.c` decodes the CD-i's ADPCM sound
  - `gap.c` has C versions of the game's hand-written assembly ((sprite and font drawing))
  - `m68k.c` runs the compiled enemy sprites
  - `logo.c` plays the Philips logo ((on the CD-i a seperate program, cdi_bumper))
  - `display.c`, `menu.c` and `settings.c` are the window, the settings menu and `link_port.ini`
  - `state.c` is the quick save
  - `hero.c` is the "play as Zelda" mod
  - `fixes.c` and `recolor.c` are the cutscene colour fix
- `tools/gen_globals.py` lays out the globals at their original offsets.

The CD-i is big-endian and the PC isn't. Data from the disc stays big-endian in memory, and the structs that look at it are marked `BIG_ENDIAN_DATA` so the compiler reads them the right way round.

## Project Structure

```
FacesOfEvil_port
├── config: the decomp's symbol list (where each global lives)
├── game
│   ├── include: the decomp's headers
│   └── src: the decomp's C code
├── port: the CD-i stand-in
├── third_party: SDL3 (not included)
└── tools: build helpers
```
