#include "Coin.h"

// implement functions for managing coins; this may depend on your design.
bool Coin::isDenomination(int denomination) {
    return denomination == 5 || denomination == 10 || denomination == 20 ||
           denomination == 50 || denomination == 100 || denomination == 200 ||
           denomination == 500 || denomination == 1000 || denomination == 2000;
}

Denomination Coin::intToDenomination(int denomination_val) {
    Denomination denomination =
            FIVE_CENTS; // The default return value is FIVE_CENTS

    if (denomination_val == 5) {
        denomination = FIVE_CENTS;
    } else if (denomination_val == 10) {
        denomination = TEN_CENTS;
    } else if (denomination_val == 20) {
        denomination = TWENTY_CENTS;
    } else if (denomination_val == 50) {
        denomination = FIFTY_CENTS;
    } else if (denomination_val == 100) {
        denomination = ONE_DOLLAR;
    } else if (denomination_val == 200) {
        denomination = TWO_DOLLARS;
    } else if (denomination_val == 500) {
        denomination = FIVE_DOLLARS;
    } else if (denomination_val == 1000) {
        denomination = TEN_DOLLARS;
    } else if (denomination_val == 2000) {
        denomination = TWENTY_DOLLARS;
    }
    return denomination;
}

float Coin::getTotal() { return (float)this->denom * this->count / 100; }