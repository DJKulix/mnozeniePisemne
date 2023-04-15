#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    char a[20];
    char b[20];

    printf("Mnozenie.c Zalozenie: a, b > 0\n");
    printf("Podaj a:");
    int breakPoint; //do walidacji
    do {
        breakPoint = 1;
        fgets(a, sizeof(a), stdin);
        for (int i = 0; a[i] != '\n'; i++) {
            if (!isdigit(a[i])) {
                printf("Podaj poprawna liczbe.\n");
                breakPoint = 0;
                break;
            }
        }
    } while (breakPoint == 0);

    //Usuwanie znaku /n
    a[strcspn(a, "\n")] = 0;

    printf("Podaj b:");

    breakPoint = 1;
    do {
        fflush(stdin);
        breakPoint = 1;
        fgets(b, sizeof(b), stdin);
        for (int i = 0; b[i] != '\n'; i++) {
            if (!isdigit(b[i])) {
                printf("Podaj poprawna liczbe");
                breakPoint = 0;
                break;
            }
        }
    } while (breakPoint == 0);


    //Usuwanie znaku /n
    b[strcspn(b, "\n")] = 0;

    printf("a = %s, strlen(a) = %llu, sizeof(a) = %llu\n", a, strlen(a), sizeof(a));
    printf("b = %s, strlen(b) = %llu, sizeof(b) = %llu\n\n", b, strlen(b), sizeof(b));

    int c[strlen(b)][strlen(a) + strlen(b) + 1][3];

    //Wypelnienie c zerami
    for (int i = 0; i < sizeof(c) / sizeof(c[0]); i++) {
        for (int j = 0; j < sizeof(c[0]) / sizeof(c[0][0]); j++) {
            for (int k = 0; k < sizeof(c[0][0]) / sizeof(int); k++) {
                c[i][j][k] = 0;
            }
        }
    }
 
    for (int i = strlen(b) - 1; i >= 0; i--) {
        for (int j = strlen(a) - 1; j >= 0; j--) {
            //mnożenie pisemne wykonujemy przechodząc sekwencyjnie po parach cyfr.
            int digitA = (int) a[j] - 48; //ostatnia cyfra skladnika a
            int digitB = (int) b[i] - 48; //ostatnia cyfra skladnika b
            int result = digitB * digitA; //wynik mnożenia a*b


            //tablicę wynikową c przechodzimy zaczynając od pierwszego wiersza. tu (strlen(b) - i - 1) = (strlen(b) - (streln(b) - 1) - 1) = 0.
            // użycie strlen(b) pozwala nam używać licznika pętli i.
            //pierwsza pozycją w tablicy która zostanie wypełniona znajduje się w ostatniej kolumnie. tu (i + j + 2) = (strlen(b) - 1 + strlen(a) -1 + 2) = strlen(b) + strlen(a)
            // co odpowiada ostatniemu indeksowi kolumny tablicy wynikowej c
            //c[][][1] przchowuje carriage
            c[strlen(b) - i - 1][i + j + 1][0] = (result + c[strlen(b) - i - 1][i + j + 2][1]) / 10;
            c[strlen(b) - i - 1][i + j + 1][1] = (result + c[strlen(b) - i - 1][i + j + 2][1]) / 10;
            c[strlen(b) - i - 1][i + j + 2][0] = (result + c[strlen(b) - i - 1][i + j + 2][1]) % 10;
        }
    }

//    printf("Dodawania:\n");
//    for (int k = 0; k < 2; k++) { //Arkusze
//        for (int i = 0; i < strlen(b); i++) { //
//            for (int j = 0; j < strlen(a) + strlen(b) + 1; j++) {
//                printf("[%d]", c[i][j][k]);
//            }
//            printf("\n");
//        }
//        printf("Przeniesienia: \n");
//    }

    for (int i = strlen(a) - 1; i >= 0; i--) {
        c[0][sizeof(c[0]) / sizeof(c[0][0]) - strlen(a) + i][2] = (int) a[i] - 48;
    }

    if (strlen(b) > 1)
        for (int i = strlen(b) - 1; i >= 0; i--) {
            c[1][sizeof(c[0]) / sizeof(c[0][0]) - strlen(b) + i][2] = (int) b[i] - 48;
        }

    printf("  ");
    //Wypisywanie przeniesien
    for (int i = strlen(b) - 1; i >= 0; i--) {
        printf("");
        for (int j = 0; j < strlen(a) + strlen(b) + 1; j++) {
            if (c[i][j][1] > 0)
                printf("%d", c[i][j][1]);
            else
                printf(" ");
        }
        printf("\n ");
    }
    //Koniec

    //Wypisywanie a
    int writeLeftZeros = 1;
    for (int i = 0; i < sizeof(c[0]) / sizeof(c[0][0]); i++) {
        if (c[0][i][2] > 0)
            writeLeftZeros = 0;
        if (writeLeftZeros == 0)
            printf("%d", c[0][i][2]);
        else
            printf(" ");
    }
    printf("\n");

    //Wypisywanie b
    writeLeftZeros = 1;
    printf("*");
    for (int i = 0; i < sizeof(c[0]) / sizeof(c[0][0]); i++) {
        if (strlen(b) == 1) {
            if (i == sizeof(c[0]) / sizeof(c[0][0]) - 1)
                printf("%c", b[0]);
            else
                printf(" ");

        } else {
            if (c[1][i][2] > 0)
                writeLeftZeros = 0;
            if (writeLeftZeros == 0) {
                printf("%d", c[1][i][2]);
            } else
                printf(" ");
        }

    }

    printf("\n ");
    //Koniec wypisywania a, b


    for (int i = 0; i < sizeof(c[0]) / sizeof(c[0][0]); i++)
        printf("-");


    //Wypisanie dodawan
    printf("\n ");
    for (int i = 0; i < sizeof(c) / sizeof(c[0]); i++) {
        writeLeftZeros = 1;
        for (int j = 0; j < sizeof(c[0]) / sizeof(c[0][0]); j++) {
            if (c[i][j][0] > 0)
                writeLeftZeros = 0;
            if (writeLeftZeros == 0) {
                printf("%d", c[i][j][0]);
            } else
                printf(" ");
        }

        if (i == 0 && strlen(b) > 1)
            printf("\n+");
        else
            printf("\n");
    }

    if (strlen(b) > 1) {
        for (int i = 0; i < sizeof(c[0]) / sizeof(c[0][0]) + 1; i++)
            printf("-");

        printf("\n  ");
        int result = 0;
        int x = 1;
        for (int i = sizeof(c[0]) / sizeof(c[0][0]) - 1; i >= 0; i--) {
            result += (c[0][i][0] * x) + (c[1][i][0] * x);
            x *= 10;
        }
        printf("%d\n", result);
    }
}
