#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Crypto {
    char nume[50];
    char simbol[50];
    int an_lansare;
    float pret;
    struct Crypto *urmator;
};
void citireLista(struct Crypto **cap);
void afisareLista(struct Crypto *cap);
int cautareElement(struct Crypto *cap, char cautat[50]);
void eliberareMemorie(struct Crypto **cap);
void sortareLista(struct Crypto **cap);
void inserareLaCapat(struct Crypto **cap);
void inserareLaInceput(struct Crypto **cap);
void inversareOrdine(struct Crypto **cap);
void inserareLaPozitie(struct Crypto **cap);
void stergereDeLaPozitie(struct Crypto **cap);
void curatareLista(struct Crypto **cap);
int main() {
    struct Crypto *listaCrypto = NULL;
    int optiune;

    do {
        printf("\n1. Citire lista\n");
        printf("2. Afisare lista\n");
        printf("3. Cautare element\n");
        printf("4. Eliberare memorie\n");
        printf("5. Sortare lista\n");
        printf("6. Inserare la capat\n");
        printf("7. Inserare la inceput\n");
        printf("8. Inversare ordine\n");
        printf("9. Inserare la o pozitie\n");
        printf("10. Stergere de la o pozitie\n");
        printf("11. Curatare lista\n");
        printf("0. Iesire\n");
        printf("Alege o optiune: ");
        scanf("%d", &optiune);

        switch(optiune) {
            case 1:
                citireLista(&listaCrypto);
                break;
            case 2:
                afisareLista(listaCrypto);
                break;
            case 3: {
                char cautat[50];
                printf("Introduceti valoarea pentru cautare: ");
                scanf("%s", cautat);
                int pozitie = cautareElement(listaCrypto, cautat);
                if (pozitie != -1)
                    printf("Elementul se afla pe pozitia %d.\n", pozitie);
                else
                    printf("Elementul nu a fost gasit.\n");
                break;}
            case 4:
                eliberareMemorie(&listaCrypto);
                printf("Memoria listei a fost eliberata.\n");
                break;
            case 5:
                sortareLista(&listaCrypto);
                printf("Lista a fost sortata.\n");
                break;
            case 6:
                inserareLaCapat(&listaCrypto);
                break;
            case 7:
                inserareLaInceput(&listaCrypto);
                break;
            case 8:
                inversareOrdine(&listaCrypto);
                break;
            case 9:
                inserareLaPozitie(&listaCrypto);
                break;
            case 10:
                stergereDeLaPozitie(&listaCrypto);
                break;
            case 11:
                curatareLista(&listaCrypto);
                printf("Lista a fost curatata.\n");
                break;
            case 0:
                eliberareMemorie(&listaCrypto);
                printf("Programul s-a incheiat.\n");
                break;
            default:
                printf("Optiune invalida. Va rugam sa introduceti o optiune valida.\n");
        }
    } while (optiune != 0);
    return 0;
}

void citireLista(struct Crypto **cap) {
    for (int i = 0; i < 5; ++i) {
        struct Crypto *cryptoNou = (struct Crypto*)malloc(sizeof(struct Crypto));
        printf("\nIntroduceti informatii pentru criptomoneda %d:\n", i + 1);
        printf("Nume: ");
        scanf("%s", cryptoNou->nume);
        printf("Simbol: ");
        scanf("%s", cryptoNou->simbol);
        printf("An lansare: ");
        scanf("%d", &cryptoNou->an_lansare);
        printf("Pret: ");
        scanf("%f", &cryptoNou->pret);
        cryptoNou->urmator = *cap;
        *cap = cryptoNou;
    }
}

void afisareLista(struct Crypto *cap) {
    printf("\nLista criptomonedelor:\n");
    while (cap != NULL) {
        printf("Nume: %s, Simbol: %s, An lansare: %d, Pret: %.2f\n",
               cap->nume, cap->simbol, cap->an_lansare, cap->pret);
        cap = cap->urmator;
    }
}
int cautareElement(struct Crypto *cap, char cautat[50]) {
    int pozitie = 1;
    while (cap != NULL) {
        if (strcmp(cap->nume, cautat) == 0) {
            return pozitie;
        }
        cap = cap->urmator;
        pozitie++;
    }
    return -1; // Elementul nu a fost gasit
}

void eliberareMemorie(struct Crypto **cap) {
    while (*cap != NULL) {
        struct Crypto *temp = *cap;
        *cap = (*cap)->urmator;
        free(temp);
    }
}

