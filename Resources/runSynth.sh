#!/bin/bash
cd /home/pi/openFrameworks/apps/rPi_synth/rPi_Framework
sudo make RunRelease &
cd ..
cd rPi_videoSynth
sudo make RunRelease
