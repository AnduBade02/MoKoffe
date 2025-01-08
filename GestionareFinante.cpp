#include "GestionareFinante.h"

void GestionareFinante::citesteComenziDinCSV(const std::string& numeFisier) {
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        std::cerr << "Nu s-a putut deschide fișierul " << numeFisier << std::endl;
        return;
    }

    std::string linie;
    std::getline(fisier, linie); // Ignorăm header-ul

    Comanda comanda;
    while (std::getline(fisier, linie)) {
        std::istringstream stream(linie);

        // Citim datele din linie
        stream >> comanda.espresso;
        stream.ignore(1, ',');
        stream >> comanda.latte;
        stream.ignore(1, ',');
        stream >> comanda.brownie;
        stream.ignore(1, ',');
        stream >> comanda.baghetaCrispy;
        stream.ignore(1, ',');
        stream >> comanda.ciocolataCalda;
        stream.ignore(1, ',');
        stream >> comanda.americano;
        stream.ignore(1, ',');
        stream >> comanda.fidelitate;

        // Adăugăm comanda citită la vectorul de comenzi
        comenzi.push_back(comanda);
    }

    fisier.close();
    std::cout << "Comenzile au fost încărcate din fișierul " << numeFisier << std::endl;
}

double GestionareFinante::calculeazaPretComanda(const Comanda& comanda, const GestionareProduse& gestionareProduse) const {
    double pretTotal = 0;

    // Vector de produse și numele lor
    std::vector<std::string> numeProduse = {
            "Cafea Espresso", "Cafea Latte", "Desert Brownie",
            "Bagheta Crispy", "Ciocolata Calda", "Cafea Americano"
    };

    // Parcurgem produsele și calculăm prețul total
    for (size_t i = 0; i < numeProduse.size(); ++i) {
        // Obținem numărul de produse comandate pentru fiecare produs
        int numarProduseComandate = 0;
        switch (i) {
            case 0: numarProduseComandate = comanda.espresso; break;
            case 1: numarProduseComandate = comanda.latte; break;
            case 2: numarProduseComandate = comanda.brownie; break;
            case 3: numarProduseComandate = comanda.baghetaCrispy; break;
            case 4: numarProduseComandate = comanda.ciocolataCalda; break;
            case 5: numarProduseComandate = comanda.americano; break;
        }

        // Căutăm produsul în vectorul de produse din GestionareProduse
        for (const auto& produs : gestionareProduse.getProduse()) {
            if (produs.getNume() == numeProduse[i]) {
                pretTotal += produs.getCostVanzare() * numarProduseComandate;
                break;
            }
        }
    }
    pretTotal = aplicaReducere(pretTotal,comanda.fidelitate);
    return pretTotal;
}

double GestionareFinante::aplicaReducere(double pretTotal, bool fidelitate) const {
    if (fidelitate) {
        return pretTotal * 0.90;  // Aplicăm reducerea de 10% pentru clienții fideli
    }
    return pretTotal;
}


void GestionareFinante::citesteEvenimenteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    string linie, tipEveniment;
    double pret;

    // Ignorăm header-ul
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        istringstream stream(linie);
        getline(stream, tipEveniment, ',');
        stream >> pret;

        evenimente.push_back(Eveniment{tipEveniment, pret});
    }

    fisier.close();
    cout << "Evenimentele au fost încărcate din fișierul " << numeFisier << endl;
}

// Afișarea detaliilor fiecărui eveniment
void GestionareFinante::afiseazaEvenimente() const {
    for (const auto& eveniment : evenimente) {
        cout << "Eveniment: " << eveniment.tipEveniment << ", Pret: " << eveniment.pret << " lei" << endl;
    }
}

// Calculul costului total al evenimentelor
double GestionareFinante::calculeazaCostEvenimente() const {
    double costTotal = 0;
    for (const auto& eveniment : evenimente) {
        costTotal += eveniment.pret;
    }
    return costTotal/100;
}

double GestionareFinante::calculeazaVenituriTotale(const GestionareProduse& gestionareProduse) const {
    double venituriTotale = 0;

    for (const auto& comanda : comenzi) {
        venituriTotale += calculeazaPretComanda(comanda, gestionareProduse);
    }

    return venituriTotale;
}

double GestionareFinante::calculeazaCostProduse(const GestionareProduse& gestionareProduse) const {
    double costTotal = 0;

    // Obținem vectorul de produse
    const auto& produse = gestionareProduse.getProduse();

    // Calculăm costul total al produselor
    for (const auto& produs : produse) {
        costTotal += produs.getCostAchizitie() * produs.getStoc();
    }
    costTotal += calculeazaCostEvenimente();
    return costTotal;
}

void GestionareFinante::genereazaRaportCSV(const string& numeFisier, const GestionareProduse& gestionareProduse, const GestionareAngajati& gestionareAngajati) const {
    ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    // Scriere header
    fisier << "venituri,costuri,salarii,profit\n";
    double salarii = gestionareAngajati.calculeazaTotalSalarii();
    // Calculăm valorile relevante
    double venituriTotale = calculeazaVenituriTotale(gestionareProduse);
    double costProduse = calculeazaCostProduse(gestionareProduse);
    double costEvenimente = calculeazaCostEvenimente();
    double costuriTotale = costProduse + costEvenimente + salarii;
    double profit = venituriTotale - costuriTotale;

    // Scrierea valorilor în fișier
    fisier << venituriTotale << "," << costuriTotale << "," << salarii << "," << profit << "\n";

    fisier.close();
    cout << "Raportul a fost generat în fișierul " << numeFisier << endl;
}
