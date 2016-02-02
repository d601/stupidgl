#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "matrix.h"

int matrix_new(uint8_t m, uint8_t n, float ***matrix)
{
    *matrix = malloc(m * sizeof(float *));
    if (*matrix == NULL)
        return -1;

    for (uint8_t i = 0; i < m; i++) {
        (*matrix)[i] = malloc(n * sizeof(float));
        if ((*matrix)[i] == NULL)
            return -1;
    }

    return 0;
}

void matrix_set_value(uint8_t m, uint8_t n, float ***matrix, float value)
{
    for (uint8_t i = 0; i < m; i++) {
        for (uint8_t j = 0; j < n; j++) {
            (*matrix)[i][j] = value;
        }
    }
}

void matrix_set_unit_matrix(uint8_t m, uint8_t n, float ***matrix)
{
    for (uint8_t i = 0; i < m; i++) {
        for (uint8_t j = 0; j < n; j++) {
            (*matrix)[i][j] = ((i == j) ? 1.0 : 0.0);
        }
    }
}

void matrix_print(uint8_t m, uint8_t n, float **matrix)
{
    for (uint8_t i = 0; i < m; i++) {
        printf("[");
        for (uint8_t j = 0; j < n; j++) {
            printf("%f", matrix[i][j]);
            if (j < (n - 1))
                printf(", ");
        }
        printf("]\n");
    }
}

// You can pass in an existing matrix to t, but it has to be the correct size.
// Otherwise just pass in a null pointer and it'll make a new matrix.
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
