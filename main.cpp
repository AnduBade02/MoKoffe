#include <iostream>
#include "GestionareAngajati.h"
#include "GestionareProduse.h"

using namespace std;

void afiseazaMeniuCafenea() {
    cout << "\nMeniu Cafenea\n";
    cout << "1. Gestionare angajati\n";
    cout << "2. Gestionare produse\n";
    cout << "3. Iesire\n";
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

void afiseazaMeniuGestionareProduse() {
    cout << "\nMeniu Gestionare Produse\n";
    cout << "1. Adauga produs\n";
    cout << "2. Sterge produs\n";
    cout << "3. Afiseaza produse\n";
    cout << "4. Iesire\n";
    cout << "Alege o optiune: ";
}

int main() {
    int optiuneCafenea;
    GestionareAngajati gestionareAngajati;
    GestionareProduse gestionareProduse;

    do {
        cout << "\nSelecteaza cafeneaua:\n";
        cout << "1. Bucuresti\n";
        cout << "2. Cluj\n";
        cout << "3. Timisoara\n";
        cout << "4. Iasi\n";
        cout << "5. Brasov\n";
        cout << "0. Iesire\n";  // Opțiune de ieșire
        cout << "Alege o optiune: ";
        cin >> optiuneCafenea;
        cin.ignore();  // Curățăm buffer-ul

        if (optiuneCafenea == 0) {
            cout << "Iesire din program.\n";
            break;  // Ieșim din bucla principală
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

        // Setăm orașul pentru ambele gestionări
        gestionareAngajati.schimbaOras(locatie);
        gestionareProduse.golesteProduse();

        string caleAngajati = "Orase/" + locatie + "/angajati.csv";
        string caleProduse = "Orase/" + locatie + "/produse.csv";

        gestionareAngajati.citesteDinCSV(caleAngajati);
        gestionareProduse.citesteDinCSV(caleProduse);

        int optiuneMeniu;
        do {
            afiseazaMeniuCafenea();
            cin >> optiuneMeniu;
            cin.ignore(); // Curățăm buffer-ul

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

                                if (functie == "Barista") {
                                    gestionareAngajati.adaugaAngajat(make_unique<Barista>(nume, oraInceput, oraSfarsit, salariu), caleAngajati);
                                } else if (functie == "Manager") {
                                    gestionareAngajati.adaugaAngajat(make_unique<Manager>(nume, oraInceput, oraSfarsit, salariu), caleAngajati);
                                } else if (functie == "Ospatar") {
                                    gestionareAngajati.adaugaAngajat(make_unique<Ospatar>(nume, oraInceput, oraSfarsit, salariu), caleAngajati);
                                } else {
                                    cout << "Functie necunoscuta!\n";
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
                case 3:
                    cout << "Iesire din meniul cafenelei.\n";
                    break;
                default:
                    cout << "Optiune invalida, incercati din nou.\n";
                    break;
            }
        } while (optiuneMeniu != 3);
    } while (optiuneCafenea != 0);

    return 0;
}