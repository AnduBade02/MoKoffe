#ifndef GESTIONARE_ANGAJATI_H
#define GESTIONARE_ANGAJATI_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

// Clasa de bază Angajat
class Angajat {
protected:
    string nume;         // Încapsulare: Atributele sunt protejate pentru a controla accesul
    string functie;      // Încapsulare
    int oraInceput;      // Încapsulare
    int oraSfarsit;      // Încapsulare
    double salariu;      // Încapsulare

public:
    // Constructor pentru inițializarea atributelor de bază
    Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit, double salariu); // Constructori

    virtual ~Angajat() = default; // Destructor virtual pentru Polimorfism

    virtual void afiseazaDetalii() const; // Polimorfism: Metodă virtuală suprascrisă în clasele derivate
    double getSalariu() const;           // Încapsulare: Acces controlat la atributul salariu
    string getNume() const;              // Încapsulare
    string getFunctie() const;           // Încapsulare
    int getOraInceput() const;           // Încapsulare
    int getOraSfarsit() const;           // Încapsulare
};

// Clase derivate
class Barista : public Angajat { // Moștenire: Barista moștenește Angajat
public:
    Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu); // Constructori
    void afiseazaDetalii() const override; // Polimorfism: Suprascrierea metodei virtuale
};

class Manager : public Angajat { // Moștenire
public:
    Manager(const string& nume, int oraInceput, int oraSfarsit, double salariu); // Constructori
    void afiseazaDetalii() const override; // Polimorfism
};

class Ospatar : public Angajat { // Moștenire
public:
    Ospatar(const string& nume, int oraInceput, int oraSfarsit, double salariu); // Constructori
    void afiseazaDetalii() const override; // Polimorfism
};

// Gestionare Angajați
class GestionareAngajati {
private:
    vector<unique_ptr<Angajat>> angajati; // Design Pattern: Utilizarea smart pointers (RAII)
    string currentCity;                   // Încapsulare: Atribut privat

public:
    // Factory Method
    static unique_ptr<Angajat> creeazaAngajat( // Design Pattern: Factory Method pentru crearea obiectelor
            const string& tip,
            const string& nume,
            int oraInceput,
            int oraSfarsit,
            double salariu
    ) {
        if (tip == "Barista") {
            return make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu); // Polimorfism
        } else if (tip == "Manager") {
            return make_unique<Manager>(nume, oraInceput, oraSfarsit, salariu); // Polimorfism
        } else if (tip == "Ospatar") {
            return make_unique<Ospatar>(nume, oraInceput, oraSfarsit, salariu); // Polimorfism
        } else {
            throw invalid_argument("Tipul de angajat nu este valid: " + tip); // Exceptions
        }
    }

    void schimbaOras(const string& oras); // Încapsulare
    void adaugaAngajat(unique_ptr<Angajat> angajat, const string& numeFisier); // Design Pattern: Smart Pointer
    void stergeAngajat(const string& nume, const string& numeFisier);          // Încapsulare
    void afiseazaAngajati() const;                                            // Polimorfism
    void citesteDinCSV(const string& numeFisier);                             // Încapsulare
    void scrieInCSV(const string& numeFisier);                                // Încapsulare
    double calculeazaTotalSalarii() const;                                    // Încapsulare
};

#endif