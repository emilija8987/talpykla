#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include "v0.2studentas.h"
#include "v0.2pagalbine.h"

using std::string;
using std::vector;

void generuotiStudentuFaila(const string &failoPavadinimas, int kiekis, int nd_kiek)
{
    if (failasEgzistuoja(failoPavadinimas))
    {
        std::cout << "Failas '"<<failoPavadinimas<<"' jau yra. Generavimas praleidziamas.\n";
        return;
    }

    std::cout << "Generuojamas failas '"<<failoPavadinimas<<"' ("<<kiekis<<" irasu)... ";

    std::ofstream f(failoPavadinimas);
    if (!f.is_open())
    {
        std::cout<<"\nKlaida: nepavyko sukurti failo "<<failoPavadinimas<<"\n";
        return;
    }

    vector<char> buffer(1024 * 1024);
    f.rdbuf()->pubsetbuf(buffer.data(), buffer.size());

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    f<<std::left<<std::setw(15)<<"Vardas"<<std::setw(15)<<"Pavarde";
    for (int i=1; i<=nd_kiek; i++)
    {
        f<<std::setw(8)<<("ND" + std::to_string(i));
    }
    f<<std::setw(10)<<"Egz."<<"\n";

    for (int i=1; i<=kiekis; i++)
    {
        f << std::left << std::setw(15) << ("Vardas" + std::to_string(i))
          << std::setw(15) << ("Pavarde" + std::to_string(i));

        for (int j=0; j< nd_kiek; j++)
        {
            f<<std::setw(8)<<dist(gen);
        }
        f<<std::setw(10)<<dist(gen)<<"\n";
    }

    f.close();
    std::cout<<"Atlikta\n\n";
}

bool skaitytiFaila(std::vector<studentas> &grupe, const string &failas, int kiekis)
{
    std::ifstream f(failas);
    if (!f.is_open())
    {
        std::cout<<"Nepavyko atidaryti failo '"<<failas<<"'\n";
        return false;
    }

    if (kiekis > 0) grupe.reserve(kiekis);

    string eilute;
    std::getline(f, eilute);

    while (std::getline(f, eilute))
    {
        if (eilute.empty()) continue;

        std::stringstream ss(eilute);

        studentas laik;

        ss>>laik.vardas>>laik.pavarde;

        vector<int> skaiciai;
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

void printas(const studentas &laik, std::ofstream &R)
{
    R<<std::left<<std::setw(15)<<laik.pavarde
     <<std::left<<std::setw(15)<<laik.vardas
     <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_vid
     <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_med<<"\n";
}

void irasytiIFaila(const string &failoPavadinimas, const vector<studentas> &s_grupe)
{
    std::ofstream R(failoPavadinimas);
    if (!R.is_open())
    {
        std::cout << "Klaida: nepavyko sukurti failo " << failoPavadinimas << "\n";
        return;
    }

    R << std::left << std::setw(15) << "Pavarde"
      << std::left << std::setw(15) << "Vardas"
      << std::left << std::setw(18) << "Galutinis (vid.)"
      << std::left << std::setw(18) << "Galutinis (med.)\n";
    R << "-------------------------------------------------------------------\n";

    for (const auto &x : s_grupe) printas(x, R);

    R.close();
}














