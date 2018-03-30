//
// Created by maxchil on 3/27/18.
//

#include <cmath>
#include "Trader.h"

Trader::Trader(int actions) : actions(actions) {
    inputReader = new std::stringstream(input);
    macdFactory = new MACD(*inputReader, 26, 12, 9);

    input = "";
    currentSzekel = 0;
    maxDivergence = 0;
    currentMacd = -1;
    currentSignal = -1;
    lastBuyValue = 0;
    lastSellValue = 0;
    lastActiveAction = NOT_STARTED;
    divergenceThreshold = 1;
}

Trader::~Trader() {
    delete inputReader;
    delete macdFactory;
}

void Trader::update(double signal) {
    if(macdFactory->update(signal) == NOT_ENOUGH_DATA){
        return;
    }

    currentValue = signal;
    lastMacd = currentMacd;
    lastSignal = currentSignal;

    *inputReader >> currentMacd >> currentSignal;

    if(lastMacd == -1){
        return;
    }

    maxDivergence = fabs(currentMacd / currentSignal) > maxDivergence ? fabs(currentMacd / currentSignal) : maxDivergence;

    takeAction(evaluate());


}

double Trader::getCurrentValue() const {
    return currentValue;
}

double Trader::getCurrentSzekel() const {
    return currentSzekel;
}

int Trader::getActions() const {
    return actions;
}

double Trader::getInitialValue() const {
    return initialValue;
}


HodlTrader::HodlTrader(int actions) : Trader(actions) {}

Trader::Action HodlTrader::evaluate() {
    if(lastActiveAction == NOT_STARTED){
        if(lastMacd > lastSignal && currentMacd < currentSignal && currentMacd < 0)
            return BUY;
    }

    return HODL;
}

void HodlTrader::takeAction(Trader::Action signal) {
    switch (signal){
        case BUY:
            initialValue = currentValue * actions;
            lastActiveAction = BUY;
            break;

        case NOT_STARTED:
            break;

        case HODL:
            break;
    }
}

ActiveTrader::ActiveTrader(int actions) : Trader(actions) {}

Trader::Action ActiveTrader::evaluate() {
    if(lastMacd > lastSignal &&
       currentMacd < currentSignal &&
       currentMacd < 0 &&
       maxDivergence < divergenceThreshold &&
       ((lastActiveAction == SELL && currentSzekel != 0) || lastActiveAction == NOT_STARTED))
    {
        return BUY;
    }

    if (lastMacd < lastSignal &&
        currentMacd > currentSignal &&
        currentMacd > 0 &&
        maxDivergence > divergenceThreshold &&
        lastActiveAction == BUY &&
        actions != 0)
    {
        return SELL;
    }

    return HODL;
}

void ActiveTrader::takeAction(Trader::Action signal) {
    switch (signal) {
        case BUY:{
            if(lastActiveAction == NOT_STARTED){
                currentSzekel = currentValue * actions;
                initialValue = currentSzekel;
                actions = 0;
            }

            double boughtActions = round(currentSzekel / currentValue);
            currentSzekel -= boughtActions * currentValue;
            actions += boughtActions;
            lastActiveAction = BUY;
            lastBuyValue = currentValue;
            maxDivergence = 0;
            return;
        }
        case SELL:{

            currentSzekel += actions * currentValue;
            actions = 0;
            lastActiveAction = SELL;
            lastSellValue = currentValue;
            maxDivergence = 0;
            return;
        }
        case HODL:return;
        case NOT_STARTED:return;
    }


}
