#!/bin/bash
gcc ./systemV-1.c -o systemV-1
gcc ./systemV-2.c -o systemV-2

setcap 'cap_ipc_owner+pe' ./systemV-1
setcap 'cap_ipc_owner+pe' ./systemV-2

# tmux new-session -d htop

tmux new-session -d sudo ./systemV-1 ./systemV-1.c
tmux split-window -h sudo ./systemV-2 ./systemV-1.c
tmux attach-session