# PocketTunes firmware — openfpgaOS custom core for the Analogue Pocket.
#
#   make              Build the app and assemble the SD card tree in build/pocket/
#   make copy         Build, then copy the core to the Pocket's SD card
#   make test         Build and run on the desktop (SDL2), no Pocket needed
#   make clean        Remove build output
#
#   make UI_SCALE=1   Original 320x240 look (default is the crisp 640x480)
#
# The openfpgaOS SDK is a git submodule pinned to the exact release the
# shipped core was built against (os.bin / os25.rbf_r / loader.bin match).

APP       = pockettunes
CORE_ID   = DapperLogic.PocketTunes
UI_SCALE ?= 2

SDK_ROOT ?= openfpgaSDK
SDK_DIR   = $(SDK_ROOT)/src/sdk
RUNTIME   = $(SDK_ROOT)/runtime/pocket
OBJ_DIR   = build/obj
BUILD_DIR = $(OBJ_DIR)
OUT       = build/pocket/$(APP)

SRCS   = $(wildcard src/*.c)
CFLAGS = -Isrc -DUI_SCALE=$(UI_SCALE)

.DEFAULT_GOAL := all

$(SDK_DIR)/sdk.mk:
	@echo "openfpgaSDK submodule missing; run: git submodule update --init" && exit 1

include $(SDK_DIR)/sdk.mk

ELF = $(OBJ_DIR)/app.elf

all: $(ELF) release
	@$(SIZE) $(ELF)

# Pocket SD layout: Cores/<id>/ (json + bitstream + loader), Assets/<platform>/
# common/ (os.bin, sound bank, app ELF), Platforms/<platform>.json.
release: $(ELF)
	@rm -rf $(OUT) && mkdir -p $(OUT)
	@cp -R dist/. $(OUT)/
	@cp $(RUNTIME)/os25.rbf_r $(RUNTIME)/loader.bin $(OUT)/Cores/$(CORE_ID)/
	@mkdir -p $(OUT)/Assets/$(APP)/common
	@cp $(RUNTIME)/os.bin $(SDK_ROOT)/runtime/bank.ofsf $(OUT)/Assets/$(APP)/common/
	@cp $(ELF) $(OUT)/Assets/$(APP)/common/$(APP).elf
	@echo "Ready: $(OUT)/"

# Copy to the SD card (auto-detected, or pass SD=/Volumes/NAME).
SD ?= $(firstword $(foreach v,$(wildcard /Volumes/*),$(if $(wildcard $(v)/Cores $(v)/Analogue_Pocket.json),$(v))))
copy: all
	@test -n "$(SD)" || { echo "No Pocket SD card found; pass SD=/Volumes/NAME"; exit 1; }
	@cp -R $(OUT)/Cores/. "$(SD)/Cores/"
	@cp -R $(OUT)/Assets/. "$(SD)/Assets/"
	@cp -R $(OUT)/Platforms/. "$(SD)/Platforms/"
	@sync
	@echo "Copied to $(SD). Eject and boot the Pocket."

# Desktop build: the SDK's SDL2 layer stands in for the Pocket's video,
# audio and input. The player runs from MUSIC_DIR, a folder laid out like
# music.iso (playlist.tsv, the MP3s, art/). Defaults to a generated test
# library; point it at your own: make test MUSIC_DIR=~/Music/pocket
MUSIC_DIR ?= testlib
DESKTOP   = build/pockettunes-desktop
test: $(DESKTOP) $(if $(filter testlib,$(MUSIC_DIR)),testlib/playlist.tsv)
	cd "$(MUSIC_DIR)" && "$(CURDIR)/$(DESKTOP)"

# Own rule rather than the SDK's app_pc: that one is Linux-only (it pulls
# in of_init.c, which needs <sys/auxv.h>). The SDL shim does #include_next
# <SDL2/SDL.h>, so SDL's parent include dir must be on the path.
SDL_PREFIX := $(shell sdl2-config --prefix 2>/dev/null)
$(DESKTOP): $(SRCS) $(wildcard src/*.h) $(SDK_DIR)/pc/of_sdl2.c
	@mkdir -p $(dir $@)
	$(PC_CC) -DOF_PC -O2 -Wall -Wextra -I$(SDK_DIR)/include $(CFLAGS) \
		$(SRCS) $(SDK_DIR)/pc/of_sdl2.c \
		$(SDL_CFLAGS) -I$(SDL_PREFIX)/include $(SDL_LIBS) -lm -o $@

testlib/playlist.tsv:
	scripts/make_testlib.sh testlib

clean: sdk-clean
	rm -rf build app_pc testlib

.PHONY: all release copy test clean
