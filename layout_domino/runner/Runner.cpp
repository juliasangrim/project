#include <fstream>
#include "Runner.h"



void Runner::run(long height, long width) {
    Field field = Field(height, width);
    write_in_file(field);
}

void Runner::write_in_file(Field& field) {
    std::fstream ready_field(file_name, std::ios::out);


    if (ready_field.is_open()) {
        for (int i = 0; i < field.get_height(); ++i) {
            for (int j = 0; j < field.get_width(); ++j) {
                ready_field << field.get_field()[i][j] << " ";
            }
            ready_field << "\n";
        }
        ready_field.close();
    } else std::cerr << "Open failed" << std::endl;
}
