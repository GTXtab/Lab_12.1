#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNIGNS

// Функція для створення файлу
void CreateBIN(const char* fname) {
    FILE* fout = fopen(fname, "wb");
    if (fout == NULL) {
        printf("Error: Cannot create file %s\n", fname);
        return;
    }

    char ch;
    int num;

    do {
        printf("Enter a number: ");
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, fout); // Запис числа у файл

        printf("Continue? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    fclose(fout);
}

// Функція для виведення файлу
void PrintBIN(const char* fname) {
    FILE* fin = fopen(fname, "rb");
    if (fin == NULL) {
        printf("Error: Cannot open file %s\n", fname);
        return;
    }

    int num;
    printf("File content (%s):\n", fname);
    while (fread(&num, sizeof(int), 1, fin)) {
        printf("%d ", num);
    }
    printf("\n");

    fclose(fin);
}

// Функція для обробки файлу
void ProcessBIN(const char* fname, const char* gname) {
    FILE* fin = fopen(fname, "rb");
    FILE* fout = fopen(gname, "wb");

    if (fin == NULL) {
        printf("Error: Cannot open input file %s\n", fname);
        return;
    }
    if (fout == NULL) {
        printf("Error: Cannot create output file %s\n", gname);
        fclose(fin);
        return;
    }

    int num, sum = 0;
    while (fread(&num, sizeof(int), 1, fin)) {
        sum += num; // Обчислення накопичувальної суми
        fwrite(&sum, sizeof(int), 1, fout); // Запис суми у файл
    }

    fclose(fin);
    fclose(fout);
}

int main() {
    char fname[100], gname[100];

    // Створення та виведення першого файлу
    printf("Enter file name 1: ");
    scanf("%s", fname);
    CreateBIN(fname);
    PrintBIN(fname);

    // Обробка першого файлу та запис результату у другий файл
    printf("Enter file name 2: ");
    scanf("%s", gname);
    ProcessBIN(fname, gname);

    // Виведення другого файлу
    PrintBIN(gname);

    return 0;
}
