#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"

void aide()
{
    textcolor(LIGHTCYAN);
    printf("Demarrage de la partie\r\n");
    textcolor(WHITE);
    printf("Les 64 pions sont repartis au hasard sur le plateau de jeu.\r\n"
            "Ensuite, chaque joueur retire du plateau un et un seul pion jaune.\r\n\n");

    textcolor(LIGHTCYAN);
    printf("Deroulement de la partie\r\n");
    textcolor(WHITE);
    printf("A son tour de jeu, chaque joueur choisit un pion jaune comme point de depart\r\n"
            "et effectue autant de sauts qu'il peut en deplaçant ce pion.\r\n\n"
            "Lorsque plusieurs deplacements sont possibles, le joueur dont c'est le\r\n"
            "tour choisit le deplacement qu'il veut.\r\n\n");

    textcolor(LIGHTCYAN);
    printf("Regle du saut\r\n");
    textcolor(WHITE);
    printf("* un pion jaune peut sauter un pion de n'importe quelle couleur\r\n"
            "  si la case situee derriere ce pion dans le sens du deplacement est libre.\r\n\n"
            "* Les sauts sont possibles dans toutes les directions (diagonales incluses).\r\n\n"
            "* un pion jaune ne peut sauter par dessus plusieurs pions a la fois.\r\n\n"
            "Tous les pions ainsi sautes sont retires du plateau de jeu, et le joueur\r\n"
            "dont c'est le tour marque autant de points que la valeur des pions retires.\r\n\n");

    textcolor(LIGHTCYAN);
    printf("Fin de partie\r\n");
    textcolor(WHITE);
    printf("Lorsque plus aucun deplacement n'est possible, la partie s'arrete.\r\n"
            "Chaque joueur compte alors le nombre de points qu'il a accumule jusqu'a\r\n"
            "present. On compte ensuite le nombre de points correspondant aux pions\r\n"
            "restant sur le plateau, ce qui donne un malus M. Ce malus M est applique\r\n"
            "au score du joueur qui a joue en dernier.\r\n\n");
}
