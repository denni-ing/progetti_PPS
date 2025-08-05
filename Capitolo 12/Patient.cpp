#include <iostream>
#include <set>
#include <string>

class Date{
private:
  int day = 0;
  int month = 0;
  int year = 0;
  bool valid = true;
  
public:
  Date():valid(false) {}
  Date(const int day_, const int month_, const int year_):
    day(day_), month(month_), year(year_) {
    if(month < 1 || month > 12 || year < 1900 || day < 1 || day > 31){
      valid = false;
      return;
    }
    if(month == 2 && year % 4 == 0 && day > 29){
      valid = false;
      return;
    }
    if(month == 2 && year % 4 != 0 && day > 28){
      valid = false;
      return;
    }
    if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30){
      valid = false;
      return;
    }
  }

  inline int GetDay() const {return day;}
  inline int GetMonth() const {return month;}
  inline int GetYear() const {return year;}
  inline bool GetValid() const {return valid;}
  inline bool operator==(const Date& right) const{
    return day==right.day && month==right.month && year==right.year;
  }
};

inline bool operator<(const Date& a, const Date& b){
  if(a.GetYear() != b.GetYear()) {return a.GetYear() < b.GetYear();}
  if(a.GetMonth() != b.GetMonth()) {return a.GetMonth() < b.GetMonth();}
  return a.GetDay() < b.GetDay();
}

std::ostream& operator<<(std::ostream& os, const Date& d){
  return os << d.GetDay() << "/" << d.GetMonth() << "/" << d.GetYear(); 
}

class Patient{
private:
  std::string name;
  Date date;
  
public:
  Patient(){}
  Patient(const std::string& name_, const Date& date_):
    name(name_), date(date_) {}
  
  inline Date GetDate() const {return date;}
  inline bool Valid() const {return !name.empty() && date.GetValid();}
  inline std::string GetName() const {return name;}	
};

struct cmp{
  bool operator() (const Patient& a, const Patient& b) const{
    if(a.GetDate() == b.GetDate()){
      return a.GetName() < b.GetName();
    }
    return a.GetDate() < b.GetDate();
  }
};

inline std::ostream& operator<<(std::ostream& os, const Patient& p){
  return os << p.GetName() << "\t" << p.GetDate();
}

class Clinic{
private:
  std::set<Patient, cmp> patients;
  
public:
  inline void Add(const Patient& p){patients.insert(p);}
  inline bool Empty() const {return patients.size() == 0;}
  inline const std::set<Patient, cmp>& GetPatients() const {return patients;}

  Patient CallNext(){
    if(Empty()){
      return Patient();
    }
    const Patient p = *patients.begin();
    patients.erase(p);
    return p;
  }
};


int main(){
  
  Clinic c;
  c.Add(Patient("Mario Rossi", Date(1, 1, 1933)));
  c.Add(Patient("Mario Rossi", Date(1, 1, 1963)));
  c.Add(Patient("Mario Verdi", Date(1, 1, 1930)));
  c.Add(Patient("Carla Bianchi", Date(1, 1, 1950)));
  c.Add(Patient("Carla Verdi", Date(1, 1, 1930)));

  std::cout << "lista pazienti: " << std::endl;
  for (const auto& p : c.GetPatients()) {
    std::cout << p << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Apertura ambulatorio" << std::endl;
  while(!c.Empty()){
    std::cout << c.CallNext();
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "lista fine giornata: " << std::endl;
  for (const auto& p : c.GetPatients()) {
    std::cout << p << std::endl;
  }
  
  return 0;
}
