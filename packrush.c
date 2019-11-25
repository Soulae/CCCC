#include "packrush.h"

// Fonction pour colorer le texte sur la console
void color(int t,int f)
{
    //t : couleur du texte
    //f : couleur du fond
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
/* Couleurs r�f�renc�es :
0: noir
1: bleu fonc�
2: vert
3: bleu-gris
4: marron
5: pourpre
6: kaki
7: gris clair
8: gris
9: bleu
10: vert fluo
11: turquoise
12: rouge
13: rose fluo
14: jaune fluo
15: blanc
*/

//======================================================================================
jeu * init_jeu (int x, int y)
{
    jeu * game=(jeu*)malloc(sizeof(jeu)); //Allocation du type struct

    //Initialisation des variables internes du struct aux valeurs voulues
	game->x=x;
	game->y=y;
	game->score=0;

    //Allocation du tableau � 2 dimensions
	game->plateau=(int**)malloc(sizeof(int*)*y);
	for (int i=0; i<y;i++)
	{
			game->plateau[i]=(int*)malloc(sizeof(int)*x);
	}
    return game;
}

//======================================================================================
//
void affiche_jeu (jeu *game) //Affiche "joliment" le plateau
{
	printf("\n");
	for (int i=0;i<game->y;i++)
	{
	    if (i>0 && i<10) printf("%d  ",i);
	    else if (i>9) printf("%d ",i);

		for (int j=0;j<game->x;j++)
		{
		    if (i==0 && j==0) printf("   ");
		    if (i==0 && j<9) printf("%d  ",j);
		    else if (j>=9 && i==0)printf("%d ",j);
		    if (j==game->x-1 && i==0) printf("\n%d  ",i);
		}
        for (int k=0;k<game->x;k++)
        {
             //Sert � attribuer � chaque type de pions une couleur sp�cifique pour am�liorer la lisibilit�
             switch(game->plateau[i][k])
             {
                 case 2 : color(14,0); break;
                 case 3 : color(12,0); break;
                 case 4 : color(9,0); break;
                 case 5 : color(10,0); break;
                 case 6 : color(5,0); break;
                 case 14: color(7,0); break;
                 case 15 : color(11,0); break;
                 default:;
             }
             printf("%c  ",game->plateau[i][k]); // affiche le caract�re ascii de la valeur num�rique du pion.
             color(15,0); //remet la couleur � blanc pour les textes neutres
        }

		printf("\n");
	}
	fflush(stdin);//permet de nettoyer le buffer apres l'affichage pour pouvoir proceder a une saisie
}

//=============================================================================================
void remp_val(jeu * game, int x, int y)
{
    int a=(rand() % game->j)+1;
    switch(a)
    {
        //g�re le cas ou le pion est �gal � 7 et plus : caract�res non affichables sur la console, on leur attribue une autre valeur, choisie pour son caract�re
        case 7 : game->plateau[x][y]=14; break;
        case 8 : game->plateau[x][y]=15; break;
        default : game->plateau[x][y]=a;
    }
}

//============================================================================================

void remp_jeu(jeu *game)
{
    //repmlit le tableau de pions al�atoires et effectue les combinaisons jusqu'� obtenir un tableau sans combinaison mais avec coups possibles
    do
    {
        for (int i=0;i<game->y;i++)
        {
            for (int j=0;j<game->x;j++)
            {
                remp_val(game,i,j);
            }
        }
        suppr_auto(game);
    }while (coup_possible(game)==0);

}

//===========================================================================================

int verif (jeu *game) //Fonction de v�rification de combinaison pr�sentes sur le plateau
{
    int i,j;
    for (i=0;i<game->y;i++)
    {
        for (j=0;j<game->x-2;j++)
        {
            //On teste s'il y a trois pions d'align�s horizontalement (en partant de la premi�re colonne, jusqu'� l'avant derni�re, puisqu'on teste les 2 pions suivants)
            if((game->plateau[i][j]==game->plateau[i][j+1])&&(game->plateau[i][j+1]==game->plateau[i][j+2]))
                return 1;
        }
    }
    for (i=0;i<game->y-2;i++)
    {
        for (j=0;j<game->x;j++)
        {
            //Idem mais verticalement
            if ((game->plateau[i][j]==game->plateau[i+1][j])&&(game->plateau[i+1][j]==game->plateau[i+2][j]))
                return 1;
        }
    }
	return 0;
}

//==========================================================================================
/*
    Fonction qui teste si des combinaisons possibles existent. Pour ce faire, elle va effectuer
    tous les d�placements possibles sans d�passer du tabelau et tester si cela cr�e une combinaison.
    Dans tous les cas, apr�s avoir enregistr� la valeur bool�enne du test, on annule le d�placement.
*/
int coup_possible(jeu * game)
{
    int i,j,booleen=0;
    for (i=0;i<game->y;i++)
    {
        if (booleen==1) break;
        for (j=0;j<game->x;j++)
        {
            if (i==0) // Si premiere ligne
            {
                if (j==0) // et premi�re colonne
                {
                    //on teste uniquement bas et droite

                    //BAS
                    depl_b(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_b(game,j,i);

                    //DROITE
                    depl_d(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_d(game,j,i);
                }
                else if (j==game->x-1) // sinon si derni�re colonne
                {
                    //on teste � gauche et en bas

                    //GAUCHE
                    depl_g(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_g(game,j,i);

                    //BAS
                    depl_b(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_b(game,j,i);

                }
                else //sinon, dans le reste de la premi�re ligne,
                {
                    //on teste bas gauche et droite

                    //GAUCHE
                    depl_g(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_g(game,j,i);

                    //BAS
                    depl_b(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_b(game,j,i);

                    //DROITE
                    depl_d(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_d(game,j,i);
                }
            }
            else if (i==game->y-1) //si derni�re ligne
            {
                if (j==0) // et premi�re colonne
                {
                    //on teste en haut et � droite

                    //HAUT
                    depl_h(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_h(game,j,i);

                    //DROITE
                    depl_d(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_d(game,j,i);
                }
                else if (j==game->x-1) // si derni�re colonne
                {
                    //On teste haut et gauche

                    //HAUT
                    depl_h(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_h(game,j,i);

                    //GAUCHE
                    depl_g(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_g(game,j,i);
                }
                else //sinon, dans le reste de la derni�re ligne,
                {
                    //on teste les 3 directions possible (tout sauf bas)

                    //GAUCHE
                    depl_g(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_g(game,j,i);

                    //HAUT
                    depl_h(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_h(game,j,i);

                    //DROITE
                    depl_d(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_d(game,j,i);

                }
            }
            else //sinon, si l'on est sur une des lignes du milieu,
            {
                if (j==0) //et si la premi�re colonne
                {
                    //on teste haut bas et droite

                    //HAUT
                    depl_h(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_h(game,j,i);

                    //BAS
                    depl_b(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_b(game,j,i);

                    //DROITE
                    depl_d(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_d(game,j,i);

                }
                else if (j==game->x-1) //ou si derni�re colonnne
                {
                    //on teste haut bas et gauche

                    //HAUT
                    depl_h(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_h(game,j,i);

                    //BAS
                    depl_b(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_b(game,j,i);

                    //GAUCHE
                    depl_g(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_g(game,j,i);

                }
                else // sinon, c'est que l'on se trouve sur aucun des bords, on peut donc tester les quatre directions.
                {
                    //HAUT
                    depl_h(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_h(game,j,i);

                    //BAS
                    depl_b(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_b(game,j,i);

                    //GAUCHE
                    depl_g(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_g(game,j,i);

                    //DROITE
                    depl_d(game,j,i);
                    if(verif(game))
                    {
                        booleen=1;
                    }
                    depl_d(game,j,i);

                }
            }
        }
    }
    return booleen;
}

//================================================================================================

void suppr_auto(jeu *game)
{
	int k, cpt;
	int temp;
	while (verif(game)) // tourne tant qu'il y a des combinaisons
    {
        for (int i=2;i<game->y;i++)
        {
            for (int j=0;j<game->x;j++)
            {
                // teste si 3 m�me pions sont align�s de mani�re verticale (meme test que dans verif)
                if ((game->plateau[i-2][j]==game->plateau[i-1][j])&&(game->plateau[i-1][j]==game->plateau[i][j]))
                {
                    // si c'est le cas, on regarde combien de pions en tout sont align�s.

                    temp=game->plateau[i-2][j]; //on sauvegarde la valeur du premier pion de la colonne de pions align�s
                    k=i-2; cpt=1; //initialisation de k comme coordonn�e de ligne et cpt pour compter les pions

                    while((temp==game->plateau[k][j])&&(k<game->y-1)) //si le pion courant est �gal � celui du dessous
                    {
                        k++; //on teste la ligne du dessous au prochain tour
                        cpt++;//on incr�mente le comteur de jetons align�s
                    }
                    //une fois le nombre et les coordonn�es du premier des pions align�s r�cup�r�s,
                    //on appelle la fonction qui d�truit et remplace la rang�e.
                    suppr_vertical(game,j,k,cpt);
                    // et on incr�mente le score de 2 puissance cpt
                    game->score+=pow(2,cpt);
                }
            }

        }
        for (int i=0;i<game->y;i++)
        {
            for (int j=2; j<game->x;j++)
            {
                // teste si 3 m�me pions sont align�s de mani�re horizontale
                if ((game->plateau[i][j]==game->plateau[i][j-1])&&(game->plateau[i][j-1]==game->plateau[i][j-2]))
                {
                    temp=game->plateau[i][j-2];
                    k=j-2; cpt=1;
                    // on compte le nombre total de pions identiques align�s
                    while((temp==game->plateau[i][k])&&(k<game->x-1))
                    {
                        k++;
                        cpt++;
                    }
                    // on les remplace gr�ce � la fonction d�di�e
                    suppr_horizontal(game,k,i,cpt);
                    //et on incr�mente le score
                    game->score+=pow(2,cpt);
                }
            }
        }

    }

}

//=======================================================================================

void suppr_horizontal(jeu *game, int x, int y, int nb)
{
    for (int ind=x;ind>x-nb;ind--) //on parcourt les colonnes en premier
    {
        for (int k=y; k>0; k--) //puis les lignes pour le d�calage
        {
            game->plateau[k][ind]=game->plateau[k-1][ind];
            //On d�cale ici les pions de fa�on verticale d'une case,
            //de fa�on � �craser les pions de la ligne.
        }
        // Puis on place de nouvelles valeurs au d�but des colonnes concern�es par le d�calage.
        remp_val(game,0,ind);
    }
}

//=========================================================================================

void suppr_vertical (jeu *game, int x, int y, int nb)
{
    for (int cpt=0;cpt<nb;cpt++) // on tourne sur le nombre de pions align�s
    {
        for (int ind=y;ind>0;ind--) // et sur les lignes (colonne fixe)
        {
            game->plateau[ind][x]=game->plateau[ind-1][x];
            // On d�cale nb fois les pions de la colonne concern�e
        }
        remp_val(game,0,x);
        // et l'on rajoute une valeur au d�but de la colonne � chaque tour de boucle,
        //pour au final remplacer tous les pions d�truits.
    }
}

//==========================================================================================
void depl_g(jeu * game, int x, int y)
{
    //�change la place d'un pion avec celui � sa gauche
    int temp;
    temp=game->plateau[y][x];
    game->plateau[y][x]=game->plateau[y][x-1];
    game->plateau[y][x-1]=temp;
}

//=========================================================================================
void depl_d(jeu * game, int x, int y)
{
    //�change la place d'un pion avec celui � sa droite
    int temp;
    temp=game->plateau[y][x];
    game->plateau[y][x]=game->plateau[y][x+1];
    game->plateau[y][x+1]=temp;
}

//=========================================================================================
void depl_h(jeu * game, int x, int y)
{
    // �change le pion avec celui au-dessus
    int temp;
    temp=game->plateau[y][x];
    game->plateau[y][x]=game->plateau[y-1][x];
    game->plateau[y-1][x]=temp;
}

//=========================================================================================
void depl_b(jeu * game, int x, int y)
{
    // �change le pion avec celui en-dessous
    int temp;
    temp=game->plateau[y][x];
    game->plateau[y][x]=game->plateau[y+1][x];
    game->plateau[y+1][x]=temp;
}

//===========================================================================================
void deplacement (int x, int y, char dir, jeu *game)
{
    switch(dir) //prend la valeur du caract�re saisi par l'utilisateur
    {
        case 'G' : //s'il entre un g, majuscule ou minuscule
        case 'g' : if (x==0) printf("Vous sortez du plateau en effectuant ce deplacement\n"); // on teste s'il ne d�passe pas du plateau,
                   else
                    {
                        // on effectue le d�placement,
                        depl_g(game,x,y);
                        if (!(verif(game)))//et si le d�placement ne provoque pas de combinaison, il est annul�
                        {
                            depl_g(game,x,y);
                            printf("Deplacement non valide\n");
                        }
                        else // sinon, le compteur de coups est d�cr�ment�
                        {
                            printf("Deplacement effectue\n");
                            game->k--;
                        }
                    }
                   break;

        case 'D' : // le tableau �tant indic� de 0 � x-1, on fait le bon test pour la droite
        case 'd' : if (x==game->x-1) printf("Vous sortez du plateau en effectuant ce deplacement\n");
                   else
                    {
                        depl_d(game,x,y);
                        if (!(verif(game)))
                        {
                            depl_d(game,x,y);
                            printf("Deplacement non valide\n");

                        }
                        else
                        {
                            printf("Deplacement effectue\n");
                            game->k--;
                        }
                    }
                   break;

        case 'H' :
        case 'h' : if (y==0) printf("Vous sortez du plateau en effectuant ce deplacement\n");
                   else
                   {
                        depl_h(game,x,y);
                        if (!(verif(game)))
                        {
                            depl_h(game,x,y);
                            printf("Deplacement non valide\n");
                        }
                        else
                        {
                            printf("Deplacement effectue\n");
                            game->k--;
                        }
                   }
                   break;

        case 'B' :
        case 'b' : if (y==game->y-1) printf("Vous sortez du plateau en effectuant ce deplacement\n");
                   else
                   {
                        depl_b(game,x,y);

                        if (!(verif(game)))
                        {
                            depl_b(game,x,y);
                            printf("Deplacement non valide\n");
                        }
                        else
                        {
                            printf("Deplacement effectue\n");
                            game->k--;
                        }
                   }
                   break;

        default  : printf("Les directions possibles sont : 'h','b','g','d'");
    }
}


//============================================================================================
void aide() // affiche les commandes
{
    printf("Pour jouer on entre la direction du pion que l'on souhaite deplacer avec : H,B,G,D (on ne prend pas en compte la casse)");
    printf("\nUne fois la direction saisie, on entre les coordonnees en largeur(x) puis\n en hauteur(y)");
    printf("\nPour sauvegarder la partie en cours : s\n");
}




//===========================================================================================
// Fonction de d�roulement du jeu
void action (jeu* game)
{
    int x,y,temp;
    char command;
    //score � z�ro
    game->score=0;
    //on clean la console pour enlever le menu
    system("cls");
    //tant qu'il reste des d�placements on fait tourner la boucle
    while (game->k>0)
    {
        //affichage � chaque tour du nombre de d�placements et du score
        printf("\nNombre de coups restant(s) :%d\nScore actuel : %d\n",game->k,game->score);
        affiche_jeu(game);
        // saisie de la commande
        scanf("%c",&command);
        switch(command)
        {
            case 'H': //dans le cas d'un d�placement, quelle que soit la direction,
            case 'h':
            case 'B':
            case 'b':
            case 'G':
            case 'g':
            case 'D': //on scanne les coordonn�es du pion � d�placer
            case 'd':scanf("%d%d",&x,&y); system("cls");
                     // et on appelle la fonction de d�placement
                     deplacement(x,y,command,game);break;
            case 'S': // si le joueur entre un s, on sauvegarde la partie
            case 's':system("cls"); sauvegarde(game); break;
            case 'A': // si le joueur met un a, on affiche l'aide
            case 'a':system("cls"); aide(); break;
                    //si la lettre ne fait pas partie de celles ci-dessus, on affiche un message d'erreur
            default :printf("commande non reconnue : %c",command);
        }
        //peu importe le contenu du tour, on appelle la fonction de suppression des combinaisons (qui g�re aussi le score)
        suppr_auto(game);

        //OPTION 2 : DEBLOCAGE
        //Quand il n'y a plus de coups possibles,
        if (!coup_possible(game))
        {
            //on sauvegare le score (sera modifi� par suppr_auto dans remp_jeu)
            temp=game->score;
            //message d'explication
            printf("\nIl n'y a plus de deplacement possible, reorganisation \ndu plateau : -2 deplacements.\n");
            //on r�-initialise le tableau
            remp_jeu(game);
            //on r�tablit le score pr�c�dent et d�cr�mente de 2 e nombre de d�placements
            game->score=temp;
            game->k=game->k-2;
        }

    }
    color(10,0); //met la police en vert clair
    printf("\nPartie terminee ! \nBravo, vous avez fait un score de %d points !\n",game->score);
    //appelle la fonction qui g�re les meilleurs scores
    load_meilleur_score(game->score);
    color(15,0); //remet en blanc
}

//===============================================================================
//OPTION 3 - Plateau torique
/*
M�me fonction que deplacement, avec une gestion des bords diff�rente (plateau torique)
*/
void deplacement_torique (int x, int y, char dir, jeu *game)
{
    int temp;
    switch(dir)
    {
        case 'G' :
        case 'g' : if (x==0) //si on est sur un bord, on �change avec le pion de l'autre cot� du plateau.
                    {
                        temp=game->plateau[y][x];
                        game->plateau[y][x]=game->plateau[y][game->x-1];
                        game->plateau[y][game->x-1]=temp;
                    }
                   else
                    {
                        depl_g(game,x,y);
                    }
                    if (!(verif(game)))//si le d�placement est non valide on l'annule
                    {
                        if (x==0)
                        {
                            temp=game->plateau[y][x];
                            game->plateau[y][x]=game->plateau[y][game->x-1];
                            game->plateau[y][game->x-1]=temp;
                        }
                        else
                        {
                            depl_g(game,x,y);
                        }
                        printf("Deplacement non valide\n");
                    }
                    else
                    {
                        printf("Deplacement effectue\n");
                        game->k++;
                    }
                   break;

        case 'D' :
        case 'd' : if (x==game->x-1)
                    {
                        temp=game->plateau[y][x];
                        game->plateau[y][x]=game->plateau[y][0];
                        game->plateau[y][0]=temp;
                    }

                   else
                    {
                        depl_d(game,x,y);
                    }
                    if (!(verif(game)))//si le d�placement est non valide on l'annule
                    {
                        if (x==game->x-1)
                        {
                            temp=game->plateau[y][x];
                            game->plateau[y][x]=game->plateau[y][0];
                            game->plateau[y][0]=temp;
                        }
                        else
                        {
                            depl_d(game,x,y);
                        }
                        printf("Deplacement non valide\n");

                    }
                    else
                    {
                        printf("Deplacement effectue\n");
                        game->k++;
                    }
                   break;

        case 'H' :
        case 'h' : if (y==0)
                    {
                        temp=game->plateau[y][x];
                        game->plateau[y][x]=game->plateau[game->y-1][x];
                        game->plateau[game->y-1][x]=temp;
                    }
                   else
                   {
                        depl_h(game,x,y);
                   }
                   if (!(verif(game)))//si le d�placement est non valide on l'annule
                   {
                        if (y==0)
                        {
                            temp=game->plateau[y][x];
                            game->plateau[y][x]=game->plateau[game->y-1][x];
                            game->plateau[game->y-1][x]=temp;
                        }
                        else
                        {
                            depl_h(game,x,y);
                        }
                        printf("Deplacement non valide\n");
                    }
                    else
                    {
                        printf("Deplacement effectue\n");
                        game->k++;
                    }
                   break;

        case 'B' :
        case 'b' : if (y==game->y-1)
                   {
                       temp=game->plateau[y][x];
                       game->plateau[y][x]=game->plateau[0][x];
                       game->plateau[0][x]=temp;
                   }
                   else
                   {
                        depl_b(game,x,y);
                   }
                    if (!(verif(game)))//si le d�placement est non valide on l'annule
                    {
                        if (y==game->y-1)
                        {
                            temp=game->plateau[y][x];
                            game->plateau[y][x]=game->plateau[0][x];
                            game->plateau[0][x]=temp;
                        }
                        else
                        {
                            depl_b(game,x,y);
                        }
                        printf("Deplacement non valide\n");
                    }
                    else
                    {
                        printf("Deplacement effectue\n");
                        game->k++;
                    }
                   break;

        default  : printf("Les directions possibles sont : 'h','b','g','d'");
    }
}

//============================================================================================
// MISSION SPECIALE
void action_mission (jeu* game)
{
    int x,y, cpt_coeur=0;
    char command;
    system("cls");
    printf("\nVotre mission, si vous l'acceptez est de combiner 13 coeurs en le moins de \ncoups possible.\n");
    suppr_auto(game);//On clean le plateau de toute combinaison
    game->k=0;
    game->score=0; //On remet le score � 0 (c'est la fonction suppr_auto qui l'incr�mente automatiquement)
    //On tourne tant qu'il y a des coups possibles et que le joueur n'a pas rempli la mission
    while (cpt_coeur<=13 && coup_possible(game))
    {

        printf("\nVous avez effectue %d deplacement, vous avez combine %d coeur.",game->k,cpt_coeur);
        affiche_jeu(game);
        scanf("%c",&command);
        switch(command)
        {
            case 'H':
            case 'h':
            case 'B':
            case 'b':
            case 'G':
            case 'g':
            case 'D':
            case 'd':scanf("%d%d",&x,&y); system("cls");
                     deplacement_torique(x,y,command,game);break;
            case 'S':
            case 's':system("cls");sauvegarde(game); break;
            case 'A':
            case 'a':system("cls");aide();break;
            default :printf("commande non reconnue : %d",command);
        }
        //on incr�mente le compteur de coeurs avec la fonction suppr_auto sp�ciale
        cpt_coeur+=suppr_auto_mission(game);
    }

    color(10,0); // Affiche le r�sultat en vert (positif)
    printf("Bravo ! Vous avez rempli la mission speciale avec %d coups et un score de %d !\n",game->k,game->score);
    color(15,0);
}

//==================================================================
/* Fonction comme suppr_auto mais renvoie un nombre correspondant au nombre de coeurs d�truits*/
int suppr_auto_mission(jeu *game)
{
	int k, cpt_pions,cpt_coeur=0;
	int temp;
	while (verif(game))
    {
        for (int i=2;i<game->y;i++)
        {
            for (int j=0;j<game->x;j++)
            {
                if ((game->plateau[i-2][j]==game->plateau[i-1][j])&&(game->plateau[i-1][j]==game->plateau[i][j]))
                {
                    temp=game->plateau[i-2][j];
                    k=i-2; cpt_pions=1;
                    while((temp==game->plateau[k][j])&&(k<game->y-1))
                    {
                        k++;
                        cpt_pions++;
                    }
                    suppr_vertical(game,j,k,cpt_pions);
                    if (temp==3) // si le pion est un coeur, on incr�ment cpt_coeur
                    {
                        cpt_coeur+=cpt_pions-1; //-1 car on l'initialise � 1, ce qui nous donne le nombre de jetons aign�s +1
                    }
                    game->score+=pow(2,cpt_pions-1);
                }
            }

        }
        for (int i=0;i<game->y;i++)
        {
            for (int j=2; j<game->x;j++)
            {
                if ((game->plateau[i][j]==game->plateau[i][j-1])&&(game->plateau[i][j-1]==game->plateau[i][j-2]))
                {
                    temp=game->plateau[i][j-2];
                    k=j-2; cpt_pions=1;
                    while((temp==game->plateau[i][k])&&(k<game->x-1))
                    {
                        k++;
                        cpt_pions++;
                    }
                    suppr_horizontal(game,k,i,cpt_pions);
                    if (temp==3) // idem, si ce sont des coeurs on les compte
                    {
                        cpt_coeur+=cpt_pions-1;
                    }
                    game->score+=pow(2,cpt_pions-1);
                }
            }
        }

    }
    return cpt_coeur;
}

//=======================================================================================
//OPTION 4
/* Ouvre un fichier, enregistre les valeurs du tableau, du score, et du nombre de d�placements,
et referme le fichier */
void sauvegarde (jeu *game)
{
    FILE *fd=fopen("sauvegarde.txt","w");
    for (int i=0;i<game->y;i++)
    {
        for (int j=0;j<game->x;j++)
        {
            fprintf(fd,"%d\t",game->plateau[i][j]);//On �crit le contenu dans tableau dans le fichier
        }
    }
    fprintf(fd,"\t%d\t%d",game->k,game->score);//stockage du nb de coup et du score
    fclose(fd);
    printf("Partie sauvegardee !\n");
}
//=====================================================================================
/*
Ouvre le fichier cr�� par sauvegarde, et r�cup�re les valeurs qui y sont stock�es */
void loadsave (jeu *game)
{
    FILE *fd=fopen("sauvegarde.txt","r");
    for (int i=0;i<game->y;i++)
    {
        for (int j=0;j<game->x;j++)
        {
            fscanf(fd,"%d",&(game->plateau[i][j]));
        }
    }
    fscanf(fd,"\t%d\t%d",&(game->k),&(game->score));
    fclose(fd);
}
//=======================================================================================
/*G�re le meilleur score, qui est stock� dans un fichier texte.*/
void load_meilleur_score (int score)
{
    int score_save;
    FILE *fd=fopen("meilleur_score.txt","r");
    fscanf(fd,"%d",&score_save);
    if (score>score_save) // si le score est sup�rieur � celui du fichier, on va r�-�crire dans celui-ci la nouvelle valeur
    {
        save_meilleur_score(score);
    }
    fclose(fd);
}
//=======================================================================================
/* Ecrit dans le fichier de meileur score
S'il y a d�j� un contenu, il sera effac� avant automatiquement */
void save_meilleur_score (int score)
{
    FILE *fd=fopen("meilleur_score.txt","w");
    fprintf(fd,"%d",score);
    fclose(fd);
}

//==========================================================================================
//OPTION 6 : Jeu a deux joueur
void action_multi (jeu *game)
{
    int x,y,scorej1=0,scorej2=0; //gestion de 2 scores
    char command;
    system("cls");
    while (game->k>0 && coup_possible(game))
    {
        game->score=0;// remise � �ro du score pour obtenir seulement le score du tour
        printf("\nNombre de coups restant(s) :%d\nScore j1 : %d\nScore j2 : %d \n",game->k,scorej1,scorej2);
        //a noter que si k est impair la partie est d�s�quilibr�e
        affiche_jeu(game);
        //Les tours des joueurs sont d�cid�s selon la parit� du nombre de coups restants
        if (game->k % 2 ==0)
        {
            printf("Au tour du joueur 1 :\n");
        }
        else
        {
            printf("Au tour du joueur 2 :\n");
        }
        scanf("%c",&command);
        switch(command)
        {
            case 'H':
            case 'h':
            case 'B':
            case 'b':
            case 'G':
            case 'g':
            case 'D':
            case 'd':scanf("%d%d",&x,&y); system("cls");
                     deplacement(x,y,command,game);break;
            case 'A':
            case 'a':system("cls"); aide();break;
            default :printf("commande non reconnue : %d",command);
        }
        suppr_auto(game);
        //attribution des scores (conditions invers�es car k est d�cr�ment� dans le switch s'il y a eu un d�placement)
        if (game->k % 2 ==0)
        {
            scorej2+=game->score; // incr�mentation des scores
        }
        else
        {
            scorej1+=game->score;
        }
    }

    printf("\nPartie terminee ! \n");
    color(10,0);
    //Affichage des r�sultats
    if (scorej1>scorej2)
    {
        printf("Bravo au joueur 1 qui remporte la partie avec %d points !\n",scorej1);
    }
    else
    {
        printf("Bravo au joueur 2 qui remporte la partie avec %d points !\n",scorej2);
    }
    color(15,0);
}


