#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct CryptoCurrency {
  char nume[50];
  char simbol[10];
  double pret;
  double volumTranzactionat;
  double capitalizarePiata;
  double schimbare24h;
};

void citire(struct CryptoCurrency *tablou, int dimensiune);
void afisare(struct CryptoCurrency *tablou, int dimensiune);
int cautare(struct CryptoCurrency *tablou, int dimensiune,char valoareCautata[]);
void eliberare(struct CryptoCurrency *tablou);
void sortare(struct CryptoCurrency *tablou, int dimensiune);
void inserareLaCapat(struct CryptoCurrency **tablou, int *dimensiune);
void inserareLaInceput(struct CryptoCurrency **tablou, int *dimensiune);
void inserareLaPozitie(struct CryptoCurrency **tablou, int *dimensiune,
                       int pozitie);
void stergere(struct CryptoCurrency **tablou, int *dimensiune, int pozitie);
int main() {
  int dimensiune = 0;
  struct CryptoCurrency *tablou = NULL;
  int optiune;
  char valoareCautata[50];
  int pozitie;
  do {
    printf("\nMeniu:\n");
    printf("1. Citirea de la tastatura a elementelor tabloului\n");
    printf("2. Afisarea elementelor tabloului\n");
    printf("3. Cautarea unui element dupa valoarea unui camp din structura\n");
    printf("4. Eliberarea memoriei tabloului\n");
    printf("5. Sortarea elementelor dupa un camp al structurii\n");
    printf("6. Inserarea unui element nou la capatul tabloului\n");
    printf("7. Inserarea unui element nou la inceputul tabloului\n");
    printf("8. Inserarea unui element la o anumita pozitie\n");
    printf("9. Stergerea unui element de pe o anumita pozitie\n");
    printf("0. Iesire\n");
    printf("Alege o optiune: ");
    scanf("%d", &optiune);
    switch (optiune) {
    case 1:
      printf("Introduceti dimensiunea tabloului de criptomonede: ");
      scanf("%d", &dimensiune);
      tablou = (struct CryptoCurrency *)malloc(dimensiune *
                                               sizeof(struct CryptoCurrency));
      citire(tablou, dimensiune);
      break;
    case 2:
      afisare(tablou, dimensiune);
      break;
    case 3:
      printf("Introduceti valoarea cautata: ");
      scanf("%s", valoareCautata);
      pozitie = cautare(tablou, dimensiune, valoareCautata);
      if (pozitie != -1)
        printf("Elementul a fost gasit pe pozitia %d\n", pozitie + 1);
      else
        printf("Elementul nu a fost gasit\n");
      break;
    case 4:
      eliberare(tablou);
      dimensiune = 0;
      break;
    case 5:
      sortare(tablou, dimensiune);
      break;
    case 6:
      inserareLaCapat(&tablou, &dimensiune);
      break;
    case 7:
      inserareLaInceput(&tablou, &dimensiune);
      break;
    case 8:
      printf("Introduceti pozitia unde doriti sa inserati elementul: ");
      scanf("%d", &pozitie);
      inserareLaPozitie(&tablou, &dimensiune, pozitie);
      break;
    case 9:
      printf("Introduceti pozitia de unde doriti sa stergeti elementul: ");
      scanf("%d", &pozitie);
      stergere(&tablou, &dimensiune, pozitie);
      break;
    case 0:
      printf("Programul se inchide...\n");
      break;
    default:
      printf("Optiune invalida! Va rugam sa alegeti o optiune valida.\n");
      break;
    }
  } while (optiune != 0);
  return 0;
}
void citire(struct CryptoCurrency *tablou, int dimensiune) {
  printf("Introduceti informatiile despre criptomonede:\n");
  for (int i = 0; i < dimensiune; i++) {
    printf("Criptomoneda %d:\n", i + 1);
    printf("Nume: ");
    scanf("%s", tablou[i].nume);
    printf("Simbol: ");
    scanf("%s", tablou[i].simbol);
    printf("Pret: ");
    scanf("%lf", &tablou[i].pret);
    printf("Volum tranzactionat: ");
    scanf("%lf", &tablou[i].volumTranzactionat);
    printf("Capitalizare piata: ");
    scanf("%lf", &tablou[i].capitalizarePiata);
    printf("Schimbare 24h: ");
    scanf("%lf", &tablou[i].schimbare24h);
  }
}
void afisare(struct CryptoCurrency *tablou, int dimensiune) {
  printf("Informatiile despre criptomonede:\n");
  for (int i = 0; i < dimensiune; i++) {
    printf("Criptomoneda %d - Nume: %s, Simbol: %s, Pret: %.2lf, Volum "
           "tranzactionat: %.2lf, Capitalizare piata: %.2lf, Schimbare 24h: "
           "%.2lf\n",
           i + 1, tablou[i].nume, tablou[i].simbol, tablou[i].pret,
           tablou[i].volumTranzactionat, tablou[i].capitalizarePiata,
           tablou[i].schimbare24h);
  }
}
int cautare(struct CryptoCurrency *tablou, int dimensiune,
            char valoareCautata[]) {
  for (int i = 0; i < dimensiune; i++) {
    if (strcmp(tablou[i].nume, valoareCautata) == 0 ||
        strcmp(tablou[i].simbol, valoareCautata) == 0) {
      return i; // returneaza pozitia elementului gasit
    }
  }
  return -1; //-1 daca nu s-a gasit elementul
}
void eliberare(struct CryptoCurrency *tablou) {
  free(tablou);
  printf("Memoria a fost eliberata\n");
}
void sortare(struct CryptoCurrency *tablou, int dimensiune) {
  // sortarea crescatoare dupa pret
  struct CryptoCurrency temp;
  for (int i = 0; i < dimensiune - 1; i++) {
    for (int j = 0; j < dimensiune - i - 1; j++) {
      if (tablou[j].pret > tablou[j + 1].pret) {
        temp = tablou[j];
        tablou[j] = tablou[j + 1];
        tablou[j + 1] = temp;
      }
    }
  }
  printf("Tabloul a fost sortat dupa pret\n");
}
void inserareLaCapat(struct CryptoCurrency **tablou, int *dimensiune) {
  (*dimensiune)++;
  *tablou = (struct CryptoCurrency *)realloc(
      *tablou, (*dimensiune) * sizeof(struct CryptoCurrency));
  citire(*tablou + (*dimensiune) - 1, 1);
}
void inserareLaInceput(struct CryptoCurrency **tablou, int *dimensiune) {
  struct CryptoCurrency temp;
  (*dimensiune)++;
  *tablou = (struct CryptoCurrency *)realloc(
      *tablou, (*dimensiune) * sizeof(struct CryptoCurrency));
  for (int i = (*dimensiune) - 1; i > 0; i--) {
    (*tablou)[i] = (*tablou)[i - 1];
  }
  citire(*tablou, 1);
}
void inserareLaPozitie(struct CryptoCurrency **tablou, int *dimensiune,
                       int pozitie) {
  if (pozitie < 0 || pozitie > *dimensiune) {
    printf("Pozitie invalida!\n");
    return;
  }
  (*dimensiune)++;
  *tablou = (struct CryptoCurrency *)realloc(
      *tablou, (*dimensiune) * sizeof(struct CryptoCurrency));
  for (int i = (*dimensiune) - 1; i > pozitie; i--) {
    (*tablou)[i] = (*tablou)[i - 1];
  }
  citire(*tablou + pozitie, 1);
}
void stergere(struct CryptoCurrency **tablou, int *dimensiune, int pozitie) {
  if (pozitie < 0 || pozitie >= *dimensiune) {
    printf("Pozitie invalida!\n");
    return;
  }
  for (int i = pozitie; i < (*dimensiune) - 1; i++) {
    (*tablou)[i] = (*tablou)[i + 1];
  }
  (*dimensiune)--;
  *tablou = (struct CryptoCurrency *)realloc(
      *tablou, (*dimensiune) * sizeof(struct CryptoCurrency));
  printf("Elementul de pe pozitia %d a fost sters.\n", pozitie + 1);
}
