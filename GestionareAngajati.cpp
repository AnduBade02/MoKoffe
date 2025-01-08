#include "GestionareAngajati.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Implementare clasa Angajat
Angajat::Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit, double salariu, const string& oras)
        : nume(nume), functie(functie), oraInceput(oraInceput), oraSfarsit(oraSfarsit), salariu(salariu), oras(oras) {}

void Angajat::afiseazaDetalii() const {
    cout << "Nume: " << nume << ", Functie: " << functie
         << ", Tura: " << oraInceput << " - " << oraSfarsit
         << ", Salariu: " << salariu << ", Oras: " << oras << endl;
}

double Angajat::getSalariu() const {
    return salariu;
}

string Angajat::getNume() const {
    return nume;
}

string Angajat::getFunctie() const {
    return functie;
}

int Angajat::getOraInceput() const {
    return oraInceput;
}

int Angajat::getOraSfarsit() const {
    return oraSfarsit;
}

string Angajat::getOras() const {
    return oras;
}

// Implementare clase derivate
Barista::Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu, const string& oras)
        : Angajat(nume, "Barista", oraInceput, oraSfarsit, salariu, oras) {}

void Barista::afiseazaDetalii() const {
    cout << "[Barista] ";
    Angajat::afiseazaDetalii();
}

Manager::Manager(const string& nume, int oraInceput, int oraSfarsit, double salariu, const string& oras)
        : Angajat(nume, "Manager", oraInceput, oraSfarsit, salariu, oras) {}

void Manager::afiseazaDetalii() const {
    cout << "[Manager] ";
    Angajat::afiseazaDetalii();
}

Ospatar::Ospatar(const string& nume, int oraInceput, int oraSfarsit, double salariu, const string& oras)
        : Angajat(nume, "Ospatar", oraInceput, oraSfarsit, salariu, oras) {}

void Ospatar::afiseazaDetalii() const {
    cout << "[Ospătar] ";
    Angajat::afiseazaDetalii();
}

// Implementare GestionareAngajati
void GestionareAngajati::adaugaAngajat(std::unique_ptr<Angajat> angajat) {
    angajati.push_back(move(angajat));
    scrieInCSV("angajati.csv"); // Actualizează fișierul CSV după adăugare
}

void GestionareAngajati::stergeAngajat(const string& nume) {
    auto it = remove_if(angajati.begin(), angajati.end(),
                        [&nume](const std::unique_ptr<Angajat>& angajat) {
                            return angajat->getNume() == nume;
                        });

    if (it != angajati.end()) {
        angajati.erase(it, angajati.end());
        cout << "Angajatul \"" << nume << "\" a fost șters.\n";
        scrieInCSV("angajati.csv"); // Actualizează fișierul CSV după ștergere
    } else {
        cout << "Angajatul \"" << nume << "\" nu a fost găsit.\n";
    }
}

void GestionareAngajati::afiseazaAngajati(const string& orasSelectat) const {
    cout << "Lista angajaților din orasul " << orasSelectat << ":\n";
    for (const auto& angajat : angajati) {
        if (angajat->getOras() == orasSelectat) {
            angajat->afiseazaDetalii();
        }
    }
}

void GestionareAngajati::citesteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    string linie, nume, functie, oras;
    int oraInceput, oraSfarsit;
    double salariu;

    // Ignorăm prima linie (header-ul)
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, nume, ',');
        getline(stream, functie, ',');
        stream >> oraInceput;
        stream.ignore(1); // Ignorăm separatorul ','
        stream >> oraSfarsit;
        stream.ignore(1); // Ignorăm separatorul ','
        stream >> salariu;
        stream.ignore(1); // Ignorăm separatorul ',' înainte de oraș

        // Citim orașul
        getline(stream, oras); // Orașul ar trebui să fie ultima coloană

        if (functie == "Barista") {
            adaugaAngajat(make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu, oras));
        } else if (functie == "Manager") {
            adaugaAngajat(make_unique<Manager>(nume, oraInceput, oraSfarsit, salariu, oras));
        } else if (functie == "Ospatar") {
            adaugaAngajat(make_unique<Ospatar>(nume, oraInceput, oraSfarsit, salariu, oras));
        } else {
            cerr << "Funcție necunoscută pentru angajatul " << nume << endl;
        }
    }

    fisier.close();
    cout << "Angajații au fost încărcați din fișierul " << numeFisier << endl;
}

// Funcția care scrie în fișierul CSV
void GestionareAngajati::scrieInCSV(const string& numeFisier) {
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    fisier << "Nume,Functie,OraInceput,OraSfarsit,Salariu,Oras\n"; // Header-ul fișierului CSV

    for (const auto& angajat : angajati) {
        fisier << angajat->getNume() << ","
               << angajat->getFunctie() << ","
               << angajat->getOraInceput() << ","
               << angajat->getOraSfarsit() << ","
               << angajat->getSalariu() << ","
               << angajat->getOras() << "\n";
    }

    fisier.close();
    cout << "Fișierul CSV a fost actualizat.\n";
}