#!/bin/sh	

mkdir 2T
echo "Created Dirs"

mpiexec -np 2 bt.A.x > 1T/bt.A.res.txt
mpiexec -np 2 bt.B.x > 1T/bt.B.res.txt
mpiexec -np 2 bt.C.x > 1T/bt.C.res.txt
mpiexec -np 2 sp.A.x > 1T/sp.A.res.txt
mpiexec -np 2 sp.B.x > 1T/sp.B.res.txt
mpiexec -np 2 sp.C.x > 1T/sp.C.res.txt

echo "Finished 2"
