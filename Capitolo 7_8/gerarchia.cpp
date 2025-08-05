#include <iostream>

using namespace std;

class Persona{
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
        void PrintDocente() const{
            cout << "Docente: " << endl <<
            "nome: " << name << "\t" << "cittadinanza: " << cittadinanza << 
            "\t" << "corso: " << corso << endl;
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
        void PrintRicercatore() const{
            cout << "Ricercatore: " << endl <<
            "nome: " << name << "\t" << "cittadinanza: " << cittadinanza << 
            "\t" << "argomenti: " << argomenti << endl;
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
        void PrintStudente() const{
            cout << "Studente: " << endl << 
            "nome: " << name << "\t" << "cittadinanza: " << cittadinanza << "\t" 
            << "Facoltà: " << facolta << "\t" << "Corso: " << corso << endl;
        }
};

int main(){

    Studente s1("Denni", "Italiana", "Ingegneria", "Programmazione");
    s1.PrintStudente();

    Ricercatore r1("Mario", "Italiana", "IA");
    r1.PrintRicercatore();

    Docente d1("Verdi", "Svizzera", "Machine Learning");
    d1.PrintDocente();

    return 0;
}
