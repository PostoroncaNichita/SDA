#include <stdio.h>
#include <string.h>
struct CryptoCurrency {
  char nume[50];
  char simbol[10];
  double pret;
  double volumTranzactionat;
  double capitalizarePiata;
  double schimbare24h;
};
void citire(struct CryptoCurrency tablou[], int dimensiune) {
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
void afisare(struct CryptoCurrency tablou[], int dimensiune) {
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
int cautare(struct CryptoCurrency tablou[], int dimensiune,
            char valoareCautata[]) {
  for (int i = 0; i < dimensiune; i++) {
    if (strcmp(tablou[i].nume, valoareCautata) == 0 ||
        strcmp(tablou[i].simbol, valoareCautata) == 0) {
      return i; // returneaza pozitia elementului gasit
    }
  }
  return -1;
}
int main() {
  int dimensiune;
  printf("Introduceti dimensiunea tabloului de criptomonede: ");
  scanf("%d", &dimensiune);
  // Alocare statica a tabloului de criptomonede
  struct CryptoCurrency tablou[dimensiune];
  // Citirea informatiilor despre criptomonede
  citire(tablou, dimensiune);
  afisare(tablou, dimensiune);
  // Cautarea unui element dupa nume sau simbol
  char valoareCautata[50];
  printf("Introduceti numele sau simbolul pentru cautare: ");
  scanf("%s", valoareCautata);
  int pozitie = cautare(tablou, dimensiune, valoareCautata);
  if (pozitie != -1) {
    printf("Criptomoneda cu numele/simbolul \"%s\" se afla la pozitia %d.\n",
           valoareCautata, pozitie + 1);
  } else {
    printf("Criptomoneda cu numele/simbolul \"%s\" nu a fost gasita.\n",
           valoareCautata);
  }
  return 0;
}

