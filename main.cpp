#include <iostream>
#include "conio.h"
#include <stdlib.h>
#include <stdio.h>
#include "aide.h"
#include <string.h>
#include <time.h>
using namespace std;

/* [DEBUT] Fonctions affichages */

// Fonction permettant de creer un tableau de 8*8 vide.

void separeTab(int n)
{
    int cpt;

    for (cpt = 0; cpt < n; cpt++)
    {
        printf("+---");
    }
    puts("+");
    return;
}

// Coloration des pions du tableau selon la couleur : Jaune, Rouge ou Noir.

void colorTab(int tab[8][8], int x, int y, int x_active, int y_active)
{
    char pion = 'O';
    printf("|");

    if(x_active == x && y_active == y && tab[x_active][y_active] == 'J')
    {
        textcolor(YELLOW);
        textbackground(LIGHTBLUE);
        printf("%2c ", pion);
        textbackground(DARKGRAY);
    }
    else if(tab[x][y] == 'J')
    {
        textcolor(YELLOW);
        printf("%2c ", pion);
    }
    else if(tab[x][y] == 'R')
    {
        textcolor(LIGHTRED);
        printf("%2c ", pion);
    }
    else if(tab[x][y] == 'N')
    {
        textcolor(BLACK);
        printf("%2c ", pion);
    }
    else if(tab[x][y] == 0)
    {
        textcolor(DARKGRAY);
        printf("%2c ", pion);

    }
    else if((tab[x][y] >= 'A' && tab[x][y] <= 'H') || (tab[x][y] >= '0' && tab[x][y] <= '7'))
    {
        textcolor(LIGHTGREEN);
        printf("%2c ", tab[x][y]);
    }
    // printf("%2c ", tab[x][y]);
    // printf("%2c ", pion);
    textcolor(BLACK);
    return;
}

// Fonction affichage du tableau de jeu.

void afficheTab(int tab[8][8], int taille_x, int taille_y, int ligne, int colonne, int x_active, int y_active)
{
    int x, y;

    gotoxy(ligne, colonne);

    for (y = 0; y < taille_y; y++)
    {
        gotoxy(ligne, colonne++);
        separeTab(taille_x);

        gotoxy(ligne, colonne++);
        for (x = 0; x < taille_x; x++)
        {
            // printf("|%2c ", tab[x][y]);
            colorTab(tab, x, y, x_active, y_active);
        }
        puts("|");
    }

    gotoxy(ligne, colonne++);
    separeTab(taille_x);
    return;
}

// FONCTION DETERMINANT LA COULEUR DES PIONS

int genereCouleur()
{
    int nb;
    int couleur;

    nb = rand() % 3 + 1;

    if(nb == 1)
    {
        couleur = 'J';
    }
    else if(nb == 2)
    {
        couleur = 'R';
    }
    else
    {
        couleur = 'N';
    }
    return couleur;
}


// FONCTION PERMETTANT LE PLACAGE DES PIONS

void initTab(int tab[8][8], int taille)
{
    int R = 1, J = 1, N = 1, x, y;
    int couleur;

    for (y = 0; y < taille; y++)
    {
        for (x = 0; x < taille; x++)
        {
            do
            {
                couleur = genereCouleur();

                if(couleur == 'J' && J <= 34)
                {
                    tab[x][y] = couleur;
                    J = J + 1;
                }
                else if(couleur == 'R' && R <= 20)
                {
                    tab[x][y] = couleur;
                    R = R + 1;
                }
                else if(couleur == 'N' && N <= 10)
                {
                    tab[x][y] = couleur;
                    N = N + 1;
                }
                else
                {
                    tab[x][y] = 0;
                }

            } while(tab[x][y] == 0);
        }
    }
    return;
}


// AFFICHAGE DU MENU DE DEPART

char menu()
{
    char selection;

    do
    {
        system("cls");

        printf("L'attrape-sous\n");
        printf("--------------\n");
        printf("1. Mode solo\n");
        printf("2. Mode deux joueurs\n");
        printf("3. Aide\n\n");
        printf("Selection du mode : ");
        cin >> selection;
    } while(selection < '1' || selection > '2');

    return selection;
}

// AFFICHAGE DU SCORE DANS LES ESPACES PREVUS

