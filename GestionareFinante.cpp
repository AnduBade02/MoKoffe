#include "GestionareFinante.h"

string obtineDataSiOraCurenta() {
    std::time_t timpCurent = std::time(nullptr);  // Obținem timpul curent
    std::tm* timpLocal = std::localtime(&timpCurent);  // Convertim timpul în format local

    std::ostringstream buffer;  // Folosim un buffer pentru a formata data
    buffer << std::put_time(timpLocal, "%Y-%m-%d %H:%M:%S");  // Formatare data și oră
    return buffer.str();  // Returnăm data și ora curente ca șir de caractere
}

void GestionareFinante::citesteComenziDinCSV(const std::string& numeFisier) {
    std::ifstream fisier(numeFisier);  // Deschidem fișierul pentru citire
    if (!fisier.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul comenzi: " + numeFisier);  // Aruncăm excepție dacă fișierul nu se poate deschide
    }

    std::string linie;
    std::getline(fisier, linie);  // Ignorăm header-ul

    Comanda comanda;
    while (std::getline(fisier, linie)) {
        std::istringstream stream(linie);  // Citim fiecare linie

        // Citim datele din linie și le stocăm în structura Comanda
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

        // Adăugăm comanda citită în vectorul de comenzi
        comenzi.push_back(comanda);
    }

    fisier.close();  // Închidem fișierul
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
        // Obținem numărul de produse comandate pentru fiecare tip de produs
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

    // Aplicăm reducerea de fidelitate dacă este cazul
    pretTotal = aplicaReducere(pretTotal, comanda.fidelitate);
    return pretTotal;
}

double GestionareFinante::aplicaReducere(double pretTotal, bool fidelitate) const {
    if (fidelitate) {
        return pretTotal * 0.90;  // Reducere de 10% pentru clienții fideli
    }
    return pretTotal;
}

void GestionareFinante::citesteEvenimenteDinCSV(const string& numeFisier) {
    ifstream fisier(numeFisier);  // Deschidem fișierul pentru citire
    if (!fisier.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul evenimente: " + numeFisier);  // Aruncăm excepție dacă fișierul nu se poate deschide
    }

    string linie, tipEveniment;
    double pret;

    // Ignorăm header-ul fișierului
    getline(fisier, linie);

    while (getline(fisier, linie)) {
        istringstream stream(linie);  // Citim fiecare linie
        getline(stream, tipEveniment, ',');
        stream >> pret;

        // Adăugăm evenimentul citit în vectorul de evenimente
        evenimente.push_back(Eveniment{tipEveniment, pret});
    }

    fisier.close();  // Închidem fișierul
    cout << "Evenimentele au fost încărcate din fișierul " << numeFisier << endl;
}

// Calculul costului total al evenimentelor
double GestionareFinante::calculeazaCostEvenimente() const {
    double costTotal = 0;
    int cnt = 0;

    for (const auto& eveniment : evenimente) {
        costTotal += eveniment.pret;
        cnt++;
    }

    // Inițializare generator de numere aleatoare pentru determinarea unui cost mediu
    static bool initializat = false;
    if (!initializat) {
        srand(static_cast<unsigned>(time(0)));
        initializat = true;
    }

    // Determinăm dacă returnăm costul mediu sau 0
    int sansa = rand() % 7; // Valoare între 0 și 6 (1/7 șansă să fie 0)
    if (sansa == 0 && cnt > 0) {
        return costTotal / cnt;
    } else {
        return 0.0;
    }
}

double GestionareFinante::calculeazaVenituriTotale(const GestionareProduse& gestionareProduse) const {
    double venituriTotale = 0;

    for (const auto& comanda : comenzi) {
        venituriTotale += calculeazaPretComanda(comanda, gestionareProduse);  // Calculăm veniturile din comenzi
    }

    return venituriTotale;
}

double GestionareFinante::calculeazaCostProduse(const GestionareProduse& gestionareProduse) const {
    double costTotal = 0;

    // Obținem vectorul de produse
    const auto& produse = gestionareProduse.getProduse();

    // Calculăm costul total al produselor
    for (const auto& produs : produse) {
        costTotal += produs.getCostAchizitie() * produs.getStoc();  // Costul de achiziție al fiecărui produs
    }
    costTotal += calculeazaCostEvenimente();  // Adăugăm costul evenimentelor
    return costTotal;
}

void GestionareFinante::genereazaRaportCSV(const string& numeFisier, const GestionareProduse& gestionareProduse, const GestionareAngajati& gestionareAngajati) const {
    // Deschidem fișierul pentru a adăuga un nou raport
    ofstream fisier(numeFisier, ios::app);
    if (!fisier.is_open()) {
        cerr << "Nu s-a putut deschide fișierul " << numeFisier << endl;
        return;
    }

    double salarii = gestionareAngajati.calculeazaTotalSalarii();  // Calculăm salariile
    double venituriTotale = calculeazaVenituriTotale(gestionareProduse);  // Calculăm veniturile totale
    double costProduse = calculeazaCostProduse(gestionareProduse);  // Calculăm costurile produselor
    double costEvenimente = calculeazaCostEvenimente();  // Calculăm costurile evenimentelor
    double costuriTotale = costProduse + costEvenimente + salarii;  // Totalul costurilor
    double profit = venituriTotale - costuriTotale;  // Profitul

    // Obținem data și ora curente
    string dataOraCurenta = obtineDataSiOraCurenta();

    // Scriem linia raportului în fișier
    fisier << venituriTotale << "," << costuriTotale << "," << salarii << "," << profit << "," << dataOraCurenta << "\n";

    fisier.close();  // Închidem fișierul
    cout << "Raportul a fost generat și adăugat în fișierul " << numeFisier << endl;
}