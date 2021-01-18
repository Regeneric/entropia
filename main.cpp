#include <iostream>
#include <fstream>
#include <streambuf>
#include <chrono>

#include <map>
#include <string>

#include <cmath>


double entropy(std::string testString, bool debug);
double jointEntropy(std::string firstString, std::string secondString);
// double condEntropy(std::string firstString, std::string secondString, double jointValue);

int main(int argc, char** argv) {
    if(argc <= 1) {std::cout << "Muisz podać ściężkę do pliku .txt!" << std::endl; return 1;}   // Programu nie da się uruchomić bez danych wejściowych

    // Zwykłe czytanie pliku do stringa
    std::ifstream textFile(argv[1]);
    std::string testString((std::istreambuf_iterator<char>(textFile)), std::istreambuf_iterator<char>());
    // auto begin = std::chrono::high_resolution_clock::now();

    // Wypisywanie wyników na ekranie
    std::cout << "Entropy: " << ([&testString, &argc, &argv]() {
        return (argc > 2 && !(static_cast<std::string>("-d").compare(argv[2]))) 
            ? entropy(testString, true) : entropy(testString, false);
        })() << std::endl;

    std::cout << "Joint entropy: " << jointEntropy(testString, "abcd") << std::endl;
    // std::cout << "Cond entropy: " << condEntropy(testString, "abcd", jointEntropy(testString, "abcd")) << std::endl;


    // auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    return 0;
}


double entropy(std::string testString, bool debug) {
    // Pętla która zapisuje w mapie ile razy dany znak wystąpił w tekście
    // Struktura to: ['A' 357, 'B' 241]
    std::map<char, int> charsCounted{};
    for(const char &c : testString) charsCounted[c] ++;

    int numLen = testString.length();
    double infoContent = .0;

    // H(X) = - \sum p(x) \log p(x)
    for(const std::pair<char, int> &p : charsCounted) {    
        double freq = static_cast<double>(p.second)/numLen;     // Prawdopodobieństwo wystąpienia danego znaku
        infoContent -= freq * ([&freq](){return log(freq)/log(2);})();    // Wyliczanie entropii bitowej

        // Flaga '-d' może zostać wykorzystana do wyświetlenia sobie dodatkowych informacji
        if(debug) std::cout << "Char: " << p.first << " Count: " << p.second << " Prob: " << freq << std::endl;
    } if(debug) std::cout << "\nString: " << testString << "\n\n";
    
    return infoContent;
}

double jointEntropy(std::string firstString, std::string secondString) {
    // Tworzenie płaszczyzny na podstawie przekazanych stringów
    std::map<char, int> charsCounted{};
    for(const char &fs : firstString) {
        charsCounted[fs] ++;
        for(const char &ss : secondString) {
            charsCounted[ss] ++;
        }
    }

    int numLen = firstString.length() * secondString.length();
    double infoContent = .0;

    // H(XY) = - \sum_x \sum_y p(xy) \log p(xy)
    for(const std::pair<char, int> &p : charsCounted) {
        double freq = static_cast<double>(p.second)/numLen;
        infoContent -= freq * ([&freq](){return log(freq)/log(2);})();
    } return infoContent;
}

// double condEntropy(std::string firstString, std::string secondString, double jointValue) {
//     std::map<char, int> charsCounted{};
//     std::map<char, int> charsCountedSecond{};

//     // Tworzenie płaszczyzny na podstawie przekazanych stringów oraz zapisywanie informacji o drugim stringu
//     for(const char &fs : firstString) {
//         charsCounted[fs] ++;
//         for(const char &ss : secondString) {
//             charsCounted[ss] ++;
//             charsCountedSecond[ss] ++;
//         }
//     }

//     int numLen = firstString.length() * secondString.length();
//     double infoContent = .0;

//     // H(X|Y) = - \sum_x \sum_y p(x,y) \log p(x,y)/p(y)
//     for(const std::pair<char, int> &p : charsCounted) {
//         for(const std::pair<char, int> &ccs : charsCountedSecond) {
//             double freq = static_cast<double>(p.second)/numLen;    // Pierwszy string idzie standardową iteracją
//             double condValue = static_cast<double>(p.second)/firstString.length();    // Drugi string idzie iteracją podzieloną przez ilość wystąpień znaków w pierwszym

//             if(freq > 0 && condValue > 0) infoContent -= freq * ([&freq, &condValue](){return log(freq/condValue)/log(2);})();
//         }
//     } return infoContent;
// }