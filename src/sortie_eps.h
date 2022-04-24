/******************************************************************** 
  Interface du module sortie_eps
*********************************************************************/

#ifndef _EPS_H_
#define _EPS_H_

#include "liste_contour.h"
#include "types_macros.h"

/* Definition du type de remplissage */
typedef enum {STROKE, FILL} Mode;

/*Ecrit l'entiereté de l'image à plusieurs contours */
void ecrire_contours_eps(FILE* fichier, Liste_Contour liste, UINT largeur, UINT hauteur, Mode m);

/* Ecrit l'entiereté de l'image à plusieurs contours de type bezier 3 */
void ecrire_contours_bezier_eps(FILE* f, Liste_Contour L, UINT l, UINT h, Mode m);


/* Ecrit le contour dans un fichier dont les entetes on déjà été écrites */
void ecrire_contour_eps(FILE* nom, Contour c, UINT largeur, UINT hauteur);

/* Ecrit le contour avec des courbes de bezier dans un fichier dont les entetes on déjà été écrites */
void ecrire_contour_bezier_eps(FILE* f, Contour c, UINT l, UINT h);


/* Ecrit l'entete du fichier eps
   Necessite les dimensions du cadre eps */
void ecrire_entete_eps(FILE* nom, UINT largeur, UINT hauteur);

/* Ecrit la fin du fichier */
void ecrire_fin_eps(FILE* nom, Mode m);

#endif /* _EPS_H_ */