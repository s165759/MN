#include <fstream>
#include <iostream>
#include "MACD.h"

int main(int argc, char **argv){

    std::ofstream file;
    std::ifstream input;
    std::string date;
    double s;

    if (argc < 3){
        std::cout << "Za mało argumentów!!! " << argc << std::endl;
        return 255;
    }

    file.open(argv[2]);
    input.open(argv[1]);

    MACD macd(file, 26, 12, 9);

    while (input >> date >> s){
        macd.update(date, s);
    }

    file.close();
    input.close();

    return 0;
}