#include <iostream>
#include "Field.h"
#include "Runner.h"


int main(int argc, char** argv) {
    std::string filePath = "../field.txt";
    Runner runner = Runner(filePath, atoi(argv[1]), atoi(argv[2]), atof(argv[3]));
    //TODO here long
    runner.run();
    return 0;
}