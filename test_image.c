/****************************************************************************** 
  Programme de test du module image
******************************************************************************/

#include"image.h"

int main(int argc, char *argv[])
{

    Image img, neg, msq;
    
	/*****************
	 *  TEST MANUEL  *
	 *****************/

	// on affiche le titre du test
	printf("TEST IMAGE MANUEL\n");

	// on creer une image blanche
	img = creer_image(3,2);

	// on colorie 2 cases
	set_pixel_image(img, 2,1 , NOIR);
    set_pixel_image(img, 2,2, NOIR);
	set_pixel_image(img, 3,2 , NOIR);

	// on affiche l'image
	printf("image :\n");
	ecrire_image(img);

	// on teste sur un pixel à l'extérieur de l'image
	set_pixel_image(img, 0,10 , NOIR);
	printf("couleur pixel (0,10) : %s\n", (get_pixel_image(img, 0,10) == BLANC) ? "BLANC" : "NOIR");

    // test du négatif
    printf("\nnégatif : \n");
    neg = negatif_image(img);
    ecrire_image(neg);

	// test du masque
	msq = calculer_masque_image(img);
	printf("\nmasque : \n");
	ecrire_image(msq);

	// on supprime les images
	supprimer_image(&img);
    supprimer_image(&neg);
	supprimer_image(&msq);


	/************************
	 *  TEST IMAGE FICHIER  *
	 ************************/
	printf("----------------------------\nTEST IMAGE DANS UN FICHIER\n");

	// on lit l'image
	img = lire_fichier_image("test.pbm");

	// on affiche les dimensions
	printf("image : largueur et hauteur : %d par %d pixels\n", largeur_image(img), hauteur_image(img));

	// on affiche l'image
	ecrire_image(img);

	// test du masque
	printf("\nmasque : \n");
	msq = calculer_masque_image(img);
	ecrire_image(msq);

    // test du négatif
    printf("\nnégatif : \n");
    neg = negatif_image(img);
    ecrire_image(neg);

	// on supprime les images
	supprimer_image(&img);
    supprimer_image(&neg);
	supprimer_image(&msq);

	return 0;
}