void afficheScore(int num_J, int J_J1, int N_J1, int R_J1, int J_J2, int N_J2, int R_J2)
{
    int scoreT_J1, scoreT_J2;
    scoreT_J1 = J_J1 + R_J1 * 2 + N_J1 * 3;
    scoreT_J2 = J_J2 + R_J2 * 2 + N_J2 * 3;

    if(num_J == 3 || num_J == 4 || num_J == 7 || num_J == 8)
    {
        int J, R, N, Malus;
        J = 34 - (J_J1 + J_J2);
        R = 20 - (R_J1 + R_J2);
        N = 10 - (N_J1 + N_J2);
        Malus = J + R * 2 + N * 3;

        if((num_J == 3 && num_J != 7) || (num_J == 7 && num_J != 3))
        {
            scoreT_J1 = scoreT_J1 - Malus;
        }
        else
        {
            scoreT_J2 = scoreT_J2 - Malus;
        }

        textcolor(WHITE);
        textbackground(BLACK);
        gotoxy(55, 20);
        printf("Score Total\r\n");
        gotoxy(55, 22);
        if(num_J == 7 || num_J == 8)
        {
            printf("Joueur : %i\r\n\n", scoreT_J1);
            gotoxy(55, 24);
            printf("CPU IA : %i\r\n\n", scoreT_J2);
        }
        else
        {
            printf("Joueur 1 : %i\r\n\n", scoreT_J1);
            gotoxy(55, 24);
            printf("Joueur 2 : %i\r\n\n", scoreT_J2);
        }
        textcolor(BLACK);
        textbackground(DARKGRAY);
    }
    else
    {
        textcolor(WHITE);
        textbackground(BLACK);
        printf("Score\r\n");
        gotoxy(1, 10);
        if(num_J == 5 || num_J == 6)
        {
            printf("Joueur\r\n\nJaune : %i\r\nRouge : %i\r\nNoir : %i\r\nTotal : %i\r\n\n", J_J1, R_J1, N_J1, scoreT_J1);
            gotoxy(1, 20);
            printf("CPU IA\r\n\nJaune : %i\r\nRouge : %i\r\nNoir : %i\r\nTotal : %i\r\n\n", J_J2, R_J2, N_J2, scoreT_J2);
        }
        else
        {
            printf("Joueur 1\r\n\nJaune : %i\r\nRouge : %i\r\nNoir : %i\r\nTotal : %i\r\n\n", J_J1, R_J1, N_J1, scoreT_J1);
            gotoxy(1, 20);
            printf("Joueur 2\r\n\nJaune : %i\r\nRouge : %i\r\nNoir : %i\r\nTotal : %i\r\n\n", J_J2, R_J2, N_J2, scoreT_J2);
        }
        textcolor(BLACK);
        textbackground(DARKGRAY);
    }
}

void afficheSelection(int numJoueur, char texte[1000], char texte2[1000], char texte3[1000], int J, int R, int N)
{
    int pointT;
    pointT = J + R * 2 + N * 3;

    textbackground(BLACK);
    textcolor(WHITE);

    if(numJoueur != 3 && numJoueur != 4 && numJoueur != 7 && numJoueur != 8)
    {
        gotoxy(55, 8);
        if(numJoueur == 5)
        {
            printf("Joueur :\r\n\n");
        }
        else if(numJoueur == 6)
        {
            printf("CPU IA :\r\n\n");
        }
        else
        {
            printf("Joueur %i :\r\n\n", numJoueur);
        }
        gotoxy(55, 10);
        printf("%s\r\n\n", texte);
        gotoxy(55, 11);
        printf("%s\r\n\n", texte2);
        gotoxy(55, 13);
        printf("%s\r\n\n", texte3);

        gotoxy(55, 16);
        if(numJoueur == 6)
        {
            printf("Appuyez sur une touche");
            gotoxy(55, 17);
            printf("pour continuer");
        }
        else
        {
            printf("Ligne : \t Colonne : \r\n");
        }

        gotoxy(55, 20);
        if(pointT <= 1)
        {
            printf("Point restant : %i\r\n", pointT);
        }
        else
        {
            printf("Points restants : %i\r\n", pointT);
        }
        gotoxy(55, 22);
        printf("Pions restants :\r\n");
        gotoxy(55, 23);
        printf("%i Jaunes\r\n", J);
        gotoxy(55, 24);
        printf("%i Rouges\r\n", R);
        gotoxy(55, 25);
        printf("%i Noirs\r\n", N);
    }
    else
    {
        strcpy(texte, "Fin de partie");
        strcpy(texte2, "Merci d'avoir joue !");
        gotoxy(55, 13);
        printf("%s\r\n\n", texte);
        gotoxy(55, 15);
        printf("%s\r\n\n", texte2);

        // gotoxy(20,13);
        // printf("%s\r\n\n", "Voulez vous rejouer ? ");
    }

    textcolor(BLACK);
    textbackground(DARKGRAY);
}

