#include "GestionareCSV.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Constructorul clasei GestionareCSV - Demonstrează utilizarea conceptului de Constructor
GestionareCSV::GestionareCSV(const string& limba) : limba(limba) {
    // Încapsulare: Inițializarea datelor clasei private `limba` și `hartaHeadere`
    hartaHeadere["ro"] = {
            {"angajati.csv", {"Nume", "Functie", "OraInceput", "OraSfarsit", "Salariu"}},
            {"comenzi.csv", {"CafeaEspresso", "CafeaLatte", "DesertBrownie", "BaghetaCrispy", "CiocolataCalda", "CafeaAmericano", "Fidelitate"}},
            {"evenimente.csv", {"Eveniment", "Pret"}},
            {"produse.csv", {"produse", "stoc", "costAchizitie", "costVanzare"}},
            {"raport.csv", {"venituri", "costuri", "salarii", "profit", "dataora"}}
    };

    hartaHeadere["en"] = {
            {"angajati.csv", {"Name", "Position", "StartHour", "EndHour", "Salary"}},
            {"comenzi.csv", {"EspressoCoffee", "LatteCoffee", "BrownieDessert", "CrispyBaguette", "HotChocolate", "AmericanoCoffee", "Loyalty"}},
            {"evenimente.csv", {"Event", "Price"}},
            {"produse.csv", {"products", "stock", "purchaseCost", "saleCost"}},
            {"raport.csv", {"revenue", "costs", "salaries", "profit", "datetime"}}
    };
}

// Funcție pentru obținerea căii complete a fișierului - Exemplu de utilizare a unui string
string GestionareCSV::getCaleFisier(const string& oras, const string& numeFisier) {
    return oras + "/" + numeFisier; // Concatenează șiruri de caractere
}

// Utilizarea template-ului std::vector pentru a returna o listă de headere
vector<string> GestionareCSV::getHeadere(const string& numeFisier) {
    return hartaHeadere[limba][numeFisier]; // Returnează vectorul corespunzător limbii și fișierului
}

// Funcție pentru schimbarea header-elor - utilizează std::vector pentru a manipula headerele
void GestionareCSV::schimbaHeadere(const string& oras, const string& numeFisier) {
    string caleFisier = getCaleFisier(oras, numeFisier);
    vector<string> headere = getHeadere(numeFisier); // Obținem headerele corespunzătoare

    if (headere.empty()) {
        cout << "Header-ele pentru " << numeFisier << " nu sunt disponibile in limba " << limba << "." << endl;
        return;
    }
    caleFisier = "Orase/" + caleFisier;
    ifstream infile(caleFisier); // Deschidem fișierul pentru citire
    stringstream buffer;
    buffer << infile.rdbuf(); // Citim tot conținutul fișierului
    string continut = buffer.str();

    // Inlocuim prima linie (header-ul) cu noile header-e
    size_t poz = continut.find("\n");
    if (poz != string::npos) {
        string headerNou = alatura(headere, ",") + "\n"; // Concatenăm noile headere
        continut.replace(0, poz + 1, headerNou); // Înlocuim header-ul
    }

    // Scriem continutul modificat în fișier
    ofstream outfile(caleFisier); // Deschidem fișierul pentru scriere
    outfile << continut;

    cout << "Header-ele pentru " << numeFisier << " in orasul " << oras << " au fost schimbate cu succes in limba " << limba << "." << endl;
}

// Funcție care alătură elementele unui vector folosind un separator - Utilizarea vectorului ca parametru
string GestionareCSV::alatura(const vector<string>& vec, const string& separator) {
    string rezultat;
    for (size_t i = 0; i < vec.size(); ++i) {
        rezultat += vec[i];
        if (i < vec.size() - 1) rezultat += separator; // Adăugăm separatorul între elemente
    }
    return rezultat; // Returnăm șirul concatenat
}

// Funcție care schimbă toate header-ele pentru mai multe orașe - Utilizarea unui vector de orașe
void GestionareCSV::schimbaToateHeaderelePentruOrase(const vector<string>& orase) {
    for (const string& oras : orase) {
        for (const string& numeFisier : {"angajati.csv", "comenzi.csv", "evenimente.csv", "produse.csv", "raport.csv"}) {
            schimbaHeadere(oras, numeFisier); // Schimbăm header-ele pentru fiecare fișier
        }
    }
}