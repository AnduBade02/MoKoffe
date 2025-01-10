#ifndef GESTIONARE_PRODUSE_H
#define GESTIONARE_PRODUSE_H

#include <string>
#include <vector> // Utilizare template: vector este un template
#include <unordered_map>
#include <iostream>

using namespace std;

class Produs {
private:
    string nume;
    int stoc;
    double costAchizitie;
    double costVanzare;

public:
    Produs(const string& nume, int stoc, double costAchizitie, double costVanzare);

    const string& getNume() const;
    int getStoc() const;
    double getCostAchizitie() const;
    double getCostVanzare() const;

    void afiseazaDetalii() const;
};

class GestionareProduse {
private:
    vector<Produs> produse; // Utilizare template: vector de obiecte de tip Produs

public:
    void citesteDinCSV(const string& numeFisier);
    void scrieInCSV(const string& numeFisier) const;

    void adaugaProdus(const Produs& produs, const string& numeFisier);
    void eliminaProdus(const string& nume, const string& numeFisier);
    const std::vector<Produs>& getProduse() const { // Utilizare template: returnam o referinta catre vector
        return produse;
    };

    void afiseazaProduse() const;
    void golesteProduse(); // Goleste lista pentru schimbarea orasului
};

#endif