void afficheTabFinal(int plateau[8][8], int taille, int tour, int num_J, int J_J1, int N_J1, int R_J1, int J_J2, int N_J2, int R_J2, char texte[1000], char texte2[1000], char texte3[1000], int x_active, int y_active)
{
    system("cls");
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(33, 4);
    printf("Tour : %i\r\n", tour);

    textcolor(BLACK);
    textbackground(DARKGRAY);
    // Gestion des coordonnees
    int coordonnees_x[8][8] = {{'0'}, {'1'}, {'2'}, {'3'}, {'4'}, {'5'}, {'6'}, {'7'}};     // Repérage des colonnes du plateau
    int coordonnees_y[8][8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};                     // Repérage des lignes du plateau

    gotoxy(1, 6);
    afficheScore(num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2);

    afficheTab(coordonnees_x, taille, 1, 20, 6, -1, -1);
    afficheTab(coordonnees_y, 1, taille, 14, 10, -1, -1);
    afficheTab(plateau, taille, taille, 20, 10, x_active, y_active);

    int J, R, N;
    J = 34 - (J_J1 + J_J2);
    R = 20 - (R_J1 + R_J2);
    N = 10 - (N_J1 + N_J2);

    afficheSelection(num_J, texte, texte2, texte3, J, R, N);

    textbackground(BLACK);
    textcolor(WHITE);
}

// CONVERTION DES COORDONNEES DE TYPE CHAR EN INT.
int convert_coordonnees(char x)
{
    int x_converted;

    if(x == 'A')
    {
        x_converted = 0;
    }
    else if(x == 'B')
    {
        x_converted = 1;
    }
    else if(x == 'C')
    {
        x_converted = 2;
    }
    else if(x == 'D')
    {
        x_converted = 3;
    }
    else if(x == 'E')
    {
        x_converted = 4;
    }
    else if(x == 'F')
    {
        x_converted = 5;
    }
    else if(x == 'G')
    {
        x_converted = 6;
    }
    else if(x  == 'H')
    {
        x_converted = 7;
    }
    else if(x == '0')
    {
        x_converted = 0;
    }
    else if(x == '1')
    {
        x_converted = 1;
    }
    else if(x == '2')
    {
        x_converted = 2;
    }
    else if(x == '3')
    {
        x_converted = 3;
    }
    else if(x == '4')
    {
        x_converted = 4;
    }
    else if(x == '5')
    {
        x_converted = 5;
    }
    else if(x == '6')
    {
        x_converted = 6;
    }
    else if(x == '7')
    {
        x_converted = 7;
    }
    else
    {
        x_converted = -1;
    }
    return x_converted;
}

// CONVERTION DES COORDONNEES POUR L'IA
int convert_lig_IA(int x)
{
    int x_converted;

    if(x == 0)
    {
        x_converted = 'A';
    }
    else if(x == 1)
    {
        x_converted = 'B';
    }
    else if(x == 2)
    {
        x_converted = 'C';
    }
    else if(x == 3)
    {
        x_converted = 'D';
    }
    else if(x == 4)
    {
        x_converted = 'E';
    }
    else if(x == 5)
    {
        x_converted = 'F';
    }
    else if(x == 6)
    {
        x_converted = 'G';
    }
    else if(x  == 7)
    {
        x_converted = 'H';
    }
    else
    {
        x_converted = -1;
    }
    return x_converted;
}

int verif_coordonnees(int plateau[8][8], int lig, int col)
{
    int erreur = 0;

    if(lig != -1 && col != -1)
    {
        if(plateau[col][lig] == 'J')
        {
            erreur = 1;
        }
    }

    return erreur;
}

int SelectionCol()
{
    int col = -1;
    char col_t[2];
    int erreur_msg = 0;

    do
    {
        if(erreur_msg == 1)
        {
            gotoxy(55, 13);
            printf("Colonne incorrecte !\r\n");
            erreur_msg = 0;
        }
        gotoxy(76, 16);
        printf("\t\t    ");
        gotoxy(76, 16);
        scanf("%2s", col_t);
        erreur_msg = 1;

        if(((int)col_t[0] >= '0' && (int)col_t[0] <= '7') && col_t[1] == NULL)
        {
            col = convert_coordonnees(col_t[0]);
        }
    } while(col == -1 || col < 0);
    return col;
}

