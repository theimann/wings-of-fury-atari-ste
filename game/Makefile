# =============================================================================
#	Wings of Fury STE - prototype (level scroll + flyable Hellcat)
# =============================================================================
# AGTROOT: the AGT tree with agt-patch/agtools-local.patch applied (default: ../../agtools, beside this repository)
ifeq ($(AGTROOT),)
AGTROOT := ../../agtools
endif
$(info $$AGTROOT is [${AGTROOT}])

# CROSS_MINT: where the m68k-atari-mint toolchain is installed (AGT's makedefs.mintgcc says /opt/cross-mint;
# $HOME/cross-mint is used when it exists). PYTHON: a Python 3 with Pillow (a venv in ../.venv is used when it exists).
ifeq ($(CROSS_MINT),)
ifneq ($(wildcard $(HOME)/cross-mint/bin),)
CROSS_MINT := $(HOME)/cross-mint
endif
endif
ifneq ($(CROSS_MINT),)
override TOOLCHAIN_INSTALL := $(CROSS_MINT)
override TOOLCHAIN_PREFIX := $(CROSS_MINT)/bin/m68k-atari-mint-
endif
ifeq ($(PYTHON),)
PYTHON := $(firstword $(wildcard ../.venv/bin/python ../../tools/venv/bin/python) python3)
endif
export PYTHON

PROJECT := wof
BUILD_CFG = release
REMOTE_PRG = wof.prg
AGLIB=$(AGLIB_STE)
AGLIB_OBJ=$(AGLIB_STE_OBJ)
PACK=${AGTROOT}/scripts/pack.sh
REBUILD_COLMAPS = no
USE_HATARI_NATFEATS = no
POST_UPX_PACKER = no

PRODUCT_DISK1 := ./disk1
IMAGES := ./images

COMPILERDEFS += \
		-DAGT_CONFIG_WORLD_XMAJOR \
		-DAGT_CONFIG_PACKER_ANY \
		-DAGT_CONFIG_QUIET \
		-DAGT_CONFIG_ENTITYLAYERS=4 \
		-DAGT_CONFIG_WORLDMAP_POSTPAD=2 \
		$(WOF_EXTRA_DEFS)

# The split screen runs on the standard 200-line display (AGT_CONFIG_NICKEL_NOTOP, a local AGT patch).
COMPILERDEFS += -DAGT_CONFIG_NICKEL_NOTOP

# build the diagnostic variant with: make diag   (-> disk1/WOFDIAG.PRG)

PROJECT_SRC_LIST =
PROJECT_INC_LIST =
PALETTE_SOURCES =

# map letters built into the disk (tools/make_proto_assets.py writes level_<x>.png + map_<x>.dat for each)
MAPS ?= a b c d e f g h i j k l m n o

COM_SRC = source_assets
SOURCE_ASSETS_COMMON = \
	$(foreach m,$(MAPS),${COM_SRC}/level_$(m).png ${COM_SRC}/map_$(m).dat) \
	${COM_SRC}/hellcat.png \
	${COM_SRC}/wheels.png \
	${COM_SRC}/torp.png \
	${COM_SRC}/elev.png \
	${COM_SRC}/gmov.png \
	${COM_SRC}/fx.png \
	${COM_SRC}/crew.png \
	${COM_SRC}/hud.png \
	${COM_SRC}/panel.png \
	${COM_SRC}/panelspr.png \
	${COM_SRC}/sepbar.png \
	${COM_SRC}/mini.png \
	${COM_SRC}/flags.png \
	${COM_SRC}/soldiers.png \
	${COM_SRC}/guns.png \
	${COM_SRC}/weapons.png \
	${COM_SRC}/zeros.png \
	${COM_SRC}/zmini.png \
	${COM_SRC}/font.png \
	${COM_SRC}/tfont.png

