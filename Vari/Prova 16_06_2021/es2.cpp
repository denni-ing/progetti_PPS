/*Un ente gestisce un insieme di biciclette per il bike sharing. Le
bici si dividono in elettriche e muscolari per le quali si memorizza il
peso in kg. Le bici elettriche contengono anche i kwh della batteria
mentre le muscolari il costo ed il numero di rapporti. Permettere di:
a) permettere di scrivere e leggere da files le biciclette;
b) ottenere le bici ordinate per peso crescente.*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class BikeBase{
public:
    virtual bool ToFile(const std::string& filename) const = 0;
    virtual float GetPeso() const = 0;
    virtual ~BikeBase() { }
    static BikeBase* Build(const std::string& def);
};

class Electric : public BikeBase{
protected:
    std::string id;
    float peso;
    float Kwh;

public:
    Electric(const std::string& id_,
            const float peso_,
            const float Kwh_) : 
            id(id_), peso(peso_), Kwh(Kwh_) { }

    virtual std::string GetId() const {return id;}
    virtual float GetPeso() const {return peso;}
    virtual float GetKwh() const {return Kwh;}

    virtual bool ToFile(const std::string& filename) const{
        std::ofstream of(filename);
        if(!of.good()){
            std::cerr << "Can not open " << filename << std::endl;
            return false;
        }

        of << "Elettrica " << id << " " << peso << " " << Kwh << std::endl;
        return true;
    }

    virtual ~Electric() { }
};

class Muscolare : public BikeBase{
protected:
    std::string id;
    float peso;
    int rapporti;
    float costo;

public:
    Muscolare(const std::string& id_,
            const float peso_,
            const int rapporti_,
            const float costo_):
            id(id_), peso(peso_), rapporti(rapporti_), costo(costo_) { }

    virtual std::string GetId() const {return id;}
    virtual float GetPeso() const {return peso;}
    virtual int GetRapporti() const {return rapporti;}
    virtual float GetCosto() const {return costo;}

    virtual bool ToFile(const std::string& filename) const{
        std::ofstream of(filename);
        if(!of.good()){
            std::cerr << "Can not open " << filename << std::endl;
            return false;
        }

        of << "Muscolare " << id << " " << peso << " " << rapporti << " " << costo << std::endl;
        return true;
    }
    
    virtual ~Muscolare() { }
};

class BikeComposite{
protected:
    std::vector<const BikeBase*> BikeSharing;

    static bool ComparePeso(const BikeBase* a, const BikeBase* b){
        return a->GetPeso() < b->GetPeso();
    }

public:
    BikeComposite() { }

    void AddBike(BikeBase* bike){
        BikeSharing.push_back(bike);
    }

    void SaveToFile(const std::string& filename){
        std::ifstream is(filename);
        if(!is.good()){
            std::cerr << "Can not open " << filename << std::endl;
            return;
        }

        for(const auto& bike : BikeSharing){
            bike->ToFile(filename);
        }
    }

    void LoadFromFile(const std::string& filename){
        std::ifstream is(filename);
        if(!is.good()){
            std::cerr << "Can not open " << filename << std::endl;
            return;
        }

        std::string line;
        while(std::getline(is, line)){
            BikeBase* bike = BikeBase::Build(line);
            if(bike){
                AddBike(bike);
            }
        }
    }

    void SortByPeso(){
        std::sort(BikeSharing.begin(), BikeSharing.end(), ComparePeso);
    }

    void PrintAll() const{
        for(const auto& iter : BikeSharing){
            std::cout << "- peso: " << iter->GetPeso() << std::endl;
        }
    }

    ~BikeComposite() {
        for (auto bike : BikeSharing) {
            delete bike;
        }
    }

};

BikeBase* BikeBase::Build(const std::string& def){
        std::istringstream is(def);
        std::string type;
        is >> type;
        std::string id;
        float peso;
        is >> id >> peso;

        if(type=="Elettrica"){
            float Kwh;
            is >> Kwh;
            return new Electric(id, peso, Kwh);
        }

        if(type=="Muscolare"){
            int rapporti;
            float costo;
            is >> rapporti >> costo;
            return new Muscolare(id, peso, rapporti, costo);
        }

        std::cerr << "Bici non definita " << def << std::endl;
        return nullptr; 
};

int main() {
    BikeComposite bikeManager;

    // Carica bici da file (devi creare un file "bikes.txt" con righe come queste):
    // Elettrica bike01 12.5 3.7
    // Muscolare bike02 9.0 21 120.0
    bikeManager.LoadFromFile("bikes.txt");

    // Ordina le bici per peso crescente
    bikeManager.SortByPeso();

    // Salva le bici ordinate in un altro file
    bikeManager.SaveToFile("bikes_sorted.txt");

    // Stampa a video le bici caricate e ordinate
    std::cout << "Biciclette caricate e ordinate per peso:" << std::endl;
    bikeManager.PrintAll();
    
    return 0;
}