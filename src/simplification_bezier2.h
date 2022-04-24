/******************************************************************** 
  Interface du module simplification_bezier2
*********************************************************************/

#ifndef _SIMPLIFICATION_BEZIER2_H_
#define _SIMPLIFICATION_BEZIER2_H_

#include "liste_contour.h"
#include "types_macros.h"

/* Simplifie (par bezier de deg 2) tous les contours 
   d'une liste de contours suivant la distance seuil d
   Renvoie la liste simplifiée
*/
Liste_Contour simplification_bezier2(Liste_Contour LCONT, double d);


/*
  Algorithme de simplification par courbe de bezier de degre 2 dit de Douglas Peucker
  Simplification de la partie du contour CONT entre j1 et j2 avec d la distance seuil
  Renvoie une sequence de points (équivalente à une sequence de courbes)
  Procedure recursive
*/
Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point CONT, UINT j1, UINT j2, double d);


/* Détermination d'une courbe de Bezier de degre 2 suivant le tableau de point donne */
Bezier2 approx_bezier2(Tableau_Point CONT, UINT j1, UINT j2);

#endif /* _SIMPLIFICATION_BEZIER2_H_ */