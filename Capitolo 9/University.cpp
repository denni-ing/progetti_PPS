#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class PersonBase{
    public:
        virtual string ToString() const = 0;
        virtual bool ToFile(const string& filename) const = 0;
};

class Persona : public PersonBase{
    protected:
        string name;
        string cittadinanza;

    public:
        Persona(){
            name = "Unkn";
            cittadinanza = "Unkn";
        }
        Persona(const string name_, const string cittadinanza_):
            name(name_), cittadinanza(cittadinanza_) { }
        inline string GetName() const{
            return name;
        }
        inline string GetCittadinanza() const{
            return cittadinanza;
        }
};

class Docente : public Persona{
    protected:
        string corso;

    public:
        Docente(const string name_, const string cittadinanza_, const string corso_):
            Persona(name_, cittadinanza_), corso(corso_) { }
        inline string GetCorso() const{
            return corso;
        }
        virtual string ToString() const{
            return "Docente: " + name + " " + cittadinanza + " " + corso + "\n";
        }
        virtual bool ToFile(const string& filename) const{
            ofstream of(filename, ios::app);
            if(!of.good()){
                cerr << "Errore apertura del file" << endl;
                return false;
            }
            of << this->ToString();
            return true;
        }
};

class Ricercatore : public Persona{
    protected:
        string argomenti;

    public:
        Ricercatore(const string name_, const string cittadinanza_, const string argomenti_):
            Persona(name_, cittadinanza_), argomenti(argomenti_) { }
        inline string GetArg() const{
            return argomenti;
        }
        virtual string ToString() const{
            return "Ricercatore: " + name + " " + cittadinanza + " " + argomenti + "\n";
        }
        virtual bool ToFile(const string& filename) const{
            ofstream of(filename, ios::app);
            if(!of.good()){
                cerr << "Errore apertura del file" << endl;
                return false;
            }
            of << this->ToString();
            return true;
        }
};

class Studente : public Persona{
    protected:
        string facolta;
        string corso;
    
    public:
        Studente(const string name_, const string cittadinanza_, const string facolta_, const string corso_):
            Persona(name_, cittadinanza_), facolta(facolta_), corso(corso_) { }
        inline string GetFacolta() const{
            return facolta;
        }
        inline string GetCorso() const{
            return corso;
        }
        virtual string ToString() const{
            return "Studente: " + name + " " + cittadinanza + " " + facolta + " " + corso + "\n";
        }
        virtual bool ToFile(const string& filename) const{
            ofstream of(filename, ios::app);
            if(!of.good()){
                cerr << "Errore apertura del file" << endl;
                return false;
            }
            of << this->ToString();
            return true;
        }
};

int main(){

    Studente student("Mario Rossi", "Italiana", "Ingegneria", "PPS");
    student.ToFile("file.txt");
    
    Docente docente("Mario Rossi", "Italiana", "PPS");
    docente.ToFile("file.txt");
    
    Ricercatore ricercatore("Mario Rossi", "Italiana", "PPS");
    ricercatore.ToFile("file.txt");

    return 0;
}
