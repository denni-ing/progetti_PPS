#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class PersonBase{
    public:
        virtual string ToString() const = 0;
        virtual bool ToFile(const string& filename) const = 0;
        virtual ~PersonBase() {}
};

class Person : public PersonBase{
    protected:
        string name;
        string citizenship;
        virtual ostream& ToStream(ostream& os) const{
            os << name << " " << citizenship;
            return os;
        }

    public:
        Person(const string& name_, const string& citizenship_):
            name(name_), citizenship(citizenship_) { }
        inline string GetName() const {return name;}
        inline string GetCitizenship() const {return citizenship;}
        virtual ~Person() {};
};

class Student : public Person{
    protected:
        string faculty;
        string program;

    public:
        Student(const string& name_, 
            const string& citizenship_, 
            const string& faculty_, 
            const string& program_):
            Person(name_, citizenship_), faculty(faculty_), program(program_) {}
        inline string GetFaculty() const {return faculty;}
        inline string GetProgram() const {return program;}
        virtual string ToString() const{
            ostringstream os;
            os << "Student ";
            ToStream(os);
            os << " " << faculty << " " << program;
            return os.str();
        }
        virtual bool ToFile(const string& filename) const{
            ofstream of(filename, ios::app);
            if(!of.good()){
                cerr << "Errore nell'apertura del file" << endl;
                return false;
            }
            of << "Student ";
            ToStream(of);
            of << " " << faculty << " " << program << endl;
            return true;
        }
        virtual ~Student() {}
};

class Researcher : public Person{
    protected:
        string topics;

    public:
        Researcher(
            const string& name_,
            const string& citizenship_,
            const string& topics_):
            Person(name_, citizenship_), topics(topics_) { }
        inline string GetTopics() const {return topics;}
        virtual string ToString() const{
            ostringstream os;
            os << "Resercher ";
            ToStream(os);
            os << " " << topics;
            return os.str();
        }
        virtual bool ToFile(const string& filename) const{
            ofstream of(filename, ios::app);
            if(!of.good()){
                cerr << "Errore nell'apertura del file" << endl;
                return false;
            }
            of << "Researcher ";
            ToStream(of);
            of << " " << topics << endl;
            return true;
        }
        virtual ~Researcher() {}
};

class Teacher : public Researcher{
    protected:
        string program;
    
    public:
        Teacher(
            const string& name_,
            const string& citizenship_,
            const string& topics_,
            const string& program_):
            Researcher(name_, citizenship_, topics_), program(program_) { }
        inline string GetProgram() const {return program;}
        virtual string ToString() const{
            ostringstream os;
            os << "Teacher ";
            ToStream(os);
            os << " " << program;
            return os.str();
        }
        virtual bool ToFile(const string& filename) const{
            ofstream of(filename, ios::app);
            if(!of.good()){
                cerr << "Errore nell'apertura del file" << endl;
                return false;
            }
            of << "Teacher ";
            ToStream(of);
            of << " " << program << endl;
            return true;
        }
        virtual ~Teacher() {}
};

int main(int argc, char** argv){

    PersonBase* person = nullptr;

    if(argc < 2){
        cerr << "Usage: " << argv[0] << " [Student, Researcher, Teacher] [Filename]" << endl;
    }

    const string p_type(argv[1]);

    if(p_type == "Student"){
        person = new Student("Mario_Rossi", "Italia", "Ingegneria", "PPS");
    }else if(p_type == "Researcher"){
        person = new Researcher("Mario_Rossi", "Italia", "Informatica");
    }else if(p_type == "Teacher"){
        person = new Teacher("Mario_Rossi", "Italia", "Informatica", "PPS");
    }else{
        cerr << "Errore nella classe " << p_type;
        return 1;
    }

    const string p_str = person->ToString();
    cout << "La Persona e' " << p_str << endl;

    if(argc > 2){
        person->ToFile(argv[2]);
    }

    if(person!=nullptr){
        delete person;
    }

    return 0;
}