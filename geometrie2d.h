/********************************************************************* 
  Interface du module geometrie2d
*********************************************************************/

#ifndef _GEOMETRIE2D_H_
#define _GEOMETRIE2D_H_

/* Type Vecteur */
typedef struct Vecteur_ { double x, y; } Vecteur;

/* Type Point */
typedef struct Point_ { double x, y; } Point;

/* Type Segment */
typedef struct Segment_ { Point A, B; } Segment;

/* Type Courbe de Bezier de dimension 2*/
typedef struct Bezier2_ { Point C1, C2, C3; } Bezier2;

/* Type Courbe de Bezier de dimension 3*/
typedef struct Bezier3_ { Point C1, C2, C3, C4; } Bezier3; 

/* Creation d'une courbe de bezier a partir de trois points de controle */
Bezier2 creer_bezier2_points(Point p1, Point p2, Point p3);

/* Creation d'une courbe de bezier a partir de trois points de controle */
Bezier3 creer_bezier3_points(Point p1, Point p2, Point p3, Point p4);

/* Creation du point des coordonnees x, y */
Point creer_point(double x, double y);

/* Creation d'un vecteur de coordonnees x, y */
Vecteur creer_vecteur_xy(double x, double y);

/* Creation d'un vecteur a partir d'un point */
Vecteur creer_vecteur_point(Point p);

/* Creation d'un vecteur a partir de deux points */
Vecteur creer_vecteur_points(Point p1, Point p2);

/* Creation d'un segment a partir de deux points */
Segment creer_segment_points(Point p1, Point p2);

/* Somme deux points */
Point somme_points(Point p1, Point p2);

/* Somme deux vecteurs */
Vecteur somme_vecteurs(Vecteur v, Vecteur w);

/* Multiplication d'un point par un scalaire */
Point mult_point(Point p, double a);

/* Multiplication d'un vecteur par un scalaire */
Vecteur mult_vecteur(Vecteur v, double a);

/* Calcule le produit scalaire de deux vecteurs */
double produit_scalaire(Vecteur v, Vecteur w);

/* Retourne la norme euclidienne (norme 2) d'un vecteur */
double norme_vecteur(Vecteur v);

/* Retourne la distance (euclidienne) entre deux points */
double distance_points(Point p1, Point p2);

/* Calcule la distance entre un point et un segment */
double distance_point_segment(Point P, Segment S);

/* calcule du point C(t) d'une courbe de bezier 2 */
Point point_courbe_bezier2(Bezier2 C, double t);

/* calcule du point C(t) d'une courbe de bezier  3 */
Point point_courbe_bezier3(Bezier3 C, double t);

/* convertit une courbe de bezier de degre 2 en courbe de degre 3 */
Bezier3 conversion_bezier2_vers_3(Bezier2 B);

/* Approche la distance entre un point P et une courbe de bezier2 
   Avec n subdivisions */
double distance_point_bezier2(Point P, Bezier2 C, double ti);

/* Approche la distance entre un point P et une courbe de bezier3 
   Avec n subdivisions */
double distance_point_bezier3(Point P, Bezier3 C, double ti);


#endif /* _GEOMETRIE2D_H_ */