ASSETS_COMMON = \
	$(foreach m,$(MAPS),$(ASSETS)/level_$(m).ccm $(ASSETS)/level_$(m).cct $(ASSETS)/map_$(m).dat) \
	$(ASSETS)/hellcat.spr \
	$(ASSETS)/wheels.spr \
	$(ASSETS)/torp.spr \
	$(ASSETS)/elev.spr \
	$(ASSETS)/gmov.spr \
	$(ASSETS)/fx.spr \
	$(ASSETS)/crew.spr \
	$(ASSETS)/hud.spr \
	$(ASSETS)/panel.ccm \
	$(ASSETS)/panel.cct \
	$(ASSETS)/panelspr.spr \
	$(ASSETS)/sepbar.emx \
	$(ASSETS)/mini.spr \
	$(ASSETS)/flags.spr \
	$(ASSETS)/soldiers.spr \
	$(ASSETS)/guns.spr \
	$(ASSETS)/weapons.spr \
	$(ASSETS)/zeros.spr \
	$(ASSETS)/zmini.spr \
	$(ASSETS)/font.spr \
	$(ASSETS)/tfont.spr \
	$(ASSETS)/broder.pic \
	$(ASSETS)/title.pic \
	$(ASSETS)/credits.pic \
	$(ASSETS)/rank.pic \
	$(ASSETS)/brief.pic \
	$(ASSETS)/hiscore.pic \
	$(ASSETS)/intro.dat \
	$(ASSETS)/music.dat

include $(AGTROOT)/makedefs

all: disk1

DISK1_BINARY = $(BUILD_DIR)/wof.prg
DISK1_ASSETS = $(ASSETS_COMMON)
DISK1_FILES = $(DISK1_ASSETS:$(ASSETS)/%=%)

disk1: $(CACHE)/disk1.tag
.PHONY: disk1

$(CACHE)/disk1.tag: $(DISK1_BINARY) $(DISK1_ASSETS)
	@echo "GENERATING DISK $(PRODUCT_DISK1)"
	@mkdir -p $(CACHE)
	@mkdir -p $(PRODUCT_DISK1)/auto
	cp -r $(DISK1_BINARY) $(PRODUCT_DISK1)/auto/.
	$(if $(strip $(DISK1_FILES)),$(AGTROOT)/scripts/copyassets.sh $(ASSETS) "$(DISK1_FILES)" ../$(PRODUCT_DISK1)/)
	@touch $(CACHE)/disk1.tag

$(CACHE)/assets_common.tag: $(CACHE)/asset_tree.tag $(SOURCE_ASSETS_COMMON)
	@echo "BUILDING COMMON ASSETS: $(PROJECT)"
	AGTROOT=$(AGTROOT) MAPS="$(MAPS)" ./assets_com.sh
	@touch $(CACHE)/assets_common.tag

$(ASSETS_COMMON): $(CACHE)/assets_common.tag

assets_common: $(ASSETS_COMMON)
.PHONY: assets_common

$(CACHE)/asset_tree.tag:
	@mkdir -p $(ASSETS)
	@mkdir -p $(CACHE)
	@touch $(CACHE)/asset_tree.tag

assets: assets_common
.PHONY: assets

# scripted-input build for automated runs in Hatari (tools/hatari_play.py): make play -> disk1/WOFPLAY.PRG
play:
	$(MAKE) BUILD_DIR=build_play USE_HATARI_NATFEATS=yes WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_HDIAG -DWOF_REPLAY -DAGT_CONFIG_HATARI_DEBUG" build_play/wof.prg
	cp build_play/wof.prg $(PRODUCT_DISK1)/WOFPLAY.PRG
.PHONY: play

# scripted runs on the real machines (docs/BUILDING.md, "Scripted runs on real machines"): make runs ->
# disk1/WOFRUN.PRG; the run log goes to RUNS/RUN<n>.LOG (REPLAY.LOG with a REPLAY.TXT); padded to an even length
# (the SidecarTridge's GEMDRIVE loader gets the last byte of odd-sized files wrong)
runs:
	$(MAKE) BUILD_DIR=build_runs WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_REPLAY -DWOF_RUNLOG" build_runs/wof.prg
	cp build_runs/wof.prg $(PRODUCT_DISK1)/WOFRUN.PRG
	[ $$(( $$(wc -c < $(PRODUCT_DISK1)/WOFRUN.PRG) % 2 )) = 0 ] || printf '\0' >> $(PRODUCT_DISK1)/WOFRUN.PRG
