//
// Created by maxchil on 3/27/18.
//

#ifndef MACD_TRADER_H
#define MACD_TRADER_H

#include <sstream>
#include "MACD.h"

class Trader {

protected:
    enum Action {
        BUY,
        SELL,
        HODL,
        NOT_STARTED
    };

    Action lastActiveAction;
    MACD *macdFactory;
    std::stringstream *inputReader;
    std::string input;

    double maxDivergence;
    double lastMacd;
    double currentMacd;
    double lastSignal;
    double currentSignal;
    double currentValue;
    double lastBuyValue;
    double lastSellValue;
    double initialValue;
    double divergenceThreshold;


    int actions;
    double currentSzekel;

public:

    explicit Trader(int actions);
    virtual ~Trader();

    double getCurrentValue() const;

    int getActions() const;

    double getCurrentSzekel() const;

    double getInitialValue() const;

private:

    virtual Action evaluate() = 0;
    virtual void takeAction(Action signal) = 0;

public:

    void update(double signal);
};



class HodlTrader : public Trader{

    Action evaluate() override;
    void takeAction(Action signal) override;

public:
    explicit HodlTrader(int actions);

};

class ActiveTrader : public Trader{
public:
    explicit ActiveTrader(int actions);

private:
    Action evaluate() override;

    void takeAction(Action signal) override;

};


#endif //MACD_TRADER_H
