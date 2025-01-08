#include <iostream>
#include "GestionareAngajati.h"

using namespace std;

int main() {
    GestionareAngajati gestionare;

    // Citire angajați din CSV
    gestionare.citesteDinCSV("angajati.csv");

    // Afișare angajați după citire
    gestionare.afiseazaAngajati();

    return 0;
}