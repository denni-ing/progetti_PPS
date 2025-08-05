//Crea un programma che simula una rubrica dove ogni contatto può avere più numeri di telefono.
//Inserire un nuovo contatto con uno o più numeri.
//Aggiungere un numero a un contatto esistente.
//Stampare tutti i contatti con i loro numeri, uno per riga.

#include <iostream>
#include <string>
#include <map>
#include <set>

class Rubrica{
private:
    typedef std::set<std::string> Numero;
    typedef std::map<std::string, Numero> Contatto2Number;
    Contatto2Number contatto2number;

public:
    void Add(const std::string& name, const std::string& number){
        contatto2number[name].insert(number);
    }

    void Delete(const std::string& name, const std::string& number){
        contatto2number[name].erase(number);
    }

    void Print() const{
        for(const auto& iter : contatto2number){
            std::cout << iter.first << ":\n";
            for(const auto& number_iter : iter.second){
                std::cout << number_iter << "\n";
            }
        }
        std::cout << "\n";
    }

};

int main(){

    Rubrica r1;
    r1.Add("Denni", "3334119237");
    r1.Add("Denni", "1234567891");
    r1.Add("Marco", "2671542383");
    r1.Add("Marco", "2671542383");
    r1.Add("Denni", "1237767891");

    r1.Print();

    r1.Delete("Denni", "1234567891");

    r1.Print();

    return 0;
}