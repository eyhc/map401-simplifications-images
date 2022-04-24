/******************************************************************** 
  Interface du module sequence de contours
*********************************************************************/

#ifndef _SEQUENCE_CONTOUR_H_
#define _SEQUENCE_CONTOUR_H_

#include "contour.h"   /* utilisation du type contour */
#include "types_macros.h"

/*---- le type cellule de liste de Contour ----*/
typedef struct Cellule_Liste_Contour_
{
	Contour data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Contour_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Contour;

/*---- le type liste de contour ----*/
typedef struct Liste_Contour_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Contour *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Contour *last;  /* pointeur sur le dernier element de la liste */
	                            /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour;

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Contour *creer_element_liste_contour(Contour c);

/* creer une liste vide */
Liste_Contour creer_liste_contour_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_contour(Liste_Contour L, Contour c);

/* suppression de tous les elements de la liste, renvoie la liste L vide */
Liste_Contour supprimer_liste_contour(Liste_Contour L);

/* ecrit le contour dans un fichier dont le nom est donné en argument */
void ecrire_liste_contours_fichier(Liste_Contour L, FILE* fichier);

/* Retourne le nombre de contour d'une liste de contours L */
UINT nombre_contours(Liste_Contour L);

/* Retourne le nombre de segments total de tous les contours de L */
UINT nombre_segments_contours(Liste_Contour L);

/* Retourne le nombre de courbes de bezier de tous les contours de L */
UINT nombre_beziers_contours(Liste_Contour L);

#endif /* _SEQUENCE_CONTOUR_H_ */