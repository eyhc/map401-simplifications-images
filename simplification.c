/***************************************************************************** 
 *    Programme de test des modules simplification
 *****************************************************************************/

#include "types_macros.h"
#include "image.h"
#include "sortie_eps.h"
#include "extraction_contours.h"
#include "simplification_segments.h"
#include "simplification_bezier2.h"
#include "simplification_bezier3.h"

/*
    Fonction principale que permet de simplifier suivant 
      des segments, courbes de bezier 2 ou 3.

    L'ensemble des arguments sont passés par paramètres
*/
int main(int argc, char *argv[])
{
    /* Vérifie qu'il y a le bon nombre d'arguments*/
    if(argc < 4){
        printf("Usage : %s image_source type_simplification dist_seuil [image_dest]\n", argv[0]);
        printf("    type_simplification : \n"
            "        - 1 : segments\n"
            "        - 2 : bezier 2\n"
            "        - 3 : bezier 3\n");
        exit(1);
    }

    // On lit l'image
    Image im = lire_fichier_image(argv[1]);

    // On récupère les dimmensions
    UINT l = largeur_image(im);
    UINT h = hauteur_image(im);

    // On lit tous les contours
    Liste_Contour L = lire_contours(im);

    // on ecrit le nom du fihcier puis le contour
    printf("Image : %s (%d x %d) \n", argv[1], l, h);
    printf("    nombres de contours : %d\n", nombre_contours(L));
    printf("    nb segments sans simplification : %d\n", nombre_segments_contours(L));

    // on recupère le type de simplification
    int type = strtol(argv[2], NULL, 10);

    // on recupère la distance d
    double d = strtod(argv[3], NULL);

    // on applique la simplification
    Liste_Contour LS;
    switch(type) {
        case 1: LS = simplification_segments(L, d); break;
        case 2: LS = simplification_bezier2(L, d); break;
        default: LS = simplification_bezier3(L, d); break;
    }

    // on ecrit le resultat dans le fichier resultat
    switch(type) {
        case 1:
            printf("    nb segments avec simplification d=%.2lf : %d\n", d, nombre_segments_contours(LS));
            break;
        case 2: 
            printf("    nb courbes bezier 2 avec simplification d=%.2lf : %d\n", d, nombre_beziers_contours(LS));
            break;
        default:
            printf("    nb courbes bezier 3 avec simplification d=%.2lf : %d\n", d, nombre_beziers_contours(LS));
            break;
    }

    // FICHIER SORTIE EPS
    if (argv[4] != NULL)
    {
        // on ouvre le fichier eps
        FILE* feps = fopen(argv[4], "w+");

        //On verifie que le fichier est ouvert
        if(feps == NULL) {
            printf("Erreur (sortie eps dans simplification segments):"
                " ouverture fichier a echoue.\n");
            exit(1);
        }
        
        // on ecrit les contours dans le fichier eps
        switch(type) {
            case 1: 
                ecrire_contours_eps(feps, LS, l, h, FILL);
                break;
            default:
                ecrire_contours_bezier_eps(feps, LS, l, h, FILL);
                break;
        }

        // on ferme le fichier
        fclose(feps);
    }

    // On supprime
    supprimer_liste_contour(LS);
    supprimer_liste_contour(L);
    supprimer_image(&im);
}
