#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person{

    private:
        string name;
        int n_p;
        string day;

    public:
        Person(){
            name = "Unkn";
            n_p = 0;
            day = "";
        }
        Person(const string name_, const string day_){
            name = name_;
            n_p++;
            day = day_;
        }
        inline string GetName() const{
            return name;
        }
        inline string GetDay() const{
            return day;
        }
};

class Ambulatory{

    private:
    string branca;
    int max_p;
    int n_p;
    float cost;
    vector<string> open;
    vector<Person> person;

    public:
        Ambulatory(){
            branca = "Unkn";
            max_p = 0;
            n_p = 0;
            cost = 0.0;
            open = {};
            person = {};
        }
        Ambulatory(const string& branca_, const int max_p_, const float cost_){
            branca = branca_;
            max_p = max_p_;
            n_p = 0;
            cost = cost_;
            open = {};
            person = {};
        }
        inline int GetMaxP() const{
            return max_p;
        }
        inline string GetBranca() const{
            return branca;
        }
        inline float GetCost() const{
            return cost;
        }
        void SetOpen(const int day){
            if(day == 0){
                open.push_back("Lunedi");
            }
            if(day == 1){
                open.push_back("Martedi");
            }
            if(day == 2){
                open.push_back("Mercoledi");
            }
            if(day == 3){
                open.push_back("Giovedi");
            }
            if(day == 4){
                open.push_back("Venerdi");
            }
            if(day == 5){
                open.push_back("Sabato");
            }
            if(day == 6){
                open.push_back("Domenica");
            }
        }
        bool Register(const Person& p){
            if(n_p == max_p){
                cerr << "Numero massimo di pazienti per l'ambulatorio " << branca << " raggiunto" << endl;
            }

            bool validDay = false;
            for(int i=0; i<open.size(); i++){
                if(open[i] == p.GetDay()){
                    validDay = true;
                }
            }

            if(!validDay){
                cerr << "L'ambulatorio " << branca << " non e' aperto il giorno " << p.GetDay() << endl;
                return false;
            }

            person.push_back(p);
            n_p++;
            cout << "Paziente " << p.GetName() << " registrato nell'ambulatorio " << branca 
            << " per il giorno " << p.GetDay() << endl;
            return true;
        }
        void PrintPerson() const{
            for(int i=0; i<person.size(); i++){
                cout << person[i].GetName() << "\t" << person[i].GetDay() << endl; 
            }
        }
};

class Clinic{

    private:
    int max_p; //max pazienti
    int max_a; //max ambulatori
    int n_a; //numero ambulatori
    float income;
    int tot_p; //pazienti totali
    vector<Ambulatory> ambulatory;
    vector<Person> person;

    public:
        Clinic(){
            max_p = 0;
            max_a = 0;
            n_a = 0;
            income = 0.0;
            tot_p = 0;
            ambulatory = {};
            person = {};
        }
        Clinic(const int max_a_){
            max_p = 0;
            max_a = max_a_;
            n_a = 0;
            income = 0.0;
            tot_p = 0;
            ambulatory = {};
            person = {};
        }
        inline void SetMaxP(const int val){
            max_p+=val;
        }
        inline float GetIncome() const{
            return income;
        }
        Clinic& operator+=(const Ambulatory& right){
            if(n_a == max_a){
                cerr << "Numero massimo ambulatori raggiunto" << endl;
                return *this;
            }
            ambulatory.push_back(right);
            n_a++;
            SetMaxP(right.GetMaxP());
            cout << "Ambulatorio " << right.GetBranca() << " aggiunto con successo" << endl;

            return *this;
        }
        Clinic& operator+=(const Person& right){
            if(tot_p == max_p){
                cerr << "Numero massimo pazienti per la clinica raggiunto" << endl;
                return *this;
            }
            person.push_back(right);
            tot_p++;
            cout << "Paziente " << right.GetName() << " registrato nella clinica" << endl;
            return *this;
        }
        void AssignPerson(int ambIndex, int perIndex){
            if(ambIndex < 0 || ambIndex >= ambulatory.size()){
                cerr << "Indice ambulatorio non valido" << endl;
                return;
            }
            if(perIndex < 0 || perIndex >= person.size()){
                cerr << "Indice paziente non valido" << endl;
                return;
            }
            Person p = person[perIndex];
            bool check = false;
            check = ambulatory[ambIndex].Register(p);
            if(check){
                income += ambulatory[ambIndex].GetCost();
            }
        }
        void SetOpenAmbulatory(const int ambIndex, const int day){
            ambulatory[ambIndex].SetOpen(day);
        }
        void PrintResume() const{
            cout << endl;
            cout << "------------RIEPILOGO------------" << endl;
            cout << "PAZIENTI:" << endl;
            for(int i=0; i<person.size(); i++){
                cout << person[i].GetName() << endl;
            }
            cout << endl << "AMBULATORI E VISITE:" << endl;
            for(int i=0; i<ambulatory.size(); i++){
                cout << ambulatory[i].GetBranca() << ":" << endl;
                ambulatory[i].PrintPerson();
                cout << endl;
            }
            cout << endl << "INTROITI: " << income << endl;
            cout << "--------------------------------" << endl;
        }
};

int main(){

    int M = 3;
    Clinic c1(M);

    c1+=Ambulatory("Oculistica", 3, 40);
    c1+=Ambulatory("Fisioterapia", 4, 70);

    c1.SetOpenAmbulatory(0, 0);
    c1.SetOpenAmbulatory(0, 4);
    c1.SetOpenAmbulatory(1, 1);

    c1+=Person("Mario Rossi", "Venerdi");
    c1+=Person("Anna Bianchi", "Martedi");
    c1+=Person("Gennaro Gattuso", "Venerdi");
    c1+=Person("Peppino Prisco", "Lunedi");
    c1+=Person("Diego Milito", "Martedi");

    c1.AssignPerson(0,0);
    c1.AssignPerson(1,1);
    c1.AssignPerson(0,2);
    c1.AssignPerson(0,3);
    c1.AssignPerson(1,4);

    c1.PrintResume();

    return 0;

}