#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using std::string;
using std::vector;

struct studentas {
    string vardas, pavarde;
    vector<int> nd;
    int egz;
    double galutinis;
};
void printas(const studentas &laik);
int main()
{
    std::vector<studentas> grupe;
    std::cout<<"Iveskite studentu kieki : ";
    int n;
    std::cin>>n;
    for(int j=0; j<n; j++)
    {
        studentas laik;
        std::cout<<"Iveskite per tarpa studento varda ir pavarde: ";
        std::cin>>laik.vardas>>laik.pavarde;
        std::cout<<"Iveskite studento pazymiu kieki: ";
        int k;
        std::cin>>k;
        double suma = 0,vid = 0;
        if (k>0)
        {
            for (int i=0; i<k; i++)
            {
                std::cout<<"Iveskite "<<i+1<<" pazymi: ";
                int a;
                std::cin>>a;
                suma = suma + a;
                laik.nd.push_back(a);
            }
            vid = suma / k;
        }
        std::cout<<"Iveskite egzamino rezultata: ";
        std::cin>>laik.egz;
        laik.galutinis = 0.4 * vid + 0.6 * laik.egz;
        grupe.push_back(laik);
        //laik.vardas.clear();
        //laik.pavarde.clear();
        //laik.nd.clear();
    }
    std::cout<<std::left<<std::setw(15)<<"Pavarde"<<std::left<<std::setw(15)<<"Vardas"<<std::left<<std::setw(16)<<"Galutinis (vid.)\n";
    std::cout<<"------------------------------------------------\n";
    for (const auto &x : grupe) printas(x);
}

void printas(const studentas &laik)
{
    std::cout<<std::left<<std::setw(15)<<laik.pavarde<<std::left<<std::setw(15)<<laik.vardas<<std::left<<std::setw(16)<<std::fixed<<std::setprecision(2)<<laik.galutinis<<"\n";

}









