#include "v0.2pagalbine.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>

using std::string;
using std::vector;

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

bool failasEgzistuoja(const string &pavadinimas)
{
    std::ifstream F(pavadinimas);
    return F.is_open();
}









































