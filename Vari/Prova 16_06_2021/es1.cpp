/*Realizzare un contenitore templetizzato SamplingContainer
che permetta di gestire un gruppo di elementi:
a) aggiungere un elemento;
b) determinare se due insiemi coincidono mediante un operator!=;
c) cercare se un elemento fa parte dell’insieme;
d) ottenete un campione di N elementi casuali dall’insieme.*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <set>

template<typename T>
class SamplingContainer;

template<typename T>
bool operator!=(const SamplingContainer<T>& left, const SamplingContainer<T>& right);

template<typename T>
class SamplingContainer{
private:
    std::vector<T> Elements;
    friend bool operator!=<>(const SamplingContainer<T>& left, const SamplingContainer<T>& right);

public:
    SamplingContainer() { }
    void Add(const T element){
        for(const auto& iter : Elements){
            if(iter == element){
                std::cout << "Elemento gia' presente nel contenitore" << std::endl;
                return;
            }
        }
        Elements.push_back(element);
    }

    void search(const T element){
        for(const auto& iter : Elements){
            if(iter == element){
                std::cout << "Elemento " << iter << " presente nel contenitore" << std::endl;
                return;
            }
        }
        std::cout << "Elemento " << element << " non presente nel contenitore" << std::endl;
    }

    void Random() const{

        if(Elements.empty()){
            std::cerr << "Contenitore vuoto, nessun campione possibile." << std::endl;
            return;
        }

        std::set<T> random;

        int maxlen = Elements.size();
        int numero = std::rand() % maxlen + 1;

        while((int)random.size() < numero){
            int index = std::rand() % maxlen;
            random.insert(Elements[index]);
        }

        std::cout << "Campione casuale (" << numero << " elementi)" << std::endl;
        for(const auto& iter : random){
            std::cout << iter << std::endl;
        }
    }

    
};

template<typename E>
bool operator!=(const SamplingContainer<E>& left, const SamplingContainer<E>& right){
    if(left.Elements.size() != right.Elements.size()) {return true;}

    std::vector<E> leftcopy = left.Elements;
    std::vector<E> rightcopy = right.Elements;

    std::sort(leftcopy.begin(), leftcopy.end());
    std::sort(rightcopy.begin(), rightcopy.end());

    return leftcopy != rightcopy;
}


int main(){

    SamplingContainer<std::string> c1;

    c1.Add("ciao");
    c1.Add("Hello");
    c1.Add("Bye");
    c1.Add("prova1");
    c1.Add("prova2");

    SamplingContainer<std::string> c2;

    c2.Add("Hello");
    c2.Add("ciao");

    c1.search("Hello");

    if(c1!=c2){
        std::cout << "Contenitori non uguali" << std::endl;
    }else{
        std::cout << "Contenitori uguali" << std::endl;
    }

    c1.Random();

    return 0;
}