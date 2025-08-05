#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Text{
    private:
        string str; //frase
        string substr; //stringa da cercare

    public:
        Text(){
            str = "";
            substr = "";
        }
        Text(string str_, string substr_){
            str = str_;
            substr = substr_;
        }
        bool searchString(bool* check){
            if(str.find(substr) != string::npos){
                *check = true;
                return *check;
            }
        }
};

class newFile{
    private:
        string filename;

    public:
        newFile(){
            filename = "";
        }
        newFile(string filename_){
            filename = filename_;
        }
        void writeOnFile(){
            ofstream of(filename);
            if (!of.good()){
                cerr << "Error, can not open file" << endl;
                return;
            }
            string testo = "";
            cout << "Inserisci il testo da copiare nel file: ";
            getline(cin, testo);  //prende tutta la frase
            of << testo; 
            cout << "Upload Successfully!" << endl;
            of.close();
        }
};

class ReadFile{
    private:
        string filename;

    public:
        ReadFile(){
            filename = "";
        }
        ReadFile(string filename_){
            filename = filename_;
        }
        void readFile(string* str){
            ifstream inf(filename);
            if(!inf.good()){
                cerr << "Error, can not open file" << endl;
                return;
            }
            string line;
            *str = "";
            while(getline(inf, *str)){ //legge tutta la stringa del testo
                *str += line;
            }
            inf.close();
        }
};

int main(){

    string filename = "stringa.txt";

    newFile file1(filename);
    file1.writeOnFile();

    ReadFile text1(filename);
    string testo = "";
    text1.readFile(&testo);

    string substr = "";
    string sn = "Y";
    while(sn == "Y"){
        cout << "Inserisci la parola da cercare nel testo: ";
        cin.ignore(); //ripulisce il buffer
        getline(cin, substr); //prende tutta la stringa da cercare
        bool check = false;
        Text t1(testo, substr);
        t1.searchString(&check);
        if (check == true){
            cout << "Stringa trovata!" << endl;
        }
        else{
            cerr << "Stringa non trovata" << endl;
        }
        substr = "";
        cout << "Vuoi cercare un'altra parola? ";
        cin >> sn;
        while (sn != "Y" && sn != "N"){
            cerr << "Errore di inserimento, digitare Y(si) o N(no) ";
            cin >> sn;
        }
    }

    return 0;
}

