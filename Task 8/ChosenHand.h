#pragma once
#include "Hand.h"
#include <iostream>

class ChosenHand {
private:
    Hand hand;

public:
    // Constructor untuk menginisialisasi hand yang dipilih
    ChosenHand(const Hand& selectedHand);

    // Mengambil data hand
    Hand getHand() const;

    // Menampilkan kartu yang dipilih ke layar
    void displayHand() const;
};
