#include "Balance.h"
#include "Coin.h"

Balance::Balance() {
    Denomination denoms[9] = {FIVE_CENTS,   TEN_CENTS,   TWENTY_CENTS,
                              FIFTY_CENTS,  ONE_DOLLAR,  TWO_DOLLARS,
                              FIVE_DOLLARS, TEN_DOLLARS, TWENTY_DOLLARS};
    // Create a default balance with no money
    for (int i = 0; i < 9; i++) {
        // Create Coin representing each denomination
        Coin coin = Coin();
        coin.count = 0;
        coin.denom = denoms[i];
        this->balance[i] = coin;
    }
}

int Balance::pay(int cost, int denomination) { return 0; }

bool Balance::enoughDenomination(int denomination) {
    bool result = false;

    for (Coin coin : this->balance) {
        if (Coin::intToDenomination(denomination) == coin.denom && coin.count > 0) {
            result = true;
        }
    }

    return result;
}

void Balance::insert(Coin newCoin) {
    // Check if the inputed Coin match any coin in balance
    for (Coin &coin : this->balance) {
        // If the denomination matches then add to the coin in balance
        if (coin.denom == newCoin.denom) {
            coin.count += newCoin.count;
        }
    }
}

int Balance::getMaxValue() {
    int maxValue = 0;
    for (Coin coin : this->balance) {
        if (coin.getTotal() > maxValue) {
            maxValue = coin.getTotal();
        }
    }
    return maxValue;
}

int Balance::getMaxQuantity() {
    int maxQuantity = 0;
    for (Coin coin : this->balance) {
        if (coin.count > maxQuantity) {
            maxQuantity = coin.count;
        }
    }
    return maxQuantity;
}