#include "GestionareCSV.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

GestionareCSV::GestionareCSV(const string& limba) : limba(limba) {
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

string GestionareCSV::getCaleFisier(const string& oras, const string& numeFisier) {
    return oras + "/" + numeFisier;
}

vector<string> GestionareCSV::getHeadere(const string& numeFisier) {
    return hartaHeadere[limba][numeFisier];
}

void GestionareCSV::schimbaHeadere(const string& oras, const string& numeFisier) {
    string caleFisier = getCaleFisier(oras, numeFisier);
    vector<string> headere = getHeadere(numeFisier);

    if (headere.empty()) {
        cout << "Header-ele pentru " << numeFisier << " nu sunt disponibile in limba " << limba << "." << endl;
        return;
    }
    caleFisier = "Orase/" + caleFisier;
    ifstream infile(caleFisier);
    stringstream buffer;
    buffer << infile.rdbuf();
    string continut = buffer.str();

    // Inlocuieste prima linie (header-ul) cu noile header-e
    size_t poz = continut.find("\n");
    if (poz != string::npos) {
        string headerNou = alatura(headere, ",") + "\n";
        continut.replace(0, poz + 1, headerNou);
    }

    // Scrie continutul modificat inapoi in fisier
    ofstream outfile(caleFisier);
    outfile << continut;

    cout << "Header-ele pentru " << numeFisier << " in orasul " << oras << " au fost schimbate cu succes in limba " << limba << "." << endl;
}

string GestionareCSV::alatura(const vector<string>& vec, const string& separator) {
    string rezultat;
    for (size_t i = 0; i < vec.size(); ++i) {
        rezultat += vec[i];
        if (i < vec.size() - 1) rezultat += separator;
    }
    return rezultat;
}

void GestionareCSV::schimbaToateHeaderelePentruOrase(const vector<string>& orase) {
    for (const string& oras : orase) {
        for (const string& numeFisier : {"angajati.csv", "comenzi.csv", "evenimente.csv", "produse.csv", "raport.csv"}) {
            schimbaHeadere(oras, numeFisier);
        }
    }
}