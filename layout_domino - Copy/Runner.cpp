#include <fstream>
#include <random>
#include <ctime>
#include "Runner.h"

Runner:: Runner(std::string &file, int height, int width, double prob1, double prob2) {
    this -> file_name = file;
    this -> templates = new Template[AMOUNT_TEMPLATE];
    this -> oldField = new Field(height, width);
    this -> newField = new Field(height, width);
    this -> window = new Cell[WINDOW_SIZE * WINDOW_SIZE];
    this->probability = prob1;
    this->probability_max = prob2;
    init_templates();
}

void Runner::init_templates() {
   for (int y = 0; y < HEIGHT; ++y) {
       for (int x = 0; x < WIDTH; ++x) {
           Coord center(x,y);
           templates[y * WIDTH + x].init_template(center);
          // std::cout << templates[y * WIDTH + x] << std::endl;
       }
   }
}


void Runner::fill_window(Coord center) {
    Coord begin_coord (center.get_x() - oldField->get_width_bound(), center.get_y() - oldField->get_width_bound());
   // std::cout << "BEGIN: " << begin_coord << std::endl;
    for (int  y = 0; y < WINDOW_SIZE; ++y) {
        for (int x = 0; x < WINDOW_SIZE; ++x) {
            window[y * WINDOW_SIZE + x] = oldField->get_cell_by_xy(begin_coord.get_x() + x, begin_coord.get_y() + y);
//            std::cout << window[y * WINDOW_SIZE + x].get_state() << " ";

        }
//        std::cout << std::endl;
    }
//    std::cout << std::endl;

}


void Runner::evolve() {
    auto start = clock();
    std::mt19937 mt(start);
    std::uniform_int_distribution<int> dist1(0, oldField->get_width() - 2 * oldField->get_width_bound() - 1);
    std::uniform_int_distribution<int> dist2(0, oldField->get_height() - 2 * oldField->get_height_bound() - 1);
    int all_point_number = (oldField->get_width() - 2 * oldField->get_width_bound())
            * (oldField->get_height() - 2 * oldField->get_height_bound());
    for (int i = 0; i < ITER_COUNT; ++i) {
        for (int j = 0; j < all_point_number; ++j) {
            int randX = dist1(mt) + oldField->get_width_bound();
            int randY = dist2(mt) % (oldField->get_height() - 2 * oldField->get_height_bound()) + oldField->get_height_bound();
            Coord center = Coord(randX, randY);

            fill_window(center);

            auto hits = count_hits(center);
 //           std::cout << std::endl;
 //           std::cout << "HITS  " << hits << std::endl;
 //           std::cout << " hits "<< oldField->get_cell_by_coord(center).get_hits() << " " << hits << std::endl;
            oldField->change_cell_hits_by_coord(center, hits);
            change_state(center);
//            std::cout << "hits " << oldField->get_cell_by_coord(center).get_hits() << " " << hits << std::endl;
        }
        std::cout << "BEFORE COPY" << std::endl;
        std::cout << *oldField << std::endl;
        std::cout << *newField << std::endl;
        oldField->copy_filed(newField->get_field());
        std::cout << "AFTER COPY" << std::endl;
        std::cout << "ITER: " << i << std::endl;
        std::cout << *oldField << std::endl;
        std::cout << *newField << std::endl;
    }

}

void Runner::run() {
    std::cout << *oldField << std::endl;
    evolve();
    write_in_file();

}

void Runner::write_in_file() {
    std::fstream ready_field(file_name, std::ios::out);

    if (ready_field.is_open()) {
        ready_field << *oldField;
        ready_field.close();
    } else std::cerr << "Open failed" << std::endl;
}

Runner::~Runner() {
    delete oldField;
    delete[] templates;
    delete[] window;
}

