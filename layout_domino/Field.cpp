
#include <random>
#include "Field.h"

Field::Field(int rows, int columns) {
    field = new Cell [(rows + 2 * height_bound) * (columns + 2 * width_bound)];
    width = columns + 2 * width_bound;
    height = rows + 2 * height_bound;

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
            if (x >= width_bound  && x < width - width_bound && y >= height_bound && y < height - height_bound) {
                field[y * width + x].set_state(rand() % 2);
                Coord coord(x - width_bound, y - height_bound);
                field[y * width + x].set_coord(coord);
            } else {
                field[y * width + x].set_state(-1);
                Coord coord(-1, -1);
                field[y * width + x].set_coord(coord);
            }
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
            if (_field.field[y * _field.width + x].get_state() == -1) {
                out << "#" << " ";
            } else {
                out << _field.field[y * _field.width + x].get_state() << " ";
            }
        }
        out << std::endl;
    }
//TODO:for testing
//    for (int y = 0; y < _field.height; ++y) {
//        for (int x = 0; x < _field.width; ++x) {
//            out << _field.field[y * _field.width + x].get_coord() << " ";
//        }
//        out << std::endl;
//    }
    return out;
}

int Field::get_width_bound() const {
    return width_bound;
}

int Field::get_height_bound() const {
    return height_bound;
}

Cell Field::get_cell_by_index(int index) {
    return field[width * height_bound + index + width_bound];
}

void Field::change_cell_by_coord(Coord coord, int hits, int status) {
    int shifted_y = coord.get_y() + height_bound;
    int shifted_x = coord.get_x() + width_bound;
    field[shifted_y * width + shifted_x].set_state(status);
    field[shifted_y * width + shifted_x].set_hits(hits);
}

Cell Field::get_cell_by_coord(Coord coord) {
    int shifted_y = coord.get_y() + height_bound;
    int shifted_x = coord.get_x() + width_bound;
    return field[shifted_y * width + shifted_x];
}

Cell Field::get_cell_by_xy(int x, int y) {
    int shifted_y = y + height_bound;
    int shifted_x = x + width_bound;
    return field[shifted_y * width + shifted_x];
}
