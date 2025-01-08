#ifndef GESTIONARE_ANGAJATI_H
#define GESTIONARE_ANGAJATI_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

// Clasa de bază Angajat
class Angajat {
protected:
    string nume;
    string functie;
    int oraInceput;
    int oraSfarsit;
    double salariu;

public:
    Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit, double salariu);
    virtual ~Angajat() = default;

    virtual void afiseazaDetalii() const;
    double getSalariu() const;
    string getNume() const;
    string getFunctie() const;
    int getOraInceput() const;
    int getOraSfarsit() const;
};

// Clase derivate
class Barista : public Angajat {
public:
    Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu);
    void afiseazaDetalii() const override;
};

class Manager : public Angajat {
public:
    Manager(const string& nume, int oraInceput, int oraSfarsit, double salariu);
    void afiseazaDetalii() const override;
};

class Ospatar : public Angajat {
public:
    Ospatar(const string& nume, int oraInceput, int oraSfarsit, double salariu);
    void afiseazaDetalii() const override;
};

// Gestionare Angajați
class GestionareAngajati {
private:
    vector<unique_ptr<Angajat>> angajati;
    string currentCity;  // Orașul curent

public:
    void schimbaOras(const string& oras);
    void adaugaAngajat(unique_ptr<Angajat> angajat, const string& numeFisier);
    void stergeAngajat(const string& nume, const string& numeFisier);
    void afiseazaAngajati() const;
    void citesteDinCSV(const string& numeFisier);
    void scrieInCSV(const string& numeFisier);
};

#endif