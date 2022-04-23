/******************************************************************** 
  Implémentation du module sortie_eps
*********************************************************************/

#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "sortie_eps.h"

/* Ecrit l'entiereté de l'image à plusieurs contours */
void ecrire_contours_eps(FILE* f, Liste_Contour L, UINT l, UINT h, Mode m) {
    // On écrit d'abord l'entete
    ecrire_entete_eps(f, l, h);

    // On fait un schema de parcours et appelle ecrire_contour_eps pour chaque contour
    Cellule_Liste_Contour *cel = L.first;
    while(cel != NULL) {
        ecrire_contour_eps(f, cel->data, l, h);
        cel = cel->suiv;
    }

    // On écrit la fin du fichier
    ecrire_fin_eps(f, m);
}

/* Ecrit l'entiereté de l'image à plusieurs contours de type bezier 3 */
void ecrire_contours_bezier_eps(FILE* f, Liste_Contour L, UINT l, UINT h, Mode m) {
    // On écrit d'abord l'entete
    ecrire_entete_eps(f, l, h);

    // On fait un schema de parcours et appelle ecrire_contour_eps pour chaque contour
    Cellule_Liste_Contour *cel = L.first;
    while(cel != NULL) {
        ecrire_contour_bezier_eps(f, cel->data, l, h);
        cel = cel->suiv;
    }

    // On écrit la fin du fichier
    ecrire_fin_eps(f, m);
}

/* Ecrit le contour avec des segments dans un fichier dont les entetes on déjà été écrites */
void ecrire_contour_eps(FILE* f, Contour c, UINT l, UINT h) {
    //On ecrit le contenu des fichiers.
    Cellule_Liste_Point* cel = c.first;

    // on écrit le premier point du contour
    fprintf(f,"%.1f %.1f m ", cel->data.x, h - cel->data.y);
    cel = cel->suiv;
    
    // On ecrit les points du contour qui suivent
    for(int i=1 ;i < c.taille-1; i++){
        // On ecrit le point courant
        fprintf(f,"%.1f %.1f l ", cel->data.x, h - cel->data.y);
        
        // On change en passant au point suivant
        cel = cel->suiv;
    }
}

/* Ecrit l'entete du fichier eps
   Necessite les dimensions du cadre eps*/
void ecrire_entete_eps(FILE* f, UINT l, UINT h) {
    fprintf(f, "%c!PS-Adobe-3.0 EPSF-3.0\n", '%');
    fprintf(f, "%c%cBoundingBox: %d %d %d %d\n", '%', '%', 0, 0, l, h);
    fprintf(f, "0 setlinewidth\n");
    fprintf(f, "/l {lineto} def\n");
    fprintf(f, "/m {moveto} def\n");
    fprintf(f, "/c {curveto} def\n");
}

/* Ecrit la fin du fichier*/
void ecrire_fin_eps(FILE* f, Mode m) {
    // mode de tracé
    if (m == FILL)
        fprintf(f,"\nfill\n");
    else
        fprintf(f,"\nstroke\n");
    //affichage
    fprintf(f,"showpage\n");
}

/* Ecrit le contour avec des courbes de bezier dans un fichier dont les entetes on déjà été écrites */
void ecrire_contour_bezier_eps(FILE* f, Contour c, UINT l, UINT h) {
    //On ecrit le contenu des fichiers.
    Cellule_Liste_Point* cel = c.first;

    // on écrit le premier point du contour
    fprintf(f,"%.1f %.1f m ", cel->data.x, h - cel->data.y);
    cel = cel->suiv;

    // On ecrit les points du contour qui suivent
    for (int i = 0; i < c.taille-1; i += 3) {
        // On ecrit le point courant, cel->data.x, h - cel->data.y
        fprintf(f,"%.1f %.1f %.1f %.1f %.1f %.1f c ", cel->data.x, h - cel->data.y, cel->suiv->data.x, h - cel->suiv->data.y, cel->suiv->suiv->data.x, h - cel->suiv->suiv->data.y);
        
        // On change en passant au point suivant
        cel = cel->suiv->suiv->suiv;
    }
} 