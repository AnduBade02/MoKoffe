#include "GestionareAngajati.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Implementare clasa Angajat
Angajat::Angajat(const string& nume, const string& functie, int oraInceput, int oraSfarsit, double salariu)
        : nume(nume), functie(functie), oraInceput(oraInceput), oraSfarsit(oraSfarsit), salariu(salariu) {} // Constructori

void Angajat::afiseazaDetalii() const { // Polimorfism: Metoda virtuală care poate fi suprascrisă
    cout << "Nume: " << nume << ", Functie: " << functie
         << ", Tura: " << oraInceput << " - " << oraSfarsit
         << ", Salariu: " << salariu << endl;
}

double Angajat::getSalariu() const { // Încapsulare: Acces controlat la atributul salariu
    return salariu;
}

string Angajat::getNume() const { // Încapsulare
    return nume;
}

string Angajat::getFunctie() const { // Încapsulare
    return functie;
}

int Angajat::getOraInceput() const { // Încapsulare
    return oraInceput;
}

int Angajat::getOraSfarsit() const { // Încapsulare
    return oraSfarsit;
}


// Implementare clase derivate
Barista::Barista(const string& nume, int oraInceput, int oraSfarsit, double salariu)
        : Angajat(nume, "Barista", oraInceput, oraSfarsit, salariu) {} // Constructori și Moștenire

void Barista::afiseazaDetalii() const { // Polimorfism: Suprascrierea metodei afiseazaDetalii
    cout << "[Barista] ";
    Angajat::afiseazaDetalii();
}

Manager::Manager(const string& nume, int oraInceput, int oraSfarsit, double salariu)
        : Angajat(nume, "Manager", oraInceput, oraSfarsit, salariu) {} // Constructori și Moștenire

void Manager::afiseazaDetalii() const { // Polimorfism
    cout << "[Manager] ";
    Angajat::afiseazaDetalii();
}

Ospatar::Ospatar(const string& nume, int oraInceput, int oraSfarsit, double salariu)
        : Angajat(nume, "Ospatar", oraInceput, oraSfarsit, salariu) {} // Constructori și Moștenire

void Ospatar::afiseazaDetalii() const { // Polimorfism
    cout << "[Ospătar] ";
    Angajat::afiseazaDetalii();
}

// Implementare GestionareAngajati
void GestionareAngajati::adaugaAngajat(std::unique_ptr<Angajat> angajat, const string& numeFisier) {
    // Design Pattern: Utilizarea smart pointers (RAII)
    // Exceptions: Verificăm și gestionăm existența unui angajat

    bool angajatExistent = false;
    for (const auto& a : angajati) {
        if (a->getNume() == angajat->getNume()) {
            angajatExistent = true;
            break;
        }
    }

    if (!angajatExistent) {
        angajati.push_back(move(angajat)); // Design Pattern: Transfer de proprietate cu smart pointers
    } else {
        for (auto& a : angajati) {
            if (a->getNume() == angajat->getNume()) {
                a = move(angajat);
                break;
            }
        }
    }

    scrieInCSV(numeFisier); // Abstracție: Scrierea într-un fișier CSV
}

void GestionareAngajati::stergeAngajat(const string& nume, const string& numeFisier) {
    auto it = remove_if(angajati.begin(), angajati.end(),
                        [&nume](const std::unique_ptr<Angajat>& angajat) {
                            return angajat->getNume() == nume;
                        });

    if (it != angajati.end()) {
        angajati.erase(it, angajati.end());
        cout << "Angajatul \"" << nume << "\" a fost șters.\n";
        scrieInCSV(numeFisier); // Abstracție
    } else {
        throw invalid_argument("Angajatul cu numele " + nume + " nu a fost gasit."); // Exceptions
    }
}

void GestionareAngajati::afiseazaAngajati() const {
    cout << "Lista angajaților din orasul " << currentCity << ":\n";
    for (const auto& angajat : angajati) {
        angajat->afiseazaDetalii(); // Polimorfism: Apelare dinamică a metodei afiseazaDetalii
    }
}

void GestionareAngajati::citesteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul angajati: " + numeFisier); // Exceptions
    }

    string linie, nume, functie, oras;
    int oraInceput, oraSfarsit;
    double salariu;

    getline(fisier, linie); // Abstracție: Gestionarea fișierelor CSV

    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, nume, ',');
        getline(stream, functie, ',');
        stream >> oraInceput;
        stream.ignore(1);
        stream >> oraSfarsit;
        stream.ignore(1);
        stream >> salariu;
        stream.ignore(1);

        getline(stream, oras);
        schimbaOras(oras);

        if (functie == "Barista") {
            adaugaAngajat(make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu), numeFisier); // Design Pattern
        } else if (functie == "Manager") {
            adaugaAngajat(make_unique<Manager>(nume, oraInceput, oraSfarsit, salariu), numeFisier); // Design Pattern
        } else if (functie == "Ospatar") {
            adaugaAngajat(make_unique<Ospatar>(nume, oraInceput, oraSfarsit, salariu), numeFisier); // Design Pattern
        } else {
            cerr << "Funcție necunoscută pentru angajatul " << nume << endl;
        }
    }

    fisier.close();
    cout << "Angajații au fost încărcați din fișierul " << numeFisier << endl;
}

void GestionareAngajati::scrieInCSV(const string& numeFisier) {
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    fisier << "Nume,Functie,OraInceput,OraSfarsit,Salariu\n";

    for (const auto& angajat : angajati) {
        fisier << angajat->getNume() << ","
               << angajat->getFunctie() << ","
               << angajat->getOraInceput() << ","
               << angajat->getOraSfarsit() << ","
               << angajat->getSalariu() << "\n";
    }

    fisier.close();
    cout << "Fișierul CSV a fost actualizat.\n";
}

void GestionareAngajati::schimbaOras(const string& oras) {
    if (oras != currentCity) {
        currentCity = oras; // Încapsulare: Atribut protejat
        angajati.clear();
        cout << "Orașul a fost schimbat în: " << oras << endl;
    }
}

double GestionareAngajati::calculeazaTotalSalarii() const {
    double totalSalarii = 0;

    for (const auto& angajat : angajati) {
        totalSalarii += angajat->getSalariu(); // Încapsulare: Acces controlat la salariu
    }

    return totalSalarii;
}