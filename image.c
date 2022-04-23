/****************************************************************************** 
  Implémentation du module image_pbm
******************************************************************************/

#include"image.h"

/* macro donnant l'indice d'un pixel de coordonnees (_x,_y) de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).L*((_y)-1)

/* creation d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H)
{
<<<<<<< HEAD
    Image I;
    UINT i;
    
    I.L = L;
    I.H = H;
    
    /* alloctaion dynamique d'un tableau de L*H Pixel*/
    I.tab = (Pixel *)malloc(sizeof(Pixel)*L*H);
    
    /* test si le tableau a ete correctement alloue */
    if (I.tab == (Pixel *)NULL)
    {
        ERREUR_FATALE("Impossible de creer une image");
    }
    
    /* remplir le tableau avec des pixels blancs */
    for (i=0; i<L*H; i++)
        I.tab[i] = BLANC;
        
    return I;
=======
	Image I;
	UINT i;
	
	I.L = L;
	I.H = H;
	
	/* alloctaion dynamique d'un tableau de L*H Pixel*/
	I.tab = (Pixel *)malloc(sizeof(Pixel)*L*H);
	
	/* test si le tableau a ete correctement alloue */
	if (I.tab == (Pixel *)NULL)
	{
		ERREUR_FATALE("Impossible de creer une image");
	}
	
	/* remplir le tableau avec des pixels blancs */
	for (i=0; i<L*H; i++)
		I.tab[i] = BLANC;
		
	return I;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* suppression de l'image I = *p_I*/
