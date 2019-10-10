#include <stdlib.h>
#include <stdio.h>
#include <math.h> #include <sys/time.h>
#include <omp.h>

double get_walltime() {
				struct timeval tp; gettimeofday(&tp, NULL);
				return (double) (tp.tv_sec + tp.tv_usec*1e-6); }

void force_repulsionStatic(int np, const double *pos, double L, double krepulsion, double *forcesStatic, int cs)
{ int i, j;
				double posi [4]; double rvec [4];
				double s2, s, f;
				// initialize forces to zero
				for (i=0; i<3*np; i++)
								forcesStatic[i] = 0.;
				// loop over all pairs
				for (i=0; i<np; i++)
				{
								posi[0] = pos[3*i ];
								posi[1] = pos[3*i+1]; posi[2] = pos[3*i+2];
								for (j=i+1; j<np; j++)
								{
												// compute minimum image difference
												rvec[0] = remainder(posi[0] - pos[3*j ], L); rvec[1] = remainder(posi[1] - pos[3*j+1], L);
												rvec[2] = remainder(posi[2] - pos[3*j+2], L);
												s2 = rvec [0]* rvec [0] + rvec [1]* rvec [1] + rvec [2]* rvec [2];
												if (s2 < 4)
												{
																s = sqrt(s2);
																rvec[0] /= s; rvec[1] /= s;
																rvec[2] /= s;
																f = krepulsion*(2.-s);
																
printf("%d - %f \n", 3*i,f*rvec[0]);
printf("%d - %f \n", 3*i+1, f*rvec[1]);
printf("%d - %f \n", 3*i+2, f*rvec[2]);
printf("%d - %f \n", 3*j,-f*rvec[0]); 
printf("%d - %f \n", 3*j+1, -f*rvec[1]);
printf("%d - %f \n", 3*j+2, -f*rvec[2]); 
                                          
                                          
forcesStatic[3*i ] += f*rvec[0];
forcesStatic[3*i+1] += f*rvec[1];
forcesStatic[3*i+2] += f*rvec[2];
forcesStatic[3*j ] += -f*rvec[0]; 
forcesStatic[3*j+1] += -f*rvec[1];
forcesStatic[3*j+2] += -f*rvec[2];
                                          
printf("\n-----------------\n"); 
                                          
printf("%f\n", forcesStatic[3*i ]); 
printf("%f\n", forcesStatic[3*i+1]);  
printf("%f\n", forcesStatic[3*i+2]);  
printf("%f\n", forcesStatic[3*j ]) ; 
printf("%f\n", forcesStatic[3*j+1]);  
printf("%f\n", forcesStatic[3*j+2]);  
                                          												
                                          												
printf("\n-----------------\n");         												
												
												}
								} }
}

void force_repulsion(int np, const double *pos, double L, double krepulsion, double *forces, int cs)
{

#pragma omp parallel 
				{
								int i, j, xi;
								double posi[4]; 
								double rvec[4];  
								double s2, s, f; ;
								// initialize forces to zero

								for (i = 0; i < 3 * np; i++)
												forces[i] = 0.;
#pragma omp for 
								for (i=0; i<np; i++)
								{
												posi[0] = pos[3*i];
												posi[1] = pos[3*i+1]; 
												posi[2] = pos[3*i+2];
												for (j=i+1; j<np; j++)
												{
																// compute minimum image difference
																rvec[0] = remainder(posi[0] - pos[3*j ], L); 
																rvec[1] = remainder(posi[1] - pos[3*j+1], L);
																rvec[2] = remainder(posi[2] - pos[3*j+2], L);
																s2 = rvec[0]* rvec[0] + rvec[1]* rvec[1] + rvec[2]* rvec[2];
																if (s2 < 4)
																{
																				s = sqrt(s2);
																				rvec[0] /= s; rvec[1] /= s;
																				rvec[2] /= s;
																				f = krepulsion*(2.-s);

																				printf("%d - %f \n", 3*i,f*rvec[0]);
																				printf("%d - %f \n", 3*i+1, f*rvec[1]);
																				printf("%d - %f \n", 3*i+2, f*rvec[2]);
																				printf("%d - %f \n", 3*j,-f*rvec[0]); 
																				printf("%d - %f \n", 3*j+1, -f*rvec[1]);
																				printf("%d - %f \n", 3*j+2, -f*rvec[2]); 


																				forces[3*i ] += f*rvec[0];
																				forces[3*i+1] += f*rvec[1];
																				forces[3*i+2] += f*rvec[2];
																				forces[3*j ] += -f*rvec[0]; 
																				forces[3*j+1] += -f*rvec[1];
																				forces[3*j+2] += -f*rvec[2];

																				printf("\n-----------------\n"); 

																				printf("%f\n", forces[3*i ]); 
																				printf("%f\n", forces[3*i+1]);  
																				printf("%f\n", forces[3*i+2]);  
																				printf("%f\n", forces[3*j ]) ; 
																				printf("%f\n", forces[3*j+1]);  
																				printf("%f\n", forces[3*j+2]);  


																				printf("\n-----------------\n"); 



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
				double *pos, *posStatic; double *forces, *forcesStatic;
				double L, time0 , time1, time2, time3;

				if (argc > 1)
								np = atoi(argv[1]);

				L = pow(4./3.*3.1415926536*np/phi, 1./3.);
				// generate random particle positions inside simulation box

				forces = (double *) malloc(3*np*sizeof(double));
				forcesStatic = (double *) malloc(3*np*sizeof(double));

				posStatic = (double *) malloc(3*np*sizeof(double));
				pos = (double *) malloc(3*np*sizeof(double));
				for (i=0; i<3*np; i++)
								pos[i] = posStatic[i] = rand()/(double)RAND_MAX*L;
				// measure execution time of this function

				time0 = get_walltime ();
				force_repulsion(np, pos, L, krepulsion, forces, 1);
				time1 = get_walltime ();
printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<\n");
				time2 = get_walltime ();
				force_repulsionStatic(np, posStatic, L, krepulsion, forcesStatic, 1);
				time3 = get_walltime ();

				for(int x=0; x<=np; x++) {
								printf("%d %f \t\t %f \n", x, forcesStatic[x], forces[x]); 

				}

				printf("number of particles: %d\n", np);
				printf("elapsed time ST: %f\n", time3-time2);
				printf("elapsed time MT static: %f\n", time1-time0);

				free(forces);
				free(forcesStatic);
				free(pos);
				free(posStatic); 
				return 0;

}

