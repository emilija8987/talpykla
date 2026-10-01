#ifndef V02_STUDENTAS_H
#define V02_STUDENTAS_H

#include <string>
#include <vector>
#include <fstream>

struct studentas {
    std::string vardas, pavarde;
    std::vector<int> nd;
    int egz;
    double galutinis_vid;
    double galutinis_med;
    bool operator<(const studentas &kito) const {
        if (pavarde != kito.pavarde) return pavarde < kito.pavarde;
        return vardas < kito.vardas;
    }
};

void printas(const studentas &laik, std::ofstream &R);
bool skaitytiFaila(std::vector<studentas> &grupe, const std::string &failas, int kiekis = 0);
void generuotiStudentuFaila(const std::string &failoPavadinimas, int kiekis, int nd_kiek = 5);
void irasytiIFaila(const std::string &failoPavadinimas, const std::vector<studentas> &s_grupe);

#endif













