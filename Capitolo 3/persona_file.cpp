#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Person{
    private:
        string name;
        int age;

    public:
        Person(){
            name = "";
            age = 0;
        }
        Person(string name_, int age_){
            name = name_;
            age = age_;
        }
        void copyInFile(const string& filename){
            ofstream outf(filename, ios::app);
            if (!outf.good()){
                cerr << "ERROR, can not open file" << endl;
                return;
            }
            outf << name << "," << age << endl;
            outf.close();
            cout << "Saved successfully!" << endl;
        }
        static void readFromFile(const string& filename){
            ifstream inf(filename);
            if (!inf.good()){
                cerr << "Error, can not open file" << endl;
                return;
            }
            string line;
            while (getline(inf, line)){
                cout << line << endl;
            }
            inf.close();
        }
};


int main(){

    string filename = "person.txt";

    Person p1("Denni", 21);
    p1.copyInFile(filename);

    Person p2("Matteo", 40);
    p2.copyInFile(filename);

    string namein;
    int agein;
    string yn = "Y";

    while(yn == "Y"){
        cout << "Inserisci nome persona: ";
        cin >> namein;
        cout << "Inserisci eta persona: ";
        cin >> agein;

        Person p3(namein, agein);
        p3.copyInFile(filename);

        cout << "Vuoi aggiungere un'altra persona?: (Y si, N no) ";
        cin >> yn;
        while (yn != "Y" && yn != "N"){
            cerr << "Errore di inserimento, digitare Y o N: ";
            cin >> yn;
        }
    }

    cout << "\nRead from file: " << endl;
    Person::readFromFile(filename);
}