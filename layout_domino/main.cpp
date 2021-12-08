#include <iostream>
#include "Field.h"
#include "Runner.h"


int main(int argc, char** argv) {
    std::string filePath = "../field.txt";
    Runner runner = Runner(filePath);
    //TODO here long
    runner.run(atoi(argv[1]), atoi(argv[2]));
    return 0;
}