int SelectionLig(int plateau[8][8], int type_case)
{
    int cpt, lig = -1, erreur = 0;
    char lig_t[2];
    int erreur_msg = 0;

    do
    {
        if(erreur_msg == 1)
        {
            gotoxy(55, 13);
            printf("Ligne incorrecte !\t");
            erreur_msg = 0;
        }
        gotoxy(63, 16);
        printf("   Colonne :\t\t    ");
        gotoxy(63, 16);
        scanf("%2s", lig_t);
        erreur_msg = 1;

        if((int)lig_t[0] >= 'A' && (int)lig_t[0] <= 'H' && lig_t[1] == NULL)
        {
            lig = convert_coordonnees(lig_t[0]);

            if(type_case == 0)
            {
                for(cpt = 0; cpt <= 7; cpt++)
                {
                    if(verif_coordonnees(plateau, lig, cpt) == 1)
                    {
                        erreur = 1;
                    }
                }
            }
            else if(type_case == 1)
            {
                erreur = 1;
            }
        }
    } while(lig == -1 || lig < 0 || erreur == 0);

    /* Effacement du message d'erreur */
    gotoxy(55, 13);
    textcolor(BLACK);
    printf("Ligne incorrecte !\t");
    textcolor(WHITE);
    /* Effacement du message d'erreur */

    return lig;
}
/* [FIN] Fonctions affichages */

/* [DEBUT] Fonctions déplacements */

// VERIFICATION DE LA PRESENCE OU NON D'UNE CASE REMPLIE
int verif_case_A(int plateau[8][8], int lig, int col, int lig_a, int col_a)
{
    int erreur = 0;
    double x, y;                 // Coordonnées du milieu

    x = (col + col_a) / 2.0;
    y = (lig + lig_a) / 2.0;

    if((x == (int)x && y == (int)y) && plateau[(int)x][(int)y] != 0 && plateau[col_a][lig_a] == 0 && (x != col || y != lig))
    {
        erreur = 1;
    }
    return erreur;
}

// VERIFICATION SI LE PION J SELECTIONNE PEUT SE DEPLACER
int verif_deplacement(int plateau[8][8], int lig, int col)
{
    int cpt, cpt2;
    int erreur = 0;

    if(verif_coordonnees(plateau, lig, col) == 1)
    {
        for(cpt = lig - 2; cpt <= lig + 2; cpt = cpt + 2)
        {
            for(cpt2 = col - 2; cpt2 <= col + 2; cpt2 = cpt2 + 2)
            {
                if((cpt >= 0 && cpt <= 7) && (cpt2 >= 0 && cpt2 <= 7) && (cpt != lig || cpt2 != col)) // A METTRE DANS LE RAPPORT
                {
                    if(plateau[cpt2][cpt] == 0)
                    {
                        if(verif_case_A(plateau, lig, col, cpt, cpt2) == 1)
                        {
                            erreur = 1;
                        }
                    }
                }
            }
        }
    }
    return erreur;
}
/* [FIN] Fonctions déplacements */

/* [DEBUT] Fonctions robot */
int verif_coordonnees_vide(int plateau[8][8], int lig, int col)
{
    int erreur = 0;

    if(lig != -1 && col != -1)
    {
        if(plateau[col][lig] == 0)
        {
            erreur = 1;
        }
    }

    return erreur;
}
/* [FIN] Fonctions robot */

/* [DEBUT] Fonction fin de partie */
int fin_partie(int plateau[8][8], int taille)
{
    int x, y;
    int fin = 0;

    for (y = 0; y < taille; y++)
    {
        for (x = 0; x < taille; x++)
        {
            if(verif_deplacement(plateau, x, y) == 1)
            {
                fin = 1;
            }
        }
    }
    return fin;
}
/* [FIN] Fonction fin de partie */


