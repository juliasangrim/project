
#include <random>
#include "Field.h"

Field::Field(long rows, long columns) {
    field = new Cell [rows * columns];
    width = columns;
    height = rows;

    init_field();
}

Field::~Field() {
    delete[] field;
}


Cell* Field::get_field() {
    return field;
}

void Field::init_field() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            //TODO use different rand(this temporarily)
            field[y * width + x].set_state(rand() % 2);
            Coord coord(x, y);
            field[y * width + x].set_coord(coord);
        }
    }
}

int Field::get_width(){
    return width;
}

int Field::get_height(){
    return height;
}

std::ostream &operator<<(std::ostream &out, const Field &_field) {
    for (int y = 0; y < _field.height; ++y) {
        for (int x = 0; x < _field.width; ++x) {
            out << _field.field[y * _field.width + x].get_state() << " ";
        }
        out << std::endl;
    }

    for (int y = 0; y < _field.height; ++y) {
        for (int x = 0; x < _field.width; ++x) {
            out << _field.field[y * _field.width + x].get_coord() << " ";
        }
        out << std::endl;
    }
    return out;
}
