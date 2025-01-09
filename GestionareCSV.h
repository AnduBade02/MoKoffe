#ifndef GESTIONARECSV_H
#define GESTIONARECSV_H

#include <string>
#include <vector>
#include <unordered_map>

class GestionareCSV {
private:
    std::string limba;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> hartaHeadere;

public:
    GestionareCSV(const std::string& limba = "ro");
    std::string getCaleFisier(const std::string& oras, const std::string& numeFisier);
    std::vector<std::string> getHeadere(const std::string& numeFisier);
    void schimbaHeadere(const std::string& oras, const std::string& numeFisier);
    std::string alatura(const std::vector<std::string>& vec, const std::string& separator);
    void schimbaToateHeaderelePentruOrase(const std::vector<std::string>& orase);
};

#endif // GESTIONARECSV_H