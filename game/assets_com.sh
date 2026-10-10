#!/usr/bin/env bash
#==============================================================================
#	Cut prototype assets (source PNGs + flight_data.h come from wof/tools/make_proto_assets.py)
#==============================================================================
set -e
AGTROOT=${AGTROOT:-../../agtools}
OUT=assets
mkdir -p ${OUT}
SRC=source_assets
AGTBIN=${AGTROOT}/bin/`${AGTROOT}/config.sh`
GENTEMP=./build
mkdir -p ${GENTEMP}

MAPS=${MAPS:-a}
# 8-bit indexed PNGs (agtcut misreads 4-bit packed PNGs), first 16 colours used (-nr). All maps share one palette;
# the sprite sheets take it from the first map's level image.
for m in ${MAPS}; do
	${AGTBIN}/agtcut -cm tiles -om direct -bp 4 -ts 16 -t 0.0 -nr -v -p ${SRC}/level_${m}.png -o ${OUT}/level_${m}.cct -s ${SRC}/level_${m}.png
	cp ${SRC}/map_${m}.dat ${OUT}/map_${m}.dat
done
PAL=${SRC}/level_${MAPS%% *}.png

# hellcat: 108 frames (incl. muzzle flashes fa/fb) in 128x48 cells (10 per row), hotspot at cell (64,24); index 0 transparent (IMSPR: EMX would need 863KB, too much for a 2MB STE)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 128 -sys 48 -sxi 128 -syi 48 -sxc 10 -syc 11 -sc 108 \
	-o ${OUT}/hellcat.spr -s ${SRC}/hellcat.png

# wheels overlay: 20 frames in 96x32 cells, hotspot at (62,12) (the x anchors set the draw order, see the generator). IMSPR (layer 1 with the Hellcat): the EMX version
# made the STE screen flash black whenever a deck wheel frame was drawn
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 96 -sys 32 -sxi 96 -syi 32 -sxc 10 -syc 2 -sc 20 \
	-o ${OUT}/wheels.spr -s ${SRC}/wheels.png

# carrier elevator platform: one frame in a 64x16 cell, hotspot at (28,0), IMSPR (drawn directly by the game)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 64 -sys 16 -sxi 64 -syi 16 -sxc 1 -syc 1 -sc 1 \
	-o ${OUT}/elev.spr -s ${SRC}/elev.png

# 'gmov' game-over sign: one frame in a 208x24 cell, IMSPR (drawn directly by the game)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 208 -sys 24 -sxi 208 -syi 24 -sxc 1 -syc 1 -sc 1 \
	-o ${OUT}/gmov.spr -s ${SRC}/gmov.png

# torpedo slung under the plane: 57 overlay frames in the plane's 128x48 cells (same hotspot), IMSPR layer 1
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 128 -sys 48 -sxi 128 -syi 48 -sxc 10 -syc 6 -sc 57 \
	-o ${OUT}/torp.spr -s ${SRC}/torp.png

# effects: 12 bomb frames, exp0-5, spl0-6, ric0, smk0-5, 3 balloons in 48x32 cells, hotspot at (20,22)
# IMSPR in layer 1 (122 KB of memory as EMX)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 48 -sys 32 -sxi 48 -syi 32 -sxc 10 -syc 4 -sc 35 \
	-o ${OUT}/fx.spr -s ${SRC}/fx.png

# deck crew poses fgy0..fgyf: 32x16 cells, 8 per row, hotspot (17,45) (above the cell)
# IMSPR (as EMX the sheet took 70 KB of memory for a single sprite on screen; it is alone in layer 0)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 32 -sys 16 -sxi 32 -syi 16 -sxc 8 -syc 2 -sc 16 \
	-o ${OUT}/crew.spr -s ${SRC}/crew.png

# HUD: digits 0-9, rope segments 1..16 px, bomb icon in 16x8 cells (IMSPR: drawn in layer 1 with the Hellcat)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 16 -sys 8 -sxi 16 -syi 8 -sxc 10 -syc 3 -sc 27 \
	-o ${OUT}/hud.spr -s ${SRC}/hud.png

# cockpit panel (tools/make_panel.py): 320x48 tile source in the dash palette, sprites (digits, icons, gauge needles, lamp) 32x24 cells
${AGTBIN}/agtcut -cm tiles -om direct -bp 4 -ts 16 -t 0.0 -nr -v -p ${SRC}/panel.png -o ${OUT}/panel.cct -s ${SRC}/panel.png
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${SRC}/panel.png \
	-sxp 0 -syp 0 -sxs 32 -sys 24 -sxi 32 -syi 24 -sxc 10 -syc 5 -sc 50 \
	-o ${OUT}/panelspr.spr -s ${SRC}/panelspr.png

