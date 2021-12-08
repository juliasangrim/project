#ifndef LAYOUT_DOMINO_FIELD_H
#define LAYOUT_DOMINO_FIELD_H


#include <iostream>
#include "Cell.h"


class Field {
private:
    Cell *field;
    long width;
    long height;

    void init_field();

public:
    Field(long rows, long columns);

    ~Field();

    Cell *get_field();


    int get_width();
    int get_height();

    //smth do

    friend std::ostream& operator<< (std::ostream &out, const Field & _field);

};


#endif //LAYOUT_DOMINO_FIELD_H