void sortareLista(struct Crypto **cap) {
    struct Crypto *current, *index;
    char tempNume[50];
    char tempSimbol[50];
    int tempAnLansare;
    float tempPret;

    if (*cap == NULL) {
        return;
    } else {
        for (current = *cap; current->urmator != NULL; current = current->urmator) {
            for (index = current->urmator; index != NULL; index = index->urmator) {
                if (strcmp(current->nume, index->nume) > 0) {
                    strcpy(tempNume, current->nume);
                    strcpy(current->nume, index->nume);
                    strcpy(index->nume, tempNume);

                    strcpy(tempSimbol, current->simbol);
                    strcpy(current->simbol, index->simbol);
                    strcpy(index->simbol, tempSimbol);

                    tempAnLansare = current->an_lansare;
                    current->an_lansare = index->an_lansare;
                    index->an_lansare = tempAnLansare;

                    tempPret = current->pret;
                    current->pret = index->pret;
                    index->pret = tempPret;
                }
            }
        }
    }
}

void inserareLaCapat(struct Crypto **cap) {
    struct Crypto *cryptoNou = (struct Crypto*)malloc(sizeof(struct Crypto));
    printf("\nIntroduceti informatii pentru criptomoneda noua la capat:\n");
    printf("Nume: ");
    scanf("%s", cryptoNou->nume);
    printf("Simbol: ");
    scanf("%s", cryptoNou->simbol);
    printf("An lansare: ");
    scanf("%d", &cryptoNou->an_lansare);
    printf("Pret: ");
    scanf("%f", &cryptoNou->pret);

    cryptoNou->urmator = NULL;

    if (*cap == NULL) {
        *cap = cryptoNou;
    } else {
        struct Crypto *temp = *cap;
        while (temp->urmator != NULL) {
            temp = temp->urmator;
        }
        temp->urmator = cryptoNou;
    }
}

void inserareLaInceput(struct Crypto **cap) {
    struct Crypto *cryptoNou = (struct Crypto*)malloc(sizeof(struct Crypto));
    printf("\nIntroduceti informatii pentru criptomoneda noua la inceput:\n");
    printf("Nume: ");
    scanf("%s", cryptoNou->nume);
    printf("Simbol: ");
    scanf("%s", cryptoNou->simbol);
    printf("An lansare: ");
    scanf("%d", &cryptoNou->an_lansare);
    printf("Pret: ");
    scanf("%f", &cryptoNou->pret);

    cryptoNou->urmator = *cap;
    *cap = cryptoNou;
}

void inversareOrdine(struct Crypto **cap) {
    struct Crypto *prev = NULL, *current = *cap, *next = NULL;
    while (current != NULL) {
        next = current->urmator;
        current->urmator = prev;
        prev = current;
        current = next;
    }
    *cap = prev;
}

void inserareLaPozitie(struct Crypto **cap) {
    int pozitie;
    printf("Introduceti pozitia pentru inserare: ");
    scanf("%d", &pozitie);

    if (pozitie < 1) {
        printf("Pozitie invalida. Inserarea nu este posibila.\n");
        return;
    }
    if (pozitie == 1) {
        inserareLaInceput(cap);
    } else {
        struct Crypto *cryptoNou = (struct Crypto*)malloc(sizeof(struct Crypto));
        printf("\nIntroduceti informatii pentru criptomoneda noua la pozitia %d:\n", pozitie);
        printf("Nume: ");
        scanf("%s", cryptoNou->nume);
        printf("Simbol: ");
        scanf("%s", cryptoNou->simbol);
        printf("An lansare: ");
        scanf("%d", &cryptoNou->an_lansare);
        printf("Pret: ");
        scanf("%f", &cryptoNou->pret);
struct Crypto *temp = *cap;
        for (int i = 1; i < pozitie - 1 && temp != NULL; ++i) {
            temp = temp->urmator;
        }
        if (temp == NULL) {
            printf("Pozitie invalida. Inserarea nu este posibila.\n");
            free(cryptoNou);
            return;
        }
        cryptoNou->urmator = temp->urmator;
        temp->urmator = cryptoNou;
    }
}

void stergereDeLaPozitie(struct Crypto **cap) {
    int pozitie;
    printf("Introduceti pozitia pentru stergere: ");
    scanf("%d", &pozitie);
    if (pozitie < 1) {
        printf("Pozitie invalida. Stergerea nu este posibila.\n");
        return;
    }
    if (*cap == NULL) {
        printf("Lista este goala. Stergerea nu este posibila.\n");
        return;
    }
    struct Crypto *temp = *cap;
    if (pozitie == 1) {
        *cap = temp->urmator;
        free(temp);
    } else {
        for (int i = 1; i < pozitie - 1 && temp != NULL; ++i) {
            temp = temp->urmator;
        }
        if (temp == NULL || temp->urmator == NULL) {
            printf("Pozitie invalida. Stergerea nu este posibila.\n");
            return;
        }
        struct Crypto *nodDeSters = temp->urmator;
        temp->urmator = nodDeSters->urmator;
        free(nodDeSters);
    }
}

void curatareLista(struct Crypto **cap) {
    eliberareMemorie(cap);
    *cap = NULL;
}
