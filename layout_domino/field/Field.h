#ifndef LAYOUT_DOMINO_FIELD_H
#define LAYOUT_DOMINO_FIELD_H


#include <iostream>
#include "../cell/Cell.h"


class Field {
private:
    Cell* field;
    long width;
    long height;

    void init_field();

public:
    Field(long rows, long columns) {
        field = new Cell [rows * columns];
        width = columns;
        height = rows;

        init_field();
    }

    ~Field() {
        delete[] field;
    }

    Cell* get_field();


    long get_width() const;
    long get_height() const;

    //smth do
};


#endif //LAYOUT_DOMINO_FIELD_H
