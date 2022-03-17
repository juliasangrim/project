#ifndef LAYOUT_DOMINO_RUNNER_H
#define LAYOUT_DOMINO_RUNNER_H


#include <string>
#include <utility>
#include "Field.h"
#include "Template.h"

class Runner {
private:
    const int WINDOW_SIZE = 5;
    const int ITER_COUNT = 482;

    //TODO
    Template *templates;
    Field* field;
    Cell *window;
    //TODO array?
    double probability;
    double probability_max;
    std::string file_name;

    void init_templates();
    void evolve();
    void fill_window(Coord center);
    void write_in_file();
    int count_hits(Coord &point);
    bool compare_with_template(int begin_x, int begin_y, int index_template, Tiletype tiletype);

    void change_state(Coord &point);

public:
    const int AMOUNT_TEMPLATE = 12;

    explicit Runner(std::string &file, int height, int width, double prob_1, double prob_2);
    ~Runner();
    void run();
};


#endif //LAYOUT_DOMINO_RUNNER_H