# 1/8 view sheet (8thscale): 25 player frames (lpn*) + 13 effect frames (bumb, exp0-5, spl0-3, smk0-1) + 2 soldiers (guy0/1), 32x16 cells, hotspot (16,8)
# IMSPR in layer 1 (84 KB of memory as EMX)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 32 -sys 16 -sxi 32 -syi 16 -sxc 10 -syc 4 -sc 40 \
	-o ${OUT}/mini.spr -s ${SRC}/mini.png

# separator bar: 32x8 solid (10 entities; a single 320-wide sprite crashed) index 11 (black in the panel palette, which is active on these lines);
# frame 1: a 16x1 index-11 line, drawn last in the panel pass over the black frame of the centre screen (the IMSPR panel
# sprites must not be the last thing drawn in a pass)
${AGTBIN}/agtcut -cm emxspr -nr -key 0 -emgx 32 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 32 -sys 8 -sxi 32 -syi 8 -sxc 2 -syc 1 -sc 2 \
	-o ${OUT}/sepbar.emx -s ${SRC}/sepbar.png

# (muzzle flashes: drawn from the hellcat sheet, frames 68..107)

# flags (draw_special_map_cell): flg3..6 (carrier tower, opaque), flg0..2 + POST (island) in 32x48 cells, top-left anchored.
# IMSPR (EMX would be 75 KB); safe because the EMX separator bar is always drawn last
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 32 -sys 48 -sxi 32 -syi 48 -sxc 8 -syc 1 -sc 8 \
	-o ${OUT}/flags.spr -s ${SRC}/flags.png

# island soldiers (FUN_13eee): guy0..guy7 (right), guy9..gy10 (left) in 48x16 cells, hotspot (24,10)
# IMSPR in layer 1 (56 KB of memory as EMX)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 48 -sys 16 -sxi 48 -syi 16 -sxc 8 -syc 2 -sc 16 \
	-o ${OUT}/soldiers.spr -s ${SRC}/soldiers.png

# AA guns (13d78): gun0..gun6 barrel angles, gnf0..gnf6 firing, frame 14 = 1/8-view 'expl'; 64x32 cells, hotspot (32,24)
# IMSPR in layer 1 (68 KB of memory as EMX)
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 64 -sys 32 -sxi 64 -syi 32 -sxc 8 -syc 2 -sc 15 \
	-o ${OUT}/guns.spr -s ${SRC}/guns.png

# weapons (IMSPR, layer 1): rockets rc01..rc14 / ro01..ro14, torpedo tor2 / tor7, menu 'selt' + rows rock/bomb/torp
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 112 -sys 80 -sxi 112 -syi 80 -sxc 8 -syc 6 -sc 46 \
	-o ${OUT}/weapons.spr -s ${SRC}/weapons.png

# enemy planes (japplane.shp, IMSPR, layer 1): 26 frames (jp/jt/jc attitudes, muzzle flashes, parked) in 112x48 cells,
# hotspot (56,24); 1/8 view zpn* frames (IMSPR too: 39 KB as EMX) in 32x16 cells
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 112 -sys 48 -sxi 112 -syi 48 -sxc 8 -syc 4 -sc 26 \
	-o ${OUT}/zeros.spr -s ${SRC}/zeros.png
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 32 -sys 16 -sxi 32 -syi 16 -sxc 8 -syc 2 -sc 16 \
	-o ${OUT}/zmini.spr -s ${SRC}/zmini.png

# help page font (tools/make_font.py): ASCII 32..95 in 16x10 cells, IMSPR, drawn directly
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 16 -sys 10 -sxi 16 -syi 10 -sxc 8 -syc 8 -sc 64 \
	-o ${OUT}/font.spr -s ${SRC}/font.png

# message line font (tools/make_tfont.py): ASCII 32..95, 5x7 glyphs in 16x8 cells, drawn directly over the separator bar.
# IMSPR: as EMX the sheet took 171 KB
${AGTBIN}/agtcut -cm sprites -nr -key 0 -bld ${GENTEMP} -p ${PAL} \
	-sxp 0 -syp 0 -sxs 16 -sys 8 -sxi 16 -syi 8 -sxc 8 -syc 8 -sc 64 \
	-o ${OUT}/tfont.spr -s ${SRC}/tfont.png

# start-up pictures (tools/make_pics.py): the Amiga's publisher, title and credits pictures as raw 16-colour screens
${PYTHON:-python3} ../tools/make_pics.py ../amiga-graphics ${OUT}
${PYTHON:-python3} ../tools/make_intro.py ${OUT}/intro.dat   # intro text scroller: font + text
${PYTHON:-python3} ../tools/make_music.py ${OUT}/music.dat   # menu music: songs + instruments
