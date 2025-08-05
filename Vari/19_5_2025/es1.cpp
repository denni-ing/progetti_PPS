#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>

class Person{
private:
  std::string name;
  
public:
  Person(){}
  Person(const std::string& name_) : name(name_) { }
  
  inline std::string GetName() const {return name;}
  
  bool operator==(const Person& right) const{
    return name==right.name;
  }
};

struct Cmp{
  bool operator()(const Person& a, const Person& b) const{
    return a.GetName() < b.GetName();
  }
};

class Airline{
private:
  typedef std::set<Person, Cmp> people;
  typedef std::map<std::string, people> Voli;
  Voli voli;
  
public:
  void AddPerson(const std::string& filename);
  bool SearchPerson(const std::string& cod_volo, const Person& p) const;
  void PrintList(const std::string& cod_volo) const;
};

void Airline::AddPerson(const std::string& filename){
  std::ifstream is(filename);
  if(!is.good()){
    std::cerr << "Can not open file " << filename << std::endl;
    return;
  }
  
  std::string code;
  std::string name;
  while(is >> code && std::getline(is, name)){
    if(name.length() > 0 && code.length() > 0){
      name = name.substr(1);
      Person p(name);
      voli[code].insert(p);
    }
  }
}

bool Airline::SearchPerson(const std::string& cod_volo, const Person& p) const{
  auto iter = voli.find(cod_volo);
  
  if(iter == voli.end()){return false;}
  
  const std::set<Person, Cmp>& people = iter->second;
  return people.find(p) != people.end();
}

void Airline::PrintList(const std::string& cod_volo) const{
  auto iter_volo = voli.find(cod_volo);
  if(iter_volo == voli.end()){return;}
  std::cout << "Lista volo " << cod_volo << std::endl;
  const std::set<Person, Cmp>& people = iter_volo->second;
  for(const auto& person : people){
    std::cout << person.GetName() << std::endl;
  }
}

int main() {
  Airline a1;
  
  std::string filename = "voli.txt";
  a1.AddPerson(filename);
  
  Person p("Mario_Rossi");
  
  std::string cod_volo = "AZ001";
  
  if (a1.SearchPerson(cod_volo, p)) {
    std::cout << p.GetName() << " è presente sul volo " << cod_volo << std::endl;
  } else {
    std::cout << p.GetName() << " NON è presente sul volo " << cod_volo << std::endl;
  }
  
  a1.PrintList(cod_volo);
  
  return 0;
}

