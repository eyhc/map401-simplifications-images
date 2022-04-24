/******************************************************************** 
  Interface du module sequence
*********************************************************************/

#ifndef _SEQUENCE_POINT_H_
#define _SEQUENCE_POINT_H_

#include "geometrie2d.h" /* Utilisation du type point */
#include "types_macros.h"

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
    Point data;    /* donnee de l'element de liste */
    struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
    unsigned int taille;        /* nombre d'elements dans la liste */
    Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
    Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
                                /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
    unsigned int taille; /* nombre d'elements dans le tableau */
    Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;

/* definition du type contour */
typedef Liste_Point Contour;

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* creer une liste vide */
Liste_Point creer_liste_Point_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* suppression de tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concatene L2 à la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* creer une sequence de points sous forme d'un tableau de points 
   à partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* ecrire le contour L à l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Contour C);

/* ecrit le contour dans un fichier dont le nom est donné en argument */
void ecrire_contour_fichier(Contour C, FILE* fichier);

/* Retourne le nombre de segments d'un contour C */
UINT nb_segments_contour(Contour C);

/* Retourne le nombre de courbe de bezier d'un contour C */
UINT nb_beziers_contour(Contour C);

#endif /* _SEQUENCE_POINT_H_ */