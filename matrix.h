#pragma once

#include <stdint.h>

int matrix_new(uint8_t m, uint8_t n, float **matrix);

int matrix_set_identity(uint8_t m, uint8_t n, float **matrix);

void matrix_print(uint8_t m, uint8_t n, float *matrix);

int matrix_set_perspective(
    float l,
    float b,
    float n,
    float r,
    float t,
    float f,
    float **matrix);
