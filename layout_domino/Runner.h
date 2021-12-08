#ifndef LAYOUT_DOMINO_RUNNER_H
#define LAYOUT_DOMINO_RUNNER_H


#include <string>
#include <utility>
#include "Field.h"
#include "Template.h"

class Runner {
private:
    Template* templates;
    std::string file_name;
    void init_templates();

    void write_in_file(const Field& field);
public:
    const int AMOUNT_TEMPLATE = 12;

    explicit Runner(std::string &file);
    ~Runner();
    void run(long height, long width);
};


#endif //LAYOUT_DOMINO_RUNNER_H
