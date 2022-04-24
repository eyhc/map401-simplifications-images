/******************************************************************** 
  Interface du module contour
*********************************************************************/

#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "image.h"
#include "geometrie2d.h"
#include "contour.h"
#include "liste_contour.h"
#include "types_macros.h"


/* definition du type orientation (du robot) */
typedef enum { Nord, Sud, Est, Ouest } Orientation;

/* definition du type position (du robot) */
typedef Point Position;

/* Determine tous les contours de l'image I */
Liste_Contour lire_contours(Image I);

/* lire le contour d'une image en partant de la position
  donnee de depart et l'orientation EST 
  Supprime les cases noires limitrophes de l'image masque M
  Retoune un contour */
Contour lire_contour(Image I, Image *M, Position p);

/* trouve la position de depart (du robot)
   en partant du pixel (x, y)
   si l'image est vide, on retourne la position (-1,-1) */
Position trouver_position_depart(Image I, int x, int y);

/* ecrit la position (du robot) */
void ecrire_position(Position p);

/* ecrit la position (du robot) */
void ecrire_orientation(Orientation o);

/* Calcule la nouvelle orientation du robot */
Orientation nouvelle_orientation(Image I, Position p, Orientation o);

/* avancer suivant l'orientation (le robot) */
Position avancer(Position p, Orientation o);

/* Tourne d'un quart de tour à gauche */
Orientation tourner_gauche(Orientation o);

/* Tourne d'un quart de tour à droite */
Orientation tourner_droite(Orientation o);

/* retourne le pixel à gauche dans l'image I à la position p
et suivant l'orientation o */
Pixel valeur_pixel_gauche(Image I, Position p, Orientation o);

/* retourne le pixel à droite dans l'image I à la position p
et suivant l'orientation o */
Pixel valeur_pixel_droit(Image I, Position p, Orientation o);

#endif /* _CONTOUR_H_ */