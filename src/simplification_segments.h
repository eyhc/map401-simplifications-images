/******************************************************************** 
  Interface du module simplification_segments
*********************************************************************/

#ifndef _SIMPLIFICATION_SEGMENTS_H_
#define _SIMPLIFICATION_SEGMENTS_H_

#include "liste_contour.h"
#include "types_macros.h"

/*
  Simplifie (par segments) tous les contours d'une liste de contours
  Suivant la distance seuil d
  Renvoie la liste simplifiée
*/
Liste_Contour simplification_segments(Liste_Contour LCONT, double d);

/*
  Algorithme de simplification par segment dit de Douglas Peucker
  Simplification de la partie du contour CONT entre j1 et j2 avec d la distance seuil
  Renvoie une sequence de points (équivalente à une sequence de segment)
  Procedure recursive
*/
Liste_Point simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, double d);

#endif /* _SIMPLIFICATION_SEGMENTS_H_ */