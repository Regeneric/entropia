```cpp
double entropy(std::string testString, bool debug);
```

Funkcja na samym początku zlicza wystąpienia znaków w tekście, przyjętym w parametrze `testString`. Wykorzystano `std::map<char, int>` z powodu prostoty. 

Zamiast ręcznie śledzić wystąpienia danego znaku, a potem korzystać z np. `std::vector<std::pair<char, int>>`, możemy w prosty sposób odwołać się do zadanej wartości, by zinkrementować o 1 ilość wystąpień danego znaku.

W przypadku niewielkich stringów, wektor mógłby być szybszy, a wykorzystanie `std::unordered_map` dość konkretnie przyspieszyć działanie całości w wybranych wypadkach, ale do danych odnosimy się później w sposób liniowy, więc została zwykła mapa.

```cpp
std::map<char, int> charsCounted{};
for(const char &c : testString) charsCounted[c] ++;
```

`freq` określa prawdopodobieństwo wystąpienia danego znaku. Zwyczajne podliczenie wszystkich wystąpień podzielone przez długość stringa `testString`.

Zastosowanie lambdy w postaci `([&](){return})()` ma jedynie za zadanie trochę skompresować kod. Nie ma przeszkód, by wrzucić sobie to w jakąś zwykłą funkcję pokroju `double log2(double);`. Referencja jest, żeby nie pracować na kopii, ale jednocześnie nie modyfikować oryginału, więc bez słowa kluczowego `mutable`. Przekazanie przez wartość też by działało, a samo kiopowanie `double` jest lekkie i szybkie, no ale jak już mamy `const char &c` w pętli, to i tutaj coś urwiemy na wydajności.

```cpp
int numLen = testString.length();
double infoContent = .0;

for(const std::pair<char, int> &p : charsCounted) {    
    double freq = static_cast<double>(p.second)/numLen;
    infoContent -= freq * ([&freq](){return log(freq)/log(2);})();
}
```

## ---------------

Czas działania programu mierzony jest z użyciem biblioteki `<chrono>`, a także pliku testowego `pol.txt`.

```cpp
auto begin = std::chrono::high_resolution_clock::now();
// kod
auto end = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
```

`double entropy(std::string, bool);` - 0.004 sekundy.  
`double jointEntropy(std::string, std::string);` - 0.003 sekundy.  
`double condEntropy(std::string, std::string, double);` - 0.030 sekundy.

Przy próbie wykorzystanie -NIXowego `time`, zarówno wall jak i CPU są równe `0.00`, przez domyślną precyzję pomiaru.

## ---------------

Przykładowe wyniki na podstawie plików `control.txt`, `pol.txt`, `ger.txt` oraz `eng.txt`.

`control.txt` - Entropia: 2  
`pol.txt` - Entropia: 4.86325  
`ger.txt` - Entropia: 4.54964  
`eng.txt` - Entropia: 4.38463  