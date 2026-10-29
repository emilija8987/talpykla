#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <list>
#include "studentas.h"
#include "pagalbine.h"

using std::string;
using std::vector;
using std::list;
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

int gautiRusiavimoKriteriju()
{
    std::cout << "\nPasirinkite rusiavimo kriteriju:\n";
    std::cout << "1 - Pagal varda\n";
    std::cout << "2 - Pagal pavarde\n";
    std::cout << "3 - Pagal galutini vidurki\n";
    std::cout << "4 - Pagal galutine mediana\n";
    return ivestiSkaiciu("Jusu pasirinkimas (1-4): ", 1, 4);
}

template <typename Container>
void atliktiAnalize(int strategijos_nr, const string &failo_pavadinimas, int kiekis, int rusiavimo_kriterijus, string konteinerio_pavadinimas)
{
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << strategijos_nr << " STRATEGIJA | Konteineris: " << konteinerio_pavadinimas << " | Failas: " << failo_pavadinimas << " (" << kiekis << " irasu)\n";
    std::cout << "------------------------------------------------------------------------\n";

    if (!failasEgzistuoja(failo_pavadinimas))
    {
        generuotiStudentuFaila(failo_pavadinimas, kiekis);
    }
    else
    {
        std::cout << "Failas '" << failo_pavadinimas << "' jau egzistuoja. Generavimas praleidziamas.\n";
    }

    int testu_kiekis = 3;
    double suma_skaitymas = 0;
    double suma_rusiavimas = 0;
    double suma_dalijimas = 0;
    double suma_isvedimas = 0;
    double suma_bendras = 0;

    for (int i = 0; i < testu_kiekis; i++)
    {
        Container grupe;

        auto t1 = Clock::now();
        skaitytiFaila(grupe, failo_pavadinimas, kiekis);
        auto t2 = Clock::now();
        double t_skaitymas = Duration(t2 - t1).count();

        auto t3 = Clock::now();
        rusiuotiStudentus(grupe, rusiavimo_kriterijus);
        auto t4 = Clock::now();
        double t_rusiavimas = Duration(t4 - t3).count();

        Container vargsiukai;
        Container kietiakiai;

        auto t5 = Clock::now();
        if (strategijos_nr == 1) {
            dalinti1Strategija(grupe, vargsiukai, kietiakiai);
        } else if (strategijos_nr == 2) {
            dalinti2Strategija(grupe, vargsiukai, kietiakiai);
        } else if (strategijos_nr == 3) {
            dalinti3Strategija(grupe, vargsiukai, kietiakiai);
        }
        auto t6 = Clock::now();
        double t_dalijimas = Duration(t6 - t5).count();

        auto t7 = Clock::now();
        irasytiIFaila("vargsiukai.txt", vargsiukai);
        irasytiIFaila("kietiakiai.txt", kietiakiai);
        auto t8 = Clock::now();
        double t_isvedimas = Duration(t8 - t7).count();

        suma_skaitymas += t_skaitymas;
        suma_rusiavimas += t_rusiavimas;
        suma_dalijimas += t_dalijimas;
        suma_isvedimas += t_isvedimas;
        suma_bendras += (t_skaitymas + t_rusiavimas + t_dalijimas + t_isvedimas);
    }

    std::cout << "1. Duomenu nuskaitymas (vidurkis): " << suma_skaitymas / testu_kiekis << " s\n";
    std::cout << "2. Studentu rusiavimas ir dalijimas (vidurkis): " << suma_rusiavimas / testu_kiekis << " s\n";
    std::cout << "3. Studentu dalijimas (vidurkis): "<< suma_dalijimas / testu_kiekis << " s\n";
    std::cout << "4. Isvedimas i du failus (vidurkis): " << suma_isvedimas / testu_kiekis << " s\n";
    std::cout << "-> Bendras laikas (vidurkis): " << suma_bendras / testu_kiekis << " s\n\n";
}

template <typename Container>
void vykdytiRankiniIvedima(string konteinerio_pavadinimas)
{
    Container grupe;
    int n = ivestiSkaiciu("Iveskite studentu kieki: ", 1, 100000);

    for (int j = 0; j < n; j++)
    {
        studentas laik;
        std::cout << "Iveskite per tarpa studento varda ir pavarde: ";
        std::cin >> laik.vardas >> laik.pavarde;

        std::cout << "\nPasirinkite kaip ivesti pazymius:\n";
        std::cout << "1 - Ivesti pazymius ir egzamina ranka\n";
        std::cout << "2 - Ivesti pazymius ir egzamina atsitiktinai\n";
        int pasirinkimas = ivestiSkaiciu("Jusu pasirinkimas (1 arba 2): ", 1, 2);

        double suma = 0;
        if (pasirinkimas == 1)
        {
            std::cout << "Veskite studento pazymius. Noredami baigti iveskite '0'.\n";
            while (true)
            {
                int a = ivestiSkaiciu("Iveskite " + std::to_string(laik.nd.size() + 1) + " pazymi: ", 0, 10);
                if (a == 0) break;
                suma += a;
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
                suma += p;
                std::cout << p << " ";
            }
            std::cout << "\n";
            laik.egz = atspazymiai(1, 10);
            std::cout << "Egzaminas: " << laik.egz << "\n";
        }

        double vid = 0;
        double med = 0;
        int k = laik.nd.size();
        if (k > 0)
        {
            vid = suma / k;
            med = mediana(laik.nd);
        }

        laik.galutinis_vid = 0.4 * vid + 0.6 * laik.egz;
        laik.galutinis_med = 0.4 * med + 0.6 * laik.egz;

        grupe.push_back(laik);
        std::cout << "Studento atminties adresas (" << konteinerio_pavadinimas << "): " << &grupe.back() << "\n";
    }

    if (!grupe.empty())
    {
        int rusiavimo_kriterijus = gautiRusiavimoKriteriju();
        rusiuotiStudentus(grupe, rusiavimo_kriterijus);

        Container vargsiukai;
        Container kietiakiai;

        for (const auto &s : grupe)
        {
            if (s.galutinis_vid < 5.0) vargsiukai.push_back(s);
            else kietiakiai.push_back(s);
        }

        irasytiIFaila("vargsiukai.txt", vargsiukai);
        irasytiIFaila("kietiakiai.txt", kietiakiai);
        std::cout << "Duomenys irasyti i 'vargsiukai.txt' ir 'kietiakiai.txt'.\n";
    }
    else
    {
        std::cout << "Nera duomenu isvedimui.\n";
    }
}

