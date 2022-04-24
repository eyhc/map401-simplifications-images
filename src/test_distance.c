/****************************************************************************** 
  Programme de test de la fonction distance point_segment
******************************************************************************/

#include <stdio.h>
#include "geometrie2d.h"

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    double d; // la valeur de la distance
    double x, y; // coordonnees d'un point

    printf("Choississez les six coordonées et en commencant par les points du segments.\n");
    scanf("%lf", &x);
    scanf("%lf", &y);
    Point p1 = creer_point(x, y);

    scanf("%lf",&x);
    scanf("%lf",&y);
    Point p2 = creer_point(x, y);
    Segment s = creer_segment_points(p1, p2);

    scanf("%lf",&x);
    scanf("%lf",&y);
    Point p3 = creer_point(x, y);

    // Calcule et affiche les informations.
    d = distance_point_segment(p3, s);

    printf("La distance entre le segment passant par les points "
    "(%.2f, %.2f) et (%.2f, %.2f)\n"
    "et le point de cordonnées (%.2f, %.2f),\n"
    "est de %.10f\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, d);
=======
  double d; // la valeur de la distance
  double x, y; // coordonnees d'un point

  printf("Choississez les six coordonées et en commencant par les points du segments.\n");
  scanf("%lf", &x);
  scanf("%lf", &y);
  Point p1 = creer_point(x, y);

  scanf("%lf",&x);
  scanf("%lf",&y);
  Point p2 = creer_point(x, y);
  Segment s = creer_segment_points(p1, p2);

  scanf("%lf",&x);
  scanf("%lf",&y);
  Point p3 = creer_point(x, y);

  // Calcule et affiche les informations.
  d = distance_point_segment(p3, s);

  printf("La distance entre le segment passant par les points "
  "(%.2f, %.2f) et (%.2f, %.2f)\n"
  "et le point de cordonnées (%.2f, %.2f),\n"
  "est de %.10f\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, d);
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}
