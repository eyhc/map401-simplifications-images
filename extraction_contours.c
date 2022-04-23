/******************************************************************** 
  Implémentation du module contour
*********************************************************************/

#include "extraction_contours.h"

/* Determine l'ensemble des contours d'une image */
Liste_Contour lire_contours(Image I) {
    // On crée la liste de contours nécessaire pour stocker les contours
    Liste_Contour liste_c = creer_liste_contour_vide();
    
    // On calcule l'image masque
    Image M = calculer_masque_image(I);
    
    // On initialise la position de départ
    Position p = trouver_position_depart(M, 1, 1);
    
    // On parcourt l'image
    while (p.y != -1  && p.x != -1)
    {
        // On lit le contour à partir de la position déterminée
        Contour c = lire_contour(I, &M, p);

        // On ajoute ce contour dans notre liste
        liste_c = ajouter_element_liste_contour(liste_c, c);
        
        // On détermine la nouvelle position 
        p = trouver_position_depart(M, p.x+1, p.y+1);
    }

    return liste_c;
}

/* lire le contour d'une image en partant de la position
  donnee de depart et l'orientation EST  
  Avec l'adresse d'une liste de point*/
Contour lire_contour(Image I, Image *M, Position p) {
    // initialisation du robot
    Position p0 = p;
    Orientation o = Est;

    // On cree le contour vide
    Contour cont = creer_liste_Point_vide();

    // on suit le contour de l'image
    do
    {   
        /* on met en BLANC la valeur du pixel en bas gauche de l'image masque
           seulement si l'orientation est Est */
        if (o == Est)
            set_pixel_image(*M, p.x + 1, p.y + 1, BLANC);

        // On ajoute le point dans la liste
        cont = ajouter_element_liste_Point(cont, p);

        // on avance
        p = avancer(p, o);

        // on calcule la nouvelle orientation
        o = nouvelle_orientation(I, p, o);

    // tant que on est pas revenu à la position initiale avec une orientation Est
    } while (p.x != p0.x || p.y != p0.y || o != Est);
    
    // on memorise à nouveau la position à la fin
    cont = ajouter_element_liste_Point(cont, p);

    return cont;
}

/* trouve la position de depart (du robot)
   en partant du pixel (x, y)
   si l'image est vide, on retourne la position (-1,-1) */
Position trouver_position_depart(Image I, int x0, int y0) {
    int l = largeur_image(I);
    int h = hauteur_image(I);

    // On initialise nos deux compteurs
    int x = x0, y = y0;

    /* on cherche le premier pixel noir (par un double parcours)
       ligne par ligne */
    while (y <= h)
    {
        while (x <= l)
        {
            // si le pixel est noir on a trouvé notre champion
            if (get_pixel_image(I, x, y) == NOIR)
            {
                // on renvoie la position du pixel
                return (Position)creer_point(x-1, y-1);
            }

            // on avance d'une colonne
            x++;
        }

        // on retourne à la ligne
        x = 1;
        y++;
    }

    // Cas d'image vide
    return (Position)creer_point(-1, -1);
}

/* Calcule la nouvelle orientation du robot */
Orientation nouvelle_orientation(Image I, Position p, Orientation o) {
    // on récupère la valeur du pixel devant à gauche et à droite
    Pixel pg = valeur_pixel_gauche(I, p, o);
    Pixel pd = valeur_pixel_droit(I, p, o);

    // si pg est noir on va à gauche
    if (pg == NOIR)
        return tourner_gauche(o);
    
    // sinon si pd est blanc, on va à droite
    else if (pd == BLANC)
        return tourner_droite(o);

    // sinon on tourne pas
    return o;
}

/* avancer suivant l'orientation (le robot) */
Position avancer(Position p, Orientation o) {
    switch (o)
    {
        case Sud: return (Position)creer_point(p.x, p.y + 1);
        case Ouest: return (Position)creer_point(p.x - 1, p.y);
        case Nord: return (Position)creer_point(p.x, p.y - 1);
        default: return (Position)creer_point(p.x + 1, p.y);
    }
}

/* Tourne d'un quart de tour à gauche */
Orientation tourner_gauche(Orientation o) {
    // rose des sables en sens anti-horaire
    switch (o)
    {
        case Nord: return Ouest;
        case Ouest: return Sud; 
        case Sud : return Est;
        default: return Nord;
    }
}

/* Tourne d'un quart de tour à droite */
Orientation tourner_droite(Orientation o) {
    // rose des sables en sens horaire
    switch (o)
    {
        case Sud: return Ouest;
        case Ouest: return Nord;
        case Nord: return Est; 
        default: return Sud;
    }
}

/* ecrit la position (du robot) */
void ecrire_position(Position p) {
    printf("(%.0f, %.0f) ; ", p.x, p.y);
}

/* ecrit l'orientation (du robot) */
void ecrire_orientation(Orientation o) {
    switch (o)
    {
        case Sud: printf("\nSud\n"); break;
        case Ouest: printf("\nOuest\n");break;
        case Nord: printf("\nNord\n"); break;
        default: printf("\nEst\n"); break;
    }
}

/* retourne le pixel à gauche dans l'image I à la position p
et suivant l'orientation o */
Pixel valeur_pixel_gauche(Image I, Position p, Orientation o) {
    switch (o)
    {
        case Nord: return get_pixel_image(I, p.x, p.y);
        case Sud: return get_pixel_image(I, p.x+1, p.y+1);
        case Ouest: return get_pixel_image(I, p.x, p.y+1);
        default: return get_pixel_image(I, p.x+1, p.y);
    }
}

/* retourne le pixel à droite dans l'image I à la position p
et suivant l'orientation o */
Pixel valeur_pixel_droit(Image I, Position p, Orientation o) {
    switch (o)
    {
        case Nord: return get_pixel_image(I, p.x+1, p.y);
        case Sud: return get_pixel_image(I, p.x, p.y+1);
        case Ouest: return get_pixel_image(I, p.x, p.y);
        default: return get_pixel_image(I, p.x+1, p.y+1);
    }
}