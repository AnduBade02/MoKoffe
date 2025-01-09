#ifndef GESTIONARE_EVENIMENTE_H
#define GESTIONARE_EVENIMENTE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Event {
private:
    string nume;
    double pret;

public:
    Event() : nume(""), pret(0.0) {}
    Event(const string& nume, double pret);

    const string& getNume() const;
    double getPret() const;

    void afiseazaDetalii() const;
};

class GestionareEvenimente {
private:
    vector<Event> evenimente;

public:
    void citesteDinCSV(const string& numeFisier);
    void scrieInCSV(const string& numeFisier) const;

    void adaugaEvent(const Event& event, const string& numeFisier);
    void eliminaEvent(const string& nume, const string& numeFisier);

    void afiseazaEvenimente() const;
    void golesteEvenimente(); // Golește lista pentru schimbarea orașului
};

#endif