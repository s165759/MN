//
// Created by maxchil on 3/11/18.
//

#include "MACD.h"

errCodes MACD::update(std::string date, double value) {

    if (signal_queue.size() <= slow) {
        signal_queue.push_front(value);
        return NOT_ENOUGH_DATA;
    }

    double macd = EMA(fast, signal_queue) - EMA(slow, signal_queue);

    if (MACD_queue.size() <= sig) {
        MACD_queue.push_front(macd);
        return NOT_ENOUGH_DATA;
    }


    out << date << "," << value << "," << macd << "," << EMA(sig, MACD_queue) << std::endl;

    signal_queue.push_front(value);
    signal_queue.pop_back();

    MACD_queue.push_front(macd);
    MACD_queue.pop_back();

    return ALLES_KLAR;

}

double MACD::EMA(int size, std::deque<double>& q) {
    double const alfa = 1. - 2. / (size - 1);
    double d = 1, top = 0, bottom = 0;

    auto iter = q.begin();

    for (int i = 0; i <= size; ++i) {
        top += d * *iter;
        bottom += d;
        d *= alfa;
        iter++;
    }
    return top/bottom;
}


MACD::MACD(std::ostream &out, int slow, int fast, int sig) : out(out), slow(slow), fast(fast), sig(sig) {}

double MACD::EMAr(int size, std::deque<double> &deque) {
    return 0;
}

errCodes MACD::update(double value) {
    if (signal_queue.size() <= slow) {
        signal_queue.push_front(value);
        return NOT_ENOUGH_DATA;
    }

    double ema12 = EMA(fast, signal_queue);
    double ema26 = EMA(slow, signal_queue);

    double macd =  ema12 - ema26;

    if (MACD_queue.size() <= sig) {
        MACD_queue.push_front(macd);
        return NOT_ENOUGH_DATA;
    }

    out << macd << " " << EMA(sig, MACD_queue) << std::endl;

    signal_queue.push_front(value);
    signal_queue.pop_back();

    MACD_queue.push_front(macd);
    MACD_queue.pop_back();

    return ALLES_KLAR;

}