.PHONY: runs

# the game with a live frame profile on an ATW800/2 card's output (Mega STE / TT with the card; the atw-snoop library,
# github.com/theimann/atw-snoop, path in ATWSNOOP): make atw -> disk1/WOFATW.PRG
ATWSNOOP ?= ../../atw-snoop/src
# (the library comes in through snoop_wof.c, which make does not see: a newer atwsnoop.c or .h rebuilds it and relinks)
atw:
	@for f in $(ATWSNOOP)/atwsnoop.c $(ATWSNOOP)/atwsnoop.h $(ATWSNOOP)/snoopprog.h; do [ ! -f build_atw/wof.prg ] || [ ! $$f -nt build_atw/wof.prg ] || rm -f build_atw/snoop_wof.o build_atw/wof.prg; done
	$(MAKE) BUILD_DIR=build_atw WOF_EXTRA_DEFS="-DWOF_ATWSNOOP -I$(abspath $(ATWSNOOP))" PROJECT_SRC_LIST=snoop_wof.c build_atw/wof.prg
	cp build_atw/wof.prg $(PRODUCT_DISK1)/WOFATW.PRG
	[ $$(( $$(wc -c < $(PRODUCT_DISK1)/WOFATW.PRG) % 2 )) = 0 ] || printf '\0' >> $(PRODUCT_DISK1)/WOFATW.PRG
.PHONY: atw
# SCRIPTED.PRG: plays every RUNS\RUN<n>.TXT with RUNS\RUN.PRG (the run build), one after another, without arguments
# (wofruns.c; the debug folder's layout: README_DBG.TXT)
# libcmini (github.com/freemint/libcmini, built): its start-up gives back all memory but the program's own, so the
# runs get the rest (with MiNTLib's start-up the game hung while setting up). Path in CMINI (tools/env.sh, local.env)
CMINI ?= ../../libcmini
wofruns:
	m68k-atari-mint-gcc -m68000 -O2 -s -nostdlib -I$(CMINI)/include -o $(PRODUCT_DISK1)/SCRIPTED.PRG $(CMINI)/lib/startup.o wofruns.c -L$(CMINI)/lib -lcmini -lgcc
.PHONY: wofruns
# the same with the scripted runs and the run log (make runs): make atwrun -> disk1/WOFATWR.PRG; on the card it runs as
# /WOFRUN/WOFRUN.PRG (deploy_ste.sh --run=<n> --atw), so the scripts and logs stay where they are
atwrun:
	@for f in $(ATWSNOOP)/atwsnoop.c $(ATWSNOOP)/atwsnoop.h $(ATWSNOOP)/snoopprog.h; do [ ! -f build_atwrun/wof.prg ] || [ ! $$f -nt build_atwrun/wof.prg ] || rm -f build_atwrun/snoop_wof.o build_atwrun/wof.prg; done
	$(MAKE) BUILD_DIR=build_atwrun WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_REPLAY -DWOF_RUNLOG -DWOF_ATWSNOOP -I$(abspath $(ATWSNOOP))" PROJECT_SRC_LIST=snoop_wof.c build_atwrun/wof.prg
	cp build_atwrun/wof.prg $(PRODUCT_DISK1)/WOFATWR.PRG
	[ $$(( $$(wc -c < $(PRODUCT_DISK1)/WOFATWR.PRG) % 2 )) = 0 ] || printf '\0' >> $(PRODUCT_DISK1)/WOFATWR.PRG
.PHONY: atwrun

# the run build with section markers for timing frames in Hatari (tools/hatari_frames.py): make prof -> disk1/WOFPROF.PRG
prof:
	$(MAKE) BUILD_DIR=build_prof WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_REPLAY -DWOF_RUNLOG -DWOF_PROFMARK" build_prof/wof.prg
	cp build_prof/wof.prg $(PRODUCT_DISK1)/WOFPROF.PRG
