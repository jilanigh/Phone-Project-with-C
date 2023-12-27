#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>


#pragma comment(lib, "winmm.lib")




void loading() {

    printf("\n");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x0B);  // 0x0B correspond a la couleur turquoise



    int j;
    int z;
    char name[40] = " Welcome To Your Phone ";
    z = strlen(name);
    for (j = 0; j <= 16; j++) {
        Sleep(50);

        printf("\xDB");
    }
    for (j = 0; j <= z; j++) {
        Sleep(60);
        printf(" %c", name[j]);
    }
    for (j = 0; j <= 16; j++) {
        Sleep(50);
        printf("\xDB");
    }
}

// Structures pour gerer les contacts
struct Contact {
    char nom[50];
    char numero[15];
};




// Fonction pour verifier le mot de passe
struct Utilisateur {
    char nom[50];
    char motDePasse[50];
};


// Fonction pour masquer la saisie du mot de passe
void masquerMotDePasse(char *motDePasse) {
    int caractere;
    int i = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x0B);  // 0x0B correspond � la couleur turquoise
    while (1) {
        caractere = _getch(); // Utilise la fonction getch() de la biblioth�que conio.h
        if (caractere == 13 || caractere == 10) { // Si Entr�e est press�e
            motDePasse[i] = '\0';
            break;
        } else if (caractere == 8 && i > 0) { // Si Backspace est press�e
            i--;
            printf("\b \b");
        } else if (caractere != 8) {
            motDePasse[i++] = (char)caractere;
            printf("*");
        }
    }
}

// Fonction pour v�rifier les informations de connexion
int verifierConnexion(struct Utilisateur *utilisateur) {
    char nomSaisi[50];
    char motDePasseSaisi[50];

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x0B);  // 0x0B correspond � la couleur turquoise

    printf("Nom d'utilisateur : ");
    scanf("%s", nomSaisi);

    printf("Mot de passe : ");
    masquerMotDePasse(motDePasseSaisi);


    FILE *fichier = fopen("mot_de_passe.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de mots de passe.\n");
        return 0; // Quitter le programme en cas d'erreur
    }
    int connexionReussie = 0; // Variable pour v�rifier la connexion

    while (fscanf(fichier, "%s %s", utilisateur->nom, utilisateur->motDePasse) == 2) {
        // Comparer avec les informations enregistr�es
        if (strcmp(nomSaisi, utilisateur->nom) == 0 && strcmp(motDePasseSaisi, utilisateur->motDePasse) == 0) {
            connexionReussie = 1; // Mettre la variable � vrai si les informations correspondent
            break; // Sortir de la boucle d�s qu'une correspondance est trouv�e
        }
    }

    fclose(fichier);

    if (connexionReussie) {
        printf("\n Hello %s! Connexion reussie.\n", utilisateur->nom);
        return 1; // Connexion r�ussie
    } else {
        printf("\n Nom d'utilisateur ou mot de passe incorrect. Veuillez reessayer.\n");
        return 0; // Connexion �chou�e
    }
}


// Tableau pour stocker les contacts
struct Contact contacts[100];
int nombreContacts = 0;



// Fonction pour ajouter un contact
void ajouterContact() {
    printf("Entrez le nom du contact : ");
    scanf("%s", contacts[nombreContacts].nom);

    printf("Entrez le num�ro du contact : ");
    scanf("%s", contacts[nombreContacts].numero);

    // Enregistrement du contact dans le fichier
    FILE *fichier = fopen("contacts.txt", "a"); // Ouvrir le fichier en mode "ajout"
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(fichier, "Ajout - Nom: %s, Num�ro: %s\n", contacts[nombreContacts].nom, contacts[nombreContacts].numero);

    fclose(fichier);

    nombreContacts++;
    printf("Contact ajout� avec succ�s.\n");
}

// Fonction pour supprimer un contact
void supprimerContact() {
    if (nombreContacts > 0) {
        printf("Liste des contacts :\n");
        for (int i = 0; i < nombreContacts; i++) {
            printf("%d. %s - %s\n", i + 1, contacts[i].nom, contacts[i].numero);
        }

        int choix;
        printf("Entrez le num�ro du contact � supprimer : ");
        scanf("%d", &choix);
        getchar();

        if (choix >= 1 && choix <= nombreContacts) {
            // Enregistrement de l'op�ration de suppression dans le fichier
            FILE *fichier = fopen("contacts.txt", "a"); // Ouvrir le fichier en mode "ajout"
            if (fichier == NULL) {
                printf("Erreur lors de l'ouverture du fichier.\n");
                return;
            }

            fprintf(fichier, "Suppression - Nom: %s, Num�ro: %s\n", contacts[choix - 1].nom, contacts[choix - 1].numero);

            fclose(fichier);

            // D�caler les contacts pour remplir l'emplacement supprim�
            for (int i = choix - 1; i < nombreContacts - 1; i++) {
                contacts[i] = contacts[i + 1];
            }

            nombreContacts--;
            printf("Contact supprim� avec succ�s.\n");
        } else {
            printf("Num�ro de contact invalide.\n");
        }
    } else {
        printf("Aucun contact � supprimer.\n");
    }
}
// Fonction pour modifier un contact
void modifierContact() {
    if (nombreContacts > 0) {
        printf("Liste des contacts :\n");
        for (int i = 0; i < nombreContacts; i++) {
            printf("%d. %s - %s\n", i + 1, contacts[i].nom, contacts[i].numero);
        }

        int choix;
        printf("Entrez le num�ro du contact � modifier : ");
        scanf("%d", &choix);
        getchar();

        if (choix >= 1 && choix <= nombreContacts) {
            printf("Entrez le nouveau nom du contact : ");
            scanf("%s", contacts[choix - 1].nom);

            printf("Entrez le nouveau num�ro du contact : ");
            scanf("%s", contacts[choix - 1].numero);

            printf("Contact modifi� avec succ�s.\n");
        } else {
            printf("Num�ro de contact invalide.\n");
        }
    } else {
        printf("Aucun contact � modifier.\n");
    }
}