void supprimer_image(Image *p_I)
{
<<<<<<< HEAD
    free(p_I->tab);
    p_I->L = 0;
    p_I->H = 0;
=======
	free(p_I->tab);
	p_I->L = 0;
	p_I->H = 0;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, int x, int y)
{
<<<<<<< HEAD
    if (x<1 || x>I.L || y<1 || y>I.H)
        return BLANC;
    return I.tab[INDICE_PIXEL(I,x,y)];
=======
	if (x<1 || x>I.L || y<1 || y>I.H)
		return BLANC;
	return I.tab[INDICE_PIXEL(I,x,y)];
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, int x, int y, Pixel v)
{
<<<<<<< HEAD
    if (x<1 || x>I.L || y<1 || y>I.H)
        return;
    I.tab[INDICE_PIXEL(I,x,y)] = v;
=======
	if (x<1 || x>I.L || y<1 || y>I.H)
		return;
	I.tab[INDICE_PIXEL(I,x,y)] = v;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* renvoie la largeur de l'image I */
UINT largeur_image(Image I)
{
<<<<<<< HEAD
    return I.L;
=======
	return I.L;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* renvoie la hauteur de l'image I */
UINT hauteur_image(Image I)
{
<<<<<<< HEAD
    return I.H;
=======
	return I.H;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* teste si le fichier d'identificateur f debute par un en-tete
   valide pour un fichier PBM :
   - ligne 1 : P1
   - suivie de zero, une ou plusieurs lignes commencant toutes par #
   La fonction se termine correctement si le fichier est correct, 
   et le pointeur de fichier se trouve a la suite l'entete.
   Sinon, l'execution du programme est arretee avec l'affichage d'un message
   d'erreur (appel a ERREUR_FATALE)
    */ 
void entete_fichier_pbm(FILE *f)
{
<<<<<<< HEAD
    char *ligne;
    size_t n;
    size_t l_ligne;

    /* se positionner en debut de fichier */
    fseek(f, 0, SEEK_SET);
    
    /* lecture et test de la ligne 1 */
    ligne = (char *)NULL;
    n = 0;
    l_ligne = getline(&ligne, &n, f);
    
    /* la ligne est correcte si et ssi ligne = {'P','1',0} 
      soit une chaine de 3 caracteres (le dernier est le caractere nul) */
    if (l_ligne != 3)
    {
        ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
    }
    if ((ligne[0] != 'P') || (ligne[1] != '1'))
    {
        ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
    }
    free(ligne);
    
    /* lecture des eventuelles lignes commencant par # */
    bool boucle_ligne_commentaire = true;
    do
    {
        /* tester d'abord la fin de fichier */
        if (feof(f))
        {
            ERREUR_FATALE("entete_fichier_pbm : fin fichier inattendue\n");
        }
        
        /* lire un caractere et tester par rapport a '#' */
        char c;
        fscanf(f, "%c", &c);
        if (c=='#')
        {
            /* lire le reste de la ligne */
            ligne = (char *)NULL;
            n = 0;
            l_ligne = getline(&ligne, &n, f);
            free(ligne);
        }
        else
        {
            /* reculer d'un caractere dans f */
            fseek(f, -1, SEEK_CUR);
            boucle_ligne_commentaire = false;
        }
    } while (boucle_ligne_commentaire);
    
=======
	char *ligne;
	size_t n;
	size_t l_ligne;

	/* se positionner en debut de fichier */
	fseek(f, 0, SEEK_SET);
	
	/* lecture et test de la ligne 1 */
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	
	/* la ligne est correcte si et ssi ligne = {'P','1',0} 
	  soit une chaine de 3 caracteres (le dernier est le caractere nul) */
	if (l_ligne != 3)
	{
		ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1'))
	{
		ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
	}
	free(ligne);
	
	/* lecture des eventuelles lignes commencant par # */
	bool boucle_ligne_commentaire = true;
	do
	{
		/* tester d'abord la fin de fichier */
		if (feof(f))
		{
			ERREUR_FATALE("entete_fichier_pbm : fin fichier inattendue\n");
		}
		
		/* lire un caractere et tester par rapport a '#' */
		char c;
		fscanf(f, "%c", &c);
		if (c=='#')
		{
			/* lire le reste de la ligne */
			ligne = (char *)NULL;
			n = 0;
			l_ligne = getline(&ligne, &n, f);
			free(ligne);
		}
		else
		{
			/* reculer d'un caractere dans f */
			fseek(f, -1, SEEK_CUR);
			boucle_ligne_commentaire = false;
		}
	} while (boucle_ligne_commentaire);
	
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* lire l'image dans le fichier nomme nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message */
Image lire_fichier_image(char *nom_f)
{
<<<<<<< HEAD
    FILE *f;
    UINT L,H;
    UINT x,y;
    int res_fscanf;
    Image I;
    
    /* ouverture du fichier nom_f en lecture */
    f = fopen(nom_f, "r");
    if (f == (FILE *)NULL)
    {
        ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
    }
    
    /* traitement de l'en-tete et arret en cas d'erreur */
    entete_fichier_pbm(f);
    
    /* lecture des dimensions */
    res_fscanf = fscanf(f, "%d", &L);
    if (res_fscanf != 1)
    {
        ERREUR_FATALE("lire_fichier_image : dimension L incorrecte\n");
    }
    res_fscanf = fscanf(f, "%d", &H);
    if (res_fscanf != 1)
    {
        ERREUR_FATALE("lire_fichier_image : dimension H incorrecte\n");
    }
    
    /* creation de l'image de dimensions L x H */
    I = creer_image(L,H);
    
    /* lecture des pixels du fichier 
       seuls les caracteres '0' (BLANC) ou '1' (NOIR) sont pris en compte 
       s'il manque des pixels dans le fichier (fion de fichier atteinte)
       les pixels manquants dans l'image sont laisses blancs*/
    x = 1; y = 1;
    while (!feof(f) && y<=H)
    {
        char c;
        int res;
        
        /* lire un caractere en passant les caracteres differents de '0' et '1' */
        res = fscanf(f, "%c", &c);
        while (!feof(f) && !(c == '0' || c == '1'))
        {
            res = fscanf(f, "%c", &c);
        }
        if (!feof(f))
        {
            set_pixel_image(I,x,y,c=='1' ? NOIR : BLANC );
            x++;
            if (x>L)
            {
                x = 1; y++;
            }
        }
    }
    
    /* fermeture du fichier */
    fclose(f);
    
    return I;
=======
	FILE *f;
	UINT L,H;
	UINT x,y;
	int res_fscanf;
	Image I;
	
	/* ouverture du fichier nom_f en lecture */
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
	}
	
	/* traitement de l'en-tete et arret en cas d'erreur */
	entete_fichier_pbm(f);
	
	/* lecture des dimensions */
	res_fscanf = fscanf(f, "%d", &L);
	if (res_fscanf != 1)
	{
		ERREUR_FATALE("lire_fichier_image : dimension L incorrecte\n");
	}
	res_fscanf = fscanf(f, "%d", &H);
	if (res_fscanf != 1)
	{
		ERREUR_FATALE("lire_fichier_image : dimension H incorrecte\n");
	}
	
	/* creation de l'image de dimensions L x H */
	I = creer_image(L,H);
	
	/* lecture des pixels du fichier 
	   seuls les caracteres '0' (BLANC) ou '1' (NOIR) sont pris en compte 
	   s'il manque des pixels dans le fichier (fion de fichier atteinte)
	   les pixels manquants dans l'image sont laisses blancs*/
	x = 1; y = 1;
	while (!feof(f) && y<=H)
	{
		char c;
		int res;
		
		/* lire un caractere en passant les caracteres differents de '0' et '1' */
		res = fscanf(f, "%c", &c);
		while (!feof(f) && !(c == '0' || c == '1'))
		{
			res = fscanf(f, "%c", &c);
		}
		if (!feof(f))
		{
			set_pixel_image(I,x,y,c=='1' ? NOIR : BLANC );
			x++;
			if (x>L)
			{
				x = 1; y++;
			}
		}
	}
	
	/* fermeture du fichier */
	fclose(f);
	
	return I;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* ecrire l'image I a l'ecran */
void ecrire_image(Image I)
{
<<<<<<< HEAD
    // hauteur et largeur de l'image
    int H = hauteur_image(I);
    int L = largeur_image(I);

    // on parcours chaque colonne
    for (int y = 1; y <= H; y++)
    {
        // puis dans chaque colonne chaque ligne
        for (int x = 1; x <= L; x++)
        {
            // si le pixel est noir
            if (get_pixel_image(I, x, y) == NOIR)
            {
                printf("X");
            }
            // sinon
            else {
                printf(".");
            }
        }
        printf("\n");        
    }
=======
	// hauteur et largeur de l'image
	int H = hauteur_image(I);
	int L = largeur_image(I);

	// on parcours chaque colonne
	for (int y = 1; y <= H; y++)
	{
		// puis dans chaque colonne chaque ligne
		for (int x = 1; x <= L; x++)
		{
			// si le pixel est noir
			if (get_pixel_image(I, x, y) == NOIR)
			{
				printf("X");
			}
			// sinon
			else {
				printf(".");
			}
		}
		printf("\n");		
	}
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}

/* calculer l'image "negatif" de l'image I */
/* l'image I n'est pas modifiee */
Image negatif_image(Image I)
{
<<<<<<< HEAD
    // On crée une nouvelle image
    Image neg = creer_image(largeur_image(I),hauteur_image(I));
    
    // On recupère la hauteur et la largeur de l'image
    int L = largeur_image(I);
    int H = hauteur_image(I);

    // On parcours chaques lignes
    Pixel p;
    for(int l=1; l <= L; l++){
        // On parcours chaques colonnes
        for(int h=1; h <= H; h++){
            // on attribut à chaque pixel le négatif de l'image.
            // par default p est blanc
            p = BLANC;
            if (get_pixel_image(I, l, h) == BLANC) p = NOIR;

            // On affecte la valeur au pixel (l,h)
            set_pixel_image(neg, l, h, p);
        }

    }

    // On retourne le négatif de l'image
=======
	// On crée une nouvelle image
	Image neg = creer_image(largeur_image(I),hauteur_image(I));
	
	// On recupère la hauteur et la largeur de l'image
	int L = largeur_image(I);
	int H = hauteur_image(I);

	// On parcours chaques lignes
	Pixel p;
	for(int l=1; l <= L; l++){
		// On parcours chaques colonnes
		for(int h=1; h <= H; h++){
			// on attribut à chaque pixel le négatif de l'image.
			// par default p est blanc
			p = BLANC;
			if (get_pixel_image(I, l, h) == BLANC) p = NOIR;

			// On affecte la valeur au pixel (l,h)
			set_pixel_image(neg, l, h, p);
		}

	}

	// On retourne le négatif de l'image
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
    return neg;
}

/* calculer l'image-masque de l'image I */
/* l'image I n'est pas modifiee */
Image calculer_masque_image(Image I)
{
<<<<<<< HEAD
    // hauteur et largeur de l'image
    int H = hauteur_image(I);
    int L = largeur_image(I);

    Image M = creer_image(L, H);

    // on parcours chaque colonne
    for (int y = 1; y <= H; y++)
    {
        // puis dans chaque colonne chaque ligne
        for (int x = 1; x <= L; x++)
        {
            // si le pixel est noire et celui du dessus blanc
            if (get_pixel_image(I, x, y) == NOIR && get_pixel_image(I, x, y-1) == BLANC)
            {
                set_pixel_image(M, x,y , NOIR);
            }
        }
    }

    // on retourne l'image masque M
    return M;
=======
	// hauteur et largeur de l'image
	int H = hauteur_image(I);
	int L = largeur_image(I);

	Image M = creer_image(L, H);

	// on parcours chaque colonne
	for (int y = 1; y <= H; y++)
	{
		// puis dans chaque colonne chaque ligne
		for (int x = 1; x <= L; x++)
		{
			// si le pixel est noire et celui du dessus blanc
			if (get_pixel_image(I, x, y) == NOIR && get_pixel_image(I, x, y-1) == BLANC)
			{
				set_pixel_image(M, x,y , NOIR);
			}
		}
	}

	// on retourne l'image masque M
	return M;
>>>>>>> d0ac441f0d3f0aaf4ee3fd31affc026f7faff468
}