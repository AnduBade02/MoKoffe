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
    string currentCity;

public:
    // Factory Method
    static unique_ptr<Angajat> creeazaAngajat(
            const string& tip,
            const string& nume,
            int oraInceput,
            int oraSfarsit,
            double salariu
    ) {
        if (tip == "Barista") {
            return make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu);
        } else if (tip == "Manager") {
            return make_unique<Manager>(nume, oraInceput, oraSfarsit, salariu);
        } else if (tip == "Ospatar") {
            return make_unique<Ospatar>(nume, oraInceput, oraSfarsit, salariu);
        } else {
            throw invalid_argument("Tipul de angajat nu este valid: " + tip);
        }
    }

    void schimbaOras(const string& oras);
    void adaugaAngajat(unique_ptr<Angajat> angajat, const string& numeFisier);
    void stergeAngajat(const string& nume, const string& numeFisier);
    void afiseazaAngajati() const;
    void citesteDinCSV(const string& numeFisier);
    void scrieInCSV(const string& numeFisier);
    double calculeazaTotalSalarii() const;
};

#endif