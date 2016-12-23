#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "Solution_of_Linear_Equations.h"

void Swap(double *a, double *b)
{
    double temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int Gaus(double a[], double b[], int n)
{
    int *js, l, k, i, j, is, p, q;
    double d, t;
    js = (int*)malloc(n*sizeof(int));
    l = 1;

    for (k = 0;k <= n - 2; k ++)
    {
        d = 0.0;

        for (i = k; i <= n - 1; i ++)
            for (j = k; j <= n-1; j++)
            {
                t = fabs(a[i*n + j]);
                if (t > d)
                {
                    d = t;
                    js[k] = j;
                    is = i;
                }//if
            }//for

        if (fabs(d) < ACCURACY)
        {
            for (i = k; i <= n - 1; i ++)
                if (b[i] > ACCURACY)
                {
                    l = 0;// no resolution
                    free(js);
                    js = NULL;
                    printf("no resolution\n");
                    return 0;
                }
            k --;
            break;
        }
        else
        {
            if (js[k] != k)
            {
                for (i = 0 ; i <= n -1; i ++)
                {
                    Swap(&a[i*n + k], &a[i*n + js[k]]);
                }//for
            }//if
            if(is != k)
            {
                for (j = k; j <= n - 1; j ++)
                {
                    Swap(&a[k*n + j], &a[is*n + j]);
                }//for
                Swap(&b[k], &b[is]);

            }//if

        }//else

        d = a[k*n + k];
        for (j = k; j <= n-1; j ++)
        {
            a[k*n + j] /= d;
        }//for
        b[k] /= d;

        for (i = k + 1; i <= n - 1; i ++)
        {
            for (j = k + 1; j <= n - 1; j ++)
                a[i*n + j] -= a[i*n + k] * a[k*n + j];
            b[i] = b[i] - a[i*n + k] * b[k];
            a[i*n + k] -= a[i*n + k] * a[k*n + k];

        }//for
    }//for

    d = a[k*n + k];
    if (fabs(d) < ACCURACY)
    {
        for (i = k; i <= n - 1; i ++)
            if (b[i] > ACCURACY)
            {
                l = 0;// no resolution
                free(js);
                js = NULL;
                printf("no resolution\n");
                return 0;
            }

        k --;
        d = a[k*n + k];
    }//if

    b[k] /= d;
    for (i = k -1; i >= 0; i --)
    {
        t = 0.0;
        for (j = i + 1; j <= k; j ++)
            t += a[i*n + j] * b[j];
        b[i] -= t;
    }
    
    js[k] = k;
    for (i = k; i >= 0; i --)
        if(js[i] != i)
        {
            Swap(&b[i], &b[js[i]]);
        }
    free(js);
    return n - k - 1; 
}

int Cgas(double ar[], double ai[], int n, double br[], double bi[])
{
    int *js, l, k, i, j, is, u, v;
    double p, q, s, d, tempr, tempi;
    js = (int*)malloc(n * sizeof(int));

    for (k = 0;k <= n - 2; k ++)
    {
        d = 0.0;

        //max element
        for (i = k; i <= n - 1; i ++)
            for (j = k; j <= n-1; j ++)
            {
                u = i * n + j;
                p = ar[u] * ar[u] + ai[u] * ai[u];
                if (p > d)
                {
                    d = p;
                    js[k] = j;
                    is = i;
                }//if
            }//for

        if (d < ACCURACY)
        {
            for (i = k; i < n; i ++)
            {
                p = br[i] * br[i] + bi[i] * bi[i];
                if (p >= ACCURACY)
                {
                    free(js);
                    printf("after %d b is not 0, have no resolution\n", k);
                    return 0;
                }//if
            }//for

            k --;
            break;
        }//if

        if (is != k)
        {
            for (j = k; j <= n-1; j++)
            {
                u = k * n + j;
                v = is * n + j;
                Swap(&ar[u], &ar[v]);
                Swap(&ai[u], &ai[v]);
            }
            Swap(&br[k], &br[is]);
            Swap(&bi[k], &bi[is]);

        }//if
        if (js[k] != k)
        {
            for (i = 0; i <= n-1; i ++)
            {
                u = i * n + k;
                v = i * n + js[k];
                Swap(&ar[u], &ar[v]);
                Swap(&ai[u], &ai[v]);
            }//for
        }//if
         
        //Coefficient matrix normalization
        v = k * n + k;
        tempr = ar[v];
        tempi = ai[v];
        for (j = k; j <= n-1; j++)
        {
            u = k * n + j;
            p = ar[u] * tempr;
            q = -ai[u] * tempi;
            s = (tempr-tempi) * (ar[u]+ai[u]);
            ar[u] = (p - q) / d;
            ai[u] = (s - p -q) / d;
        }//for
        p = br[k] * tempr;
        q = -bi[k] * tempi;
        s = (tempr-tempi) * (br[k]+bi[k]);
        br[k] = (p - q) / d;
        bi[k] = (s - p -q) / d;


        //
        for (i = k + 1; i <= n -1; i ++)
        {
            u = i * n + k;

            for (j = k + 1; j <= n - 1; j ++)
            {
                v = k * n + j;
                l = i * n + j;
                p = ar[u] * ar[v];
                q = ai[u] * ai[v];
                s = (ar[u] + ai[u]) * (ar[v] + ai[v]);
                ar[l] = ar[l] - p + q;
                ai[l] = ai[l] - s + p + q;
            }//for

            p = ar[u] * br[k];
            q = ai[u] * bi[k];
            s = (ar[u] + ai[u]) * (br[k] + bi[k]);
            br[i] = br[i] - p + q;
            bi[i] = bi[i] - s + p + q;

            v = k * n + k;
            l = i * n + k;
            p = ar[u] * ar[v];
            q = ai[u] * ai[v];
            s = (ar[u] + ai[u]) * (ar[v] + ai[v]);
            ar[l] = ar[l] - p +q;
            ai[l] = ai[l] - s + p + q;
        }//for

    }//for

    printf("k=%d\n",k);
    u = k * n + k;
    d = ar[u]*ar[u] + ai[u]*ai[u];
    if (d < ACCURACY)
    {
        for (i = k; i < n; i ++)
        {
            p = br[i] * br[i] + bi[i] * bi[i];
            if (p >= ACCURACY)
            {
                free(js);
                js = NULL;
                printf("after %d b is not 0, have no resolution\n", k);
                return 0;
            }//if
        }//for
        k--;
        u = k * n + k;
        d = ar[u]*ar[u] + ai[u]*ai[u];
    }

    printf("k=%d\n",k);
    p = ar[u] * br[k];
    q = -ai[u] * bi[k];
    s = (ar[u]-ai[u]) * (br[k]+bi[k]);
    br[k] = (p - q) / d;
    bi[k] = (s - p - q) / d;
    for (i = k - 1; i >= 0; i --)
    {
        for(j = i + 1; j <= k; j ++)
        {
            u = i * n + j;
            p = ar[u] * br[j];
            q = ai[u] * bi[j];
            s = (ar[u]+ai[u]) * (br[j]+bi[j]);
            br[i] = br[i] - p + q;
            bi[i] = bi[i] - s + p + q;

        }//for
        
        for (u = 0; u < n; u++)
        {
            for (v = 0;v < n; v++)
            {
                printf("%f    ",ar[u*n+v]);
            }
            printf("%f\n",br[u]);
        }
        printf("----------------------------------------------\n");
    }
        
    js[k] = k;
    for (i = k - 1; i >= 0; i --)
        if (js[i] != i)
        {
            Swap(&br[i], &br[js[i]]);
            Swap(&bi[i], &bi[js[i]]);
        }//if

    free(js);
    return n - k + 1;
}

int BasicSolutionSystem(double ar[], double ai[], int n)
{

    int *js, l, k, i, j, is, u, v, ret;
    double p, q, s, d, tempr, tempi;
    js = (int*)malloc(n * sizeof(int));

    for (k = 0;k <= n - 1; k ++)
    {
        d = 0.0;

        //max element
        for (i = k; i <= n - 1; i ++)
            for (j = k; j <= n-1; j ++)
            {
                u = i * n + j;
                p = ar[u] * ar[u] + ai[u] * ai[u];
                if (p > d)
                {
                    d = p;
                    js[k] = j;
                    is = i;
                }//if
            }//for

        if (d < ACCURACY)
        {
            k --;
            printf("break\n");
            break;
        }//if

        if (is != k)
        {
            for (j = k; j <= n-1; j++)
            {
                u = k * n + j;
                v = is * n + j;
                Swap(&ar[u], &ar[v]);
                Swap(&ai[u], &ai[v]);
            }

        }//if
        if (js[k] != k)
        {
            for (i = 0; i <= n-1; i ++)
            {
                u = i * n + k;
                v = i * n + js[k];
                Swap(&ar[u], &ar[v]);
                Swap(&ai[u], &ai[v]);
            }//for
        }//if
         
        //Coefficient matrix normalization
        v = k * n + k;
        tempr = ar[v];
        tempi = ai[v];
        for (j = k; j <= n-1; j++)
        {
            u = k * n + j;
            p = ar[u] * tempr;
            q = -ai[u] * tempi;
            s = (tempr-tempi) * (ar[u]+ai[u]);
            ar[u] = (p - q) / d;
            ai[u] = (s - p -q) / d;
        }//for

        //
        for (i = k + 1; i <= n -1; i ++)
        {
            u = i * n + k;

            for (j = k + 1; j <= n - 1; j ++)
            {
                v = k * n + j;
                l = i * n + j;
                p = ar[u] * ar[v];
                q = ai[u] * ai[v];
                s = (ar[u] + ai[u]) * (ar[v] + ai[v]);
                ar[l] = ar[l] - p + q;
                ai[l] = ai[l] - s + p + q;
            }//for

            v = k * n + k;
            l = i * n + k;
            p = ar[u] * ar[v];
            q = ai[u] * ai[v];
            s = (ar[u] + ai[u]) * (ar[v] + ai[v]);
            ar[l] = ar[l] - p +q;
            ai[l] = ai[l] - s + p + q;
        }//for

    }//for
    for (i = 0; i < 3; i ++)
    {
        for (j = 0; j < 3; j++)
            printf("%f + %fi    ",ar[i*3+j],ai[i*3+j]);
        printf("%d   \n", k);
    }
    printf("------------------------------------------\n");

    if (k == n)
        k --;
    ret = k;

    for (; k > 0; k--)
    {
        for (i = k - 1; i >= 0; i --)
        {
            u = i * n + k;

            for (j = ret + 1; j <= n - 1; j ++)
            {
                v = k * n + j;
                l = i * n + j;
                p = ar[u] * ar[v];
                q = ai[u] * ai[v];
                s = (ar[u] + ai[u]) * (ar[v] + ai[v]);
                ar[l] = ar[l] - p + q;
                ai[l] = ai[l] - s + p + q;
            }//for
            v = k * n + ret;
            l = i * n + ret;
            p = ar[u] * ar[v];
            q = ai[u] * ai[v];
            s = (ar[u] + ai[u]) * (ar[v] + ai[v]);
            ar[l] = ar[l] - p + q;
            ai[l] = ai[l] - s + p + q;

        }//for
    }
    for (i = 0; i < 3; i ++)
    {
        for (j = 0; j < 3; j++)
            printf("%f + %fi    ",ar[i*3+j],ai[i*3+j]);
        printf("%d   \n", k);
    }
    printf("------------------------------------------\n");
        
    js[ret] = ret;
    for (i = ret - 1; i >= 0; i --)
        if (js[i] != i)
        {
            for (j = 0; j < n; j ++)
            {
                Swap(&ar[i*n+j], &ar[js[i]*n+j]);
                Swap(&ai[i*n+j], &ai[js[i]*n+j]);
            }
        }//if

    free(js);
    return n - ret + 1;
}

int main(void)
{

    //double a[9] = {3, 2, 0, 2, 1, 0, 1, 1, 0};
    //double b[3] = {5, 3, 2};
    //int ret = Gaus(a,b,3);
    //printf("res:%d\n",ret);
    int i = 0,j = 0;
    //for (i = 0; i < 3; i ++)
    //    printf("%f   ", b[i]);
    //printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    double ar[9] = {1-16.1168,2,3,4,5-16.1168,6,7,8,9-16.1168};//{1+10.3556, 25, 3, 4, 15.3356, 6,0,8,19.3556 };
    double ai[9] = {0};//{-9.2283, -41,0, -0.579, -11.2283, 3,7,0,-2.0283};
    double br[3] = {0}, bi[3] = {0};
    //Cgas(ar, ai, 3, br, bi);
    BasicSolutionSystem(ar,ai,3);
    for (i = 0; i < 3; i ++)
    {
        for (j = 0; j < 3; j++)
            printf("%f + %fi    ",ar[i*3+j],ai[i*3+j]);
        printf("%f + %fi   \n", br[i], bi[i]);
    }
    printf("\n");

    return 0;
}
