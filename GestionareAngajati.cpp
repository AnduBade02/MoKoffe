#include "GestionareAngajati.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Implementare clasa Angajat
Angajat::Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit)
        : nume(nume), functie(functie), oraInceput(oraInceput), oraSfarsit(oraSfarsit) {}

void Angajat::afiseazaDetalii() const {
    std::cout << "Nume: " << nume << ", Funcție: " << functie
              << ", Tura: " << oraInceput << " - " << oraSfarsit << std::endl;
}

string Angajat::getNume() const {
    return nume;
}

string Angajat::getFunctie() const {
    return functie;
}

// Implementare clase derivate
Barista::Barista(const string& nume, int oraInceput, int oraSfarsit)
        : Angajat(nume, "Barista", oraInceput, oraSfarsit) {}

void Barista::afiseazaDetalii() const {
    std::cout << "[Barista] ";
    Angajat::afiseazaDetalii();
}

Manager::Manager(const std::string& nume, int oraInceput, int oraSfarsit)
        : Angajat(nume, "Manager", oraInceput, oraSfarsit) {}

void Manager::afiseazaDetalii() const {
    std::cout << "[Manager] ";
    Angajat::afiseazaDetalii();
}

Ospatar::Ospatar(const string& nume, int oraInceput, int oraSfarsit)
        : Angajat(nume, "Ospatar", oraInceput, oraSfarsit) {}

void Ospatar::afiseazaDetalii() const {
    std::cout << "[Ospătar] ";
    Angajat::afiseazaDetalii();
}

// Implementare GestionareAngajati
void GestionareAngajati::adaugaAngajat(std::unique_ptr<Angajat> angajat) {
    angajati.push_back(std::move(angajat));
}

void GestionareAngajati::stergeAngajat(const string& nume) {
    auto it = std::remove_if(angajati.begin(), angajati.end(),
                             [&nume](const std::unique_ptr<Angajat>& angajat) {
                                 return angajat->getNume() == nume;
                             });

    if (it != angajati.end()) {
        angajati.erase(it, angajati.end());
        cout << "Angajatul \"" << nume << "\" a fost șters.\n";
    } else {
        cout << "Angajatul \"" << nume << "\" nu a fost găsit.\n";
    }
}

void GestionareAngajati::afiseazaAngajati() const {
    cout << "Lista angajaților:\n";
    for (const auto& angajat : angajati) {
        angajat->afiseazaDetalii();
    }
}

void GestionareAngajati::citesteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    string linie, nume, functie;
    int oraInceput, oraSfarsit;

    // Ignorăm prima linie (header-ul)
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, nume, ',');
        getline(stream, functie, ',');
        stream >> oraInceput;
        stream.ignore(1); // Ignorăm separatorul ','
        stream >> oraSfarsit;

        if (functie == "Barista") {
            adaugaAngajat(make_unique<Barista>(nume, oraInceput, oraSfarsit));
        } else if (functie == "Manager") {
            adaugaAngajat(make_unique<Manager>(nume, oraInceput, oraSfarsit));
        } else if (functie == "Ospatar") {
            adaugaAngajat(make_unique<Ospatar>(nume, oraInceput, oraSfarsit));
        } else {
            cerr << "Funcție necunoscută pentru angajatul " << nume << endl;
        }
    }

    fisier.close();
    cout << "Angajații au fost încărcați din fișierul " << numeFisier << endl;
}