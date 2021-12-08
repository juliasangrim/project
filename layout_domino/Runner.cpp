#include <fstream>
#include "Runner.h"

Runner:: Runner(std::string &file) {
    file_name = file;
    templates = new Template[AMOUNT_TEMPLATE];
    init_templates();
}

void Runner::init_templates() {
   for (int y = 0; y < HEIGHT; ++y) {
       for (int x = 0; x < WIDTH; ++x) {
           Coord center(x,y);
           templates[y * WIDTH + x].init_template(center);
           std::cout << templates[y * WIDTH + x] << std::endl;
       }
   }
}

void Runner::run(long height, long width) {
    Field field(height, width);
    write_in_file(field);

}

void Runner::write_in_file(const Field& field) {
    std::fstream ready_field(file_name, std::ios::out);
    std::cout << field;

    if (ready_field.is_open()) {
        ready_field << field;
        ready_field.close();
    } else std::cerr << "Open failed" << std::endl;
}

Runner::~Runner() {
    delete[] templates;
}

