/****************************************************************************** 
  Programme de test du module contour
******************************************************************************/

#include <string.h>
#include "types_macros.h"
#include "image.h"
#include "sortie_eps.h"
#include "extraction_contours.h"

/* Prend en paramètre une image*/
int main(int argc,char **argv){

    /* Vérifie qu'il y a le bon nombre de paramètres */
    if (argc < 4) {
        printf("Usage : %s fichier_image type_sortie fichier_sortie [mode]\n", argv[0]);
        printf("    type_sortie : eps | txt \n"
               "    mode (dans le cas eps) : FILL | STROKE  (par defaut: FILL)\n");
        exit(1);
    }

    // On lit l'image
    Image im = lire_fichier_image(argv[1]);
    // On récupère les dimmensions
    UINT l = largeur_image(im);
    UINT h = hauteur_image(im);

    // On lit tous les contours
    Liste_Contour L = lire_contours(im);

    /* Affichage des infos à l'écran */
    //info image
    printf("Image : %s (%dx%d)\n", argv[1], l, h);

    // nombre de contours
    printf("Nombre de contours : %d\n", nombre_contours(L));

    // nombre total de segments
    printf("Nombre total de segments : %d\n", nombre_segments_contours(L));

    /* Affiche dans le fichier */
    // On ouvre le fichier de résultat
    FILE *f = fopen(argv[3], "w+");

    // On verifie que le fichier est ouvert
    if(f == NULL){
        printf("Erreur (Extraction): ouverture fichier a echoue.\n");
        exit(1);
    }

    // Sortie au format text
    if (!strcmp(argv[2], "txt")) {
        // on ecrit les contours dans le fichier
        ecrire_liste_contours_fichier(L, f);
    }

    // Sortie au format eps
    if (!strcmp(argv[2], "eps")) {
        // On écrit le fichier image au format eps
        if (argc > 4 && !strcmp(argv[4], "STROKE"))
            ecrire_contours_eps(f, L, l, h, STROKE);
        else
            ecrire_contours_eps(f, L, l, h, FILL);
    }

    // on ferme le fichier
    fclose(f);

    // On supprime 
    supprimer_liste_contour(L);
    supprimer_image(&im);
}
