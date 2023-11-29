#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fonction permettant de choisir un Pseudo */
void Nom_Joueur();

/* Fonction d'affichage du pendu */
int affichage(int Etat);

/* Fonction qui transforme le mot en Underscore */
void Mot_Underscore(int Taille_Mot, char Under[]);

/* Fonction de vérification si le caractère est une lettre */
int Verification_est_une_lettre(char *Caractere);

/* Fonction qui vérifie si une lettre est dans le mot et remplace les
 * underscores */
int Est_dans_le_Mot(char Mot, char *Reponse);

/* Fonction qui remplace la lettre dans le mot caché */
char RemplaceLettre(char *Reponse, int i, char Under[]);

/* Fonction qui choisi un mot aléatoire dans un fichier */
void Mot(char Main_Mot[]);

// Début de la fonction main()
int main() {
  // Initialisations des variables
  char Main_Nom_Joueur[50];
  char Main_Mot[50];
  int Incrementation_Occurence = 0;
  char *Client = (char *)malloc(sizeof(char));
  if (Client == NULL) {
    return -1; // EXIT_FAILURE
  }
  int IncrementationMot = 0;
  int IncrementationEssais = 1;
  int Taille_Mot = 0;
  int lettresEntreesCounter = 0;
  char Underscore[50];

  // Allouer de l'espace pour stocker les lettres entrées par le joueur
  char *lettresEntrees = (char *)malloc((8 + Taille_Mot) * sizeof(char));
  if (lettresEntrees == NULL) {
    return -1; // EXIT_FAILURE
  }

  // Affichage initial du pendu
  affichage(0);

  // Demander et stocker le nom du joueur
  Nom_Joueur(Main_Nom_Joueur);

  // Choisir un mot aléatoire à partir d'un fichier
  Mot(Main_Mot);
  // printf("%s\n", Main_Mot);                                    //a enlever si
  // besoin pour voir le mot choisi

  // Calculer la taille du mot
  Taille_Mot = strlen(Main_Mot);

  // Initialiser le mot caché avec des underscores
  Mot_Underscore(Taille_Mot, Underscore);
  printf("%s\n", Underscore);

  // Boucle principale du jeu
  while (strcmp(Underscore, Main_Mot) != 0 && IncrementationEssais <= 8) {

    affichage(IncrementationEssais); // Afficher l'état actuel du pendu

    // Afficher les lettres déjà entrées par le joueur
    printf("Lettres déjà entrées : ");
    for (size_t i = 0; i < 8 + Taille_Mot; i++) {
      printf("%c ", *(lettresEntrees + i * sizeof(char)));
    }
    printf("\nChoisissez une lettre (en minuscule)\n");

    // Lire la lettre proposée par le joueur
    scanf("%s", Client);

    // Vérifier si la lettre est une lettre valide
    if (Verification_est_une_lettre(Client) == 0) {
      IncrementationMot = 0;
      bool correct = false;

      // Vérifier si la lettre n'a pas déjà été entrée
      for (size_t i = 0; i < 8 + Taille_Mot; i++) {
        if (strcmp(Client, (lettresEntrees + i * sizeof(char))) == 0) {
          printf("Lettre déjà entrée\n");
          Incrementation_Occurence++;
          if (Incrementation_Occurence >= 8) {
              IncrementationEssais++;
          }
        }
      }

      // Vérifier si la lettre est dans le mot et mettre à jour le mot caché
      while (IncrementationMot < Taille_Mot) {
        if (Est_dans_le_Mot(Main_Mot[IncrementationMot], Client) == 0) {
          correct = true;
          RemplaceLettre(Client, IncrementationMot, Underscore);
        }
        IncrementationMot++;
      }

      // Si la lettre n'est pas dans le mot, incrémenter le nombre d'essais
      if (!correct) {
        printf("Cette lettre n'est pas dans le mot\n");
        IncrementationEssais++;
      }

      // Mettre à jour le tableau des lettres entrées
      lettresEntreesCounter++;
      *(lettresEntrees + lettresEntreesCounter * sizeof(char)) += *Client;

      // Si les conditions ne sont pas remplie = Forcément Invalide
    } else {
      printf("Ce n'est pas une lettre\n");
    }

    // Afficher le mot caché après chaque essai
    printf("%s\n", Underscore);
  }

  // Afficher le résultat du jeu
  if (IncrementationEssais < 8) {
    printf("Gagné ! Le mot est bien %s\n", Main_Mot);
  } else {
    printf("Perdu ! Le mot était : %s\n", Main_Mot);
  }

  // Libérer la mémoire allouée
  if (Client != NULL) {
    free(Client);
  }
  if (lettresEntrees != NULL) {
    free(lettresEntrees);
  }
  return 1;
}

