#include "packrush.h"

int main(int argc,char** argv)
{
    // si le nombre d'arguments du programme diffère de ce que l'on attend, on sort en erreur
    if (argc !=5)
    {
        return EXIT_FAILURE;
    }

    // Initialisation pour la fonction random
    srand(time(NULL));

    int choix, meilleur_score, n, m;
    FILE *fd=fopen("meilleur_score.txt","r");

    //On récupère les valeur des arguments
    n=strtol(argv[3],NULL,10);//Largeur(x)
    m=strtol(argv[4],NULL,10);//Hauteur(y)
    jeu * game=init_jeu(n,m);

    game->k=strtol(argv[1],NULL,10);//initialisation des coups possibles
    game->j=strtol(argv[2],NULL,10);//initialisation du nombres de jetons

    fscanf(fd,"%d",&meilleur_score);

    //Affichage du menu
    color(15,0);
    printf("#################################################\n");
    printf("#\t\t\t\t\t\t#\n");
    printf("#\tBIENVENUE DANS CANDY CRUSH EN C\t\t#\n");
    printf("#\t\t\t\t\t\t#\n");
    printf("#################################################\n\n");
    printf("Le meilleur score est de : %d\n",meilleur_score);
    printf("1 ----> Nouvelle partie classique\n");
    printf("2 ----> Continuer\n");
    printf("3 ----> Mission speciale plateau torique, sans meilleur score\n");
    printf("4 ----> Jeu a deux joueurs, sans sauvegarde\n");
    printf("5 ----> Reset du meilleur score\n");
    printf("6 ----> Afficher l'aide\n");

    //Boucle principale
    do
    {
        scanf("%d",&choix);
        switch(choix)
        {
            case 1  :remp_jeu(game);
                     action(game);break; //fonction qui fait tourner le jeu

            case 2  :loadsave(game);
                     action(game);break;

            case 3  :remp_jeu(game);
                     action_mission(game);break;

            case 4  :remp_jeu(game);
                     action_multi(game); break;

            case 5 : save_meilleur_score(0);
                     printf("Meilleur score remis a zero !"); choix=42; break;

            case 6  :aide();

            default :choix=42;//Permet de pouvoir effectuer une nouvelle saisie après l'affichage de l'aide
                     printf("\nNouvelle saisie : ");
        }
    }while (choix==42);

    fclose(fd);
    return EXIT_SUCCESS;
}
