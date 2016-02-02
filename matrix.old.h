#pragma once
#include <stdint.h>

int matrix_new(uint8_t m, uint8_t n, float ***matrix);

void matrix_set_value(uint8_t m, uint8_t n, float ***matrix, float value);

void matrix_set_unit_matrix(uint8_t m, uint8_t n, float ***matrix);

void matrix_print(uint8_t m, uint8_t n, float **matrix);

int matrix_multiply(
    uint8_t m1m,
    uint8_t m1n,
    float **m1,
    uint8_t m2m,
    uint8_t m2n,
    float **m2,
    uint8_t *tm,
    uint8_t *tn,
    float ***t);
