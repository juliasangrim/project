#include <fstream>
#include "Runner.h"

Runner:: Runner(std::string &file, int height, int width) {
    this -> file_name = file;
    this -> templates = new Template[AMOUNT_TEMPLATE];
    this -> field = new Field(height, width);
    this -> window = new Cell[WINDOW_SIZE * WINDOW_SIZE];
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


void Runner::fill_window(Coord center) {
    Coord begin_coord (center.get_x() - 2, center.get_y() - 2);
    std::cout << "BEGIN: " << begin_coord << std::endl;
    for (int  y = 0; y < WINDOW_SIZE; ++y) {
        for (int x = 0; x < WINDOW_SIZE; ++x) {
            window[y * WINDOW_SIZE + x] = field->get_cell_by_xy(begin_coord.get_x() + x, begin_coord.get_y() + y);
            std::cout << window[y * WINDOW_SIZE + x].get_state() << " ";

        }
        std::cout << std::endl;
    }

}


void Runner::evolve() {
    int all_point_number = (field->get_width() - 2 * field->get_width_bound())
            * (field->get_height() - 2 * field->get_height_bound());

    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 1; ++j) {
            //TODO: change rand
            int randPoint = rand() % all_point_number;
            Cell center = field->get_cell_by_index(randPoint);
            //TODO : delete
            std::cout << "CENTER: " << center.get_coord() << std::endl;
            std::cout << center.get_state() << std::endl;
            //
           // Coord begin_coord (center.get_coord().get_x() - 2, center.get_coord().get_y() - 2);

            fill_window(center.get_coord());

            count_hits();
        }
    }

}

void Runner::run() {

    evolve();

    write_in_file();

}

void Runner::write_in_file() {
    std::fstream ready_field(file_name, std::ios::out);

    if (ready_field.is_open()) {
        ready_field << *field;
        ready_field.close();
    } else std::cerr << "Open failed" << std::endl;
}

Runner::~Runner() {
    delete field;
    delete[] templates;
    delete[] window;
}

void Runner::count_hits() {
    for (int i = 0; )
}

bool Runner::compare_with_template() {
    return false;
}



