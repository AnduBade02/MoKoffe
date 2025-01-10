#include "GestionareEvenimente.h"
#include <fstream>
#include <sstream>

// Implementare clasa Event
Event::Event(const string& nume, double pret)
        : nume(nume), pret(pret) {}  // Constructorul parametrizat al clasei Event (constructori)

// Returnează referința constantă la numele evenimentului
const string& Event::getNume() const {
    return nume;  // Încapsulare: metoda de acces pentru atributul 'nume'
}

// Returnează prețul evenimentului
double Event::getPret() const {
    return pret;  // Încapsulare: metoda de acces pentru atributul 'pret'
}

// Afișează detalii despre eveniment (nume și preț)
void Event::afiseazaDetalii() const {
    cout << "Event: " << nume << ", Pret: " << pret << endl;  // Polimorfism: se afișează detaliile unui eveniment
}

// Implementare clasa GestionareEvenimente
void GestionareEvenimente::citesteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul evenimente: " + numeFisier);  // Excepții: aruncă excepție în caz de eroare la deschiderea fișierului
    }

    string linie, nume;
    double pret;

    // Ignorăm header-ul
    getline(fisier, linie);

    // Citim fiecare linie din fișier, împărțind valorile de pe fiecare linie pe baza separatorului ','
    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, nume, ',');
        stream >> pret;

        // Adăugăm evenimentul citit în lista de evenimente
        evenimente.emplace_back(nume, pret);  // Folosim std::vector<Event> (vector este un template)
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
    // Iterăm prin lista de evenimente și le scriem în fișier
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
        evenimente.push_back(event);  // Folosim std::vector<Event> (vector este un template)
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
    // Căutăm evenimentul cu numele specificat și îl eliminăm din lista de evenimente
    auto it = remove_if(evenimente.begin(), evenimente.end(),
                        [&nume](const Event& event) {
                            return event.getNume() == nume;
                        });

    if (it != evenimente.end()) {
        evenimente.erase(it, evenimente.end());
        scrieInCSV(numeFisier);
        cout << "Eventul \"" << nume << "\" a fost șters.\n";
    } else {
        throw invalid_argument("Eventul cu numele " + nume + " nu a fost găsit.");  // Excepții: aruncă excepție dacă evenimentul nu este găsit
    }
}

void GestionareEvenimente::afiseazaEvenimente() const {
    // Afișăm detaliile fiecărui eveniment
    for (const auto& event : evenimente) {
        event.afiseazaDetalii();  // Polimorfism: afișează detaliile unui eveniment
    }
}

void GestionareEvenimente::golesteEvenimente() {
    // Golește lista de evenimente
    evenimente.clear();  // Încapsulare: modifică intern vectorul de evenimente
}