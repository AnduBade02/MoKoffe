#ifndef GESTIONARE_EVENIMENTE_H
#define GESTIONARE_EVENIMENTE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// Clasa Event reprezintă un eveniment, conținând numele și prețul acestuia
class Event {
private:
    string nume;  // Numele evenimentului
    double pret;  // Prețul evenimentului

public:
    // Constructor implicit care inițializează cu valori implicite
    Event() : nume(""), pret(0.0) {}  // Constructor implicit

    // Constructor parametrizat pentru a seta valorile numelui și prețului
    Event(const string& nume, double pret);  // Constructor parametrizat

    // Returnează referința constantă la numele evenimentului
    const string& getNume() const;  // Încapsulare: metoda de acces pentru atributul 'nume'

    // Returnează prețul evenimentului
    double getPret() const;  // Încapsulare: metoda de acces pentru atributul 'pret'

    // Afișează detalii despre eveniment (nume și preț)
    void afiseazaDetalii() const;  // Polimorfism: metodă pentru a afișa detalii
};

// Clasa GestionareEvenimente este responsabilă pentru gestionarea unui set de evenimente
class GestionareEvenimente {
private:
    // Vectorul de evenimente - Folosim un vector de obiecte de tip Event
    vector<Event> evenimente;  // Templates: vector de obiecte 'Event'

public:
    // Funcție pentru citirea evenimentelor dintr-un fișier CSV
    void citesteDinCSV(const string& numeFisier);  // Abstracție: se ascunde detaliul implementării citirii din fișier

    // Funcție pentru a scrie evenimentele în fișierul CSV
    void scrieInCSV(const string& numeFisier) const;  // Abstracție: se ascunde detaliul implementării scrierii în fișier

    // Funcție pentru a adăuga un eveniment într-un fișier
    void adaugaEvent(const Event& event, const string& numeFisier);  // Polimorfism: poate manipula obiecte de tip Event

    // Funcție pentru a elimina un eveniment dintr-un fișier pe baza numelui
    void eliminaEvent(const string& nume, const string& numeFisier);  // Excepții: aruncă excepție dacă evenimentul nu este găsit

    // Afișează lista de evenimente
    void afiseazaEvenimente() const;  // Polimorfism: permite afișarea evenimentelor din vectorul de obiecte

    // Golește lista de evenimente, utilizată în cazul schimbării orașului
    void golesteEvenimente();  // Încapsulare: metoda care manipulează intern vectorul de evenimente
};

#endif