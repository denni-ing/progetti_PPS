#include <iostream>
#include <string>
using namespace std;

class Paziente{

    private:
        string name;
        int num_prenotazione;
        int data; //indica il giorno (ad es: 0 = lunedì)

    public:
        Paziente(){
            name = "Unkn";
            num_prenotazione = 0;
            data = 0;
        }
        Paziente(const string name_, const int num_prenotazione_, const int data_){
            name = name_;
            num_prenotazione = num_prenotazione_;
            data = data_;
        }
        inline string GetName() const{
            return name;
        }
        inline int GetNumPrenotazione() const{
            return num_prenotazione;
        }
        inline int GetData() const{
            return data;
        }
        Paziente& operator=(const Paziente& right){
            if(this==&right){
                return *this;
            }
            name = right.name;
            num_prenotazione = right.num_prenotazione;
            data = right.data;
            return *this;
        }
};

class Ambulatorio{

    private:
        string branca;
        int max_pazienti;
        int num_pazienti;
        float costo;
        bool apertura[7];
        Paziente* paziente;
        friend ostream& operator<<(ostream& out, const Ambulatorio& a);

    public:
        Ambulatorio(){
            branca = "Unkn";
            max_pazienti = 0;
            num_pazienti = 0;
            costo = 0.0;
            paziente = new Paziente[max_pazienti];
        }
        Ambulatorio(const string branca_, const int max_pazienti_, const float costo_, const bool apertura_[7]){
            branca = branca_;
            max_pazienti = max_pazienti_;
            num_pazienti = 0;
            costo = costo_;
            for(int i=0; i<7; i++){
                apertura[i] = apertura_[i];
            }
            paziente = new Paziente[max_pazienti]();
        }
        ~Ambulatorio(){
            delete[] paziente;
        }
        Ambulatorio(const Ambulatorio& right){
            branca = right.branca;
            num_pazienti = right.num_pazienti;
            max_pazienti = right.max_pazienti;
            costo = right.costo;
            for(int i=0; i<7; i++){
                apertura[i] = right.apertura[i];
            }
            paziente = new Paziente[max_pazienti]();
            for(int i=0; i<max_pazienti; i++){
                paziente[i] = right.paziente[i];
            }
        }
        Ambulatorio& operator=(const Ambulatorio& right){
            if(this == &right){
                return *this;
            }
            branca = right.branca;
            num_pazienti = right.num_pazienti;
            max_pazienti = right.max_pazienti;
            costo = right.costo;
            for(int i=0; i<7; i++){
                apertura[i] = right.apertura[i];
            }
            paziente = new Paziente[max_pazienti]();
            for(int i=0; i<max_pazienti; i++){
                paziente[i] = right.paziente[i];
            }
        }
        inline string GetBranca() const{
            return branca;
        }
        inline int GetMaxPazienti() const{
            return max_pazienti;
        }
        inline int GetNumPazienti() const{
            return num_pazienti;
        }
        inline float GetCosto() const{
            return costo;
        }
        inline bool GetApertura(const int i) const{
            return apertura[i];
        }
        string Giorno(const int i) const{
            if(i==0){
                return "Lunedi";
            }if(i==1){
                return "Martedi";
            }if(i==2){
                return "Mercoledi";
            }if(i==3){
                return "Giovedi";
            }if(i==4){
                return "Venerdi";
            }if(i==5){
                return "Sabato";
            }if(i==6){
                return "Domenica";
            }
        }
        inline bool SetPazienti(const Paziente& p){ //Aggiunge pazienti all'ambulatorio
            if (num_pazienti >= max_pazienti){ 
                cerr << "Ambulatorio pieno, impossibile aggiungere altri pazienti" << endl;
                return false;
            }
            if(apertura[p.GetData()] == false){
                cerr << "Ambulatorio chiuso nella seguente data" << endl;
                return false;
            }
            paziente[num_pazienti] = p; 
            num_pazienti++;
            cout << "Prenotazione avvenuta: " << p.GetName() << " giorno: " << Giorno(p.GetData()) << endl;
            return true;
        }
};

ostream& operator<<(ostream& out, const Ambulatorio& a){
    cout << "----PAZIENTI AMBULATORIO " << a.GetBranca() << " ----" << endl;
    for(int i=0; i<a.num_pazienti; i++){
        cout << a.paziente[i].GetName() << endl;
    }
    cout << "----------------------------------------" << endl << endl;
    return out; 
}

class Clinica{

    private:
        int max_pazienti_clinica;
        int max_ambulatori;
        int num_ambulatori;
        float tot_introiti;
        int tot_pazienti;
        Ambulatorio* ambulatorio;
        Paziente* paziente;
        friend ostream& operator<<(ostream& out, const Clinica& c);
    
