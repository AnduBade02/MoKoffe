#ifndef GESTIONARECSV_H
#define GESTIONARECSV_H

#include <string>
#include <vector> // Utilizarea vectorilor, care sunt template-uri din STL
#include <unordered_map> // Utilizarea unordered_map, de asemenea un template din STL

// Clasa GestionareCSV - Demonstrează utilizarea conceptelor de Encapsulare și Constructori
class GestionareCSV {
private:
    std::string limba; // Încapsulare: atribut privat, accesibil doar prin metodele clasei
    // Utilizare de template-uri: vector și unordered_map
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> hartaHeadere;

public:
    // Constructor care inițializează limba implicit cu "ro" - Demonstrează utilizarea Constructorilor
    GestionareCSV(const std::string& limba = "ro");

    // Encapsulare: Metode publice pentru accesarea și manipularea datelor private
    std::string getCaleFisier(const std::string& oras, const std::string& numeFisier);

    // Utilizarea unui vector ca return value - Vectorii sunt template-uri
    std::vector<std::string> getHeadere(const std::string& numeFisier);

    void schimbaHeadere(const std::string& oras, const std::string& numeFisier);

    // Utilizare de vectori ca parametru - Vectorii sunt template-uri
    std::string alatura(const std::vector<std::string>& vec, const std::string& separator);

    void schimbaToateHeaderelePentruOrase(const std::vector<std::string>& orase);
};

#endif // GESTIONARECSV_H