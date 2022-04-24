/******************************************************************** 
  Implémentation du module geometrie2d
*********************************************************************/

#include <math.h>
#include "geometrie2d.h"

/* Creation du point des coordonnees x, y */
Point creer_point(double x, double y) {
    Point P = {x, y};
    return P;
}

/* Creation d'un vecteur de coordonnees x, y */
Vecteur creer_vecteur_xy(double x, double y) {
    Vecteur V = {x, y};
    return V;
}

/* Creation d'un vecteur a partir d'un point */
Vecteur creer_vecteur_point(Point p) {
    Vecteur V = {p.x, p.y};
    return V;
}

/* Creation d'une courbe de bezier de dimension 2 a partir de trois points */
Bezier2 creer_bezier2_points(Point p1, Point p2, Point p3) {
    Bezier2  B = {p1, p2, p3};
    return B;
}

/* Creation d'une courbe de bezier de dimension 3 a partir de quatre points */
Bezier3 creer_bezier3_points(Point p1, Point p2, Point p3, Point p4) {
    Bezier3  B = {p1, p2, p3, p4};
    return B;
}


/* Creation d'un vecteur a partir de deux points */
Vecteur creer_vecteur_points(Point p1, Point p2) {
    Vecteur V = {p2.x - p1.x, p2.y - p1.y};
    return V;
}

/* Creation d'un segment a partir de deux points */
Segment creer_segment_points(Point p1, Point p2) {
    Segment S = {p1, p2};
    return S;
}

/* Somme deux points */
Point somme_points(Point p1, Point p2) {
    Point p = {p1.x + p2.x, p1.y + p2.y};
    return p;
}

/* Somme deux vecteurs */
Vecteur somme_vecteurs(Vecteur v, Vecteur w) {
    return creer_vecteur_xy(v.x + w.x, v.y + w.y);
}

/* Multiplication d'un point par un scalaire */
Point mult_point(Point p, double a) {
    return creer_point(a*p.x, a*p.y);
}

/* Multiplication d'un vecteur par un scalaire */
Vecteur mult_vecteur(Vecteur v, double a) {
    return creer_vecteur_xy(a*v.x, a*v.y);
}

/* Calcule le produit scalaire de deux vecteurs */
double produit_scalaire(Vecteur v, Vecteur w) {
    return v.x*w.x + v.y*w.y;
}

/* Retourne la norme euclidienne (norme 2) d'un vecteur */
double norme_vecteur(Vecteur v) {
    return sqrt(produit_scalaire(v, v));
}

/* Retourne la distance (euclidienne) entre deux points */
double distance_points(Point p1, Point p2) {
    Vecteur v = creer_vecteur_points(p1, p2);
    return norme_vecteur(v);
}

/* Calcule la distance entre un point et un segment */
double distance_point_segment(Point P, Segment S) {
    Vecteur AP = creer_vecteur_points(S.A, P);
    Vecteur AB = creer_vecteur_points(S.A, S.B);

    /* on calcule lambda tel que :
         - Q = A + lambda * (B - A)
         - <AB,PQ> = 0
         ie lamdba = <AP,AB> / <AB,AB>
    */
    double p = produit_scalaire(AB, AB);
    if (p == 0) return norme_vecteur(AP); // on ne divise pas par 0 !

    double lambda = produit_scalaire(AP, AB) / p;

    // cas du projeté orthogonal Q à gauche
    if (lambda < 0)
        return norme_vecteur(AP);

    // cas du projeté orthogonal Q à droite
    if (lambda > 1)
        return distance_points(S.B, P);

    // Cas du projeté orthogonal Q sur le segment
    // Q = A + lambda * (B-A)
    Point Q;
    Q = mult_point(S.A, -1);     // Q = -A
    Q = somme_points(S.B, Q);    // Q = B - A
    Q = mult_point(Q, lambda);   // Q = lambda (B-A)
    Q = somme_points(Q, S.A);

    return distance_points(Q, P);
}

/* calcule du point C(t) d'une courbe de bezier 2 */
Point point_courbe_bezier2(Bezier2 C, double t) {
    Point P1 = mult_point(C.C1, (1-t)*(1-t));  // P1 = (1-t)²C1
    Point P2 = mult_point(C.C2, 2*t*(1-t));    // P2 = 2t(1-t)C2
    Point P3 = mult_point(C.C3, t*t);          // P3 = t²C3
    P3 = somme_points(P3, P2);                 
    P3 = somme_points(P3, P1);                 // P = P1 + P2 + P3

    return P3;
}

/* calcule du point C(t) d'une courbe de bezier 3 */
Point point_courbe_bezier3(Bezier3 C, double t) {
    Point P1 = mult_point(C.C1, (1-t)*(1-t)*(1-t));  // P1 = (1-t)³C1
    Point P2 = mult_point(C.C2, 3*t*(1-t)*(1-t));    // P2 = 3t(1-t)²C2
    Point P3 = mult_point(C.C3, 3*t*t*(1-t));        // P3 = 3t²(1-t)C3
    Point P4 = mult_point(C.C4, t*t*t);              // P4 = t³C4
    P4 = somme_points(P4, P1);    
    P4 = somme_points(P4, P2);
    P4 = somme_points(P4, P3);                 // P = P1 + P2 + P3 + P4
    return P4;
}

/* convertit une courbe de bezier de degre 2 en courbe de degre 3 */
Bezier3 conversion_bezier2_vers_3(Bezier2 B) {
    // C1' = B.C1 et C4'=B.C3
    
    // C2' = (B.C1 + 2 B.C2)/3
    Point C2 = somme_points(B.C1, mult_point(B.C2, 2));
    C2 = mult_point(C2, (double)1/3);

    // C3' = (B.C3 + 2 B.C2)/3
    Point C3 = somme_points(B.C3, mult_point(B.C2, 2));
    C3 = mult_point(C3, (double)1/3);

    // retourne B[C1',C2',C3',C4']
    return creer_bezier3_points(B.C1, C2, C3, B.C3);
}

/* Approche la distance entre un point P et une courbe de bezier2
   A l'aide du point C(ti) */
double distance_point_bezier2(Point P, Bezier2 C, double ti) {
    return distance_points(point_courbe_bezier2(C, ti), P);
}

/* Approche la distance entre un point P et une courbe de bezier3
   A l'aide du point C(ti) */
double distance_point_bezier3(Point P, Bezier3 C, double ti) {
    return distance_points(point_courbe_bezier3(C, ti), P);
}