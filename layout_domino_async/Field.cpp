
#include <random>
#include <ctime>
#include <iomanip>
#include "Field.h"

Field::Field(int rows, int columns) {
    field = new Cell[(rows + 2 * height_bound) * (columns + 2 * width_bound)];
    width = columns + 2 * width_bound;
    height = rows + 2 * height_bound;

}

Field::~Field() {
    delete[] field;
}


Cell *Field::get_field() {
    return field;
}

void Field::init_field() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            //array creates with size + bounds
            if (x >= width_bound && x < width - width_bound && y >= height_bound && y < height - height_bound) {
                field[y * width + x].set_state(dist(mt));
                //field[y * width + x].set_state(0);
                //add romb state
                Coord coord(x - width_bound, y - height_bound);
                field[y * width + x].set_coord(coord);
            } else {
                field[y * width + x].set_state(0);
                Coord coord(-1, -1);
                field[y * width + x].set_coord(coord);
            }
            field[y * width + x].set_hits(0);
        }
    }
}

int Field::get_width() {
    return width;
}

int Field::get_height() {
    return height;
}

std::ostream &operator<<(std::ostream &out, const Field &_field) {
    //write state of field
    out << "Status :" << std::endl;
    for (int y = -1; y < _field.height; ++y) {
        for (int x = -1; x < _field.width; ++x) {
            if (y == -1 && x >= 0) {
                out << std::setw(3) << x;
                continue;
            }
            if (x == -1 && y >= 0) {
                out << std::setw(3) << y;
                continue;
            } else if (x < _field.width_bound || y < _field.height_bound
                       || x >= _field.width - _field.width_bound || y >= _field.height - _field.height_bound) {
                out << std::setw(3) << "#";
            } else {
                out << std::setw(3) << _field.field[y * _field.width + x].get_state();
            }
        }
        out << std::endl;
    }
  //  out << "Hits :" << std::endl;
    //write hits TODO for debug
//    for (int y = -1; y < _field.height; ++y) {
//        for (int x = -1; x < _field.width; ++x) {
//            if (y == -1 && x >= 0) {
//                out << std::setw(3) << x;
//                continue;
//            }
//            if (x == -1 && y >= 0) {
//                out << std::setw(3) << y;
//                continue;
//            } else if (x < _field.width_bound || y < _field.height_bound
//                       || x >= _field.width - _field.width_bound || y >= _field.height - _field.height_bound) {
//                out << std::setw(3) << "#";
//            } else {
//                out << std::setw(3) << _field.field[y * _field.width + x].get_hits();
//            }
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
