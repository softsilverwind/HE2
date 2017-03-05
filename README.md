# Holy Empire Training Grounds 2

## Overview

This game is a simple game inspired by "Gorillas" distributed with MS-DOS.
It is also the simplest playable testcase for the Starlia engine.

The first game of the series (HE Training Grounds) was written in Visual Basic 6,
in Windows forms. I decided to recreate my game using openGL, as it seemed a good
starting point to actually learn openGL.

This game is licenced under GNU General Public Licence version 3 or later.

## Build and Usage

Unfortunately I either have to do some digging to find the correct changeset of
(openGL 1) Starlia, or should port this to the latest version of (openGL 2+)
Starlia (which does not support many things, e.g. sounds). Both solutions need
significant amount of work :)

## Changelog

* 0.1 : 1.00-alpha1 codename Turtle

initial version, very simple collision detection, no explosions, only way to
win is to hit the enemy directly.

* 0.2 : 1.00-alpha2 codename Firebug

added an explosion effect using a simple particle engine.

* 0.3 : 1.00-alpha3 codename Tzitziki

added an explosion sound using openAL.

* 0.4 : 1.00-alpha4 codename Cross

	1. deleted openAL code as it was not clean (and also failed on Windows)
	1. cross-compiled for Windows

* 0.41 : 1.00-alpha4-1

	1. changed the particle engine a bit

* 0.45 : 1.00-alpha5 codename Re-F\*ck-Tor

	1. performed major refactoring on the game engine and classes
	1. fitted a new display engine to all the animations
	1. fitted a new particle engine
	1. added rain

* 0.5 : 1.00-beta1 codename You can reach the stars:

	1. 1st public release! (To friends of course :) )
	1. HE2 has been fully ported to Starlia, no overrides. This means that Starlia
	1. must be installed before compiling.
	1. HE2 now uses the widget scheme of Starlia, which is a bit underwhelming.
	1. Since Starlia is for now toy game engine (not even alpha yet), and since many
	1. API/ABI breaks are bound to happen, see HE2 as the best benchmark for Starlia,
	1. and not something that is going to be the way it is now :)
	1. added main menu
	1. added labels, rendering command line prints useless
	1. added in-game menu
	1. now cannon fires at the point clicked, not at the last pointed position
	1. various bugfixes and polishes
