#ifndef LAYOUT_DOMINO_RUNNER_H
#define LAYOUT_DOMINO_RUNNER_H


#include <string>
#include <utility>
#include "../field/Field.h"

class Runner {
private:
    std::string file_name;

    void write_in_file(Field& field);
public:
    Runner(std::string file) {
        file_name = std::move(file);
    }
    void run(long height, long width);
};


#endif //LAYOUT_DOMINO_RUNNER_H
