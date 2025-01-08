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
    string oras;

public:
    Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit, double salariu, const string& oras);
    virtual ~Angajat() = default;

    virtual void afiseazaDetalii() const;
    double getSalariu() const;
    string getNume() const;
    string getFunctie() const;
    int getOraInceput() const;
    int getOraSfarsit() const;
    string getOras() const;
};

// Clase derivate
class Barista : public Angajat {
public:
    Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu, const string& oras);
    void afiseazaDetalii() const override;
};

class Manager : public Angajat {
public:
    Manager(const string& nume, int oraInceput, int oraSfarsit, double salariu, const string& oras);
    void afiseazaDetalii() const override;
};

class Ospatar : public Angajat {
public:
    Ospatar(const string& nume, int oraInceput, int oraSfarsit, double salariu, const string& oras);
    void afiseazaDetalii() const override;
};

// Gestionare Angajați
class GestionareAngajati {
private:
    std::vector<std::unique_ptr<Angajat>> angajati;

public:
    void adaugaAngajat(unique_ptr<Angajat> angajat);
    void stergeAngajat(const string& nume);
    void afiseazaAngajati(const string& orasSelectat) const;
    void citesteDinCSV(const string& numeFisier);
    void scrieInCSV(const string& numeFisier);
    void afiseazaAngajatiDinOras(const string& oras) const; // Afișare angajați dintr-un anumit oraș
};

#endif