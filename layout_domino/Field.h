#ifndef LAYOUT_DOMINO_FIELD_H
#define LAYOUT_DOMINO_FIELD_H


#include <iostream>
#include "Cell.h"


class Field {
private:
    Cell *field;
    int height;
    int width;

    int height_nobound;
    int width_nobound;
//TODO
    const int width_bound = 2;
    const int height_bound = 2;

    void init_field();

public:
    Field(int rows, int columns);

    ~Field();

    Cell *get_field();

    //TODO
    int get_width_bound() const;
    int get_height_bound() const;
    int get_width();
    int get_height();
    Cell get_cell_by_index(int index);
    Cell get_cell_by_coord(Coord coord);
    Cell get_cell_by_xy(int x, int y);
    void change_cell_by_coord(Coord coord, int hits, int status);

    //smth do

    friend std::ostream& operator<< (std::ostream &out, const Field & _field);

};


#endif //LAYOUT_DOMINO_FIELD_H
