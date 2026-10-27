Wings of Fury - atw-snoop reference build
=========================================

This is not a release of the game. It is a reference build showing how
atw-snoop is used: a live frame profile of a running game on the second
video output of an ATW800/2 card (Mega STE or TT), at almost no cost to
the game. Source and documentation: github.com/theimann/atw-snoop
The game itself: www.atari.love/wof

The game runs on the Atari's own screen; the card's output shows where
each frame's time goes. Without the card it runs as the normal game.

WOF.PRG       Play the game yourself, with the profile on the card.

SCRIPTED.PRG  Watch: plays all scripted runs one after another by
              itself (no keys needed). Between two runs it waits
              3 seconds; Esc there ends the series. Ctrl+Q ends the
              current run. Each run writes its log to RUNS\RUN<n>.LOG.

WOF.DAT       All the game's data in one archive.
RUNS\         The scripted runs (RUN1.TXT ...), their logs and saves,
              and RUN.PRG, which SCRIPTED.PRG starts for each run.

Ctrl+Q quits the game to the desktop.
Known issue (Mega STE): after a resolution change the picture can come up
garbled in 16-pixel blocks at random; a cold boot clears it.
