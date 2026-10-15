# talpykla
projektai
# V0.3 Versija - Konteineriø testavimas (std::vector vs std::list)

Ðioje programos versijoje atliktas spartos tyrimas ir palyginimas, kaip keièiasi programos veikimo laikas naudojant skirtingus standartinës bibliotekos konteinerius: **std::vector** ir **std::list**.

## 1. Testavimo sistemos parametrai
* **Operacinë sistema (OS):** Windows 10 / 11
* **CPU (Procesorius):** Intel(R) Core(TM) i3-7020U CPU @ 2.30GHz
* **RAM (Atmintis):** 4 GB
* **Diskas:** SSD

---

## 2. Eksperimento rezultatai

Testavimas buvo atliktas su keturiais skirtingø dydþiø failais (nuo 1 000 iki 1 000 000 áraðø). Kiekvienas testas paleistas po 3 kartus, o lentelëse pateikiami laiko **vidurkiai sekundëmis**.

### std::vector konteinerio rezultatai
| Áraðø kiekis | Nuskaitymas (vidurkis) | Rûðiavimas ir dalijimas (vidurkis) | Áraðymas á failus (vidurkis) | Bendras laikas |
| :--- | :--- | :--- | :--- | :--- |
| **1 000** | 0.0208 s | 0.0104 s | 0.0178 s | 0.0490 s |
| **10 000** | 0.1590 s | 0.1025 s | 0.1201 s | 0.3816 s |
| **100 000** | 1.7973 s | 1.3800 s | 1.3390 s | 4.5163 s |
| **1 000 000** | 16.1350 s | 13.5235 s | 11.4650 s | 41.1250 s |

![std::vector testavimo rezultatai](vector.png)

### std::list konteinerio rezultatai
| Áraðø kiekis | Nuskaitymas (vidurkis) | Rûðiavimas ir dalijimas (vidurkis) | Áraðymas á failus (vidurkis) | Bendras laikas |
| :--- | :--- | :--- | :--- | :--- |
| **1 000** | 0.0252 s | 0.0052 s | 0.0208 s | 0.0512 s |
| **10 000** | 0.1588 s | 0.0312 s | 0.1233 s | 0.3134 s |
| **100 000** | 1.5708 s | 0.3008 s | 1.1520 s | 3.0236 s |
| **1 000 000** | 16.6096 s | 3.4378 s | 12.1857 s | 32.2331 s |

![std::list testavimo rezultatai](list.png)

---

## 3. Rezultatø analizë ir iðvados

* **Rûðiavimas ir dalijimas:** Þvelgiant á rezultatus pastebima, kad `std::list` konteineris rûðiavimo ir dalijimo etape su didesniais kiekiais (100k ir 1M áraðø) veikia þenkliai greièiau nei `std::vector` (pvz., prie 1 000 000 áraðø `std::list` uþtruko ~3.44 s, o `std::vector` – ~13.52 s). Taip yra todël, kad sàraðas naudoja savo vidiná `sort()` metodà, kuris keièia tik elementø rodykles (mazgus), o vektoriui tenka perstumti didelius atminties blokus.
* **Nuskaitymas ir áraðymas:** Duomenø nuskaitymo ir áraðymo á failus etapuose abiejø konteineriø laikai yra gana panaðûs, nes pagrindinis laikas èia priklauso nuo disko (SSD) spartos ir srautø (`std::fstream`), o ne nuo paèio konteinerio vidinës struktûros.
