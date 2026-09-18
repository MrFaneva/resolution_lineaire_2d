#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS      1e-7
#define DET_EPS  1e-18
#define M_BOUND  1e15
typedef struct { double x, y; } Point;
typedef struct { double a, b, d; int signe; } Droite; // signe: -1=>=, 1=<=
double saisir() {
    double v;
    while (scanf("%lf", &v) != 1) { while (getchar()!='\n'); printf(" [!] Nombre valide : "); }
    return v;
}
int saisirSigne() {
    char buf[8]; int s;
    do {
        printf(" Signe (1=<= / 2=>=) : ");
        if (scanf("%7s", buf) != 1) {
            while (getchar()!='\n');
            s = 0;
            continue;
        }
        s = (buf[0]=='1') ? 1 : (buf[0]=='2') ? -1 : 0;
    } while (!s);
    return s;
}
int realisable(double x, double y, Droite *c, int n) {
    if (x < -EPS || y < -EPS) return 0;
    for (int i = 0; i < n; i++) {
        double v = c[i].a*x + c[i].b*y;
        double m = EPS * fmax(1.0, fmax(fabs(v), fabs(c[i].d)));
        if (c[i].signe == 1  && v > c[i].d + m) return 0;
        if (c[i].signe == -1 && v < c[i].d - m) return 0;
    }
    return 1;
}
int intersection(Droite d1, Droite d2, double *x, double *y) {
    double det = d1.a*d2.b - d2.a*d1.b;
    if (fabs(det) < DET_EPS) return 0;
    *x = (d1.d*d2.b - d2.d*d1.b) / det;
    *y = (d1.a*d2.d - d2.a*d1.d) / det;
    return 1;
}
int main() {
    int n, opt;
    double c1, c2;
    printf("=== OPTIMISEUR LINEAIRE 2D ===\n");
    do { printf("Nb contraintes (>=1) : "); n = (int)saisir(); } while (n <= 0);
    do { printf("Objectif (1=MAX / 2=MIN) : "); opt = (int)saisir(); } while (opt!=1 && opt!=2);
    printf("%s z = c1*x + c2*y\n c1: ", opt==1?"MAX":"MIN"); c1 = saisir();
    printf(" c2: "); c2 = saisir();
    Droite *dr = malloc((n+4)*sizeof(Droite));
    for (int i = 0; i < n; i++) {
        printf("--- Contrainte %d ---\n a: ", i+1); dr[i].a = saisir();
        printf(" b: "); dr[i].b = saisir();
        printf(" d: "); dr[i].d = saisir();
        dr[i].signe = saisirSigne();
    }
    // Bornes: x>=0, y>=0, x<=M_BOUND, y<=M_BOUND
    dr[n]   = (Droite){-1, 0, 0, -1};
    dr[n+1] = (Droite){ 0,-1, 0, -1};
    dr[n+2] = (Droite){ 1, 0, M_BOUND, 1};
    dr[n+3] = (Droite){ 0, 1, M_BOUND, 1};
    int m = n+4, nb = 0;
    Point *pts = malloc(m*m*sizeof(Point));
    for (int i = 0; i < m; i++)
        for (int j = i+1; j < m; j++) {
            double tx, ty;
            if (intersection(dr[i], dr[j], &tx, &ty))
                if (realisable(tx, ty, dr, n) && tx <= M_BOUND+EPS && ty <= M_BOUND+EPS)
                    pts[nb++] = (Point){tx, ty};
        }

    if (!nb) { printf("\n[!] Domaine vide.\n"); }
    else {
        double zbest = opt==1 ? -1e300 : 1e300;
        for (int i = 0; i < nb; i++) {
            double z = c1*pts[i].x + c2*pts[i].y;
            if ((opt==1 && z > zbest) || (opt==2 && z < zbest)) zbest = z;
        }
        int inf = 0;
        for (int i = 0; i < nb; i++) {
            double z = c1*pts[i].x + c2*pts[i].y;
            if (fabs(z-zbest) < EPS*fmax(1.0,fabs(zbest)))
                if (pts[i].x > M_BOUND*0.99 || pts[i].y > M_BOUND*0.99) inf = 1;
        }
        if (inf) printf("\n>>> SOLUTION NON BORNEE\n");
        else {
            printf("\n>>> z%s = %.4f | Sommet(s) optimal/aux :\n", opt==1?"max":"min", zbest);
            for (int i = 0; i < nb; i++) {
                if (fabs((c1*pts[i].x+c2*pts[i].y)-zbest) >= EPS*fmax(1.0,fabs(zbest))) continue;
                int dup = 0;
                for (int k = 0; k < i; k++)
                    if (fabs(pts[i].x-pts[k].x)<1e-4 && fabs(pts[i].y-pts[k].y)<1e-4) dup=1;
                if (!dup) printf("  -> (x=%.4f, y=%.4f)\n", pts[i].x, pts[i].y);
            }
        }
    }
    free(dr); free(pts);
    return 0;
}
