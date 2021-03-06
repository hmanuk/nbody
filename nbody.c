#include <stdio.h>
#include <math.h>
#include <stdlib.h>


main () {
    FILE * fp;
    fp = fopen("nbs.txt", "w");
    int n = 3;
    float dt = 1;
    float G = 6.67384 * pow(10,-8);
    int i;
    int j;
    float ax, ay, az, dx, dy, dz, invr, invr3, f, eps;
    eps = .01;
    float x[3] = {1., -2., 1.};
    float y[3] = {3., -1., -1.};
    float z[3] = {0., 0., 0.};
    float xnew[n];
    float ynew[n];
    float znew[n];
    float vx[3] = {0., 0., 0.};
    float vy[3] = {0., 0., 0.};
    float vz[3] = {0., 0., 0.};
    float m[3] = {3, 4, 5};
    int T = 100000;
    int t;
    for(t=0; t < T; t++){
        for(i=0; i < n; i++) {
            ax = 0.0;
            ay = 0.0;
            az = 0.0;
            for(j=0; j < n; j++) {
                dx = x[j] - x[i];
                dy = y[j] - y[i];
                dz = z[j] - z[i];
                invr = 1.0/sqrt(dx*dx + dy*dy + dz*dz + eps);
                invr3 = invr*invr*invr;
                f = G*m[j]*invr3;
                ax += f*dx;
                ay += f*dy;
                az += f*dz;
            }
            xnew[i] = x[i] + dt*vx[i] + 0.5*dt*dt*ax;
            ynew[i] = y[i] + dt*vy[i] + 0.5*dt*dt*ay;
            znew[i] = z[i] + dt*vz[i] + 0.5*dt*dt*az;
            vx[i] += dt*ax;
            vy[i] += dt*ay;
            vz[i] += dt*az;
        }
        for(i=0; i < n; i++) {
            x[i] = xnew[i];
            y[i] = ynew[i];
            z[i] = znew[i];
            if(t%100 == 0) {
                fprintf(fp, "%f\t%f\t%f\t", x[i], y[i], z[i]);
            }
        }
        if(t%100 == 0) {
            fprintf(fp, "\n");
        }
        /*for(i=0; i < n; i++) {
            printf("Particle %d: Xpos: %f, Ypos: %f, Zpos: %f\n", i, xnew[i], ynew[i], znew[i]);
        }
        */
    }
    fclose(fp);
}
