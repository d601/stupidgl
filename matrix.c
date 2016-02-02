#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int matrix_new(uint8_t m, uint8_t n, float **matrix)
{
    (*matrix) = malloc(sizeof(float) * m * n);
    return 0;
}

int matrix_set_identity(uint8_t m, uint8_t n, float **matrix)
{
    for (uint8_t i = 0; i < m; i++) {
        for (uint8_t j = 0; j < n; j++) {
            (*matrix)[i * m + j] = ((i == j) ? 1.0 : 0.0);
        }
    }
}

void matrix_print(uint8_t m, uint8_t n, float *matrix)
{
    for (uint8_t i = 0; i < m; i++) {
        printf("[");
        for (uint8_t j = 0; j < n; j++) {
            printf("%f", matrix[i * m + j]);
            if (j < (n - 1))
                printf(", ");
        }
        printf("]\n");
    }
}

int matrix_set_perspective(
    float l,
    float b,
    float n,
    float r,
    float t,
    float f,
    float **matrix)
{
    if (matrix == NULL)
        return -1;

    (*matrix)[0 * 4 + 0] = (2.0 * n) / (r - l);
    (*matrix)[0 * 4 + 1] = 0.0;
    (*matrix)[0 * 4 + 2] = (r + l) / (r - l);
    (*matrix)[0 * 4 + 3] = 0.0;
    (*matrix)[1 * 4 + 0] = 0.0;
    (*matrix)[1 * 4 + 1] = (2 * n) / (t - b);
    (*matrix)[1 * 4 + 2] = (t + b) / (t - b);;
    (*matrix)[1 * 4 + 0] = 0.0;
    (*matrix)[2 * 4 + 0] = 0.0;
    (*matrix)[2 * 4 + 1] = 0.0;
    (*matrix)[2 * 4 + 2] = -((f + n) / (f - n));
    (*matrix)[2 * 4 + 3] = -((2.0 * f * n) / (f - n));
    (*matrix)[3 * 4 + 0] = 0.0;
    (*matrix)[3 * 4 + 1] = 0.0;
    (*matrix)[3 * 4 + 2] = 1.0;
    (*matrix)[3 * 4 + 3] = 0.0;
}

//int matrix_multiply(

/*
int matrix_multiply(
    uint8_t m1m,
    uint8_t m1n,
    float **m1,
    uint8_t m2m,
    uint8_t m2n,
    float **m2,
    uint8_t *tm, // result
    uint8_t *tn,
    float ***t)
{
    if (m1n != m2n)
        return -1;

    if ((*t != NULL) && ((*tm != m1m) || (*tn != m2n)))
        return -1;

    if (*t == NULL)
        matrix_new(m1m, m2n, t);

    for (uint8_t i = 0; i < m1m; i++) {
        for (uint8_t j = 0; j < m2n; j++) {
            (*t)[i][j] = 0.0;
            for (uint8_t k = 0; j < m1n; k++) {
                (*t)[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return 0;
}
*/
