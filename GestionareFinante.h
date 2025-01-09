#ifndef GESTIONAREFINANTE_H
#define GESTIONAREFINANTE_H

#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include "GestionareProduse.h"  // Importăm GestionareProduse pentru a accesa produsele
#include "GestionareAngajati.h"

struct Eveniment {
    string tipEveniment;
    double pret;
};

class GestionareFinante {
public:
    struct Comanda {
        int espresso;
        int latte;
        int brownie;
        int baghetaCrispy;
        int ciocolataCalda;
        int americano;
        bool fidelitate; // true dacă clientul are card de fidelitate
    };

    void citesteComenziDinCSV(const std::string& numeFisier);
    double calculeazaPretComanda(const Comanda& comanda, const GestionareProduse& gestionareProduse) const;
    double aplicaReducere(double pretTotal, bool fidelitate) const ;

    void citesteEvenimenteDinCSV(const string& numeFisier);
    void afiseazaEvenimente() const;
    double calculeazaCostEvenimente() const;
    void genereazaRaportCSV(const string& numeFisier, const GestionareProduse& gestionareProduse, const GestionareAngajati& gestionareAngajati) const;

    double calculeazaVenituriTotale(const GestionareProduse& gestionareProduse) const;
    double calculeazaCostProduse(const GestionareProduse& gestionareProduse) const;


private:
    vector<Eveniment> evenimente;
    std::vector<Comanda> comenzi;  // Stocăm comenzile citite
};

#endif // GESTIONAREFINANTE_H