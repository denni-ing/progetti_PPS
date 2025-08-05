//Scrivi un programma per gestire un catalogo di libri. Ogni genere è associato a un vettore di titoli.
//Inserire titoli in base al genere.
//Stampare i generi in ordine alfabetico con l’elenco dei libri.
//Utilizzare iteratori per scorrere la mappa e i vettori.

#include <iostream>
#include <string>
#include <map>
#include <set>

class Catalogo{
private:
    typedef std::set<std::string> Libri;
    typedef std::map<std::string, Libri> Genere2Libri;
    Genere2Libri genere2libri;

public:
    void Add(const std::string& genere, const std::string& libro){
        genere2libri[genere].insert(libro);
    }

    void Delete(const std::string& genere, const std::string& libro){
        genere2libri[genere].erase(libro);
    }

    void Print() const{
        for(const auto& iter : genere2libri){
            std::cout << "\n" << iter.first << ":\n";
            for(const auto& libri_iter : iter.second){
                std::cout << "- " << libri_iter << "\n";
            }
        }
        std::cout << "\n";
    }
};


int main(){

    Catalogo c1;
    c1.Add("Fantascienza", "Dune");
    c1.Add("Fantascienza", "Neuromante");
    c1.Add("Fantasy", "Il Signore degli Anelli");

    c1.Print();

    return 0;
}