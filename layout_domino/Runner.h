#ifndef LAYOUT_DOMINO_RUNNER_H
#define LAYOUT_DOMINO_RUNNER_H


#include <string>
#include <utility>
#include "Field.h"
#include "Template.h"

class Runner {
private:
    const int WINDOW_SIZE = 5;
    const int ITER_COUNT = 10;

    //TODO
    Template *templates;
    Field* field;
    Cell *window;

    std::string file_name;

    void init_templates();
    void evolve();
    void fill_window(Coord center);
    void write_in_file();
    void count_hits();
    bool compare_with_template();


public:
    const int AMOUNT_TEMPLATE = 12;

    explicit Runner(std::string &file, int height, int width);
    ~Runner();
    void run();
};


#endif //LAYOUT_DOMINO_RUNNER_H
