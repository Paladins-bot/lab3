#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    int N, M;
    if (fscanf(file, "%d %d", &N, &M) != 2) {
        printf("Ошибка чтения размеров матрицы\n");
        fclose(file);
        return 1;
    }

    int **matrix = (int **)malloc(N * sizeof(int *));
    if (!matrix) {
        printf("Ошибка выделения памяти для указателей матрицы\n");
        fclose(file);
        return 1;
    }

    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Ошибка чтения элемента матрицы\n");
                for (int k = 0; k < N; k++) free(matrix[k]);
                free(matrix);
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < M; j++) {
            if (matrix[i][j] > 0) {
                sum += matrix[i][j];
            }
        }
    }

    int max_negative = 0;
    int found = 0;
    if (N >= 4) {
        for (int j = 0; j < M; j++) {
            if (matrix[3][j] < 0) {
                if (!found || matrix[3][j] > max_negative) {
                    max_negative = matrix[3][j];
                    found = 1;
                }
            }
        }
    }

    if (found) {
        for (int j = 0; j < M; j++) {
            if (matrix[3][j] == max_negative) {
                matrix[3][j] = sum;
                break;
            }
        }
    }

    printf("Сумма положительных элементов выше главной диагонали: %d\n", sum);
    
    if (found) {
        printf("Максимальный отрицательный элемент в 4-ой строке: %d\n", max_negative);
        printf("Замена выполнена.\n");
    } else {
        printf("В 4-ой строке нет отрицательных элементов.\n");
    }

    printf("Итоговая матрица:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
