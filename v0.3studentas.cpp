#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include <algorithm>
#include "v0.3studentas.h"
#include "v0.3pagalbine.h"

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

    //vector<char> buffer(1024 * 1024);
    //f.rdbuf()->pubsetbuf(buffer.data(), buffer.size());

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

void printas(const studentas &laik, std::ofstream &R)
{
    R<<std::left<<std::setw(15)<<laik.vardas
     <<std::left<<std::setw(15)<<laik.pavarde
     <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_vid
     <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_med<<"\n";
}
