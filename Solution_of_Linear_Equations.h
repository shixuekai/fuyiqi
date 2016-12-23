#ifndef SOLUTIONOFLINEAREQUATIONS
#define SOLUTIONOFLINEAREQUATIONS


#define ACCURACY 0.000000000001

void Swap(double *a, double *b);
int Gaus(double a[], double b[], int n);
int Cgas(double ar[], double ai[], int n, double br[], double bi[]);
int BasicSolutionSystem(double ar[], double ai[], int n);

#endif
