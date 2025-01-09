#include <iostream>
#include "GestionareAngajati.h"
#include "GestionareProduse.h"
#include "GestionareFinante.h"

using namespace std;

void afiseazaMeniuGestionareAngajati() {
    cout << "\nMeniu Gestionare Angajati (Daca doriti sa modificati detaliile unui angajat existent, introduceti numele acestuia)\n";
    cout << "1. Adauga/Modifica angajat\n";
    cout << "2. Sterge angajat\n";
    cout << "3. Afiseaza angajati\n";
    cout << "4. Iesire\n";
    cout << "Alege o optiune: ";
}

void afiseazaMeniuGestionareProduse() {
    cout << "\nMeniu Gestionare Produse\n";
    cout << "1. Adauga/Modifica produs (Daca doriti sa modificati detaliile unui produs existent, introduceti numele acestuia)\n";
    cout << "2. Sterge produs\n";
    cout << "3. Afiseaza produse\n";
    cout << "4. Iesire\n";
    cout << "Alege o optiune: ";
}

void afiseazaMeniuCafenea() {
    cout << "\nMeniu Cafenea\n";
    cout << "1. Gestionare angajati\n";
    cout << "2. Gestionare produse\n";
    cout << "3. Gestionare finante\n";
    cout << "4. Iesire\n";
    cout << "Alege o optiune: ";
}

void afiseazaMeniuGestionareFinante() {
    cout << "\nMeniu Gestionare Finante\n";
    cout << "1. Genereaza raport financiar\n";
    cout << "2. Afiseaza raport financiar\n";
    cout << "3. Iesire\n";
    cout << "Alege o optiune: ";
}

int main() {
    try {
        int optiuneCafenea;
        GestionareAngajati gestionareAngajati;
        GestionareProduse gestionareProduse;
        GestionareFinante gestionareFinante;

        do {
            cout << "\nSelecteaza cafeneaua:\n";
            cout << "1. Bucuresti\n";
            cout << "2. Cluj\n";
            cout << "3. Timisoara\n";
            cout << "4. Iasi\n";
            cout << "5. Brasov\n";
            cout << "0. Iesire\n";
            cout << "Alege o optiune: ";
            cin >> optiuneCafenea;
            cin.ignore();

            if (optiuneCafenea == 0) {
                cout << "Iesire din program.\n";
                break;
            }

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

            // Setăm orașul pentru gestionare
            gestionareAngajati.schimbaOras(locatie);
            gestionareProduse.golesteProduse();

            string caleAngajati = "Orase/" + locatie + "/angajati.csv";
            string caleProduse = "Orase/" + locatie + "/produse.csv";
            string caleComenzi = "Orase/" + locatie + "/comenzi.csv";
            string caleEvenimente = "Orase/" + locatie + "/evenimente.csv";
            string caleRaport = "Orase/" + locatie + "/raport.csv";

            gestionareAngajati.citesteDinCSV(caleAngajati);
            gestionareProduse.citesteDinCSV(caleProduse);
            gestionareFinante.citesteComenziDinCSV(caleComenzi);
            gestionareFinante.citesteEvenimenteDinCSV(caleEvenimente);

            int optiuneMeniu;
            do {
                afiseazaMeniuCafenea();
                cin >> optiuneMeniu;
                cin.ignore();

                switch (optiuneMeniu) {
                    case 1: {
                        int optiuneAngajati;
                        do {
                            afiseazaMeniuGestionareAngajati();
                            cin >> optiuneAngajati;
                            cin.ignore(); // Curățăm buffer-ul

                            switch (optiuneAngajati) {
                                case 1: {
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

                                    try {
                                        auto angajat = GestionareAngajati::creeazaAngajat(functie, nume, oraInceput, oraSfarsit, salariu);
                                        gestionareAngajati.adaugaAngajat(move(angajat), caleAngajati);
                                    } catch (const invalid_argument& e) {
                                        cout << "Eroare: " << e.what() << endl;
                                    }
                                    break;
                                }
                                case 2: {
                                    string nume;
                                    cout << "Introduceti numele angajatului de sters: ";
                                    getline(cin, nume);

                                    gestionareAngajati.stergeAngajat(nume, caleAngajati);
                                    break;
                                }
                                case 3:
                                    gestionareAngajati.afiseazaAngajati();
                                    break;
                                case 4:
                                    cout << "Iesire din gestionarea angajatilor.\n";
                                    break;
                                default:
                                    cout << "Optiune invalida, incercati din nou.\n";
                                    break;
                            }
                        } while (optiuneAngajati != 4);
                        break;
                    }
                    case 2: {
                        int optiuneProduse;
                        do {
                            afiseazaMeniuGestionareProduse();
                            cin >> optiuneProduse;
                            cin.ignore(); // Curățăm buffer-ul

                            switch (optiuneProduse) {
                                case 1: {
                                    string nume;
                                    int stoc;
                                    double costAchizitie, costVanzare;
                                    cout << "Introduceti numele produsului: ";
                                    getline(cin, nume);
                                    cout << "Introduceti stocul: ";
                                    cin >> stoc;
                                    cout << "Introduceti costul de achizitie: ";
                                    cin >> costAchizitie;
                                    cout << "Introduceti costul de vanzare: ";
                                    cin >> costVanzare;

                                    gestionareProduse.adaugaProdus(Produs(nume, stoc, costAchizitie, costVanzare), caleProduse);
                                    break;
                                }
                                case 2: {
                                    string nume;
                                    cout << "Introduceti numele produsului de sters: ";
                                    getline(cin, nume);

                                    gestionareProduse.eliminaProdus(nume, caleProduse);
                                    break;
                                }
                                case 3:
                                    gestionareProduse.afiseazaProduse();
                                    break;
                                case 4:
                                    cout << "Iesire din gestionarea produselor.\n";
                                    break;
                                default:
                                    cout << "Optiune invalida, incercati din nou.\n";
                                    break;
                            }
                        } while (optiuneProduse != 4);
                        break;
                    }
                    case 3: {
                        int optiuneFinante;
                        do {
                            afiseazaMeniuGestionareFinante();
                            cin >> optiuneFinante;
                            cin.ignore();

                            switch (optiuneFinante) {
                                case 1: {
                                    gestionareFinante.genereazaRaportCSV(caleRaport, gestionareProduse, gestionareAngajati);
                                    cout << "Raportul financiar a fost generat cu succes.\n";
                                    break;
                                }
                                case 2: {
                                    ifstream raport(caleRaport);
                                    if (!raport.is_open()) {
                                        cout << "Raportul nu a fost generat inca.\n";
                                    } else {
                                        string linie;
                                        cout << "\nRaport Financiar:\n";
                                        while (getline(raport, linie)) {
                                            cout << linie << endl;
                                        }
                                        raport.close();
                                    }
                                    break;
                                }
                                case 3:
                                    cout << "Iesire din gestionarea finantelor.\n";
                                    break;
                                default:
                                    cout << "Optiune invalida, incercati din nou.\n";
                                    break;
                            }
                        } while (optiuneFinante != 3);
                        break;
                    }
                    case 4:
                        cout << "Iesire din meniul cafenelei.\n";
                        break;
                    default:
                        cout << "Optiune invalida, incercati din nou.\n";
                        break;
                }
            } while (optiuneMeniu != 4);
        } while (optiuneCafenea != 0);
    } catch (const runtime_error& e) {
        cerr << "Eroare: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cerr << "Argument invalid: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Eroare generala: " << e.what() << endl;
    }
    return 0;
}