int main()
{
    char select_menu;
    int return_menu = 0;

/* SELECTION DU MODE DE JEU */
    do
    {
        select_menu = menu();

        /* [DEBUT] Mode un joueur */
        if(select_menu == '1')
        {
            system("cls");

            // DEFINITION DES VARIABLES

            int plateau[8][8] = {0};                                            // Plateau de jeu.
            int taille = 8;                                                     // Dimension du plateau.
            int tour = 0;                                                       // Variable contenant le nombre de tour.
            char texte[1000] = {NULL};                                          // Variable contenant le texte numéro 1.
            char texte2[1000] = {NULL};                                         // Variable contenant le texte numéro 2.
            char texte3[1000] = "Correct si possible !";                        // Variable contenant le texte numéro 3.
            int J_J1 = 0, N_J1 = 0, R_J1 = 0, J_J2 = 0, N_J2 = 0, R_J2 = 0;     // Nombre de pion de la couleur capturés par J1 ou J2.
            int num_J = 5;                                                      // Numéro du joueur.
            int lig, col;                                                       // Colonne et ligne du pion J à selectionner.
            int lig_a, col_a;                                                   // Colonne et ligne des pions entourant J.
            int x_mil, y_mil;                                                   // Coordonnées du milieu entre le pion départ et fin.
            int verif_coor = 0;                                                 // Variable booléenne pour la vérification des coordonnés.
            int affiche_texte3 = 0;                                             // Variable booléenne pour l'affichage ou non de texte3.
            int rejouer = 0;                                                    // 1 = le joueur peut rejouer.
            int fin = 1;                                                        // Condition de fin de partie.
            int cpt_initTab = 0;
            int cpt = 0;
            int x, y;
            int col_b[30] ={NULL};
            int lig_b[30] ={NULL};
            int indice, indice_vide;
            int lig_vide[30] = {NULL};
            int col_vide[30] = {NULL};
            int cpt2 = 0;

            srand(time(NULL));
            int cpt_finalTab = (rand() % 1000) + 1;

            // INITIALISATION DU PLATEAU

            while(cpt_initTab <= cpt_finalTab)
            {
                initTab(plateau, taille);
                cpt_initTab = cpt_initTab + 1;
            }

            // TOUR PRELIMINAIRE

            while(tour == 0)
            {
                strcpy(texte, "Veuillez selectionner");
                strcpy(texte2, "un pion jaune a retirer");

            // AFFICHAGE PLATEAU

                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);

            // JOUEUR 1
            num_J = 5;

                do
                {

                    if(affiche_texte3 == 1)
                    {
                        afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
                    }

                    lig = SelectionLig(plateau, 0);
                    col = SelectionCol();
                    affiche_texte3 = 1;

            // FONCTION DE VERIFICATION DES COORDONEES

                    verif_coor = verif_coordonnees(plateau, lig, col);
                } while(verif_coor == 0);

                affiche_texte3 = 0;
                plateau[col][lig] = 0;
                J_J1 = J_J1 + 1;

            // FIN DU TOUR DE J1


            // JOUEUR 2
                num_J = 6;
                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);

                for (y = 0; y < taille; y++)
                {
                    for (x = 0; x < taille; x++)
                    {
                        if((verif_coordonnees(plateau, x, y) == 1))
                        {
                            lig_b[cpt] = x;
                            col_b[cpt] = y;

                            cpt = cpt + 1;
                        }
                    }
                }

                indice = rand() % (cpt + 1);

                col = col_b[indice];
                lig = lig_b[indice];

                plateau[col][lig] = 0;
                J_J2 = J_J2 + 1;

            // FIN DU TOUR DE J2 : TOUR SUIVANT
                tour = tour + 1;
            }

           fin = fin_partie(plateau, taille);

           while(fin == 1)
            {
                if(fin_partie(plateau, taille) == 1)
                {
                // DEPLACEMENT DU PION JAUNE DEBUT :J1

                    num_J = 5;

                    strcpy(texte, "Veuillez selectionner");
                    strcpy(texte2, "un pion jaune a deplacer");

                    afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);  // Affichage du plateau de jeu

                // VERIFICATION DES COORDONNES de J

                    do
                    {

                        if(affiche_texte3 == 1)
                        {
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
                        }

                        lig = SelectionLig(plateau, 0);
                        col = SelectionCol();
                        affiche_texte3 = 1;

                        verif_coor = verif_deplacement(plateau, lig, col);
                    } while(verif_coor == 0);

                    affiche_texte3 = 0;

                // VERIFICATION ET SAISIE DE LA CASE D'ARRIVE

                    do
                    {
                        strcpy(texte, "Veuillez selectionner");
                        strcpy(texte2, "la case d'arrive");

                        // LE JOUEUR PEUX REJOUER

                        if(rejouer == 1)
                        {
                            lig = lig_a;
                            col = col_a;

                            strcpy(texte3, "Veuillez rejouer");
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, col, lig);
                            strcpy(texte3, "Correcte si possible !");
                            rejouer = 0;
                        }
                        else
                        {
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", col, lig);
                        }

                        do
                        {
                            if(affiche_texte3 == 1)
                            {
                                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, col, lig);
                            }
                            lig_a = SelectionLig(plateau, 1);
                            col_a = SelectionCol();
                            affiche_texte3 = 1;

                            verif_coor = verif_case_A(plateau, lig, col, lig_a, col_a);
                        } while(verif_coor == 0);

                        affiche_texte3 = 0;

                        x_mil = (col + col_a) / 2;
                        y_mil = (lig + lig_a) / 2;

                    /* GESTION DU SCORE */

                        if(plateau[x_mil][y_mil] == 'J')
                        {
                            J_J1 = J_J1 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'R')
                        {
                            R_J1 = R_J1 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'N')
                        {
                            N_J1 = N_J1 + 1;
                        }

                        plateau[x_mil][y_mil] = 0;
                        plateau[col_a][lig_a] = plateau[col][lig];
                        plateau[col][lig] = 0;

                        if(verif_deplacement(plateau, lig_a, col_a) == 1)
                        {
                            rejouer = 1;
                        }

                    } while(rejouer == 1);

                // FIN DU SELECTION DU DEPLACEMENT DE J1
                }

                if(fin_partie(plateau, taille) == 1)
                {
                // DEPLACEMENT DU PION JAUNE DEBUT
                    num_J = 6;

                    strcpy(texte, "IA joue");

                    afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, "", "", -1, -1);  // Affichage du plateau de jeu

                // VERIFICATION POSSIBILITE DE DEPLACEMENT DU PION J
                    cpt = 0;
                    indice = -1;

                    for (y = 0; y < taille; y++)
                    {
                        for (x = 0; x < taille; x++)
                        {
                            if((verif_deplacement(plateau, x, y) == 1))
                            {
                                lig_b[cpt] = x;
                                col_b[cpt] = y;

                                cpt = cpt + 1;
                            }
                        }
                    }

                    indice = rand() % (cpt + 1);

                    col = col_b[indice];
                    lig = lig_b[indice];

                // SAISIE DE LA CASE D'ARRIVE
                    do
                    {
                        strcpy(texte, "IA joue");
                        if(rejouer == 1)
                        {
                            lig = lig_a;
                            col = col_a;
                            rejouer = 0;
                        }
                        afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, "", "Saut multiple", col, lig);

                        cpt = 0;
                        indice = -1;

                        for(y = lig - 2; y <= lig + 2; y = y + 2)
                        {
                            for(x = col - 2; x <= col + 2; x = x + 2)
                            {
                                if((y >= 0 && y <= 7) && (x >= 0 && x <= 7) && (y != lig || x != col)) // A METTRE DANS LE RAPPORT
                                {
                                    if(plateau[x][y] == 0)
                                    {
                                        if(verif_case_A(plateau, lig, col, y, x) == 1)
                                        {
                                            lig_vide[cpt] = y;
                                            col_vide[cpt] = x;

                                            cpt = cpt + 1;
                                        }
                                    }
                                }
                            }
                        }
                        if(cpt == 0)
                        {
                            indice = 0;
                        }
                        else
                        {
                            indice = rand() % (cpt);
                        }

                        col_a = col_vide[indice];
                        lig_a = lig_vide[indice];

                        gotoxy(55, 13);
                        printf("Case de depart : (%c ; %i)", convert_lig_IA(lig), col);
                        gotoxy(55, 14);
                        printf("Case d'arrivee : (%c ; %i)", convert_lig_IA(lig_a), col_a);
                        gotoxy(70, 17);
                        getch();
                        afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, "", "", col_a, lig_a);

                        x_mil = (col + col_a) / 2;
                        y_mil = (lig + lig_a) / 2;

                        /* GESTION DU SCORE */

                        if(plateau[x_mil][y_mil] == 'J')
                        {
                            J_J2 = J_J2 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'R')
                        {
                            R_J2 = R_J2 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'N')
                        {
                            N_J2 = N_J2 + 1;
                        }

                        plateau[x_mil][y_mil] = 0;
                        plateau[col_a][lig_a] = plateau[col][lig];
                        plateau[col][lig] = 0;

                        if(verif_deplacement(plateau, lig_a, col_a) == 1)
                        {
                            rejouer = 1;
                        }

                    } while(rejouer == 1);

                // FIN DU SELECTION DU DEPLACEMENT DE J2
                }

                tour = tour + 1;
                fin = fin_partie(plateau, taille);
            }

            // AFFICHAGE DES SCORES FINAUX
            if(num_J == 5)
            {
                afficheTabFinal(plateau, taille, tour, 7, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
            }
            else
            {
                afficheTabFinal(plateau, taille, tour, 8, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
            }

            /************************************************/
            char reponse;

            gotoxy(1, 6);
            printf("Rejouer ? O/N\r\n\n Reponse : ");
            cin >> reponse;

            if(reponse == 'o' || reponse == 'O')
            {
                return_menu = 1;
            }
        }
        /* [FIN] Mode un joueur */

        /* [DEBUT] Mode deux joueurs */
        else if(select_menu == '2')
        {
            system("cls");

            // DEFINITION DES VARIABLES

            int plateau[8][8] = {0};                                            // Plateau de jeu.
            int taille = 8;                                                     // Dimension du plateau.
            int tour = 0;                                                       // Variable contenant le nombre de tour.
            char texte[1000] = {NULL};                                          // Variable contenant le texte numéro 1.
            char texte2[1000] = {NULL};                                         // Variable contenant le texte numéro 2.
            char texte3[1000] = "Correct si possible !";                        // Variable contenant le texte numéro 3.
            int J_J1 = 0, N_J1 = 0, R_J1 = 0, J_J2 = 0, N_J2 = 0, R_J2 = 0;     // Nombre de pion de la couleur capturés par J1 ou J2.
            int num_J = 1;                                                      // Numéro du joueur.
            int lig, col;                                                       // Colonne et ligne du pion J à selectionner.
            int lig_a, col_a;                                                   // Colonne et ligne des pions entourant J.
            int x_mil, y_mil;                                                   // Coordonnées du milieu entre le pion départ et fin.
            int verif_coor = 0;                                                 // Variable booléenne pour la vérification des coordonnés.
            int affiche_texte3 = 0;                                             // Variable booléenne pour l'affichage ou non de texte3.
            int rejouer = 0;                                                    // 1 = le joueur peut rejouer.
            int fin = 1;                                                        // Condition de fin de partie.
            int cpt_initTab = 0;

            srand(time(NULL));
            int cpt_finalTab = (rand() % 1000) + 1;

            // INITIALISATION DU PLATEAU

            while(cpt_initTab <= cpt_finalTab)
            {
                initTab(plateau, taille);
                cpt_initTab = cpt_initTab + 1;
            }

            // TOUR PRELIMINAIRE

            while(tour == 0)
            {
                strcpy(texte, "Veuillez selectionner");
                strcpy(texte2, "un pion jaune a retirer");

            // AFFICHAGE PLATEAU

                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);

            // JOUEUR 1
            num_J = 1;

                do
                {

                    if(affiche_texte3 == 1)
                    {
                        afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
                    }

                    lig = SelectionLig(plateau, 0);
                    col = SelectionCol();
                    affiche_texte3 = 1;

            // FONCTION DE VERIFICATION DES COORDONEES

                    verif_coor = verif_coordonnees(plateau, lig, col);
                } while(verif_coor == 0);

                affiche_texte3 = 0;
                plateau[col][lig] = 0;
                J_J1 = J_J1 + 1;

            // FIN DU TOUR DE J1


            // JOUEUR 2
                num_J = 2;
                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);

                do
                {
                    if(affiche_texte3 == 1)
                    {
                        afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
                    }
                    lig = SelectionLig(plateau, 0);
                    col = SelectionCol();
                    affiche_texte3 = 1;

                    verif_coor = verif_coordonnees(plateau, lig, col);
                } while(verif_coor == 0);

                affiche_texte3 = 0;
                plateau[col][lig] = 0;
                J_J2 = J_J2 + 1;

            // FIN DU TOUR DE J2 : TOUR SUIVANT
                tour = tour + 1;
            }

            fin = fin_partie(plateau, taille);

            /* TOUR 1 A N */

            while(fin == 1)
            {
                if(fin_partie(plateau, taille) == 1)
                {
                // DEPLACEMENT DU PION JAUNE DEBUT :J1

                    num_J = 1;

                    strcpy(texte, "Veuillez selectionner");
                    strcpy(texte2, "un pion jaune a deplacer");

                    afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);  // Affichage du plateau de jeu

                // VERIFICATION DES COORDONNES de J

                    do
                    {

                        if(affiche_texte3 == 1)
                        {
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
                        }

                        lig = SelectionLig(plateau, 0);
                        col = SelectionCol();
                        affiche_texte3 = 1;

                        verif_coor = verif_deplacement(plateau, lig, col);
                    } while(verif_coor == 0);

                    affiche_texte3 = 0;

                // VERIFICATION ET SAISIE DE LA CASE D'ARRIVE

                    do
                    {
                        strcpy(texte, "Veuillez selectionner");
                        strcpy(texte2, "la case d'arrive");

                        // LE JOUEUR PEUX REJOUER

                        if(rejouer == 1)
                        {
                            lig = lig_a;
                            col = col_a;

                            strcpy(texte3, "Veuillez rejouer");
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, col, lig);
                            strcpy(texte3, "Correcte si possible !");
                            rejouer = 0;
                        }
                        else
                        {
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", col, lig);
                        }

                        do
                        {
                            if(affiche_texte3 == 1)
                            {
                                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, col, lig);
                            }
                            lig_a = SelectionLig(plateau, 1);
                            col_a = SelectionCol();
                            affiche_texte3 = 1;

                            verif_coor = verif_case_A(plateau, lig, col, lig_a, col_a);
                        } while(verif_coor == 0);

                        affiche_texte3 = 0;

                        x_mil = (col + col_a) / 2;
                        y_mil = (lig + lig_a) / 2;

                    /* GESTION DU SCORE */

                        if(plateau[x_mil][y_mil] == 'J')
                        {
                            J_J1 = J_J1 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'R')
                        {
                            R_J1 = R_J1 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'N')
                        {
                            N_J1 = N_J1 + 1;
                        }

                        plateau[x_mil][y_mil] = 0;
                        plateau[col_a][lig_a] = plateau[col][lig];
                        plateau[col][lig] = 0;

                        if(verif_deplacement(plateau, lig_a, col_a) == 1)
                        {
                            rejouer = 1;
                        }

                    } while(rejouer == 1);

                // FIN DU SELECTION DU DEPLACEMENT DE J1
                }

                if(fin_partie(plateau, taille) == 1)
                {
                // DEPLACEMENT DU PION JAUNE DEBUT
                    num_J = 2;

                    strcpy(texte, "Veuillez selectionner");
                    strcpy(texte2, "un pion jaune a deplacer");

                    afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", -1, -1);  // Affichage du plateau de jeu

                // VERIFICATION POSSIBILITE DE DEPLACEMENT DU PION J
                    do
                    {
                        if(affiche_texte3 == 1)
                        {
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
                        }
                        lig = SelectionLig(plateau, 0);
                        col = SelectionCol();
                        affiche_texte3 = 1;

                        verif_coor = verif_deplacement(plateau, lig, col);
                    } while(verif_coor == 0);

                    affiche_texte3 = 0;

                // SAISIE DE LA CASE D'ARRIVE
                    do
                    {
                        strcpy(texte, "Veuillez selectionner");
                        strcpy(texte2, "la case d'arrive");

                        if(rejouer == 1)
                        {
                            lig = lig_a;
                            col = col_a;

                            strcpy(texte3, "Veuillez rejouer");
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, col, lig);
                            strcpy(texte3, "Correcte si possible !");
                            rejouer = 0;
                        }
                        else
                        {
                            afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, "", col, lig);
                        }

                        do
                        {
                            if(affiche_texte3 == 1)
                            {
                                afficheTabFinal(plateau, taille, tour, num_J, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, col, lig);
                            }
                            lig_a = SelectionLig(plateau, 1);
                            col_a = SelectionCol();
                            affiche_texte3 = 1;

                    // VERIFICATION SI LE DEPLACEMENT EST POSSIBLE OU NON

                            verif_coor = verif_case_A(plateau, lig, col, lig_a, col_a);
                        } while(verif_coor == 0);

                        affiche_texte3 = 0;

                        x_mil = (col + col_a) / 2;
                        y_mil = (lig + lig_a) / 2;

                        /* GESTION DU SCORE */

                        if(plateau[x_mil][y_mil] == 'J')
                        {
                            J_J2 = J_J2 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'R')
                        {
                            R_J2 = R_J2 + 1;
                        }
                        else if(plateau[x_mil][y_mil] == 'N')
                        {
                            N_J2 = N_J2 + 1;
                        }

                        plateau[x_mil][y_mil] = 0;
                        plateau[col_a][lig_a] = plateau[col][lig];
                        plateau[col][lig] = 0;

                        if(verif_deplacement(plateau, lig_a, col_a) == 1)
                        {
                            rejouer = 1;
                        }

                    } while(rejouer == 1);

                // FIN DU SELECTION DU DEPLACEMENT DE J2
                }

                tour = tour + 1;
                fin = fin_partie(plateau, taille);
            }

            // AFFICHAGE DES SCORES FINAUX
            if(num_J == 1)
            {
                afficheTabFinal(plateau, taille, tour, 3, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
            }
            else
            {
                afficheTabFinal(plateau, taille, tour, 4, J_J1, N_J1, R_J1, J_J2, N_J2, R_J2, texte, texte2, texte3, -1, -1);
            }

            /************************************************/
            char reponse;

            gotoxy(1, 6);
            printf("Rejouer ? O/N\r\n\n Reponse : ");
            cin >> reponse;

            if(reponse == 'o' || reponse == 'O')
            {
                return_menu = 1;
            }
        }

/* [FIN] Mode deux joueurs */

/* [DEBUT] Aide */

        else if(select_menu == '3')
        {
            system("cls");

            aide();

            system("pause");
            return_menu = 1;
        }

 /* [FIN] Aide  */

    } while(return_menu == 1);

    return 0;
}
