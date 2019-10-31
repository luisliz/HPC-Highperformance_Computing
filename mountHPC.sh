#!/bin/bash

server=129.114.109.44
mountDir=~/Desktop/HPC-VM
mkdir $mountDir
cd $mountDir
sshfs -o IdentityFile=~/.ssh/LLCloud cc@$server:/home/cc/ $mountDir -C
echo "Mounted to $mountDir"
