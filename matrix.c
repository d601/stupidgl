#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/**
 * Matrix functions
 *
 * Each function (should have) two versions, one that operates on a matrix struct and
 * one that operates on a bare matrix. In a lot of cases, the size of a matrix
 * can be assumed so there's no need to waste overhead on extra data.
 *
 */

int matrix_new(uint8_t m, uint8_t n, struct matrix **matrix)
{
    *matrix = malloc(sizeof(struct matrix));
    (*matrix)->rows = m;
    (*matrix)->columns = n;
    return matrix_b_new(m, n, &((*matrix)->data));
}

int matrix_b_new(uint8_t m, uint8_t n, float **matrix)
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

    return 0;
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

// these should be *matrix, not **matrix
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

    return 0;
}

int matrix_set_rotation_x(float phi, float **matrix)
{
    if (matrix == NULL)
        return -1;

    (*matrix)[0 * 4 + 0] = 1.0;
    (*matrix)[0 * 4 + 1] = 0.0;
    (*matrix)[0 * 4 + 2] = 0.0;
    (*matrix)[0 * 4 + 3] = 0.0;

    (*matrix)[1 * 4 + 0] = 0.0;
    (*matrix)[1 * 4 + 1] = cosf(phi);
    (*matrix)[1 * 4 + 2] = - sinf(phi);
    (*matrix)[1 * 4 + 3] = 0.0;

    (*matrix)[2 * 4 + 0] = 0.0;
    (*matrix)[2 * 4 + 1] = sinf(phi);
    (*matrix)[2 * 4 + 2] = cosf(phi);
    (*matrix)[2 * 4 + 3] = 0.0;

    (*matrix)[3 * 4 + 0] = 0.0;
    (*matrix)[3 * 4 + 1] = 0.0;
    (*matrix)[3 * 4 + 2] = 0.0;
    (*matrix)[3 * 4 + 3] = 1.0;

    return 0;
}

int matrix_set_rotation_y(float phi, float **matrix)
{
    if (matrix == NULL)
        return -1;

    (*matrix)[0 * 4 + 0] = cosf(phi);
    (*matrix)[0 * 4 + 1] = 0.0;
    (*matrix)[0 * 4 + 2] = sinf(phi);
    (*matrix)[0 * 4 + 3] = 0.0;

    (*matrix)[1 * 4 + 0] = 0.0;
    (*matrix)[1 * 4 + 1] = 1.0;
    (*matrix)[1 * 4 + 2] = 0.0;
    (*matrix)[1 * 4 + 3] = 0.0;

    (*matrix)[2 * 4 + 0] = - sinf(phi);
    (*matrix)[2 * 4 + 1] = 0.0;
    (*matrix)[2 * 4 + 2] = cosf(phi);
    (*matrix)[2 * 4 + 3] = 0.0;

    (*matrix)[3 * 4 + 0] = 0.0;
    (*matrix)[3 * 4 + 1] = 0.0;
    (*matrix)[3 * 4 + 2] = 0.0;
    (*matrix)[3 * 4 + 3] = 1.0;

    return 0;
}


// multiplies a 4x4 matrix by a point
int matrix_multiply_point(float *matrix, float *point_in, float *point_out)
{
    // fill me in
    return 0;
}

// untested
int matrix_multiply(
    uint8_t m1m,
    uint8_t m1n,
    float *m1,
    uint8_t m2m,
    uint8_t m2n,
    float *m2,
    uint8_t *tm, // result
    uint8_t *tn,
    float **t)
{
    if (m1n != m2n)
        return -1;

    if ((*t != NULL) && (tm != NULL) && (tn != NULL)
        && ((*tm != m1m) || (*tn != m2n)))
        return -1;

    if (*t == NULL)
        matrix_b_new(m1m, m2n, t);

    for (uint8_t i = 0; i < m1m; i++) {
        for (uint8_t j = 0; j < m2n; j++) {
            (*t)[i * m2n + j] = 0.0;
            for (uint8_t k = 0; k < m1n; k++) {
                //printf("%u %u %u", i, j, k);
                (*t)[i * m2n + j] += m1[i * m1n + k] * m2[k * m2n + j];
            }
        }
    }

    return 0;
}
