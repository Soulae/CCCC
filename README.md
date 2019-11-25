Candy crush en C


Notre structure de données comporte un plateau, ce plateau est défini par une taille
en x et en y, un score, un nombre de coup et un tableau a deux dimension comportant
des pions. Ces pions sont en fait des entiers.

La taille du plateau, le nombre de jetons différents (8 au maximum) et le nombre de
coup sont des arguments du programme.

Les options que l'on a choisies sont : 

2 :Deblocage, quand on lance une partie classique et qu'il n'y plus de déplacement possible
alors le programme réorganise le plateau et enlève deux coups à jouer(k-2).

3 : Plateaux spéciaux, possibilité de lancer une partie avec un objectif a réaliser sur un
plateau torique.

4 : Sauvegarde, nous avons implémenté la possibilité de remettre le meilleur score a 0.

6 : Jeu à deux joueurs, au tour par tour. Le joueur ayant le meilleur score gagne la partie.

Au vu des options choisies notre jeu ne gère pas les combinaisons en coude ou en T, par rapport
à un candy crush "classique", il supprime d'abord les combinaisons verticales, puis les horizontales
restantes. Quand on commence une partie, le seul moyen de revenir au menu est de relancer le programme.

Principales fonctions :

verif : renvoie 0 si il n'y a pas de combinaison, et 1 si il y en a au moins une.

Deplacement : Quand on appelle la fonction, le déplacement est toujours effectué, on appelle
ensuite la fonction verif qui vérifie si il le deplacement est valide, sinon on l'annule.
Quand le deplacement est valide la fonction décrémente le champ K.

suppr_auto : fonction qui supprime les combinaisons en parcourant tout le tableau, d'abord 
pour les combinaisons verticales, puis horizontales. En fonction du nombre de pions supprimés,
elle calcule le score et met a jour le champ dans la structure.

affiche_jeu : Fonction qui parait barbare, les structures de contrôles sont la pour gérer les cas
ou la taille du le tableau est >10. Comme on affiche les indices du tableau le nombre 11 provoque
un décalage sur l'affichage du tableau par exemple.

coup_possible : Cette fonction parcourt tout le tableau et pour chaque pion effectue tous les deplacements.
Si un deplacement provoque une combinaison, la fonction renvoie 1, sinon elle renvoie 0.

Librairie particulière : <windows.h>, pour l'affichage des couleurs sur la console.
