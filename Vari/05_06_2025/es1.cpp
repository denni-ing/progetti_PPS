//Scrivi un programma che legge una frase dall’utente e calcola quante volte 
//appare ciascuna parola. Stampa il risultato in ordine alfabetico

#include <iostream>
#include <map>
#include <string>
#include <sstream>

class Word{
private:
    typedef std::map<std::string, int> Word2Freq;
    Word2Freq word2freq;

public:
    Word(const std::string stringa){
        std::istringstream is(stringa);
        std::string word;
        while(is >> word){
            word2freq[word]++;
        }
    }

    void Print() const{
        for(const auto& iter : word2freq){
            std::cout << iter.first << " -> " << iter.second << std::endl;
        }
    }
};

int main(){

    std::string str;
    std::cout << "Inserisci una frase: ";
    std::getline(std::cin, str);

    Word w(str);
    w.Print();

    return 0;
}