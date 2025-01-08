#include <iostream>
#include "GestionareAngajati.h"

using namespace std;

void afiseazaMeniuCafenea() {
    cout << "\nMeniu Cafenea\n";
    cout << "1. Gestionare angajati\n";
    cout << "2. Iesire\n";
    cout << "Alege o optiune: ";
}

void afiseazaMeniuGestionareAngajati() {
    cout << "\nMeniu Gestionare Angajati\n";
    cout << "1. Adauga angajat\n";
    cout << "2. Sterge angajat\n";
    cout << "3. Afiseaza angajati\n";
    cout << "4. Iesire\n";
    cout << "Alege o optiune: ";
}

int main() {
    int optiuneCafenea;
    GestionareAngajati gestionare;

    do {
        cout << "\nSelecteaza cafeneaua:\n";
        cout << "1. Bucuresti\n";
        cout << "2. Cluj\n";
        cout << "3. Timisoara\n";
        cout << "4. Iasi\n";
        cout << "5. Brasov\n";
        cout << "Alege o optiune: ";
        cin >> optiuneCafenea;
        cin.ignore();  // Curățăm buffer-ul

        string locatie;
        switch (optiuneCafenea) {
            case 1: locatie = "Bucuresti"; break;
            case 2: locatie = "Cluj"; break;
            case 3: locatie = "Timisoara"; break;
            case 4: locatie = "Iasi"; break;
            case 5: locatie = "Brasov"; break;
            default:
                cout << "Optiune invalida!\n";
                continue;
        }

        // Citim angajații din fișierul CSV corespunzător locației selectate
        gestionare.schimbaOras(locatie);

        string caleFisier = "Orase/" + locatie + "/angajati.csv";
        gestionare.citesteDinCSV(caleFisier);

        // Afișăm meniul de gestionare angajați pentru locația selectată
        int optiuneAngajati;
        do {
            afiseazaMeniuGestionareAngajati();
            cin >> optiuneAngajati;
            cin.ignore(); // Curățăm buffer-ul

            switch (optiuneAngajati) {
                case 1: {
                    // Adăugare angajat
                    string nume, functie;
                    int oraInceput, oraSfarsit;
                    double salariu;
                    cout << "Introduceti numele angajatului: ";
                    getline(cin, nume);
                    cout << "Introduceti functia (Barista, Manager, Ospatar): ";
                    getline(cin, functie);
                    cout << "Introduceti ora de inceput a turei: ";
                    cin >> oraInceput;
                    cout << "Introduceti ora de sfarsit a turei: ";
                    cin >> oraSfarsit;
                    cout << "Introduceti salariul zilnic al angajatului: ";
                    cin >> salariu;
                    cin.ignore(); // Curățăm buffer-ul

                    if (functie == "Barista") {
                        gestionare.adaugaAngajat(make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu),caleFisier);
                    } else if (functie == "Manager") {
                        gestionare.adaugaAngajat(make_unique<Manager>(nume, oraInceput, oraSfarsit, salariu),caleFisier);
                    } else if (functie == "Ospatar") {
                        gestionare.adaugaAngajat(make_unique<Ospatar>(nume, oraInceput, oraSfarsit, salariu),caleFisier);
                    } else {
                        cout << "Functie necunoscuta!\n";
                    }

                    // Scriem modificările în fișierul CSV corespunzător locației
                    gestionare.scrieInCSV(caleFisier);
                    break;
                }
                case 2: {
                    // Ștergere angajat
                    string nume;
                    cout << "Introduceti numele angajatului de sters: ";
                    getline(cin, nume);

                    gestionare.stergeAngajat(nume,caleFisier); // Ștergere angajat din locația respectivă
                    gestionare.scrieInCSV(caleFisier); // Scriem modificările în fișierul CSV corespunzător locației
                    break;
                }
                case 3:
                    // Afișare angajați
                    gestionare.afiseazaAngajati();
                    break;
                case 4:
                    cout << "Iesire din gestionarea angajatilor.\n";
                    break;
                default:
                    cout << "Optiune invalida, incercati din nou.\n";
                    break;
            }
        } while (optiuneAngajati != 4);

    } while (optiuneCafenea != 0); // Sau orice altă opțiune de ieșire

    return 0;
}