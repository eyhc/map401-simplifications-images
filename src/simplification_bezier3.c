/***************************************************************************** 
 *    Implémentation du module de simplification par bezier3
 *****************************************************************************/

#include "simplification_bezier3.h"

/* Simplifie (par bezier de deg 3) tous les contours 
   d'une liste de contours suivant la distance seuil d
   Renvoie la liste simplifiée
*/
Liste_Contour simplification_bezier3(Liste_Contour LCONT, double d) {
    // On creer une nouvelle liste de contours l
    Liste_Contour l = creer_liste_contour_vide();

    // On parcourt tous les contours
    Cellule_Liste_Contour* cel = LCONT.first;
    while (cel != NULL)
    {
        // On transforme en tableau
        Tableau_Point tab = sequence_points_liste_vers_tableau(cel->data);

        // On simplifie
        Contour csimp = simplification_douglas_peucker_bezier3(tab, 0, tab.taille-1, d);

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
Liste_Point simplification_douglas_peucker_bezier3(Tableau_Point CONT, UINT j1, UINT j2, double d) {
    Liste_Point L;  // la liste de point à retourner

    // nb de segments dans le contour
    int n = j2 - j1;

    // on creer le segment
    Bezier3 B = approx_bezier3(CONT, j1, j2);

    // initialisation pour trouver le point le plus loin du segment
    double max = 0;
    int k = j1;
    //  Test si les points sont en dessous de la distance seuil. 
    for (int j = j1+1; j <= j2; j++) {
        int i = j-j1;
        double ti = (double)i/n;
        double dj = distance_point_bezier3(CONT.tab[j], B, ti);
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
        L = ajouter_element_liste_Point(L, B.C1);
        L = ajouter_element_liste_Point(L, B.C2);
        L = ajouter_element_liste_Point(L, B.C3);
    }
    else {
        /* cas recursif : on decoupe le probleme en deux à l'aide du point
           le plus éloigné */
        Liste_Point l1 = simplification_douglas_peucker_bezier3(CONT, j1, k, d);
        Liste_Point l2 = simplification_douglas_peucker_bezier3(CONT, k, j2, d);
        L = concatener_liste_Point(l1, l2);
    }

    return L;
}

/* Détermination d'une courbe de Bezier de degre 3 suivant le tableau de point donne */
Bezier3 approx_bezier3(Tableau_Point CONT, UINT j1, UINT j2) {
    Point C1 = CONT.tab[j1];   // C1 est le premier point de controle 
    Point C4 = CONT.tab[j2];   // C4 est le dernier point du contour ie 4e pt de controle

    // on calcule le nombre de points du contour
    double n = j2 - j1;

    /* On fait les deux cas soit il y a deux  points soit il y en a plus */
    if (n < 3) {
        Bezier2 B2 = approx_bezier2(CONT, j1, j2);
        Bezier3 B = conversion_bezier2_vers_3(B2);
        return B;
    }

    Point C2; // Deuxieme point de controle
    Point C3; // Troisieme point de controle

    double alpha = (-15*n*n*n + 5*n*n + 2*n + 4)/(3 * (n + 2) * (3*n*n + 1));
    double beta = (10*n*n*n - 15*n*n + n + 2)/(3 * (n + 2) * (3*n*n + 1));
    double lambda = (70 * n)/(3 *(n*n-1)*(n*n - 4) * (3*n*n + 1));


    // on applique les formules qui calculent C2 et C3
    C2 = somme_points(mult_point(C1, alpha), mult_point(C4, beta));
    C3 = somme_points(mult_point(C1, beta), mult_point(C4, alpha));

    // somme sur i = 1 à n-1 (cf poly)
    for(int i = 1; i < n; i++) {
        C2 = somme_points(C2, mult_point(CONT.tab[j1+i], gamma(i,n) * lambda));
        C3 = somme_points(C3, mult_point(CONT.tab[j1+i], gamma(n - i, n) * lambda));
    }

    // on cree et retourne la courbe de bezier
    Bezier3 B = creer_bezier3_points(C1, C2, C3, C4);
    return B;
}


/* fonction gamma retourne un double */
double gamma(double k, double n) {
    //6*k⁴-8kn³+6k²-4nk+n⁴-n²
    return (double) (6*k*k*k*k) - (8*n*k*k*k) + (6*k*k) - (4*n*k) + (n*n*n*n) - (n*n);
}