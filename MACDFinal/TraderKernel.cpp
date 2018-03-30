#include <fstream>
#include <iostream>
#include "Trader.h"

int main(int argc, char **argv){

    std::ofstream file;
    std::ifstream input;
    std::string date;
    double s;

    ActiveTrader activeTrader(1000);
    HodlTrader hodlTrader(1000);

    if (argc < 2){
        std::cout << "Za mało argumentów!!! " << argc << std::endl;
        return 255;
    }
//
//    file.open(argv[2]);
//    input.open(argv[1]);
//
//    MACD macd(file, 26, 12, 9);
//
//    while (input >> date >> s){
//        macd.update(date, s);
//    }
//
//    file.close();
//    input.close();

    printf("%s\n", argv[1]);

    input.open(argv[1]);

    while (input >> s){
        activeTrader.update(s);
        hodlTrader.update(s);
    }
    double finalActive = activeTrader.getCurrentSzekel() + activeTrader.getActions() * activeTrader.getCurrentValue() - activeTrader.getInitialValue();
    double finalHodl = hodlTrader.getActions() * hodlTrader.getCurrentValue() + hodlTrader.getCurrentSzekel() - hodlTrader.getInitialValue();

    printf("ActiveTrader's final gain: %f\nHodlTrader's final gain: %f\ninitial Money: %f\nPercent Gain: %f%%\n",
           finalActive,
           finalHodl,
           hodlTrader.getInitialValue(),
           (finalActive - finalHodl) / finalHodl * 100
    );

    input.close();

    return 0;
}
