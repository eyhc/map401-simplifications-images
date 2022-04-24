/***************************************************************************** 
 *    Implémentation du module simplification par bezier2
 *****************************************************************************/

#include "simplification_bezier2.h"

/* Simplifie (par bezier de deg 2) tous les contours 
   d'une liste de contours suivant la distance seuil d
   Renvoie la liste simplifiée
*/
Liste_Contour simplification_bezier2(Liste_Contour LCONT, double d) {
    // On creer une nouvelle liste de contours l
    Liste_Contour l = creer_liste_contour_vide();

    // On parcourt tous les contours
    Cellule_Liste_Contour* cel = LCONT.first;
    while (cel != NULL)
    {
        // On transforme en tableau
        Tableau_Point tab = sequence_points_liste_vers_tableau(cel->data);

        // On simplifie
        Contour csimp = simplification_douglas_peucker_bezier2(tab, 0, tab.taille-1, d);

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


/*
  Algorithme de simplification par courbe de bezier de degre 2 dit de Douglas Peucker
  Simplification de la partie du contour CONT entre j1 et j2 avec d la distance seuil
  Renvoie une sequence de points (équivalente à une sequence de courbes)
  Procedure recursive
*/
Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point CONT, UINT j1, UINT j2, double d) {
    Liste_Point L;  // la liste de point à retourner

    // nb de segments dans le contour
    int n = j2 - j1;

    // on creer le segment
    Bezier2 B = approx_bezier2(CONT, j1, j2);

    // initialisation pour trouver le point le plus loin du segment
    double max = 0;
    int k = j1;
    //  Test si les points sont en dessous de la distance seuil. 
    for (int j = j1+1; j <= j2; j++) {
        int i = j-j1;
        double ti = (double)i/n;
        double dj = distance_point_bezier2(CONT.tab[j], B, ti);
        if (max < dj) {
            // On change le maximum si necessaire et son indice aussi.
            max = dj;
            k = j;
        }
    }

    if (max <= d) {
        /* cas de base : on simplifie suivant le segment s
           Ajout du premier point
           (le second sera mis soit dans l'appel recursif et la concatenation
            ou il suffit de recopier la tete un queue sinon) */
        L = creer_liste_Point_vide();
        Bezier3 B3 = conversion_bezier2_vers_3(B);
        L = ajouter_element_liste_Point(L, B3.C1);
        L = ajouter_element_liste_Point(L, B3.C2);
        L = ajouter_element_liste_Point(L, B3.C3);
    }
    else {
        /* cas recursif : on decoupe le probleme en deux à l'aide du point
           le plus éloigné */
        Liste_Point l1 = simplification_douglas_peucker_bezier2(CONT, j1, k, d);
        Liste_Point l2 = simplification_douglas_peucker_bezier2(CONT, k, j2, d);
        L = concatener_liste_Point(l1, l2);
    }

    return L;
}


/* Détermination d'une courbe de Bezier de degre 2 suivant le tableau de point donne */
Bezier2 approx_bezier2(Tableau_Point CONT, UINT j1, UINT j2) {
    Point C1 = CONT.tab[j1];     // C1 est le premier point de controle 
    Point C3 = CONT.tab[j2]; // C3 est le dnier point du ctour ie 3e pt de controle
    Point C2; // Deuxieme point de controle

    // on calcule le nombre de points du contour
    double n = j2 - j1;

    /* On fait les deux cas soit il y a deux points soit il y en a plus */
    if (n == 1){
        C2 = mult_point(somme_points(C1, C3), 0.5);
    } else {
        
        double alpha = (3 * n)/((n * n) - 1);
        double beta = (1 - (2 * n))/(2 * (n + 1));

        // on applique la formule qui calcule C2
        C2 = mult_point(somme_points(C1, C3), beta);
        for(int i=j1+1; i < j2; i++) {
            C2 = somme_points(C2, mult_point(CONT.tab[i], alpha));
        }
    }

    // on cree et retourne la courbe de bezier
    Bezier2 B = creer_bezier2_points(C1, C2, C3);
    return B;
}