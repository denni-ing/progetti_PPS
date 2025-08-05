/*Scrivere un contenitore templetizzato che memorizza un
insieme di oggetti e che implementa i seguenti metodi:
a) determinare se un oggetto e' presente nel contenitore;
b) ritornare la media delle istanze memorizzate;
c) permettere salvare i dati su file e permettere di ricaricarli.
Quindi implementare una classe NumeroComplesso che possa
essere utilizzata nel contenitore precedentemente costruito.*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class NumeroComplesso{
private:
    float re;
    float im;
    friend std::ostream& operator<<(std::ostream& os, const NumeroComplesso& n);
    friend std::istream& operator>>(std::istream& is, NumeroComplesso& n);

public:
    NumeroComplesso() : re(0.0f), im(0.0f) { }
    NumeroComplesso(const float re_, const float im_) : re(re_), im(im_) { }

    inline float GetRe() const {return re;}
    inline float GetIm() const {return im;}

    NumeroComplesso operator+(const NumeroComplesso& n1) const{
        return NumeroComplesso(re + n1.re, im + n1.im);
    }
    NumeroComplesso operator/(const float scalar){
        return NumeroComplesso(re / scalar, im / scalar);
    }
    bool operator==(const  NumeroComplesso& right) const{
        return re==right.re && im==right.im;
    }

    void PrintComplesso() const{
        if(im < 0){
            std::cout << re << " - j" << im << std::endl;
        }else{
            std::cout << re << " + j" << im << std::endl;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const NumeroComplesso& n){
    return os << n.re << " " << n.im;
}

std::istream& operator>>(std::istream& is, NumeroComplesso& n){
    return is >> n.re >> n.im;
}

template<typename T>
class Container{
private:
    std::vector<T> Element;

public:
    Container() { }

    void Add(const T element){
        for(const auto& iter : Element){
            if(iter==element){
                std::cout << "elemento " << element << " gia' presente" << std::endl;
                return;
            }
        }
        Element.push_back(element);
    }

    void Search(const T element){
        for(const auto& iter : Element){
            if(iter==element){
                std::cout << "elemento " << element << " presente nel contenitore" << std::endl;
                return;
            }
        }
        std::cerr << "L'elemento " << element << " non presente nel contenitore" << std::endl;
    }

    T Media() const{
        T sum = T();
        for(const auto& iter : Element){
            sum = sum + iter;
        }
        return sum / Element.size();
    }

    void ToFile(const std::string& filename){
        std::ofstream of(filename);
        if(!of.good()){
            std::cerr << "Can not open file " << filename << std::endl;
            return;
        }

        for(const auto& iter : Element){
            of << iter << std::endl;
        }
        std::cout << "Salvataggio su file effettuato" << std::endl;
    }

    void Uploadelement(const std::string& filename){
        std::ifstream is(filename);
        if(!is.good()){
            std::cerr << "Can not open file " << filename << std::endl;
            return;
        }

        T el;
        Element.clear();
        while(is >> el){
            Element.push_back(el);
        }
    }
};

int main(){

    Container<NumeroComplesso> c;

    // Aggiunta di alcuni numeri complessi
    NumeroComplesso n1(1.0f, 2.0f);
    NumeroComplesso n2(3.0f, 4.0f);
    NumeroComplesso n3(1.0f, 2.0f); // Duplicato

    c.Add(n1);
    c.Add(n2);
    c.Add(n3); // Non verrà aggiunto perché duplicato

    // Ricerca
    c.Search(n1);  // Presente
    c.Search(NumeroComplesso(5.0f, 6.0f));  // Assente

    // Media
    NumeroComplesso media = c.Media();
    std::cout << "Media: ";
    media.PrintComplesso();

    // Salvataggio su file
    c.ToFile("complessi.txt");

    // Caricamento da file in un nuovo contenitore
    Container<NumeroComplesso> c2;
    c2.Uploadelement("complessi.txt");

    std::cout << "Elementi caricati da file:" << std::endl;
    NumeroComplesso m2 = c2.Media();
    m2.PrintComplesso();
    c2.Search(NumeroComplesso(3.0f, 4.0f)); 

    return 0;
}

