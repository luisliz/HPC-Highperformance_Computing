Last login: Sun Oct  6 21:50:27 on ttys002
You have new mail.

 ~/Documents/Github 
 ✔  git add .
fatal: not a git repository (or any of the parent directories): .git

 ~/Documents/Github 
 ↵ 128  cd Highperformance_Computing

 ~/Documents/Github/Highperformance_Computing   master ● ? 
 ✔  ls
HW2     LICENSE

 ~/Documents/Github/Highperformance_Computing   master ● ? 
 ✔  git add .

 ~/Documents/Github/Highperformance_Computing   master ✚ 
 ✔  git commit -m "Multi processing working"
[master 42718ef] Multi processing working
 2 files changed, 9 insertions(+), 8 deletions(-)
 create mode 100644 .DS_Store

 ~/Documents/Github/Highperformance_Computing   master ↑1 
 ✔  git push
Enumerating objects: 8, done.
Counting objects: 100% (8/8), done.
Delta compression using up to 6 threads
Compressing objects: 100% (5/5), done.
Writing objects: 100% (5/5), 896 bytes | 896.00 KiB/s, done.
Total 5 (delta 2), reused 0 (delta 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/luisliz/Highperformance_Computing
   2db5340..42718ef  master -> master

 ~/Documents/Github/Highperformance_Computing   master 
 ✔ 

Session Contents Restored

Last login: Tue Oct  8 11:08:41 on console
You have new mail.

 ~/Documents/GitHub/Highperformance_Computing   master 
 ✔ 

Session Contents Restored

Last login: Tue Oct  8 18:07:48 on console
You have new mail.

 ~/Documents/GitHub/Highperformance_Computing   master 
 ✔  git pull
remote: Enumerating objects: 18, done.
remote: Counting objects: 100% (18/18), done.
remote: Compressing objects: 100% (7/7), done.
remote: Total 12 (delta 5), reused 12 (delta 5), pack-reused 0
Unpacking objects: 100% (12/12), done.
From https://github.com/luisliz/Highperformance_Computing
   42718ef..62b8d9a  master     -> origin/master
Updating 42718ef..62b8d9a
Fast-forward
 HW2/assignment2OpenMP.c | 127 +++++++++++++++++++++++++++---------------------
 1 file changed, 71 insertions(+), 56 deletions(-)

 ~/Documents/GitHub/Highperformance_Computing   master 
 ✔  cd HW2

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ✔  ls
Assignment2.pdf     assignment2         assignment2.c       assignment2OpenMP.c

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ✔  gcc -o assignment2OpenMP.c assignment2OpenMP

clang: error: no such file or directory: 'assignment2OpenMP'
clang: error: no input files

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ↵ 1 

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ↵ 1  gcc -o assignment2OpenMP.c assignment2OpenMP
clang: error: no such file or directory: 'assignment2OpenMP'
clang: error: no input files

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ↵ 1  gcc assignment2OpenMP.c -o assignment2OpenMP
assignment2OpenMP.c:5:10: fatal error: 'omp.h' file not found
#include <omp.h>
         ^~~~~~~
1 error generated.

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ↵ 1  gcc assignment2.c -o assignment2

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ✔  ./assignment2 100
number of particles: 100
elapsed time: 0.000142

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
  1 include_directories("/usr/local/include" "/usr/local/opt/llvm/include")
 ✔  ./assignment2 100
number of particles: 100
elapsed time: 0.000138

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ✔  ./assignment2 1000
number of particles: 1000
elapsed time: 0.013108

 ~/Documents/GitHub/Highperformance_Computing/HW2   master 
 ✔  ./assignment2 10000
number of particles: 10000
elapsed time: 1.336884

  1 #include <stdlib.h>
  2 #include <stdio.h>
  3 #include <math.h>
  4 #include <sys/time.h>
  5 #include <omp.h>
  6
  7 double get_walltime() {
  8     struct timeval tp; gettimeofday(&tp, NULL);
  9     return (double) (tp.tv_sec + tp.tv_usec*1e-6); }
 10
 11 void force_repulsion(int np, const double *pos, double L, double krepulsio    n, double *forces)
 12 {
 13     #pragma omp parallel
 14     {
 15         int i, j;
 16         double posi[4];
 17         double rvec[4];
 18         double s2, s, f;
 19         // initialize forces to zero
 20
 21         for (i = 0; i < 3 * np; i++)
 22             forces[i] = 0.;
 23         // loop over all pairs
"assignment2OpenMP.c" 87L, 2627C
  1 #include <stdlib.h>
  2 #include <stdio.h>
  3 #include <math.h>
  4 #include <sys/time.h>
  5 #include <omp.h>
  6
  7 double get_walltime() {
  8     struct timeval tp; gettimeofday(&tp, NULL);
  9     return (double) (tp.tv_sec + tp.tv_usec*1e-6); }
 10
 11 void force_repulsion(int np, const double *pos, double L, double krepulsion    , double *forces)
 12 {
 13     #pragma omp parallel
 14     {
 15         int i, j;
 16         double posi[4];
 17         double rvec[4];
 18         double s2, s, f;
 19         // initialize forces to zero
 20
 21         for (i = 0; i < 3 * np; i++)
 22             forces[i] = 0.;
 23         // loop over all pairs
  1 #include <stdlib.h>
  2 #include <stdio.h>
  3 #include <math.h>
  4 #include <sys/time.h>
  5 #include <omp.h>
  6
  7 double get_walltime() {
  8     struct timeval tp; gettimeofday(&tp, NULL);
  9     return (double) (tp.tv_sec + tp.tv_usec*1e-6); }
 10
 11 void force_repulsion(int np, const double *pos, double L, double krepulsion, double *forces)
 12 {
 13     #pragma omp parallel
 14     {
 15         int i, j;
 16         double posi[4];
 17         double rvec[4];
 18         double s2, s, f;
 19         // initialize forces to zero
 20
 21         for (i = 0; i < 3 * np; i++)
 22             forces[i] = 0.;
 23         // loop over all pairs
 24
 25         #pragma omp for schedule(static) //Determine Scheduling Here
 26         for (i = 0; i < np; i++) {
 27             posi[0] = pos[3 * i];
 28             posi[1] = pos[3 * i + 1];
 29             posi[2] = pos[3 * i + 2];
 30
 31             for (j = i + 1; j < np; j++) {
 32                 // compute minimum image difference
 33                 rvec[0] = remainder(posi[0] - pos[3 * j], L);
 34                 rvec[1] = remainder(posi[1] - pos[3 * j + 1], L);
 35                 rvec[2] = remainder(posi[2] - pos[3 * j + 2], L);
 36                 s2 = rvec[0] * rvec[0] + rvec[1] * rvec[1] + rvec[2] * rvec[2];
 37                 if (s2 < 4) {
 38                     s = sqrt(s2);
 39                     rvec[0] /= s;
 40                     rvec[1] /= s;
 41                     rvec[2] /= s;
  1 #include <stdlib.h>
  2 #include <stdio.h>
  3 #include <math.h>
  4 #include <sys/time.h>
  5 #include <omp.h>
  6
  7 double get_walltime() {
  8     struct timeval tp; gettimeofday(&tp, NULL);
  9     return (double) (tp.tv_sec + tp.tv_usec*1e-6); }
 10
 11 void force_repulsion(int np, const double *pos, double L, double krepulsion, double *forces)
 12 {
 13     #pragma omp parallel
 14     {
 15         int i, j;
 16         double posi[4];
 17         double rvec[4];
 18         double s2, s, f;
 19         // initialize forces to zero
 20
 21         for (i = 0; i < 3 * np; i++)
 22             forces[i] = 0.;
 23         // loop over all pairs
 24
 25         #pragma omp for schedule(static) //Determine Scheduling Here
 26         for (i = 0; i < np; i++) {
 27             posi[0] = pos[3 * i];
 28             posi[1] = pos[3 * i + 1];
 29             posi[2] = pos[3 * i + 2];
 30
 31             for (j = i + 1; j < np; j++) {
 32                 // compute minimum image difference
 33                 rvec[0] = remainder(posi[0] - pos[3 * j], L);
 34                 rvec[1] = remainder(posi[1] - pos[3 * j + 1], L);
 35                 rvec[2] = remainder(posi[2] - pos[3 * j + 2], L);
 36                 s2 = rvec[0] * rvec[0] + rvec[1] * rvec[1] + rvec[2] * rvec[2];
 37                 if (s2 < 4) {
 38                     s = sqrt(s2);
 39                     rvec[0] /= s;
 40                     rvec[1] /= s;
 41                     rvec[2] /= s;
 42                     f = krepulsion * (2. - s);
 43                     forces[3 * i] += f * rvec[0];
 44                     forces[3 * i + 1] += f * rvec[1];
 45                     forces[3 * i + 2] += f * rvec[2];
 46                     forces[3 * j] += -f * rvec[0];
 47                     forces[3 * j + 1] += -f * rvec[1];
  1 #include <stdlib.h>
  2 #include <stdio.h>
  3 #include <math.h>
  4 #include <sys/time.h>
  5 #include <omp.h>
  6
  7 double get_walltime() {
  8     struct timeval tp; gettimeofday(&tp, NULL);
  9     return (double) (tp.tv_sec + tp.tv_usec*1e-6); }
 10
 11 void force_repulsion(int np, const double *pos, double L, double krepulsion, double *forces)
 12 {
 13     #pragma omp parallel
 14     {
 15         int i, j;
 16         double posi[4];
 17         double rvec[4];
 18         double s2, s, f;
 19         // initialize forces to zero
 20
 21         for (i = 0; i < 3 * np; i++)
 22             forces[i] = 0.;
 23         // loop over all pairs
 24
 25         #pragma omp for schedule(static) //Determine Scheduling Here
 26         printf("yeet %d", omp_get_thread_num());
 27         for (i = 0; i < np; i++) {
 28             posi[0] = pos[3 * i];
 29             posi[1] = pos[3 * i + 1];
 30             posi[2] = pos[3 * i + 2];

                              forces[3 * j + 1] += -f * rvec[1];
                                                                                                                                                                forces[3 * j + 2] += -f * rvec[2];
                                                                                                                                }
                                                                                                }
                                                                }
                                }
}


int main(int argc, char *argv[]) {
                                int i;
                                int np = 100; // default number of particles
                                double phi = 0.3; // volume fraction
                                double krepulsion = 125.; // force constant
                                double *pos; double *forces;
                                double L, time0 , time1;

                                if (argc > 1)
                                                                np = atoi(argv[1]);

                                L = pow(4./3.*3.1415926536*np/phi, 1./3.);
                                // generate random particle positions inside simulation box
                                forces = (double *) malloc(3*np*sizeof(double));
                                pos = (double *) malloc(3*np*sizeof(double));
                                for (i=0; i<3*np; i++)
                                                                pos[i] = rand()/(double)RAND_MAX*L;
                                // measure execution time of this function
                                int cs;
                                for(int x = 0; x<=5; x++) {
                                                                cs = pow(2, x);
                                                                printf("Running with chunk size: %d", cs);
                                                                time0 = get_walltime ();
                                                                force_repulsion(np, pos, L, krepulsion, forces, cs);
                                                                time1 = get_walltime ();
                                }

                                printf("number of particles: %d\n", np);
                                printf("elapsed time: %f\n", time1-time0);
                                free(forces);
                                free(pos);
                                return 0;
}

~
~
                                                                                                                88,1-8        Bot
nclude <stdlib.h>
 31
nclude <stdlib.h>
 32             for (j = i + 1; j < np; j++) {
 33                 // compute minimum image difference
 34                 rvec[0] = remainder(posi[0] - pos[3 * j], L);
 35                 rvec[1] = remainder(posi[1] - pos[3 * j + 1], L);
 36                 rvec[2] = remainder(posi[2] - pos[3 * j + 2], L);
 37                 s2 = rvec[0] * rvec[0] + rvec[1] * rvec[1] + rvec[2] * rvec[2];
 38                 if (s2 < 4) {
 39                     s = sqrt(s2);
 40                     rvec[0] /= s;
 41                     rvec[1] /= s;
 42                     rvec[2] /= s;
 43                     f = krepulsion * (2. - s);
 44                     forces[3 * i] += f * rvec[0];
 45                     forces[3 * i + 1] += f * rvec[1];
 46                     forces[3 * i + 2] += f * rvec[2];
 47                     forces[3 * j] += -f * rvec[0];
"assignment2OpenMP.c" 88L, 2669C written

Session Contents Restored

Last login: Tue Oct  8 19:46:33 on console
You have new mail.

 ~/Documents/GitHub/Highperformance_Computing/HW2   master ● 
 ✔  ssh -i ~/.ssh/LLCloud cc@129.114.108.192
The authenticity of host '129.114.108.192 (129.114.108.192)' can't be established.
ECDSA key fingerprint is SHA256:qMPSEPuCLbKUDESDB4LPwpalV6+nyMwG9DVQjkA6Ccs.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added '129.114.108.192' (ECDSA) to the list of known hosts.
Welcome to Ubuntu 16.04.3 LTS (GNU/Linux 4.4.0-98-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  Get cloud support with Ubuntu Advantage Cloud Guest:
    http://www.ubuntu.com/business/services/cloud

175 packages can be updated.
9 updates are security updates.


*** System restart required ***
Last login: Tue Oct  8 23:22:54 2019
cc@ll:~$ ls
cc@ll:~$ vim omp.c
cc@ll:~$ vim omp.c
cc@ll:~$ gcc -fopenmp omp.c -lm -o staticOmp
omp.c:1:8: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘<’ token
 nclude <stdlib.h>
        ^
In file included from /usr/include/stdio.h:74:0,
                 from omp.c:2:
/usr/include/libio.h:302:3: error: unknown type name ‘size_t’
   size_t __pad5;
   ^
/usr/include/libio.h:305:67: error: ‘size_t’ undeclared here (not in a function)
   char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
                                                                   ^
/usr/include/libio.h:333:62: error: expected declaration specifiers or ‘...’ before ‘size_t’
 typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);
                                                              ^
/usr/include/libio.h:342:6: error: expected declaration specifiers or ‘...’ before ‘size_t’
      size_t __n);
      ^
/usr/include/libio.h:464:19: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘_IO_sgetn’
 extern _IO_size_t _IO_sgetn (_IO_FILE *, void *, _IO_size_t);
                   ^
In file included from omp.c:2:0:
/usr/include/stdio.h:319:35: error: expected declaration specifiers or ‘...’ before ‘size_t’
 extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
                                   ^
/usr/include/stdio.h:325:47: error: expected declaration specifiers or ‘...’ before ‘size_t’
 extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __THROW __wur;
                                               ^
/usr/include/stdio.h:337:20: error: expected declaration specifiers or ‘...’ before ‘size_t’
       int __modes, size_t __n) __THROW;
                    ^
/usr/include/stdio.h:344:10: error: expected declaration specifiers or ‘...’ before ‘size_t’
          size_t __size) __THROW;
          ^
/usr/include/stdio.h:386:44: error: expected declaration specifiers or ‘...’ before ‘size_t’
 extern int snprintf (char *__restrict __s, size_t __maxlen,
                                            ^
/usr/include/stdio.h:390:45: error: expected declaration specifiers or ‘...’ before ‘size_t’
 extern int vsnprintf (char *__restrict __s, size_t __maxlen,
                                             ^
#include <stdlib.h>
/usr/include/stdio.h:666:11: error: expected declaration specifiers or ‘...’ before ‘size_t’
           size_t *__restrict __n, int __delimiter,
           ^
/usr/include/stdio.h:669:9: error: expected declaration specifiers or ‘...’ before ‘size_t’
         size_t *__restrict __n, int __delimiter,
         ^
#include <stdlib.h>
/usr/include/stdio.h:679:8: error: expected declaration specifiers or ‘...’ before ‘size_t’
        size_t *__restrict __n,
        ^
/usr/include/stdio.h:709:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘fread’
 extern size_t fread (void *__restrict __ptr, size_t __size,
               ^
/usr/include/stdio.h:715:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘fwrite’
                                        forces[3 * i] += f * rvec[0];
 extern size_t fwrite (const void *__restrict __ptr, size_t __size,
               ^
/usr/include/stdio.h:737:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘fread_unlocked’
 extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
               ^
/usr/include/stdio.h:739:15: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘fwrite_unlocked’
 extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
               ^
omp.c: In function ‘force_repulsion’:
omp.c:26:3: error: for statement expected before ‘printf’
   printf("yeet %d", omp_get_thread_num());
                                        forces[3 * i] += f * rvec[0];
   ^
omp.c: In function ‘main’:
omp.c:66:8: warning: implicit declaration of function ‘atoi’ [-Wimplicit-function-declaration]
   np = atoi(argv[1]);
        ^
omp.c:70:22: warning: implicit declaration of function ‘malloc’ [-Wimplicit-function-declaration]
  forces = (double *) malloc(3*np*sizeof(double));
                      ^
omp.c:70:22: warning: incompatible implicit declaration of built-in function ‘malloc’
omp.c:70:22: note: include ‘<stdlib.h>’ or provide a declaration of ‘malloc’
omp.c:73:12: warning: implicit declaration of function ‘rand’ [-Wimplicit-function-declaration]
   pos[i] = rand()/(double)RAND_MAX*L;
            ^
omp.c:73:27: error: ‘RAND_MAX’ undeclared (first use in this function)
   pos[i] = rand()/(double)RAND_MAX*L;
                           ^
omp.c:73:27: note: each undeclared identifier is reported only once for each function it appears in
omp.c:86:2: warning: implicit declaration of function ‘free’ [-Wimplicit-function-declaration]
  free(forces);
  ^
omp.c:86:2: warning: incompatible implicit declaration of built-in function ‘free’
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

double get_walltime() {
        struct timeval tp; gettimeofday(&tp, NULL);
        return (double) (tp.tv_sec + tp.tv_usec*1e-6); }

void force_repulsion(int np, const double *pos, double L, double krepulsion, double *forces, int cs)
{
#pragma omp parallel
        {
                int i, j;
                double posi[4];
                double rvec[4];
                double s2, s, f;
                // initialize forces to zero

                for (i = 0; i < 3 * np; i++)
                        forces[i] = 0.;
                // loop over all pairs

#pragma omp for schedule(static) //Determine Scheduling Here
                for (i = 0; i < np; i++) {
                        posi[0] = pos[3 * i];
                        posi[1] = pos[3 * i + 1];
                        posi[2] = pos[3 * i + 2];

                        for (j = i + 1; j < np; j++) {
                                // compute minimum image difference
                                rvec[0] = remainder(posi[0] - pos[3 * j], L);
                                rvec[1] = remainder(posi[1] - pos[3 * j + 1], L);
                                rvec[2] = remainder(posi[2] - pos[3 * j + 2], L);
                                s2 = rvec[0] * rvec[0] + rvec[1] * rvec[1] + rvec[2] * rvec[2];
                                if (s2 < 4) {
                                        s = sqrt(s2);
                                        rvec[0] /= s;
                                        rvec[1] /= s;
                                        rvec[2] /= s;
                                        f = krepulsion * (2. - s);
                                        forces[3 * i] += f * rvec[0];
                                        forces[3 * i + 1] += f * rvec[1];
                                        forces[3 * i + 2] += f * rvec[2];
                                        forces[3 * j] += -f * rvec[0];
                                        forces[3 * j + 1] += -f * rvec[1];
                                                                                                                24,0-1        Top
