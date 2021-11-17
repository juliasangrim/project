#ifndef LAYOUT_DOMINO_FIELD_H
#define LAYOUT_DOMINO_FIELD_H


#include <iostream>



class Field {
private:
    int** field;
    long width;
    long height;

    void init_field();

public:
    Field(long rows, long columns) {
        field = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            field[i] = new int[columns];
        }
        width = columns;
        height = rows;

        init_field();
    }

    ~Field() {
        for (int i = 0; i < height; ++i) {
           delete[] field[i];
        }
        delete[] field;
    }

    int** get_field();
    long get_width() const;
    long get_height() const;
};


#endif //LAYOUT_DOMINO_FIELD_H
