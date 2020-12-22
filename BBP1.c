//3J T.A.
#include <stdio.h>
#include <math.h>
#include <time.h>

void main() {
    double pid;
    double s1, s2, s3, s4;
    double series(int m, int n);

    void ihex(double x, int m, char c[]);
#define NHX 16
    char chx[NHX];

    clock_t start, end;

    int id;

    printf("pi=3.\n");

    start = clock();       
    for (id = 0; id < 1000; id += 10) {

        s1 = series(1, id);
        s2 = series(4, id);
        s3 = series(5, id);
        s4 = series(6, id);
        pid = 4. * s1 - 2. * s2 - s3 - s4; 
        pid = pid - (int)pid + 1.; 
        ihex(pid, NHX, chx);

        printf("%10.10s ", chx);

        if (id % 100 == 0)
            puts("");
    }
    end = clock();         

    printf(" time = %.3f[sec]\n", (double)(end - start) / CLOCKS_PER_SEC);

}

double series(int m, int id)        //series:‹‰”
{
    int k;
    double ak, eps, p, s, t;
    double expm(double x, double y);
#define eps 1e-17

    s = 0.;

    for (k = 0; k < id; k++) {
        ak = 8 * k + m;
        p = id - k;
        t = expm(p, ak);
        s = s + t / ak;
        s = s - (int)s;
    }

    for (k = id; k <= id + 100; k++) {
        ak = 8 * k + m;
        t = pow(16., (double)(id - k)) / ak;
        if (t < eps) break;
        s = s + t;
        s = s - (int)s;
    }
    return s;
}

double expm(double p, double ak)
{
    int i, j;
    double p1, pt, r;
#define ntp 25
    static double tp[ntp];
    static int tp1 = 0;

    if (tp1 == 0) {
        tp1 = 1;
        tp[0] = 1.;

        for (i = 1; i < ntp; i++)
            tp[i] = 2. * tp[i - 1];
    }

    if (ak == 1.)
        return 0.;

    for (i = 0; i < ntp; i++)
        if (tp[i] > p) break;

    pt = tp[i - 1];
    p1 = p;
    r = 1.;

    for (j = 1; j <= i; j++) {
        if (p1 >= pt) {
            r = 16. * r;
            r = r - (int)(r / ak) * ak;
            p1 = p1 - pt;
        }
        pt = 0.5 * pt;
        if (pt >= 1.) {
            r = r * r;
            r = r - (int)(r / ak) * ak;
        }
    }

    return r;
}

void ihex(double x, int nhx, char chx[])
{
    int i;
    double y;
    char hx[] = "0123456789ABCDEF";

    y = fabs(x);   
    for (i = 0; i < nhx; i++) {
        y = 16. * (y - floor(y));
        chx[i] = hx[(int)y];
    }
}