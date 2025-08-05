#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define ERROR -1

class Train{
private:
  std::string code;
  std::string d_station;
  std::string a_station;
  float latitudine;
  float longitudine;
  
public:
  Train(){}
  Train(const std::string& code_,
	const std::string& d_station_,
	const std::string& a_station_,
	const float latitudine_,
	const float longitudine_):
    code(code_), d_station(d_station_), a_station(a_station_),
    latitudine(latitudine_), longitudine(longitudine_) { }

  inline std::string GetCode() const {return code;}
  inline std::string GetDStation() const {return d_station;}
  inline std::string GetAStation() const {return a_station;}
  inline float GetLati() const {return latitudine;}
  inline float GetLong() const {return longitudine;}
};

class TrainManagement{
private:
  std::vector<Train> trains;

public:
  void AddTrain(const Train& train);
  void SortByCode();
  Train GetTrainByCode(const std::string& code) const;
  static bool CompareTrainByCode(const Train& a, const Train& b){
    return a.GetCode() < b.GetCode();
  }

  class ConstIterator{
  private:
    unsigned int index = 0;
    const TrainManagement* tm = nullptr;

  public:
    ConstIterator(const TrainManagement& tm_) : tm(&tm_) { }
    inline Train GetNext(){
      const Train t = tm->trains[index];
      index++;
      return t;
    }
    inline bool HasNext() const{
      return index < tm->trains.size();
    }
  };

  friend class ConstIterator;
  
};

void TrainManagement::AddTrain(const Train& train){
  trains.push_back(train);
}

void TrainManagement::SortByCode(){
  std::sort(trains.begin(), trains.end(), CompareTrainByCode);
}

Train TrainManagement::GetTrainByCode(const std::string& code) const{
  for(const Train train : trains){
    if(train.GetCode() == code){return train;}
  }
  return Train t("ERROR", "NULL", "NULL", 0.0, 0.0);
}


int main(){

  TrainManagement tm;

  tm.AddTrain(Train("IC101", "Roma", "Milano", 41.9, 12.5));
  tm.AddTrain(Train("FR205", "Napoli", "Firenze", 40.8, 14.2));
  tm.AddTrain(Train("IC099", "Torino", "Venezia", 45.0, 7.7));

  tm.SortByCode();

  TrainManagement::ConstIterator it(tm);

  while(it.HasNext()){
    Train t = it.GetNext();
    std::cout << "Codice: " << t.GetCode()
              << " Latitudine: " << t.GetLati()
              << " Longitudine: " << t.GetLong() << "\n";
  }
  
  return 0;
}
