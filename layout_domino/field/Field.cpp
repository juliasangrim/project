
#include <random>
#include "Field.h"

Cell* Field::get_field() {
    return field;
}

void Field::init_field() {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            //TODO use different rand(this temporarily)
            field[i * width + j].status = rand() % 2;
        }
    }
}

long Field::get_width() const {
    return width;
}

long Field::get_height() const {
    return height;
}
