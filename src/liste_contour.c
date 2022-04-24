/******************************************************************** 
  Implémentation du module sequence de contours
*********************************************************************/

#include "liste_contour.h"

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Contour *creer_element_liste_contour(Contour c) {
    // Allocation mémoire
    Cellule_Liste_Contour *cel;
    cel = (Cellule_Liste_Contour *)malloc(sizeof(Cellule_Liste_Contour));
    if (cel == NULL) {
        fprintf(stderr, "creer_element_liste_Contour : allocation impossible\n");
        exit(-1);
    }

    // Initialisation de attributs
    cel->data = c;
    cel->suiv = NULL;

    return cel;
}

/* creer une liste vide */
Liste_Contour creer_liste_contour_vide() {
    Liste_Contour L = {0, NULL, NULL};
    return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_contour(Liste_Contour L, Contour c) {
    Cellule_Liste_Contour *cel;
    
    cel = creer_element_liste_contour(c);
    /* si c'est le premier element de la liste */
    if (L.taille == 0) {
        L.first = L.last = cel;
    }
    else {
        L.last->suiv = cel;
        L.last = cel;
    }
    L.taille++;
    return L;
}

/* suppression de tous les elements de la liste, renvoie la liste L vide */
Liste_Contour supprimer_liste_contour(Liste_Contour L) {
    Cellule_Liste_Contour *cel = L.first;
    
    while (cel) 
    {        
        Cellule_Liste_Contour *suiv = cel->suiv;
        supprimer_liste_Point(cel->data);
        free(cel);
        cel = suiv;
    }
    L.first = L.last = NULL; L.taille = 0;
    return L;
}

/* ecrit le contour dans un fichier dont le nom est donné en argument */
void ecrire_liste_contours_fichier(Liste_Contour L, FILE* f) {
    // on ecrit le nombre de contour
    fprintf(f, "%d\n\n", nombre_contours(L));

    // On ecrit chaque contour (un par un) dans le fichier
    Cellule_Liste_Contour* cel = L.first;
    while (cel != NULL) {
        ecrire_contour_fichier(cel->data, f);
        fprintf(f, "\n");
        cel = cel->suiv;
    }
}

/* Retourne le nombre de contour d'une liste de contours L */
UINT nombre_contours(Liste_Contour L) {
    return L.taille;
}

/* Retourne le nombre de segments total de tous les contours de L */
UINT nombre_segments_contours(Liste_Contour L) {
    UINT nb_seg = 0;

    // schema de parcours et utilisation de nb segment dans contour
    Cellule_Liste_Contour *cel = L.first;

    while (cel) {
        nb_seg += nb_segments_contour(cel->data);
        cel = cel->suiv;
    }

    return nb_seg;
}

/* Retourne le nombre de courbes de bezier de tous les contours de L */
UINT nombre_beziers_contours(Liste_Contour L) {
    UINT nb_c = 0;

    // schema de parcours et utilisation de nb segment dans contour
    Cellule_Liste_Contour *cel = L.first;

    while (cel) {
        nb_c += nb_beziers_contour(cel->data);
        cel = cel->suiv;
    }

    return nb_c;
}