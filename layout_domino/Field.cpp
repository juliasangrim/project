
#include <random>
#include <ctime>
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
    auto start = clock();
    std::mt19937 mt(start);
    std::uniform_int_distribution<int> dist(0, 1);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            //TODO use different rand(this temporarily)
            if (x >= width_bound  && x < width - width_bound && y >= height_bound && y < height - height_bound) {
                field[y * width + x].set_state(dist(mt));
                Coord coord(x - width_bound, y - height_bound);
                field[y * width + x].set_coord(coord);
            } else {
                field[y * width + x].set_state(0);
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
            if (x < _field.width_bound || y < _field.height_bound
            || x >= _field.width - _field.width_bound || y >= _field.height - _field.height_bound) {
                out << "#" << " ";
            } else {
                out << _field.field[y * _field.width + x].get_state() << " ";
            }
        }
        out << std::endl;
    }
    return out;
}

int Field::get_width_bound() const {
    return width_bound;
}

int Field::get_height_bound() const {
    return height_bound;
}



void Field::change_cell_status_by_coord(Coord coord, int status) {
    field[coord.get_y() * width + coord.get_x()].set_state(status);
}


void Field::change_cell_hits_by_coord(Coord coord, int hits) {
    field[coord.get_y() * width + coord.get_x()].set_hits(hits);
}

Cell Field::get_cell_by_coord(Coord coord) {
    return field[coord.get_y() * width + coord.get_x()];
}

Cell Field::get_cell_by_xy(int x, int y) {
    int shifted_y = y;
    int shifted_x = x;
    return field[shifted_y * width + shifted_x];
}
