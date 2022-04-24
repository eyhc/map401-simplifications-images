/**************************************************************************
 *  Programme de test d'approximation par une courbe de bezier de degre 3
 **************************************************************************/

#include "simplification_bezier3.h"

int main(int argc, char *argv[])
{
  int n;       // on a n+1 points
  double x, y; // coordonnees d'un point
  Liste_Point l = creer_liste_Point_vide(); // la liste de point

  printf("Entrez le nombre de points moins un (n) : \n");
  scanf("%d", &n);

  // On entre les coordonnees de chaque point Pi
  for (int i = 0; i <= n; i++)
  {
    printf("Entrer les deux coordonnées de P%d :\n", i);
    scanf("%lf,%lf", &x, &y);

    Point p = creer_point(x, y);
    l = ajouter_element_liste_Point(l, p);
  }

  // Calcule et affiche les informations.
  Tableau_Point tab = sequence_points_liste_vers_tableau(l);
  Bezier3 B = approx_bezier3(tab, 0, n);
  

  printf("Les trois points de controle sont les suivants :\n"
  "C0 = (%.6f, %.6f),\nC1 = (%.6f, %.6f),\nC2 = (%.6f, %.6f) et\n"
  "C3 = (%.6f, %.6f).\n", B.C1.x, B.C1.y, B.C2.x, B.C2.y, B.C3.x, B.C3.y, B.C4.x, B.C4.y);

  /*for (int i = 0; i <= n; i++)
  {
    double dis = distance_point_bezier3(tab.tab[i], B, (double)i/n);
    printf("distance i = %d, d = %.8f\n", i, dis);
  }*/
}