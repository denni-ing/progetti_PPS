/*Un ente gestisce un insieme di biciclette per il bike sharing. Le
bici si dividono in elettriche e muscolari per le quali si memorizza il
peso in kg. Le bici elettriche contengono anche i kwh della batteria
mentre le muscolari il costo ed il numero di rapporti. Permettere di:
a) permettere di scrivere e leggere da files le biciclette;
b) ottenere le bici ordinate per peso crescente.*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class BikeBase{
public:
    virtual bool ToFile(const std::string& filename) const = 0;
    virtual float GetPeso() const = 0;
    virtual ~BikeBase() { }
    static BikeBase* Build(const std::string& def);
};

class Bike : public BikeBase{
protected:
    float peso;

public:
    Bike(const float peso_) : peso(peso_) { }

    virtual float GetPeso() const {return peso;}

    virtual void Print() const{
        std::cout << peso;
    }

    virtual ~Bike() { }
};

class Electric : public Bike{
protected:
    float kwh;

public:
    Electric(const float peso_, const float kwh_) : Bike(peso_), kwh(kwh_) { }

    inline float GetKwh() const {return kwh;}

    virtual bool ToFile(const std::string& filename) const{
        std::ofstream of(filename, std::ios::app);
        if(!of.good()){
            std::cerr << "Can not open file " << filename << std::endl;
            return false; 
        }
        of << "Elettrica " << peso  << " " << kwh << std::endl;
        return true;
    }

    virtual ~Electric() { }
};

class Muscolare : public Bike{
protected:
    float costo;
    int rapporti;

public:
    Muscolare(const float peso_, const float costo_, const int rapporti_) : 
        Bike(peso_), costo(costo_), rapporti(rapporti_) { }

    inline float GetCosto() const {return costo;}
    inline int GetRapporti() const {return rapporti;}

    virtual bool ToFile(const std::string& filename) const{
        std::ofstream of(filename, std::ios::app);
        if(!of.good()){
            std::cerr << "Can not open file " << filename << std::endl;
            return false;
        }
        of << "Muscolare " << peso << " " << costo << " " << rapporti << std::endl;
        return true;
    }

    virtual ~Muscolare() { }
};

class BikeSharing{
private:
    std::vector<const BikeBase*> bikes;
    static bool ComparePeso(const BikeBase* a, const BikeBase* b){
        return a->GetPeso() < b->GetPeso();
    }

public:
    BikeSharing() { }

    void Add(BikeBase* bike){
        bikes.push_back(bike);  //no controllo su doppie bici perchè ne potrei avere 2 uguali
    }

    bool SaveToFile(const std::string& filename) const{
        std::ofstream clear(filename);
        if(!clear.good()){
            std::cerr << "Can not open file " << filename << std::endl;
            return false;
        }
        for(const auto& iter : bikes){
            iter->ToFile(filename);
        }
    }

    void LoadFromFile(const std::string& filename){
        std::istringstream is(filename);
        if(!is.good()){
            std::cerr << "Can not open file " << filename << std::endl;
            return;
        }

        bikes.clear();
        std::string line;
        while(std::getline(is, line)){
            BikeBase* bike = BikeBase::Build(line);
            if(bike){
                Add(bike);
            }
        }
    }

    void SortByPeso(){
        std::sort(bikes.begin(), bikes.end(), ComparePeso);
    }

    void PrintAll() const{
        for(const auto& iter : bikes){
            std::cout << "- peso " << iter->GetPeso() << std::endl;
        }
    }

    class ConstIterator{
    private:
        unsigned int index = 0;
        const BikeSharing* bikesharing = nullptr;

    public:
        inline ConstIterator(const BikeSharing& bikesharing_) : bikesharing(&bikesharing_) { }
        inline const BikeBase* GetNext() {
            const BikeBase* b = bikesharing->bikes[index];
            index++;
            return b;
        }
        inline bool HasNext() const{
            return index < bikesharing->bikes.size();
        }
    };

    friend class ConstIterator;

    ~BikeSharing() {
        for(const auto& iter : bikes){
            delete iter;
        }
    }
};

BikeBase* BikeBase::Build(const std::string& def){
    std::istringstream is(def);
    std::string type;
    is >> type;
    float peso;
    is >> peso;

    if(type=="Elettrica"){
        float kwh;
        is >> kwh;
        return new Electric(peso, kwh);
    }

    if(type=="Muscolare"){
        float costo;
        int rapporti;
        is >> costo >> rapporti;
        return new Muscolare(peso, costo, rapporti);
    }

    std::cerr << "Not well defined Bike from line " << def << std::endl;
    return nullptr;
};

int main(){

    BikeSharing sharing;

    // Aggiungiamo alcune bici
    sharing.Add(new Electric(12.5, 0.5));   // peso = 12.5 kg, kwh = 0.5
    sharing.Add(new Muscolare(9.0, 300.0, 18)); // peso = 9 kg, costo = 300€, rapporti = 18
    sharing.Add(new Electric(14.2, 0.8));   // un'altra bici elettrica
    sharing.Add(new Muscolare(10.0, 350.0, 21));

    // Stampiamo tutte le bici
    std::cout << "Tutte le bici:\n";
    sharing.PrintAll();

    // Ordiniamo per peso
    sharing.SortByPeso();
    std::cout << "\nDopo ordinamento per peso:\n";
    BikeSharing::ConstIterator it(sharing);
    while (it.HasNext()) {
        const BikeBase* b = it.GetNext();
        std::cout << " - peso: " << b->GetPeso() << std::endl;
    }

    // Salviamo le bici su file
    sharing.SaveToFile("bikes.txt");

    // Creiamo un nuovo oggetto e carichiamo le bici dal file (se si corregge LoadFromFile!)
    BikeSharing loaded;
    std::ifstream in("bikes.txt");
    if(in.good()) {
        std::string line;
        while(std::getline(in, line)){
            BikeBase* b = BikeBase::Build(line);
            if(b) loaded.Add(b);
        }

        std::cout << "\nBici caricate dal file:\n";
        loaded.PrintAll();
    } else {
        std::cerr << "Errore nell'apertura del file bikes.txt\n";
    }

    return 0;
}