int main()
{
    std::cout << "Pasirinkite programos reazima:\n";
    std::cout << "1 - Paleisti AUTOMATINE SPARTOS ANALIZE visiems 5 failams\n";
    std::cout << "2 - Vykdyti iprasta programa (pasirinkti viena faila arba vesti ranka)\n";
    int rezimas = ivestiSkaiciu("Jusu pasirinkimas (1 arba 2): ", 1, 2);

    if (rezimas == 1)
    {
        int rusiavimo_kriterijus = gautiRusiavimoKriteriju();

        struct TestData
        {
            string failas;
            int kiekis;
        };

        vector<TestData> testai =
        {
            {"studentai_1000.txt", 1000},
            {"studentai_10000.txt", 10000},
            {"studentai_100000.txt", 100000},
            {"studentai_1000000.txt", 1000000},
           // {"studentai_10000000.txt", 10000000}
        };

        std::cout << "\n=================== VYKDOMI TESTAI SU std::vector ===================\n\n";
        for (const auto &t : testai)
        {
            atliktiAnalize<std::vector<studentas>>(1, t.failas, t.kiekis, rusiavimo_kriterijus, "std::vector");
        }
        std::cout << "\n--- 2 STRATEGIJA (Vector) ---\n";
        for (const auto &t : testai) {
            atliktiAnalize<std::vector<studentas>>(2, t.failas, t.kiekis, rusiavimo_kriterijus, "std::vector");
        }
        std::cout << "\n--- 3 STRATEGIJA (Vector) ---\n";
        for (const auto &t : testai) {
            atliktiAnalize<std::vector<studentas>>(3, t.failas, t.kiekis, rusiavimo_kriterijus, "std::vector");
        }

        std::cout << "\n=================== VYKDOMI TESTAI SU std::list ===================\n\n";
        std::cout << "\n--- 1 STRATEGIJA (List) ---\n";
        for (const auto &t : testai)
        {
            atliktiAnalize<std::list<studentas>>(1, t.failas, t.kiekis, rusiavimo_kriterijus, "std::list");
        }
        std::cout << "\n--- 2 STRATEGIJA (List) ---\n";
        for (const auto &t : testai) {
            atliktiAnalize<std::list<studentas>>(2, t.failas, t.kiekis, rusiavimo_kriterijus, "std::list");
        }
        std::cout << "\n--- 3 STRATEGIJA (List) ---\n";
        for (const auto &t : testai) {
            atliktiAnalize<std::list<studentas>>(3, t.failas, t.kiekis, rusiavimo_kriterijus, "std::list");
        }
    }
    else
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

            if (!grupe.empty())
            {
                int rusiavimo_kriterijus = gautiRusiavimoKriteriju();
                rusiuotiStudentus(grupe, rusiavimo_kriterijus);

                vector<studentas> vargsiukai;
                vector<studentas> kietiakiai;

                for (const auto &s : grupe)
                {
                    if (s.galutinis_vid < 5.0) vargsiukai.push_back(s);
                    else kietiakiai.push_back(s);
                }

                irasytiIFaila("vargsiukai.txt", vargsiukai);
                irasytiIFaila("kietiakiai.txt", kietiakiai);
                std::cout << "Duomenys irasyti i 'vargsiukai.txt' ir 'kietiakiai.txt'.\n";
            }
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
            if (!grupe.empty())
            {
                int rusiavimo_kriterijus = gautiRusiavimoKriteriju();
                rusiuotiStudentus(grupe, rusiavimo_kriterijus);

                vector<studentas> vargsiukai;
                vector<studentas> kietiakiai;

                for (const auto &s : grupe)
                {
                    if (s.galutinis_vid < 5.0) vargsiukai.push_back(s);
                    else kietiakiai.push_back(s);
                }

                irasytiIFaila("vargsiukai.txt", vargsiukai);
                irasytiIFaila("kietiakiai.txt", kietiakiai);
                std::cout << "Duomenys irasyti i 'vargsiukai.txt' ir 'kietiakiai.txt'.\n";
            }
        }

        if (variantas == 7)
        {
            std::cout << "Pasirinkite konteineri rankiniam ivedimui:\n";
            std::cout << "1 - std::vector\n";
            std::cout << "2 - std::list\n";
            int kont_tipas = ivestiSkaiciu("Jusu pasirinkimas (1 arba 2): ", 1, 2);

            if (kont_tipas == 1)
            {
                vykdytiRankiniIvedima<std::vector<studentas>>("vector");
            }
            else
            {
                vykdytiRankiniIvedima<std::list<studentas>>("list");
            }
        }
    }

    return 0;
}


