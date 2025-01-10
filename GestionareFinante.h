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

// Structura Eveniment pentru a stoca tipul evenimentului și prețul asociat
struct Eveniment {
    string tipEveniment;
    double pret;
};

class GestionareFinante {
public:
    // Structura Comanda pentru a stoca detalii despre o comandă
    struct Comanda {
        int espresso;  // Numărul de cafea Espresso
        int latte;  // Numărul de cafea Latte
        int brownie;  // Numărul de deserturi Brownie
        int baghetaCrispy;  // Numărul de baghete Crispy
        int ciocolataCalda;  // Numărul de ciocolată caldă
        int americano;  // Numărul de cafea Americano
        bool fidelitate;  // true dacă clientul are card de fidelitate
    };

    // Metodele clasei GestionareFinante

    // Citirea comenzilor dintr-un fișier CSV
    void citesteComenziDinCSV(const std::string& numeFisier);

    // Calcularea prețului unei comenzi
    double calculeazaPretComanda(const Comanda& comanda, const GestionareProduse& gestionareProduse) const;

    // Aplicarea unei reduceri pe baza cardului de fidelitate
    double aplicaReducere(double pretTotal, bool fidelitate) const;

    // Citirea evenimentelor dintr-un fisier CSV
    void citesteEvenimenteDinCSV(const string& numeFisier);

    // Calcularea costului total al evenimentelor
    double calculeazaCostEvenimente() const;

    // Generarea unui raport CSV cu veniturile, costurile și salariile
    void genereazaRaportCSV(const string& numeFisier, const GestionareProduse& gestionareProduse, const GestionareAngajati& gestionareAngajati) const;

    // Calcularea veniturilor totale obținute din produse
    double calculeazaVenituriTotale(const GestionareProduse& gestionareProduse) const;

    // Calcularea costurilor totale ale produselor
    double calculeazaCostProduse(const GestionareProduse& gestionareProduse) const;

private:
    vector<Eveniment> evenimente;  // Stocăm evenimentele citite
    std::vector<Comanda> comenzi;  // Stocăm comenzile citite
};

#endif // GESTIONAREFINANTE_H