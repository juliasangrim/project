//
// Created by lohuwka on 17.11.2021.
//
#include "Field.h"

int** Field::get_field() {
    return nullptr;
}

void Field::init_field() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            field[i] = 0;
        }
    }
}
