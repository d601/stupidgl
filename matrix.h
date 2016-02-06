#pragma once

#include <stdint.h>

struct matrix {
    uint8_t rows;
    uint8_t columns;
    float *data;
};

int matrix_new(uint8_t m, uint8_t n, struct matrix **matrix);

int matrix_b_new(uint8_t m, uint8_t n, float **matrix);

int matrix_set_identity(uint8_t m, uint8_t n, float **matrix);

void matrix_print(uint8_t m, uint8_t n, float *matrix);

int matrix_set_rotation_x(float phi, float **matrix);

int matrix_set_rotation_y(float phi, float **matrix);

int matrix_set_perspective(
    float l,
    float b,
    float n,
    float r,
    float t,
    float f,
    float **matrix);

int matrix_multiply(
    uint8_t m1m,
    uint8_t m1n,
    float *m1,
    uint8_t m2m,
    uint8_t m2n,
    float *m2,
    uint8_t *tm, // result
    uint8_t *tn,
    float **t);
