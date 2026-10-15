#ifndef V03_STUDENTAS_H
#define V03_STUDENTAS_H

#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <type_traits>
#include <algorithm>
#include "v0.3pagalbine.h"

struct studentas {
    std::string vardas, pavarde;
    std::vector<int> nd;
    int egz;
    double galutinis_vid;
    double galutinis_med;
};

void printas(const studentas &laik, std::ofstream &R);
void generuotiStudentuFaila(const std::string &failoPavadinimas, int kiekis, int nd_kiek = 5);

inline bool palygintiPagalVarda(const studentas &a, const studentas &b) {
    if (a.vardas != b.vardas) return a.vardas < b.vardas;
    return a.pavarde < b.pavarde;
}

inline bool palygintiPagalPavarde(const studentas &a, const studentas &b) {
    if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
    return a.vardas < b.vardas;
}

inline bool palygintiPagalVidurki(const studentas &a, const studentas &b) {
    if (a.galutinis_vid != b.galutinis_vid) {
        return a.galutinis_vid > b.galutinis_vid;
    }
    if (a.galutinis_med != b.galutinis_med) {
        return a.galutinis_med > b.galutinis_med;
    }
    return a.pavarde < b.pavarde;
}

inline bool palygintiPagalMediana(const studentas &a, const studentas &b) {
    if (a.galutinis_med != b.galutinis_med) {
        return a.galutinis_med > b.galutinis_med;
    }
    if (a.galutinis_vid != b.galutinis_vid) {
        return a.galutinis_vid > b.galutinis_vid;
    }
    return a.pavarde < b.pavarde;
}

template <typename C>
typename std::enable_if<std::is_same<C, std::vector<studentas>>::value>::type
pabandykReserve(C &grupe, int kiekis) {
    if (kiekis > 0) grupe.reserve(kiekis);
}

template <typename C>
typename std::enable_if<!std::is_same<C, std::vector<studentas>>::value>::type
pabandykReserve(C &grupe, int kiekis) {

}

template <typename Container>
bool skaitytiFaila(Container &grupe, const std::string &failas, int kiekis = 0)
{
    std::ifstream f(failas);
    if (!f.is_open())
    {
        std::cout<<"Nepavyko atidaryti failo '"<<failas<<"'\n";
        return false;
    }

    pabandykReserve(grupe, kiekis);

    std::string eilute;
    std::getline(f, eilute);

    while (std::getline(f, eilute))
    {
        if (eilute.empty()) continue;

        std::stringstream ss(eilute);
        studentas laik;
        ss>>laik.vardas>>laik.pavarde;

        std::vector<int> skaiciai;
        int p;
        while (ss>>p)
        {
            skaiciai.push_back(p);
        }

        if (!skaiciai.empty())
        {
            laik.egz = skaiciai.back();
            skaiciai.pop_back();

            laik.nd = skaiciai;

            double suma = 0;
            for (int pazymys : laik.nd)
            {
                suma += pazymys;
            }

            int k = laik.nd.size();
            double vid = (k > 0) ? suma / k : 0.0;
            double med = mediana(laik.nd);

            laik.galutinis_vid = 0.4 * vid + 0.6 * laik.egz;
            laik.galutinis_med = 0.4 * med + 0.6 * laik.egz;

            grupe.push_back(laik);
        }
    }
    f.close();
    return true;
}

template <typename Container>
typename std::enable_if<std::is_same<Container, std::vector<studentas>>::value>::type
rusiuotiStudentus(Container &grupe, int kriterijus)
{
    if (kriterijus == 1) std::sort(grupe.begin(), grupe.end(), palygintiPagalVarda);
    else if (kriterijus == 2) std::sort(grupe.begin(), grupe.end(), palygintiPagalPavarde);
    else if (kriterijus == 3) std::sort(grupe.begin(), grupe.end(), palygintiPagalVidurki);
    else if (kriterijus == 4) std::sort(grupe.begin(), grupe.end(), palygintiPagalMediana);
}

template <typename Container>
typename std::enable_if<!std::is_same<Container, std::vector<studentas>>::value>::type
rusiuotiStudentus(Container &grupe, int kriterijus)
{
    if (kriterijus == 1) grupe.sort(palygintiPagalVarda);
    else if (kriterijus == 2) grupe.sort(palygintiPagalPavarde);
    else if (kriterijus == 3) grupe.sort(palygintiPagalVidurki);
    else if (kriterijus == 4) grupe.sort(palygintiPagalMediana);
}

template <typename Container>
void irasytiIFaila(const std::string &failoPavadinimas, const Container &s_grupe)
{
    std::ofstream R(failoPavadinimas);
    if (!R.is_open())
    {
        std::cout << "Klaida: nepavyko sukurti failo " << failoPavadinimas << "\n";
        return;
    }

    R << std::left << std::setw(15) << "Vardas"
      << std::left << std::setw(15) << "Pavarde"
      << std::left << std::setw(18) << "Galutinis (vid.)"
      << std::left << std::setw(18) << "Galutinis (med.)\n";
    R << "-------------------------------------------------------------------\n";

    for (const auto &x : s_grupe) printas(x, R);

    R.close();
}

#endif













