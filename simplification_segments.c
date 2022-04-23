/******************************************************************** 
  Implémentation du module simplification_segments
*********************************************************************/

#include "simplification_segments.h"


/* Simplifie (par segments) tous les contours d'une liste de contours
   Suivant la distance seuil d
   Renvoie la liste simplifiée
*/
Liste_Contour simplification_segments(Liste_Contour LCONT, double d) {
    // On creer une nouvelle liste de contours l
    Liste_Contour l = creer_liste_contour_vide();

    // On parcourt tous les contours
    Cellule_Liste_Contour* cel = LCONT.first;
    while (cel != NULL)
    {
        // On transforme en tableau
        Tableau_Point tab = sequence_points_liste_vers_tableau(cel->data);

        // On simplifie
        Contour csimp = simplification_douglas_peucker(tab, 0, tab.taille-1, d);

        // On ferme le contour simplifié en ecrivant le dernier point à la fin
        csimp = ajouter_element_liste_Point(csimp, csimp.first->data);

        // On ajoute le contour simplifié 
        l = ajouter_element_liste_contour(l, csimp);

        // on passe au suivant
        cel = cel->suiv;
    }
    
    // on revoie la liste de contours simplifiés
    return l;
}


/* Algorithme de simplification par segment dit de Douglas Peucker
   Simplification de la partie du contour CONT entre j1 et j2 avec d la distance seuil
   Renvoie une sequence de points (équivalente à une sequence de segment)
   Procedure recursive
*/
Liste_Point simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, double d) {
    Liste_Point L;  // la liste de point retourner

    // on creer le segment
    Segment s = creer_segment_points(CONT.tab[j1], CONT.tab[j2]);

    // initialisation pour trouver le point le plus loin du segment
    double max = 0;
    double dis;
    int indice = 0;

    //  Test si les points sont en dessous de la distance seuil. 
    for (int i = j1; i <= j2; i++) {
        dis = distance_point_segment(CONT.tab[i], s);
        if (max < dis) {
            // On change le maximum si necessaire et son indice aussi.
            max = dis;
            indice = i;
        }
    }

    if (max <= d) {
        /* cas de base : on simplifie suivant le segment s
           Ajout du premier point
           (le second sera mis soit dans l'appel recursif et la concatenation
            ou il suffit de recopier la tete un queue sinon) */
        L = creer_liste_Point_vide();
        L = ajouter_element_liste_Point(L, CONT.tab[j1]);
    }
    else {
        /* cas recursif : on decoupe le probleme en deux à l'aide du point
           le plus éloigné */
        Liste_Point l1 = simplification_douglas_peucker(CONT, j1, indice, d);
        Liste_Point l2 = simplification_douglas_peucker(CONT, indice, j2, d);
        L = concatener_liste_Point(l1, l2);
    }

    return L;
}
