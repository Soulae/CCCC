#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

typedef struct
{
	int x; //Largeur
	int y; //Hauteur
	int **plateau;
	int k;//Nb de coups
	int score;
	int j;//Nb de jetons differents
}jeu;

// Fonction qui modifie la couleur du prochian texte affiché sur la console
void color(int t,int f);

//Fonction qui cree un plateau
jeu * init_jeu (int x, int y);

//Fonction qui affiche le jeu
void affiche_jeu (jeu *j);

//Fonction qui remplit de maniere aleatoire le plateau de jeu
void remp_jeu(jeu *game);

//Fonction qui verifie s'il y a des combinaisons dans le jeu
int verif (jeu *game);

//Fonction qui supprime automatique toute les combinaisons
void suppr_auto(jeu *game);

//Fonction qui supprime les combinaisons horizontales
void suppr_horizontal(jeu *game, int ligne, int col, int nb);

//Fonction qui supprime les combinaison verticales
void suppr_vertical (jeu *game, int ligne, int col, int nb);

//Sous-fonction d'inversion gauche/droite
void depl_g(jeu * game, int x, int y);
void depl_d(jeu * game, int x, int y);

//Sous-fontcion de deplacement haut/bas
void depl_h(jeu * game, int x, int y);
void depl_b(jeu * game, int x, int y);

//Fonction qui deplace un pion et annule le deplacement si il n'est pas valide
void deplacement (int x, int y, char dir, jeu *game);

//Fonction que gère la partie
void action (jeu* game);

//Fonction qui affiche les commandes
void aide();

//OPTION 2 : Deblocage
//Fonction de test sur d'eventuels deplacement possible (retourne 1 s'il y en a, et 0 sinon)
int coup_possible(jeu * game);

//Fonction qui remplit une case avec une valeur aléatoire
void remp_val(jeu * game, int x, int y);


//============================================================================================
//OPTION 3 : Plateau torique, mission spéciale
//Copie de déplacement qui gère les déplacements d'un bord à l'autre du plateau (plateau torique)
void deplacement_torique (int x, int y, char dir, jeu *game);

//copie de "action" spécifique au mode de jeu spécial "missions coeurs"
void action_mission (jeu* game);

//Copie de suppr_auto spécifique pour la missison spéciale
int suppr_auto_mission(jeu *game);


//============================================================================================
//OPTION 4 : sauvegarde
//Fonction qui sauvegarde le plateau dans un fichier
void sauvegarde (jeu *game);

//Fonction qui charge la sauvegarde dans le plateau courant
void loadsave (jeu *game);

//Fonction qui gère les meilleurs score
void load_meilleur_score (int score);
void save_meilleur_score (int score);


//==============================================================================================
//OPTION 6 :Jeu a deux joueurs
void action_multi (jeu *game);