    public:
        Clinica(){
            max_pazienti_clinica = 0;
            max_ambulatori = 0;
            num_ambulatori = 0;
            tot_introiti = 0.0;
            tot_pazienti = 0;
            ambulatorio = new Ambulatorio[max_ambulatori];
            paziente = new Paziente[max_pazienti_clinica];   
        }
        Clinica(const int max_pazienti_clinica_, const int max_ambulatori_){
            max_pazienti_clinica = max_pazienti_clinica_;
            max_ambulatori = max_ambulatori_;
            num_ambulatori = 0;
            tot_introiti = 0.0;
            tot_pazienti = 0;
            ambulatorio = new Ambulatorio[max_ambulatori]();
            paziente = new Paziente[max_pazienti_clinica]();
        }
        ~Clinica(){
            delete[] ambulatorio;
            delete[] paziente;
        }
        inline int GetMaxPazC() const{
            return max_pazienti_clinica;
        }
        inline int GetMaxAmbulatori() const{
            return max_ambulatori;
        }
        inline int GetNumAmbulatori() const{
            return num_ambulatori;
        }
        inline float GetTotIntroiti() const{
            return tot_introiti;
        }
        inline int GetTotPazienti() const{
            return tot_pazienti;
        }
        inline void set_max_pazienti_clinica(const Ambulatorio& a){
            max_pazienti_clinica += a.GetMaxPazienti();
        }
        inline void SetPazientiAmbulatorio(const int i, const int j){
            if (i >= num_ambulatori || i < 0) {
                cerr << "Indice ambulatorio non valido" << endl;
                return;
            }
            if (j >= tot_pazienti || j < 0) {
                cerr << "Indice paziente non valido" << endl;
                return;
            }
            bool check = ambulatorio[i].SetPazienti(paziente[j]);
            if(check){  //controlla se la prenotazione è avvenuta, nel caso incrementa gli introiti
                tot_introiti += ambulatorio[i].GetCosto();
                cerr << "Pagamento visita effettuato" << endl;
            }
        }
        Clinica& operator+=(const Ambulatorio& right){  //Nuovo ambulatorio
            if(num_ambulatori == max_ambulatori){
                cerr << "Numero massimo ambulatori raggiunto, impossibile aggiungerne altri" << endl;
                return *this;
            }
            ambulatorio[num_ambulatori] = right;
            num_ambulatori++;
            set_max_pazienti_clinica(right); //incrementa il numero massimo di pazienti in clinica
            return *this;
        }
        Clinica& operator+=(const Paziente& right){
            if(tot_pazienti == max_pazienti_clinica){
                cerr << "Numero massimo pazienti nella clinica raggiunto" << endl;
                return *this;
            }
            if(right.GetData() < 0 || right.GetData() >= 7){ //controlla la data per la prenotazione(la prenotazione avviene in SetPazientiAmbulatorio)
                cerr << "Data errata";
                return *this;
            }
            paziente[tot_pazienti] = right;
            tot_pazienti++; //incrementa numero pazienti in clinica
            return *this;
        }
        Paziente& operator[](const int i) {
            if (i >= tot_pazienti || i < 0) {
                cerr << "Indice non valido o paziente non inizializzato" << endl; 
                return paziente[0]; 
            }
            return paziente[i];
        }
        Ambulatorio& GetAmbulatorio(int i) {
            if (i >= num_ambulatori || i < 0) {
                cerr << "Indice non valido o ambulatorio non inizializzato" << endl; 
                return ambulatorio[0];
            }
            return ambulatorio[i];
        }
        void stampaAmbulatori(){
            cout << endl << "----AMBULATORI----" << endl;
            for(int i=0; i<num_ambulatori; i++){
            cout << ambulatorio[i].GetBranca() << endl;
            }
            cout << "------------------" << endl;
        }
        void StampaSimSettimana() { //simula la settimana
            const string giorni_settimana[7] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi", "Sabato", "Domenica"};
        
            for (int i = 0; i < 7; i++) { //scorre i giorni
                cout << "---- " << giorni_settimana[i] << " ----" << endl;
                bool almeno_uno_aperto = false;
        
                for (int j = 0; j < GetNumAmbulatori(); j++) {
                    Ambulatorio a = GetAmbulatorio(j);
                    if (a.GetApertura(i)) {  //controlla ciascun ambulatorio se è aperto
                        cout << "Ambulatorio " << a.GetBranca() << " aperto." << endl;
                        almeno_uno_aperto = true;
                        cout << a; //stampa i pazienti prenotati nell'ambulatorio
                    }
                }
        
                if (!almeno_uno_aperto) {
                    cout << "Nessun ambulatorio aperto." << endl;
                }
                cout << "------------------------" << endl;
            }
        }
};

ostream& operator<<(ostream& out, const Clinica& c){
    cout << endl << "----PAZIENTI----" << endl;
    for(int i=0; i<c.tot_pazienti; i++){
        cout << c.paziente[i].GetName() << endl;
    }
    cout << "----------------" << endl;
    cout << "INTROITI: " << c.GetTotIntroiti() << endl << endl;
    return out;
}

int main(){

    int N = 5;
    int M = 3;
    Clinica c(N, M);

    bool apertura_oculista[7] = {false};
    apertura_oculista[0] = true;
    apertura_oculista[4] = true;

    bool apertura_fisio[7] = {false};
    apertura_fisio[1] = true;
    apertura_fisio[3] = true;

    c+=Ambulatorio("oculistica", 10, 40, apertura_oculista);
    c+=Ambulatorio("Fisioterapia", 5, 60.5, apertura_fisio);

    c+=Paziente("denni_luchetti", 1, 0);
    c+=Paziente("mario_rossi", 2, 4);
    c+=Paziente("Anna Bianchi", 3, 3);

    c.SetPazientiAmbulatorio(0, 0);
    c.SetPazientiAmbulatorio(0, 1);
    c.SetPazientiAmbulatorio(1, 2);

    cout << c;

    c.StampaSimSettimana(); //simula la settimana

    cout << c;

    return 0;
}
