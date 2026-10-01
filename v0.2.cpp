#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
using std::string;
using std::vector;

struct studentas {
    string vardas, pavarde;
    vector<int> nd;
    int egz;
    double galutinis_vid;
    double galutinis_med;
    bool operator<(const studentas &kito) const {
        if (pavarde != kito.pavarde) return pavarde < kito.pavarde;
        return vardas < kito.vardas;
    }
};

int ivestiSkaiciu(string tekstas, int maz, int did);
double mediana(std::vector<int> v);
void printas(const studentas &laik, std::ofstream &R);
int atspazymiai(int maz = 1, int did = 10);
bool skaitytiFaila(std::vector<studentas> &grupe, const string &failas, int kiekis = 0);
bool failasEgzistuoja(const string &pavadinimas);
void generuotiStudentuFaila(const string &failoPavadinimas, int kiekis, int nd_kiek = 5);


int main()
{
    std::vector<studentas> grupe;

    std::cout << "Pasirinkite duomenu ivesties buda:\n";
    std::cout << "1 - Skaityti 'studentai_1000.txt'\n";
    std::cout << "2 - Skaityti 'studentai_10000.txt'\n";
    std::cout << "3 - Skaityti 'studentai_100000.txt'\n";
    std::cout << "4 - Skaityti 'studentai_1000000.txt'\n";
    std::cout << "5 - Skaityti 'studentai_10000000.txt'\n";
    std::cout << "6 - Ivesti kito failo pavadinima\n";
    std::cout << "7 - Ivesti duomenis ranka\n";
    int variantas = ivestiSkaiciu("Jusu pasirinkimas: ", 1, 7);

    string failo_pavadinimas = "";

    int kiekis = 0;

    if (variantas == 1) { failo_pavadinimas = "studentai_1000.txt"; kiekis = 1000; }
    else if (variantas == 2) { failo_pavadinimas = "studentai_10000.txt"; kiekis = 10000; }
    else if (variantas == 3) { failo_pavadinimas = "studentai_100000.txt"; kiekis = 100000; }
    else if (variantas == 4) { failo_pavadinimas = "studentai_1000000.txt"; kiekis = 1000000; }
    else if (variantas == 5) { failo_pavadinimas = "studentai_10000000.txt"; kiekis = 10000000; }

    if (variantas >= 1 && variantas <= 5)
    {
        generuotiStudentuFaila(failo_pavadinimas, kiekis);
        skaitytiFaila(grupe, failo_pavadinimas, kiekis);
    }

    else if (variantas == 6)
    {
        while (true)
        {
            std::cout << "Iveskite duomenu failo pavadinima: ";
            std::cin >> failo_pavadinimas;

            if (skaitytiFaila(grupe, failo_pavadinimas)) break;
            std::cout << "Bandykite dar karta.\n\n";
        }
    }

    if (variantas == 7)
    {
        int n = ivestiSkaiciu("Iveskite studentu kieki: ", 1, 100000);

        for(int j=0; j<n; j++)
        {
            studentas laik;
            std::cout<<"Iveskite per tarpa studento varda ir pavarde: ";
            std::cin>>laik.vardas>>laik.pavarde;

            std::cout << "\nPasirinkite kaip ivesti pazymius:\n";
            std::cout << "1 - Ivesti pazymius ir egzamina ranka\n";
            std::cout << "2 - Ivesti pazymius ir egzamina atsitiktinai\n";
            int pasirinkimas = ivestiSkaiciu("Jusu pasirinkimas (1 arba 2): ", 1, 2);

            double suma = 0;

            if (pasirinkimas == 1)
            {
                std::cout<<("Veskite studento pazymius. Noredami baigti iveskite '0'.\n");

                while (true)
                {
                    int a = ivestiSkaiciu("Iveskite " + std::to_string(laik.nd.size()+1) + " pazymi: ", 0, 10);
                    if (a == 0) break;

                    suma = suma + a;
                    laik.nd.push_back(a);
                }
                laik.egz = ivestiSkaiciu("Iveskite egzamino rezultata: ", 1, 10);
            }
            else
            {
                int nd_kiek = ivestiSkaiciu("Kiek atsitiktiniu pazymiu (1-50)? ", 1, 50);
                std::cout << "Pazymiai: ";
                for (int i = 0; i < nd_kiek; i++)
                {
                    int p = atspazymiai(1, 10);
                    laik.nd.push_back(p);
                    suma = suma + p;
                    std::cout << p << " ";
                }
                std::cout << "\n";

                laik.egz = atspazymiai(1, 10);
                std::cout<<"Egzaminas: "<<laik.egz<<"\n";
            }

            double vid = 0;
            double med = 0;

            int k = laik.nd.size();

            if (k>0)
            {
                vid = suma / k;
                med = mediana(laik.nd);
            }

            laik.galutinis_vid = 0.4 * vid + 0.6 * laik.egz;
            laik.galutinis_med = 0.4 * med + 0.6 * laik.egz;

            grupe.push_back(laik);
        }
    }

    if (grupe.empty())
    {
        std::cout<<"Nera duomenu isvedimui.\n";
        return 0;
    }

    std::sort(grupe.begin(), grupe.end());

    std::ofstream R("rezultatai.txt");
    R << std::left << std::setw(15) << "Pavarde"
      << std::left << std::setw(15) << "Vardas"
      << std::left << std::setw(18) << "Galutinis (vid.)"
      << std::left << std::setw(18) << "Galutinis (med.)\n";
    R << "-------------------------------------------------------------------\n";

    for (const auto &x : grupe) printas(x, R);

    R.close();
    std::cout << "Rezultatai sekmingai irasyti i faila 'rezultatai.txt'.\n";

    return 0;
}

bool failasEgzistuoja(const string &pavadinimas)
{
    std::ifstream F(pavadinimas);
    return F.is_open();
}

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
    std::cout<<"Atlikta\n";
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

        std::stringstream ss;

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

int ivestiSkaiciu(string tekstas, int maz, int did)
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

int atspazymiai(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

void printas(const studentas &laik, std::ofstream &R)
{
    R<<std::left<<std::setw(15)<<laik.pavarde
     <<std::left<<std::setw(15)<<laik.vardas
     <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_vid
     <<std::left<<std::setw(18)<<std::fixed<<std::setprecision(2)<<laik.galutinis_med<<"\n";
}
