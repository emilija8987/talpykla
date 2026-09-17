#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using std::string;
using std::vector;

struct studentas {
    string vardas, pavarde;
    vector<int> nd;
    int egz;
    double galutinis_vid;
    double galutinis_med;

};

int ivestiskaiciu(string tekstas, int maz, int did);
double mediana(std::vector<int> v);
void printas(const studentas &laik);

int main()
{
    std::vector<studentas> grupe;
    int n = ivestiskaiciu("Iveskite studentu kieki: ", 1, 100000);

    for(int j=0; j<n; j++)
    {
        studentas laik;
        std::cout<<"Iveskite per tarpa studento varda ir pavarde: ";
        std::cin>>laik.vardas>>laik.pavarde;

        std::cout<<("Veskite studento pazymius. Noredami baigti iveskite '0'.\n");

        double suma = 0;

        while (true)
        {
            int a = ivestiskaiciu("Iveskite " + std::to_string(laik.nd.size()+1) + " pazymi: ", 0, 10);
            if (a == 0) break;

            suma = suma + a;
            laik.nd.push_back(a);
        }

        double vid = 0;
        double med = 0;

        int k = laik.nd.size();

        if (k>0)
        {
            vid = suma / k;
            med = mediana(laik.nd);
        }

        laik.egz = ivestiskaiciu("Iveskite egzamino rezultata: ", 1, 10);

        laik.galutinis_vid = 0.4 * vid + 0.6 * laik.egz;
        laik.galutinis_med = 0.4 * med + 0.6 * laik.egz;

        grupe.push_back(laik);
        //laik.vardas.clear();
        //laik.pavarde.clear();
        //laik.nd.clear();
    }
    std::cout<<std::left<<std::setw(15)<<"Pavarde"<<std::left<<std::setw(15)<<"Vardas"<<std::left<<std::setw(18)<<"Galutinis (vid.)"<<std::left<<std::setw(18)<<"Galutinis (med.)\n";
    std::cout<<"------------------------------------------------\n";
    for (const auto &x : grupe) printas(x);
}

int ivestiskaiciu(string tekstas, int maz, int did)
{
    int sk;
    while (true)
    {
        std::cout<<tekstas;
        if(std::cin>>sk && sk >= maz && sk <= did)
        {
            return sk;
        }
        std::cout<<"Klaida. Iveskite skaiciu is naujo. \n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
}

double mediana(std::vector<int> v)
{
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    int s = v.size();
    if (s % 2 != 0)
    {
        return v[s/2];
    }
    else
    {
        return (v[s/2-1] + v[s/2])/2.0;
    }
}


void printas(const studentas &laik)
{
    std::cout<<std::left<<std::setw(15)<<laik.pavarde
             <<std::left<<std::setw(15)<<laik.vardas
             <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_vid
             <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_med<<"\n";
}

