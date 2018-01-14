frm2png [![Build Status](https://travis-ci.org/falltergeist/frm2png.svg?branch=develop)](https://travis-ci.org/falltergeist/frm2png) [![Version](https://img.shields.io/github/release/falltergeist/frm2png.svg)](https://github.com/falltergeist/frm2png/releases/latest) [![Discord](https://img.shields.io/discord/401990446747877376.svg)](https://discord.gg/jxs6WRq)
==================
*.frm to *.png converter for Fallout 1/2 data files.


Installation:
=============

Ubuntu
------

```bash
sudo add-apt-repository ppa:falltergeist/falltergeist
sudo apt-get update
sudo apt-get install frm2png
```

Compilation from source:
============

Dependencies:
-------------

- CMake >= 2.8
- libpng >= 1.2 

Build:

```bash
mkdir build && cd build && cmake .. && make
```

Usage:
======

```bash
./frm2png PATH_TO_FILE.frm
```

Converted file will be saved as PATH_TO_FILE.png
