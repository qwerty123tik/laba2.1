#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void fillFileWithIntegers(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf(" error opening file\n");
        return;
    }

    int number;
    printf("enter int numbers to write to file (enter -1 to terminate):\n");
    while (1) {
        printf("write number: ");
        scanf_s("%d", &number);
        if (number == -1) break;

        fwrite(&number, sizeof(int), 1, file);

    }

    fclose(file);
}

int SumChetn(const char* filename) {
    FILE* file = fopen(filename, "rb+");
    if (file == NULL) {
        printf(" error opening file\n");
        return 1;
    }
    int number;
    int Sum = 0;
    while (fread(&number, sizeof(int), 1, file)) {
        if (number % 2 == 0) {
            Sum += number;
        }
    }
    fclose(file);
    return Sum;
}

void removeChetn(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int* numbers = malloc(file_size);
    if (numbers == NULL) {
        perror("Не удалось выделить память");
        fclose(file);
        return;
    }

    size_t count = fread(numbers, sizeof(int), file_size / sizeof(int), file);
    fclose(file);

    int* odd_numbers = malloc(file_size);
    if (odd_numbers == NULL) {
        perror("Не удалось выделить память");
        free(numbers);
        return;
    }

    size_t odd_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            odd_numbers[odd_count++] = numbers[i];
        }
    }

    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Не удалось открыть файл для записи");
        free(numbers);
        free(odd_numbers);
        return;
    }

    fwrite(odd_numbers, sizeof(int), odd_count, file);
    fclose(file);

    free(numbers);
    free(odd_numbers);
}


//void sortNumbersGreaterThan(const char* filename, int threshold) {
//    FILE* file = fopen(filename, "rb+");
//    if (file == NULL) {
//        perror("Не удалось открыть файл");
//        return;
//    }
//
//   
//    fpos_t n1, n2, n3;
//    int i1, i2, i3, m[] = { 1,3,5,7,2,4 };
//
//    fwrite(m, sizeof(m), 1, filename);
//    rewind(filename);
//
//    n3 = sizeof(int);
//
//    fseek(filename, -n3, 2);
//    n3 = ftell(filename);
//    rewind(filename);
//
//    n1 = 0;
//
//    while (1)
//    {
//        if (n1 > n3 - sizeof(int))
//            break;
//
//        n2 = n3;
//
//        while (n1 < n2)
//        {
//            fsetpos(filename, &n2);
//            fread(&i2, sizeof(int), 1, f);
//
//            n2 -= sizeof(int);
//
//            fsetpos(f, &n2);
//            fread(&i1, sizeof(int), 1, f);
//
//            if (i1 > i2)
//            {
//                fsetpos(f, &n2);
//                fwrite(&i2, sizeof(int), 1, f);
//                fwrite(&i1, sizeof(int), 1, f);
//            }
//        }
//
//        n1 += sizeof(int);
//    }
//
//    rewind(filename);
//
//    fread(m, sizeof(m), 1, f);
//   
//    fclose(file);
//}

void read_from_file(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error");
        return;
    }
    int num;
    while (fread(&num, sizeof(int), 1, file))
    {
        printf("%d ", num);
    }
    printf("\n");
    fclose(file);
}


int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    fillFileWithIntegers(filename);

    int Sum = SumChetn(filename);
    printf("Sum chetn number = %d\n", Sum);

    removeChetn(filename);
    printf("numbers ....\n");
    read_from_file(filename);

    int threshold;
    printf("choose a number after wich elements will be sorted:");
    scanf_s("%d", &threshold);

    /*sortNumbersGreaterThan(filename, threshold);
    printf("numbers after sort:");
    read_from_file(filename);*/


    return 0;
}

