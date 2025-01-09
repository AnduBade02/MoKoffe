#include "GestionareEvenimente.h"
#include <fstream>
#include <sstream>

// Implementare clasa Event
Event::Event(const string& nume, double pret)
        : nume(nume), pret(pret) {}

const string& Event::getNume() const {
    return nume;
}

double Event::getPret() const {
    return pret;
}

void Event::afiseazaDetalii() const {
    cout << "Event: " << nume << ", Pret: " << pret << endl;
}

// Implementare clasa GestionareEvenimente
void GestionareEvenimente::citesteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul evenimente: " + numeFisier);
    }

    string linie, nume;
    double pret;

    // Ignorăm header-ul
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, nume, ',');
        stream >> pret;

        evenimente.emplace_back(nume, pret);
    }

    fisier.close();
    cout << "Evenimentele au fost încărcate din fișierul " << numeFisier << endl;
}

void GestionareEvenimente::scrieInCSV(const string& numeFisier) const {
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    fisier << "Event,Pret\n";
    for (const auto& event : evenimente) {
        fisier << event.getNume() << ","
               << event.getPret() << "\n";
    }

    fisier.close();
    cout << "Fișierul CSV a fost actualizat.\n";
}

void GestionareEvenimente::adaugaEvent(const Event& event, const string& numeFisier) {
    // Verificăm dacă evenimentul există deja
    bool evenimentExistent = false;
    for (const auto& e : evenimente) {
        if (e.getNume() == event.getNume()) {
            evenimentExistent = true;
            break;
        }
    }

    // Dacă evenimentul nu există, adăugăm evenimentul nou și actualizăm fișierul
    if (!evenimentExistent) {
        evenimente.push_back(event);
    } else {
        // Dacă evenimentul există, îl înlocuim cu cel nou
        for (auto& e : evenimente) {
            if (e.getNume() == event.getNume()) {
                e = event; // Înlocuim evenimentul existent cu cel nou
                break;
            }
        }
    }

    // Scriem din nou toate evenimentele în fișierul CSV
    scrieInCSV(numeFisier);
}

void GestionareEvenimente::eliminaEvent(const string& nume, const string& numeFisier) {
    auto it = remove_if(evenimente.begin(), evenimente.end(),
                        [&nume](const Event& event) {
                            return event.getNume() == nume;
                        });

    if (it != evenimente.end()) {
        evenimente.erase(it, evenimente.end());
        scrieInCSV(numeFisier);
        cout << "Eventul \"" << nume << "\" a fost șters.\n";
    } else {
        throw invalid_argument("Eventul cu numele " + nume + " nu a fost găsit.");
    }
}

void GestionareEvenimente::afiseazaEvenimente() const {
    for (const auto& event : evenimente) {
        event.afiseazaDetalii();
    }
}

void GestionareEvenimente::golesteEvenimente() {
    evenimente.clear();
}