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

public:
    Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit);
    virtual ~Angajat() = default;

    virtual void afiseazaDetalii() const;
    std::string getNume() const;
    std::string getFunctie() const;
};

// Clase derivate
class Barista : public Angajat {
public:
    Barista(const string& nume, int oraInceput, int oraSfarsit);
    void afiseazaDetalii() const override;
};

class Manager : public Angajat {
public:
    Manager(const string& nume, int oraInceput, int oraSfarsit);
    void afiseazaDetalii() const override;
};

class Ospatar : public Angajat {
public:
    Ospatar(const string& nume, int oraInceput, int oraSfarsit);
    void afiseazaDetalii() const override;
};

// Gestionare Angajați
class GestionareAngajati {
private:
    std::vector<std::unique_ptr<Angajat>> angajati;

public:
    void adaugaAngajat(unique_ptr<Angajat> angajat);
    void stergeAngajat(const string& nume);
    void afiseazaAngajati() const;
    void citesteDinCSV(const std::string& numeFisier);
};

#endif