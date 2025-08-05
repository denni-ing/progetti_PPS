#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Oggetti{
    private:
        string name;
        string type;
        float prezzo;

    public:
        Oggetti(){
            prezzo = 0.0f;
        }
        Oggetti(string name_, string type_, float prezzo_){
            name = name_;
            type = type_;
            prezzo = prezzo_;
        }
        string GetName(){
            return name;
        }
        string GetType(){
            return type;
        }
        float GetPrezzo(){
            return prezzo;
        }
        void SetName(string name_){
            name = name_;
        }
        void SetType(string type_){
            type = type_;
        }
        void SetPrezzo(float prezzo_){
            prezzo = prezzo_;
        }
        float Aumenta(float aumento){
            prezzo += aumento;
            return prezzo;
        }
        float Diminuisci(float diminuzione){
            prezzo -= diminuzione;
            return prezzo;
        }
        float Sconto(int percentuale){
            float sconto = 0.0f;
            sconto = (prezzo/100) * percentuale;
            return sconto;
        }
};

int main(){

    Oggetti o1("tastiera 1", "tastiera", 50);
    cout << o1.GetName() << endl;
    cout << "Prezzo: " << o1.GetPrezzo() << endl;

    bool check = false;

    float delta = 0.0f;
    cout << "Inserisci aumento: ";
    cin >> delta;
    cout << "Nuovo prezzo: " << o1.Aumenta(delta) << endl;

    cout << "Inserisci diminuzione: ";
    while (!check){
        cin >> delta;
        if (delta >= 0.0 && delta <= o1.GetPrezzo()){
            check = true;
        }
        else{
            cerr << "Errore nell'inserimento della diminuzione" << endl;
            cout << "Inserisci diminuzione: ";
        }
    } check = false;
    cout << "Nuovo prezzo: " << o1.Diminuisci(delta) << endl;

    int percentuale = 0;
    cout << "Inserisci percentuale sconto: ";
    while (!check){
        cin >> percentuale;
        if (percentuale >= 0 && percentuale <= 100){
            check = true;
        }
        else{
            cerr << "Errore nell'inserimento della percentuale" << endl;
            cout << "Inserisci percentuale sconto: ";
        }
    }
    cout << "Sconto: " << o1.Sconto(percentuale) << endl;

    return 0;
}
