# Studentų rūšiavimo programa (V1.0)

## Versijų aprašymai

* **V0.1**
  Pradinė programos versija. Duomenys įvedami rankiniu būdu per konsolę, skaičiuojamas tik galutinis vidurkis ir namų darbų rezultatai. Rezultatai išvedami į ekraną.

* **v0.2**
  Pridėtas duomenų nuskaitymas iš failų ir atsitiktinių studentų bei jų pažymių failų generavimas (`std::vector` konteineryje). Įdiegtas galutinės medianos skaičiavimas, studentų rūšiavimas pagal pavardes bei surūšiuotų duomenų išvedimas į atskirus failus (`vargsiukai.txt` ir `kietiakiai.txt`).

* **V0.3**
  Projektas išskaidytas į atskirus modulių failus (`main.cpp`, `studentas.cpp`, `pagalbine.cpp` ir antraštinius failus). Realizuotas kelių konteinerių tipų (`std::vector` ir `std::list`) palaikymas bei trys skirtingos studentų dalijimo į dvi kategorijas strategijos. Taip pat pridėtas spartos matavimas laiko matavimo funkcijomis (`std::chrono`).

* **V1.0**
  Galutinė optimizuota programos versija. Atliktas spartos tyrimas su įvairaus dydžio failais (nuo 1 000 iki 1 000 000 įrašų), panaudoti efektyvūs STL algoritmai bei konteinerių manipuliavimo metodai. Projektas pilnai paruoštas naudojimui su įdiegimo instrukcijomis.

---

## Gautų rezultatų komentaras

Remiantis atliktais spartos analizės matavimais (testuojant su 1 000, 10 000, 100 000 ir 1 000 000 įrašų failais):

1. **Duomenų nuskaitymas ir išvedimas:** Nuskaitymas iš failo ir galutinis įrašymas į tekstinius failus užima didžiąją dalį bendro programos laiko (pavyzdžiui, 1 000 000 įrašų atveju nuskaitymas trunka apie 5 sekundes, o išvedimas – apie 4.1-4.4 sekundės). Tai rodo, kad operacijos su disku (I/O) yra pagrindinis spartos ribojantis veiksnis.
2. **Rūšiavimo trukmė (`std::vector` vs `std::list`):** Milijono elementų atveju `std::list` elementų rūšiavimas (`grupe.sort()`) užtrunka apie 1.8–2.1 sekundės, tuo tarpu `std::vector` rūšiavimas per `std::sort()` užtrunka ilgiau – apie 3.0–3.9 sekundės. Tai nutinka todėl, kad sąrašas keičia tik elementų rodykles (mazgus), o vektorius perkelia pačius objektus atmintyje.
3. **Strategijų įtaka dalijimui:** 1, 2 ir 3 strategijos parodo, kaip konteinerių pildymo ir trynimo metodika veikia veikimo spartą. Pavyzdžiui, antrojoje ir trečiojoje strategijoje vektoriui pritaikyti efektyvūs filtravimo metodai padeda sumažinti dalijimo trukmę išvengiant elementų perteklinio kopijavimo.

* **Rūšiavimas ir dalijimas:** Žvelgiant į rezultatus pastebima, kad `std::list` konteineris rūšiavimo ir dalijimo etape su didesniais kiekiais (100k ir 1M įrašų) veikia ženkliai greičiau nei `std::vector` (pvz., prie 1 000 000 įrašų `std::list` užtruko ~3.44 s, o `std::vector` – ~13.52 s). Taip yra todėl, kad sąrašas naudoja savo vidinį `sort()` metodą, kuris keičia tik elementų rodykles (mazgus), o vektoriui tenka perstumti didelius atminties blokus.
* **Nuskaitymas ir įrašymas:** Duomenų nuskaitymo ir įrašymo į failus etapuose abiejų konteinerių laikai yra gana panašūs, nes pagrindinis laikas čia priklauso nuo disko (SSD) spartos ir srautų (`std::fstream`), o ne nuo pačio konteinerio vidinės struktūros.
