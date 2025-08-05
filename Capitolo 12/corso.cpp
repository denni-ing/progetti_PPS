#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Student{
private:
  int id;
  std::string name;

public:
  Student(){}
  Student(const int id_, const std::string& name_):
    id(id_), name(name_) {}

  inline int GetId() const {return id;}
  inline std::string GetName() const {return name;}

  bool operator==(const Student& right){
    return id==right.id && name==right.name;
  }
  
};

class Course{
private:
  std::string course_name;
  std::vector<Student> students;

public:
  Course(){}
  Course(const std::string course_name_, const int max_students):
    course_name(course_name_) {students.reserve(max_students);}

  inline int GetNum() const {return students.size();}
  inline std::string GetName() const { return course_name;}

  void PrintList() const{
    auto iter = students.begin();

    std::cout << "Lista studenti corso " << course_name  << ": " << std::endl;
    for(; iter != students.end(); iter++){
      std::cout << iter->GetId() << "\t" << iter->GetName();
      std::cout << std::endl;
    }
  }

  bool Register(int student_id, const std::vector<Student>& all_students) {
    auto iter = all_students.begin();
    for (; iter != all_students.end(); iter++) {
      if (iter->GetId() == student_id) {
	auto iter2 = students.begin();
	for (; iter2 != students.end(); iter2++) {
	  if (*iter2 == *iter) {return false;}
	}
	students.push_back(*iter);
	return true;
      }
    }
    std::cerr << "Studente non trovato";
    return false;
  }

  bool Search(const Student& stud){
    auto iter = students.begin();
    for(; iter != students.end(); iter++){
      if(*iter==stud){return true;}
    }
    return false;
  }

};

std::vector<Student> ReadStudentFromFile(const std::string& filename){
  std::vector<Student> all_students;
  std::ifstream file(filename);

  if(!file.good()){
    std::cerr << "can not open file " << filename << std::endl;
    return all_students;
  }

  int id;
  std::string name;

  while(file >> id >> name){
    Student s(id, name);
    all_students.push_back(s);
  }

  return all_students;
}

int main(){

  std::string filename = "student_list.txt";

  std::vector<Student> all_students;
  all_students = ReadStudentFromFile(filename);

  Course c1("PPS", 4);
  Course c2("Fisica II", 5);

  c1.Register(1, all_students);
  c1.Register(2, all_students);
  c2.Register(3, all_students);

  c1.PrintList();
  c2.PrintList();

  if(c1.Search(all_students[3 - 1 /*id-1*/])){
    std::cout << "Studente " << all_students[3 - 1].GetName() << " iscritto al corso " << c1.GetName();
    std::cout << std::endl;
  }else{
    std::cerr << "Studente " << all_students[3 - 1].GetName() << " non iscritto al corso " << c1.GetName();
    std::cout << std::endl;
  }
  
  return 0;
}
