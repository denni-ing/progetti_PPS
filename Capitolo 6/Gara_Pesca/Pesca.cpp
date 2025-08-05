#include <iostream>
#include <string>

class Pesce{

    private:
        std::string type;
        float peso;

    public:
        Pesce(){
            type = "Unkn";
            peso = 0.0;
        }
        Pesce(const std::string type_, const float peso_){
            type = type_;
            peso = peso_;
        }
        inline float GetPeso() const{
            return peso;
        }
        inline std::string GetType() const{
            return type;
        }
        inline void SetPeso(const int peso_){
            peso = peso_;
        }
        inline void SetType(const std::string type_){
            type = type_;
        }

};

class Partecipante{
    typedef Pesce P;
    private:
        std::string name;
        int maxpesci;
        int numpesci;
        float pesotot;
        Pesce* pesce = nullptr;
        friend std::ostream& operator<<(std::ostream& out, const Partecipante& p);

    public:
        Partecipante(){
            name = "Unkn";
            numpesci = 0;
            maxpesci = 0;
            pesotot = 0.0;
            pesce = new Pesce[maxpesci];
        }
        Partecipante(const std::string name_, const int maxpesci_){
            name = name_;
            numpesci = 0;
            pesotot = 0;
            maxpesci = maxpesci_;
            pesce = new Pesce[maxpesci]();
        }
        ~Partecipante(){
            delete[] pesce;
        }
        inline std::string GetName() const{
            return name;
        }
        inline int GetNumpesci() const{
            return numpesci;
        }
        inline float GetPesotot() const{
            return pesotot;
        }
        inline void SetName(const std::string name_){
            name = name_;
        }
        inline void SetNumpesci(const int numpesci_){
            numpesci = numpesci_;
        }
        inline void SetPesotot(const P& p){
            pesotot += p.GetPeso();
        }
        void PrintPartecipante() const{
            std::cout << GetName() << std::endl;
        }
        Partecipante& operator=(const Partecipante& right){
            if(this==&right){
                return *this;
            }if(pesce){
                delete[] pesce;
            }
            name = right.name;
            numpesci = right.numpesci;
            maxpesci = right.maxpesci;
            pesotot = right.pesotot;
            pesce = new Pesce[maxpesci];
            for(int i=0; i<maxpesci; i++){
                pesce[i] = right.pesce[i];
            }
            return *this;
        }
        Partecipante& operator+=(const Pesce& right){
            if(right.GetType() == "Spigola"){
                std::cerr << "Ha pescato la spigola, rilasciarla" << std::endl;
                return *this;
            }if(numpesci<maxpesci){
                pesce[numpesci] = right;
                numpesci++;
                pesotot += right.GetPeso();
                std::cout << name << " ha pescato " << right.GetType() << std::endl;
            }else{
                std::cout << "Raggiunto massimo numero di pesci per "<< name << std::endl;
            }
            return *this;
        }
};

std::ostream& operator<<(std::ostream& out, const Partecipante& p){
    //std::cout<< "Partecipante: " << p.GetName() << ". Ha pescato " << p.GetNumpesci() << " pesci per un totale di " << p.GetPesotot() << " Kg" << std::endl;
    std::cout<< "Partecipante: " << p.name << std::endl;
    return out;
}

class Gara{
    typedef Partecipante PR;
    typedef Pesce P;
    private:
        int maxPesci = 0;
        int numPartecipante = 0;
        int maxpartecipanti = 0;
        Partecipante* partecipante = nullptr;
        friend std::ostream& operator<<(std::ostream& out, const Gara& g);

    public:
        Gara(const int maxPesci_, const int numPartecipante_, const int maxpartecipanti_){
            maxPesci = maxPesci_;
            numPartecipante = numPartecipante_;
            maxpartecipanti = maxpartecipanti_;
            partecipante = new PR[maxpartecipanti]();
        }
        ~Gara(){
            delete[] partecipante;
        }
        Partecipante& operator[](const int i){
            if(i>=numPartecipante || i<0){
                std::cerr << "Indice non valido" << std::endl;
                return partecipante[0];
            }
            return partecipante[i];
        }
        inline int GetMaxPesci() const{
            return maxPesci;
        }
        inline int GetNumPart() const{
            return numPartecipante;
        }
        inline void SetMaxPesci(const int maxPesci_){
            maxPesci = maxPesci_;
        }
        inline void SetNumPart(const int numPartecipante_){
            numPartecipante = numPartecipante_;
        }
        Gara& operator+=(const Partecipante& right){
            if(numPartecipante == maxpartecipanti){
                std::cerr << "Numero massimo di partecipanti raggiunto" << std::endl;
                return *this;
            }
            partecipante[numPartecipante] = right;
            numPartecipante++;
            return *this;
        }
        void Vincitore(){
            int widx = 0;
            float maxw = 0;
            for(int i=0; i<numPartecipante; ++i){
                float pweight = partecipante[i].GetPesotot();
                if(maxw < pweight){
                    maxw = pweight;
                    widx = i;
                }
            }
            std::cout << "Il vincitore è..... " << partecipante[widx].GetName() << " con " << partecipante[widx].GetPesotot() << " Kg di pescato!" << std::endl;
        }
};

std::ostream& operator<<(std::ostream& out, const Gara& g){
    std::cout << "Lista partecipanti: " << std::endl;
    for(int i=0; i<g.numPartecipante; i++){
        std::cout << g.partecipante[i];
    }
    std::cout << "------------------------" << std::endl;
    return out;
}

int main(){

    int max_f = 3;
    int max_p = 4;
    //Gare
    Gara g1(max_f, 0, max_p);
    g1+=Partecipante("Denni", max_f);
    g1+=Partecipante("Lorenzo", max_f);
    g1+=Partecipante("Matteo", max_f);
    g1+=Partecipante("Mario", max_f);
    std::cout << g1;

    g1[1] += Pesce("Branzino",0.8);
    g1[2] += Pesce("Occhiata",1.1);
    g1[1] += Pesce("Serra", 1.5);
    g1[3] += Pesce("Orata",0.7);
    g1[0] += Pesce("Spigola",2);
    g1[0] += Pesce("Orata",3.3);
    g1[0] += Pesce("Sogliola",0.1);
    g1[2] += Pesce("Orata",0.3);

    g1.Vincitore();

    return 0;
}

