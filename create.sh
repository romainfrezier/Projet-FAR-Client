#!/bin/bash
SHELL=/bin/bash
p=~/Projet-FAR-Client


for i in {0..69}
do
  osascript -e 'tell app "Terminal"
      do script "
cd '"$p"'
./client '"$1"'
Toto'"$i"'
Hey"
  end tell'
done