// Fonction pour afficher tous les contacts
void afficherContact() {
    FILE *fichier = fopen("contacts.txt", "r"); // Ouvrir le fichier en mode lecture
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[100]; // Une taille suffisamment grande pour stocker une ligne du fichier

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
        getchar();
    }

    fclose(fichier);
}




void afficherCalendrier() {
    time_t t;
    struct tm *info;

    time(&t);
    info = localtime(&t);

    printf("Date actuelle : %02d-%02d-%04d\n", info->tm_mday, info->tm_mon + 1, info->tm_year + 1900);
}


char tableau[3][3]; // Tableau pour le jeu Tic Tac Toe

void initialiserTicTacToe() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tableau[i][j] = ' ';
        }
    }
}

void afficherTicTacToe() {
    printf("  1 2 3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("%c", tableau[i][j]);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("  -----\n");
        }
    }
}

int estGagnant() {
    // V�rifiez les lignes
    for (int i = 0; i < 3; i++) {
        if (tableau[i][0] == tableau[i][1] && tableau[i][1] == tableau[i][2] && tableau[i][0] != ' ') {
            return 1; // Gagnant trouv�
        }
    }

    // V�rifiez les colonnes
    for (int j = 0; j < 3; j++) {
        if (tableau[0][j] == tableau[1][j] && tableau[1][j] == tableau[2][j] && tableau[0][j] != ' ') {
            return 1; // Gagnant trouv�
        }
    }

    // V�rifiez les diagonales
    if ((tableau[0][0] == tableau[1][1] && tableau[1][1] == tableau[2][2] && tableau[0][0] != ' ') ||
        (tableau[0][2] == tableau[1][1] && tableau[1][1] == tableau[2][0] && tableau[0][2] != ' ')) {
        return 1; // Gagnant trouv�
    }

    return 0; // Aucun gagnant trouv�
}

int estMatchNul() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tableau[i][j] == ' ') {
                return 0; // Il reste au moins une case vide
            }
        }
    }
    return 1; // Aucune case vide, match nul
}

void jouerTicTacToe() {
    int ligne, colonne;
    char joueurActuel = 'X';

    initialiserTicTacToe();

    do {
        afficherTicTacToe();

        printf("Joueur %c, entrez la ligne et la colonne (ex: 1 2) : ", joueurActuel);
        scanf("%d %d", &ligne, &colonne);

        // V�rifier si le mouvement est valide
        if (ligne >= 1 && ligne <= 3 && colonne >= 1 && colonne <= 3 && tableau[ligne - 1][colonne - 1] == ' ') {
            tableau[ligne - 1][colonne - 1] = joueurActuel;

            // V�rifier s'il y a un gagnant ou un match nul
            if (estGagnant()) {
                afficherTicTacToe();
                printf("Le joueur %c a gagne!\n", joueurActuel);
                break;
            } else if (estMatchNul()) {
                afficherTicTacToe();
                printf("Match nul !\n");
                break;
            }

            // Changer de joueur
            joueurActuel = (joueurActuel == 'X') ? 'O' : 'X';
        } else {
            printf("Mouvement invalide. Veuillez reessayer.\n");
        }

    } while (1); // Boucle infinie, vous pouvez ajouter des conditions de fin de jeu
}
int main() {
    int choix = 0;

    const char *nomFichierSon = "song.wav";

    // Jouer le fichier son
    PlaySound(nomFichierSon, NULL, SND_FILENAME | SND_ASYNC);

    // Laisser le programme s'exécuter pendant un certain temps pour permettre la lecture de la musique
    // Création d'un utilisateur (à des fins de démonstration)
    struct Utilisateur utilisateur;

    // Vérifier les informations de connexion
    if (!verifierConnexion(&utilisateur)) {
        return 0; // Quitter le programme si la connexion échoue
    }
    loading();

    do {
        // Affichage du menu principal
        printf("\n1. Gestion des contacts\n");
        printf("2. Afficher le calendrier\n");
        printf("3. Jouer à Tic Tac Toe\n");
        printf("4. Quitter\n");

        // Saisie du choix de l'utilisateur
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        // Traitement du choix de l'utilisateur
        switch (choix) {
            case 1:
                // Gestion des contacts
                do {
                    // Affichage du sous-menu pour la gestion des contacts
                    printf("\n1. Ajouter un contact\n");
                    printf("2. Supprimer un contact\n");
                    printf("3. Modifier un contact\n");
                    printf("4. Afficher les contacts\n");
                    printf("5. Retour\n");
                    printf("\n");
                    printf("\n");

                    // Saisie du choix dans le sous-menu
                    printf("Choisissez une option : ");
                    scanf("%d", &choix);

                    // Traitement du choix dans le sous-menu
                    switch (choix) {
                        case 1:
                            ajouterContact();
                            break;
                        case 2:
                            supprimerContact();
                            break;
                        case 3:
                            modifierContact();
                            break;
                        case 4:
                            afficherContact();
                            break;
                        default:
                            break;
                    }
                } while (choix != 5); // Retour au menu principal
                break;
            case 2:
                afficherCalendrier();
                break;
            case 3:
                jouerTicTacToe();
                break;
            case 4:
                printf("Merci pour votre attention !\n");
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 4);

    return 0;
}