int Runner::count_hits(Coord &point) {
    //for horizontal
    int count_hits = 0;
    for (int i = 0; i < AMOUNT_TEMPLATE; ++i) {
        //shifted (0,0)
        auto shiftedX = 2 - templates[i].get_center().get_x();
        auto shiftedY = 2 - templates[i].get_center().get_y();
        auto isHit = compare_with_template(shiftedX, shiftedY, i, HORIZONTAL);
        if (isHit && (templates[i].get_center_state() != 1)) {
            count_hits++;
        //    std::cout << "HORIZONTAL  " << count_hits << std::endl;
        } else {
            if (isHit &&  (templates[i].get_center_state() == 1)) {
                count_hits = 100;
           //     std::cout << "HORIZONTAL  " << count_hits << std::endl;
            }
        }
    }
    //for vertical
    for (int i = 0; i < AMOUNT_TEMPLATE; ++i) {
        //shifted (0,0)
        auto shiftedX = 2 + templates[i].get_center().get_y();
        auto shiftedY = 2 - templates[i].get_center().get_x();
        auto isHit = compare_with_template(shiftedX, shiftedY, i, VERTICAL);
        if (isHit && (templates[i].get_center_state() != 1)) {
            count_hits++;
            //std::cout << "VERTICAL  " << count_hits << "INDEX  " << i << std::endl;
        } else {
            if (isHit &&  (templates[i].get_center_state() == 1)) {
                count_hits = 100;
            //    std::cout << "VERTICAL  " << count_hits << std::endl;
            }
        }
    }
    return count_hits;
}

//first rule
void Runner::change_state(Coord &point) {
    std::random_device rd;
    auto start = clock();
    std::mt19937 mt(start);
    std::uniform_real_distribution<double> dist(0, 1);
    std::uniform_int_distribution<int> dist1(0, 1);
    auto amountHits = oldField->get_cell_by_coord(point).get_hits();
    double prob = dist(mt);
    int new_state = oldField->get_cell_by_coord(point).get_state();
   // std::cout << "Amount hits " << amountHits << " " << std::endl;
    if (amountHits > 0 && amountHits != 100) {
        new_state = 0;
    } else {
        if (amountHits == 100) {
            new_state = 1;
        } else {
            if (amountHits == 0) {
               // std::cout << "PROB RAND + PROB" << " " << prob << " " << probability << std::endl;
                prob = dist(mt);
                if (prob < probability) {
                    int new_state = dist1(mt);
                    newField->change_cell_status_by_coord(point, new_state);
                }
            }
        }
    }
}


bool Runner::compare_with_template(int begin_x, int begin_y, int index_template, Tiletype tiletype) {

//    std::cout << "INDEX TEMPLATE " << index_template << std::endl;
    //change location of template for comparing
    switch (tiletype) {
        case HORIZONTAL:
            for (int y = 0; y < HEIGHT; ++y) {
                for (int x = 0; x < WIDTH; ++x) {
                    auto curr_template = templates[index_template].get_template();
                    if (curr_template[y * WIDTH + x].get_state() != -1) {
//                        std::cout << "TEMPLATE COORD " << x << " " << y << std::endl;
//                        std::cout << curr_template[y * WIDTH + x].get_state()<<std::endl;
//                        std::cout << "WINDOW COORD " << begin_x + x << " " << begin_y + y << std::endl;
//                        std::cout << window[(begin_y + y) * WINDOW_SIZE + (begin_x + x)].get_state()<<std::endl;
                        if (curr_template[y * WIDTH + x].get_state() != window[(begin_y + y) * WINDOW_SIZE + (begin_x + x)].get_state()) {
                            //std::cout << window[(begin_y + y) * WINDOW_SIZE + (begin_x + x)].get_state()<<std::endl;
                            return false;
                        }
                    }
                }
            }
            break;
        case VERTICAL:
            for (int x = 0; x < WIDTH; ++x) {
                for (int y = 0; y < HEIGHT; ++y) {
                    auto curr_template = templates[index_template].get_template();
                    if (curr_template[y * WIDTH + x].get_state() != -1) {
//                        std::cout << "TEMPLATE COORD " << x << " " << y << std::endl;
//                        std::cout << curr_template[y * WIDTH + x].get_state()<<std::endl;
//                        std::cout << "WINDOW COORD " << begin_x - y << " " << begin_y + x << std::endl;
//                        std::cout << window[(begin_y + x) * WINDOW_SIZE + (begin_x - y)].get_state()<<std::endl;
                        if (curr_template[y * WIDTH + x].get_state() != window[(begin_y + x) * WINDOW_SIZE + (begin_x - y)].get_state()) {
                           // std::cout << window[(begin_y + y) * WINDOW_SIZE + (begin_x + x)].get_state();
                            return false;
                        }
                    }
                }
            }
        break;
    }
    return true;
}



