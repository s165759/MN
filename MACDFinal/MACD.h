//
// Created by maxchil on 3/11/18.
//

#ifndef MACD_MACD_H
#define MACD_MACD_H

#include <deque>
#include <iostream>

enum errCodes{
    NOT_ENOUGH_DATA,
    ALLES_KLAR,
};

class MACD {
    std::deque<double> signal_queue;
    std::deque<double> MACD_queue;
    std::ostream& out;

    int slow;
    int fast;
    int sig;

    double EMA(int size, std::deque<double>& deque);
    double EMAr(int size, std::deque<double>& deque);

public:

    MACD(std::ostream &out, int slow, int fast, int sig);

public:

    errCodes update(std::string date, double value);
    errCodes update(double value);
};


#endif //MACD_MACD_H
