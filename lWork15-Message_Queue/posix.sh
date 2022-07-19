#!/bin/bash
rm ./posix-1
rm ./posix-2

gcc ./posix-1.c -o posix-1 -lrt
gcc ./posix-2.c -o posix-2 -lrt

# setcap 'cap_ipc_owner+pe' ./systemV-1
# setcap 'cap_ipc_owner+pe' ./systemV-2

# tmux new-session -d htop

tmux new-session -d sudo ./posix-1
tmux split-window -h sudo ./posix-2
tmux selectp -t 0
tmux attach-session