// Début de la fonction Nom_Joueur()
void Nom_Joueur(char Fonct_nom[50]) {
  printf("Quel est votre nom ? \n");
  scanf("%s", Fonct_nom);
  return;
}

/* Fonction qui choisit un mot aléatoire à partir d'un fichier
void Mot(char Main_Mot[]) {
  printf("Quel Mot ?\n");
  scanf("%s", Main_Mot);
  return;
} */

// Fonction qui transforme le mot en Underscore
void Mot_Underscore(int Taille, char Under[]) {
  int Increm = 0;
  while (Increm < Taille) {
    Under[Increm] = '_';
    Increm++;
  }
}

// Fonction de vérification si le caractère est une lettre
int Verification_est_une_lettre(char *Caractere) {
  if (*Caractere >= 'a' && *Caractere <= 'z') {
    return 0;
  } else {
    return 1;
  }
}

// Fonction d'affichage du pendu
int affichage(int Etat) {
  if (Etat == 0) {
    printf("  ________  _______   ________   ________  ___  ___ \n");
    printf(
        " |\\   __  \\|\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\  \\|\\  \\ \n");
    printf(" \\ \\  \\|\\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  "
           "\\\\\\  \\ \n");
    printf("  \\ \\   ____\\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  "
           "\\\\\\  \\ \n");
    printf("   \\ \\  \\___|\\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\ "
           " \\\\\\  \\ \n");
    printf("    \\ \\__\\    \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ "
           "\\_______\\ \n");
    printf("     \\|__|     \\|_______|\\|__| \\|__|\\|_______|\\|_______| \n");
  }
  if (Etat == 1) {
    printf("  __\n |  |______\n |         |\n |_________|\n ");
  } // dessin du pendu en fonction du nb d'éssais
  else if (Etat == 2) {
    printf("   |\n   |\n   |\n   |\n   |\n  _|_\n |   |______\n |          |\n "
           "|__________|\n ");
  } else if (Etat == 3) {
    printf("    ____\n   |\n   |\n   |\n   |\n   |\n  _|_\n |   |______\n |    "
           "      |\n |__________|\n ");
  } else if (Etat == 4) {
    printf("    ____\n   |    |\n   |\n   |\n   |\n   |\n  _|_\n |   |______\n "
           "|          |\n |__________|\n ");
  } else if (Etat == 5) {
    printf("    ____\n   |    |\n   |    O\n   |\n   |\n   |\n  _|_\n |   "
           "|______\n |          |\n |__________|\n ");
  } else if (Etat == 6) {
    printf("    ____\n   |    |\n   |    O\n   |   / \\ \n   |\n   |\n  _|_\n "
           "|   |______\n |          |\n |__________|\n ");
  } else if (Etat == 7) {
    printf("    ____\n   |    |\n   |    O\n   |   /|\\ \n   |    |\n   |\n  "
           "_|_\n |   |______\n |          |\n |__________|\n ");
  } else if (Etat == 8) {
    printf("    ____\n   |    |\n   |    O\n   |   /|\\ \n   |    |\n   |   / "
           "\\ \n  _|_\n |   |______\n |          |\n |__________|\n ");
  }

  if (Etat == 8) {
    printf("Perdu !\n");
  }

  return 0;
}

// Fonction qui vérifie si une lettre est dans le mot et remplace les
// underscores
int Est_dans_le_Mot(char Mot, char *Reponse) {
  if (Mot == *Reponse) {
    return 0;
  }

  return 1;
}

// Fonction qui remplace la lettre dans le mot caché
char RemplaceLettre(char *Reponse, int i, char Under[]) {
  Under[i] = *Reponse;
  return *Under;
}

void Mot(char Main_Mot[50]) {
  char mot[100];
  int nombre_de_mots = 0;
  int indice_aleatoire = 0;
  int mot_courant = 0;

  FILE *fichier = fopen("words.txt", "r");

  if (fichier == NULL) {
    perror("Erreur lors de l'ouverture du fichier");
    exit(EXIT_FAILURE);
  }

  srand((unsigned int)time(NULL));

  while (fscanf(fichier, "%s", mot) == 1) { // nb de mots
    nombre_de_mots = nombre_de_mots + 1;
  }

  indice_aleatoire = rand() % nombre_de_mots; // aléatoire
  fseek(fichier, 0, SEEK_SET); // réintinialiser à 0 pour une deuxième partie

  while (fscanf(fichier, "%s", mot) == 1) {
    if (mot_courant == indice_aleatoire) {
      strcpy(Main_Mot, mot);
    }
    mot_courant = mot_courant + 1;
  }

  fclose(fichier);
}