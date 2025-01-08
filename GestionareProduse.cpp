#include "GestionareProduse.h"
#include <fstream>
#include <sstream>

// Implementare clasa Produs
Produs::Produs(const string& nume, int stoc, double costAchizitie, double costVanzare)
        : nume(nume), stoc(stoc), costAchizitie(costAchizitie), costVanzare(costVanzare) {}

const string& Produs::getNume() const {
    return nume;
}

int Produs::getStoc() const {
    return stoc;
}

double Produs::getCostAchizitie() const {
    return costAchizitie;
}

double Produs::getCostVanzare() const {
    return costVanzare;
}

void Produs::setStoc(int nouStoc) {
    stoc = nouStoc;
}

void Produs::afiseazaDetalii() const {
    cout << "Produs: " << nume << ", Stoc: " << stoc
         << ", Cost Achizitie: " << costAchizitie
         << ", Cost Vanzare: " << costVanzare << endl;
}

// Implementare clasa GestionareProduse
void GestionareProduse::citesteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    string linie, nume;
    int stoc;
    double costAchizitie, costVanzare;

    // Ignorăm header-ul
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, nume, ',');
        stream >> stoc;
        stream.ignore(1); // Separator ','
        stream >> costAchizitie;
        stream.ignore(1);
        stream >> costVanzare;

        produse.emplace_back(nume, stoc, costAchizitie, costVanzare);
    }

    fisier.close();
    cout << "Produsele au fost încărcate din fișierul " << numeFisier << endl;
}

void GestionareProduse::scrieInCSV(const string& numeFisier) const {
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    fisier << "produse,stoc,costAchizitie,costVanzare\n";
    for (const auto& produs : produse) {
        fisier << produs.getNume() << ","
               << produs.getStoc() << ","
               << produs.getCostAchizitie() << ","
               << produs.getCostVanzare() << "\n";
    }

    fisier.close();
    cout << "Fișierul CSV a fost actualizat.\n";
}

void GestionareProduse::adaugaProdus(const Produs& produs, const string& numeFisier) {
    // Verificăm dacă produsul există deja
    bool produsExistente = false;
    for (const auto& p : produse) {
        if (p.getNume() == produs.getNume()) {
            produsExistente = true;
            break;
        }
    }

    // Dacă produsul nu există, adăugăm produsul nou și actualizăm fișierul
    if (!produsExistente) {
        produse.push_back(produs);
    } else {
        // Dacă produsul există, îl înlocuim cu produsul introdus
        for (auto& p : produse) {
            if (p.getNume() == produs.getNume()) {
                p = produs; // Înlocuim produsul existent cu cel nou
                break;
            }
        }
    }

    // Scriem din nou toate produsele în fișierul CSV
    scrieInCSV(numeFisier);
}

void GestionareProduse::eliminaProdus(const string& nume, const string& numeFisier) {
    auto it = remove_if(produse.begin(), produse.end(),
                        [&nume](const Produs& produs) {
                            return produs.getNume() == nume;
                        });

    if (it != produse.end()) {
        produse.erase(it, produse.end());
        scrieInCSV(numeFisier);
        cout << "Produsul \"" << nume << "\" a fost șters.\n";
    } else {
        cout << "Produsul \"" << nume << "\" nu a fost găsit.\n";
    }
}

void GestionareProduse::afiseazaProduse() const {
    for (const auto& produs : produse) {
        produs.afiseazaDetalii();
    }
}

void GestionareProduse::golesteProduse() {
    produse.clear();
    profitZilnic = 0;
}