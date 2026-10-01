#include <iostream>
#include <algorithm>
#include "v0.2studentas.h"
#include "v0.2pagalbine.h"

using std::string;
using std::vector;

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

    vector<studentas> vargsiukai;
    vector<studentas> kietiakiai;

    for (const auto &s : grupe)
    {
        if (s.galutinis_vid < 5.0)
        {
            vargsiukai.push_back(s);
        } else
        {
            kietiakiai.push_back(s);
        }
    }

    irasytiIFaila("vargsiukai.txt", vargsiukai);
    irasytiIFaila("kietiakiai.txt", kietiakiai);

    std::cout << "Duomenys irasyti i 'vargsiukai.txt' ir 'kietiakiai.txt'.\n";
}








