#include "Coord.h"

Coord::Coord(int x_coord, int y_coord) {
    this -> x = x_coord;
    this -> y = y_coord;
}

int Coord::get_x() {
    return x;
}

int Coord::get_y() {
    return y;
}

void Coord::set_coord(int x_coord, int y_coord) {
    this -> x = x_coord;
    this -> y = y_coord;
}

Coord::Coord() {
    this -> x = 0;
    this -> y = 0;

}

std::ostream &operator<<(std::ostream &out, const Coord &point) {
    out << "(" << point.x << ";" << point.y << ")" ;
    return out;
}