.PHONY: prof

# the run build with the per-frame effect functions not inlined, for CPU profiles by function (PROF_NOINL in wof.cpp;
# tools/hatari_run.py --profile --prg WOFPROFN.PRG, tools/prof_report.py --build game/build_profn)
profn:
	$(MAKE) BUILD_DIR=build_profn WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_REPLAY -DWOF_RUNLOG -DWOF_NOINLINE" build_profn/wof.prg
	cp build_profn/wof.prg $(PRODUCT_DISK1)/WOFPROFN.PRG
.PHONY: profn

# the run build with a test of the sound mixer against the former one at the start (MIXTEST line in the run log)
mixtest:
	$(MAKE) BUILD_DIR=build_mixt WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_REPLAY -DWOF_RUNLOG -DWOF_MIXTEST" build_mixt/wof.prg
	cp build_mixt/wof.prg $(PRODUCT_DISK1)/WOFMIXT.PRG
.PHONY: mixtest

# Hatari variant of the diagnostic build (NatFeats output into Hatari's log): make hdiag -> disk1/WOFHDIAG.PRG
hdiag:
	$(MAKE) BUILD_DIR=build_hdiag USE_HATARI_NATFEATS=yes WOF_EXTRA_DEFS="-DWOF_DIAG -DWOF_HDIAG -DAGT_CONFIG_HATARI_DEBUG" build_hdiag/wof.prg
	cp build_hdiag/wof.prg $(PRODUCT_DISK1)/WOFHDIAG.PRG
.PHONY: hdiag

# flicker diagnostics: plain 200-line screen without Nickel (playfield only) -> disk1/WOFPLAIN.PRG; playplain: the same
# as a replay build for Hatari (replaces disk1/WOFPLAY.PRG until the next make play)
plain:
	$(MAKE) BUILD_DIR=build_plain WOF_EXTRA_DEFS="-DWOF_PLAIN" build_plain/wof.prg
	cp build_plain/wof.prg $(PRODUCT_DISK1)/WOFPLAIN.PRG
.PHONY: plain
playplain:
	$(MAKE) BUILD_DIR=build_playplain USE_HATARI_NATFEATS=yes WOF_EXTRA_DEFS="-DWOF_PLAIN -DWOF_DIAG -DWOF_HDIAG -DWOF_REPLAY -DAGT_CONFIG_HATARI_DEBUG" build_playplain/wof.prg
	cp build_playplain/wof.prg $(PRODUCT_DISK1)/WOFPLAY.PRG
.PHONY: playplain

diag:
	rm -f $(BUILD_DIR)/wof.o $(BUILD_DIR)/wof.prg
	$(MAKE) WOF_EXTRA_DEFS=-DWOF_DIAG $(BUILD_DIR)/wof.prg
	cp $(BUILD_DIR)/wof.prg $(PRODUCT_DISK1)/WOFDIAG.PRG
	rm -f $(BUILD_DIR)/wof.o $(BUILD_DIR)/wof.prg
	$(MAKE) $(BUILD_DIR)/wof.prg
.PHONY: diag

include $(AGTROOT)/makerules

# generated headers: wof.o must be rebuilt when they change (make does not see #include dependencies here)
# build identification (tools/version.sh), rewritten only when it changes
version.h: FORCE
	@echo '#define WOF_VERSION "'"$$(../tools/version.sh)"'"' > version.h.tmp; \
	if cmp -s version.h.tmp version.h; then rm version.h.tmp; else mv version.h.tmp version.h; fi
FORCE:
.PHONY: FORCE

$(BUILD_DIR)/wof.o build_psnd/wof.o build_snd/wof.o build_playsnd/wof.o build_play/wof.o build_runs/wof.o build_prof/wof.o build_profn/wof.o build_mixt/wof.o build_hdiag/wof.o build_plain/wof.o build_playplain/wof.o: flight_data.h flash_data.h snd_data.h snd.h version.h
