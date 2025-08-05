#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class PersonBase{
public:
  virtual string ToString() const = 0;
  virtual ~PersonBase(){}
};

class Person : public PersonBase{
protected:
  string name;
  string birth_place;
  string work_address;
  virtual ostream& ToStream(ostream& os) const{
    os << name << " " << birth_place << " " << work_address;
    return os;
  }
  
public:
  Person(){}
  Person(const string& name_, 
	 const string& birth_place_,
	 const string& work_address_):
    name(name_), birth_place(birth_place_), work_address(work_address_) {}
  
  inline string GetName() const {return name;}
  inline string GetBirthPlace() const {return birth_place;}
  inline string GetWorkAddress() const {return work_address;}

  bool operator==(const Person& right){
    return name==right.name && birth_place==right.birth_place && work_address==right.work_address;
  }
  
  virtual string ToString() const{
    return name + " " + birth_place + " " + work_address;
  }

  virtual ~Person(){}
  
};

class Student : public Person{
private:
  string faculty;
  string course;
  friend ostream& operator<<(ostream& os, const Student& s);
  
public:
  Student(){}
  Student(const string& name_, 
	  const string& birth_place_,
	  const string& work_address_,
	  const string& faculty_,
	  const string& course_):
    Person(name_, birth_place_, work_address_), faculty(faculty_), course(course_) {}
  
  inline string GetFaculty() const {return faculty;}
  inline string GetCourse() const {return course;}

  virtual string ToString() const{
    ostringstream os;
    os << "Student ";
    ToStream(os);
    os << " " << faculty << " " << course;
    return os.str();
  }

  virtual ~Student(){}
};

ostream& operator<<(ostream& os, const Student& s){
  return os << s.ToString();
}

class Resercher : public Person{
private:
  string argument;
  friend ostream& operator<<(ostream& os, const Resercher& r);
  
public:
  Resercher(){}
  Resercher(const string& name_, 
	    const string& birth_place_,
	    const string& work_address_,
	    const string& argument_):
    Person(name_, birth_place_, work_address_), argument(argument_) {}
  
  inline string GetArgument() const {return argument;}

  virtual string ToString() const{
    ostringstream os;
    os << "Resercher ";
    ToStream(os);
    os << " " << argument;
    return os.str();
  }

  virtual ~Resercher(){}
};

ostream& operator<<(ostream& os, const Resercher& r){
  return os << r.ToString();
}

class Teacher : public Resercher{
private:
  string course;
  friend ostream& operator<<(ostream& os, const Teacher& t);
  
public:
  Teacher(){}
  Teacher(const string& name_, 
	  const string& birth_place_,
	  const string& work_address_,
	  const string& argument_,
	  const string& course_):
    Resercher(name_, birth_place_, work_address_, argument_), course(course_) {}
  
  inline string GetCourse() const {return course;}

  virtual string ToString() const{
    ostringstream os;
    os << "Teacher ";
    ToStream(os);
    os << " " << course;
    return os.str();
  }

  virtual ~Teacher(){}
};

ostream& operator<<(ostream& os, const Teacher& t){
  return os << t.ToString();
}

class Administrative : public Person{
private:
  string office;
  friend ostream& operator<<(ostream& os, const Administrative& ad);
  
public:
  Administrative(){}
  Administrative(const string& name_, 
		 const string& birth_place_,
		 const string& work_address_,
		 const string& office_):
    Person(name_, birth_place_, work_address_), office(office_) {}
  
  inline string GetOffice() const {return office;}

  virtual string ToString() const{
    ostringstream os;
    os << "Administrative ";
    ToStream(os);
    os << " " << office;
    return os.str();
  }

  virtual ~Administrative(){}
};

ostream& operator<<(ostream& os, const Administrative& ad){
  return os << ad.ToString();
}

class Department{
private:
  std::vector<Person*> person;
  friend ostream& operator<<(ostream& os, const Department& dip);
  
public: 
  Department(){}
  Department(const int max_person){
    person.reserve(max_person);
  }

  void AddPerson(Person* p) {
    auto iter = person.begin();
    for(; iter != person.end(); iter++){
      if(*p==**iter){
	cerr << "Persona già presente nel Dipartimento" << endl;
	return;
      }
    }
    person.push_back(p);
    cout << p->ToString() << " inserito nel dipartimento" << endl;
    return;
  }

  bool ToFile(const string& filename) const {
    ofstream of(filename);
    if (!of.good()) {
      cerr << "Can not open " << filename << endl;
      return false;
    }
    
    of << "Student:\n";
    for (auto iter = person.begin(); iter != person.end(); ++iter) {
      if (auto s = dynamic_cast<Student*>(*iter)) {
	of << s->ToString() << '\n';
      }
    }
    
    of << "\nResercher:\n";
    for (auto iter = person.begin(); iter != person.end(); ++iter) {
      if (auto r = dynamic_cast<Resercher*>(*iter)) {
	of << r->ToString() << '\n';
      }
    }
    
    of << "\nTeacher:\n";
    for (auto iter = person.begin(); iter != person.end(); ++iter) {
      if (auto t = dynamic_cast<Teacher*>(*iter)) {
	of << t->ToString() << '\n';
      }
    }
    
    of << "\nAdministrative:\n";
    for (auto iter = person.begin(); iter != person.end(); ++iter) {
      if (auto a = dynamic_cast<Administrative*>(*iter)) {
	of << a->ToString() << '\n';
      }
    }
    
    of.close();
    return true;
  }


  ~Department(){
    for(int i=0; i<person.size(); i++){
      delete person[i];
    }
  }
};

ostream& operator<<(ostream& os, const Department& dip){
  for(int i=0; i<dip.person.size(); i++){
    os << dip.person[i]->ToString() << endl;
  }
  return os;
}

int main(){

  Department dip;
	
  Student* s1 = new Student("Mario_Rossi", "Poggibonsi", "Siena", "Ingegneria", "PPS");
  dip.AddPerson(s1);

  Teacher* t1 = new Teacher("Lorenzo_Verdi", "Torino", "Siena", "Robotica", "Fisica I");
  dip.AddPerson(t1);

  Resercher* r1 = new Resercher("Luca_Bianchi", "Milano", "Siena", "Machine_Learning");
  dip.AddPerson(r1);

  Administrative* a1 = new Administrative("Maria_Neri", "Siena", "Siena", "Didattica");
  dip.AddPerson(a1);

  cout << dip;

  dip.ToFile("dipartimento.txt");
	
  return 0;
}
