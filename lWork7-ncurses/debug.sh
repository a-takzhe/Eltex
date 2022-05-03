#!/bin/bash
tmux splitw -h -p 50 "gdbserver :2000 ./main"
tmux selectp -t 0
gdb -x debug.gdb