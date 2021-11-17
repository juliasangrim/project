
#include "Field.h"

int** Field::get_field() {
    return field;
}

void Field::init_field() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            field[i][j] = 0;
        }
    }
}

long Field::get_width() const {
    return width;
}

long Field::get_height() const {
    return height;
}
