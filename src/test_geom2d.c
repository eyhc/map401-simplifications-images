/****************************************************************************** 
  Programme de test du module geometrie2d
******************************************************************************/

#include <stdio.h>
#include "geometrie2d.h"

int main(int argc, char *argv[])
{
    Point p1 = creer_point(1,1);
    Point p2 = creer_point(5,-4.5);
    Vecteur v1 = creer_vecteur_xy(2, -2);
    Vecteur v2 = creer_vecteur_point(p1);
    Vecteur v3 = creer_vecteur_points(p1, p2);

    Point p;
    Vecteur v;

    printf("p1 = (1,1); p2 = (5,-4.5); v1 = (2, -2); v2 = vect(o,p1); v3 = vect(p1,p2)\n");

    /* somme */
    p = somme_points(p1, p2);
    printf("p1 + p2 = (%f,%f)\n", p.x, p.y);

    v = somme_vecteurs(v1, v2);
    printf("v1 + v2 = (%f,%f)\n", v.x, v.y);

    /* Multiplication par un scalaire */
    p = mult_point(p2, 3.1415);
    printf("3.1415 * p2 = (%f,%f)\n", p.x, p.y);

    v = mult_vecteur(v2, 3.5);
    printf("3.5 * v2 = (%f,%f)\n", v.x, v.y);

    /* Produit scalaire */
    printf("<v1,v2> = %f\n", produit_scalaire(v1, v2));
    printf("<v1,v3> = %f\n", produit_scalaire(v1, v3));
    
    /* norme */
    printf("|v1| = %f\n", norme_vecteur(v1));
    printf("|v2| = %f\n", norme_vecteur(v2));
    printf("|v3| = %f\n", norme_vecteur(v3));

    /* distance */
    printf("La distance entre le point 1 et le point 2 est de %f\n", distance_points(p1, p2));

    /* distance point segment */
    Point A = creer_point(1, 5);
    Point B = creer_point(3, 0);

    Point C = creer_point(0, 7.5);
    Point D = creer_point(10, 2);
    Point E = creer_point(8, 6);

    Segment AB = creer_segment_points(A, B);

    printf("\nSegment [AB] : A(1, 5) et B(3, 0):\n");
    printf("Distance du point (0, 7.5) de [AB] : %f\n", distance_point_segment(C, AB));
    printf("Distance du point (10, 2)  de [AB] : %f\n", distance_point_segment(D, AB));
    printf("Distance du point (8, 6)   de [AB] : %f\n", distance_point_segment(E, AB));
}