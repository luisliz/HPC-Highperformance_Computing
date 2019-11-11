#!/bin/bash

server=129.114.109.44
mountDir=~/Desktop/HPC-VM
mkdir $mountDir
cd $mountDir
sshfs -o allow_other,defer_permissions,IdentityFile=~/.ssh/LLCloud cc@$server:/home/cc/ $mountDir 
echo "Mounted to $mountDir"
