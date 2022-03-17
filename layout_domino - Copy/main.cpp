#include <iostream>
#include "Field.h"
#include "Runner.h"


int main(int argc, char** argv) {
    std::string filePath = "../oldField.txt";
    Runner runner = Runner(filePath, atoi(argv[1]), atoi(argv[2]), atof(argv[3]), atof(argv[4]));
    //TODO here long
    runner.run();
    return 0;
}
