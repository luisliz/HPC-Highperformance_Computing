#!/bin/sh	
mpiexec -np 24 bt.A.x > bt.A.res.txt
mpiexec -np 24 bt.B.x > bt.B.res.txt
mpiexec -np 24 bt.C.x > bt.C.res.txt
mpiexec -np 24 sp.A.x > sp.A.res.txt
mpiexec -np 24 sp.B.x > sp.B.res.txt
mpiexec -np 24 sp.C.x > sp.C.res.txt
