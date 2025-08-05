/*Realizzare un software per gestire le macchine di un noleggio.
Il software riceve messaggi di aggiornamento della posizione che
specificano l’identificativo della macchina, il tempo attuale, oltre che
la sua posizione come posizione relativa [x,y], assumendo che la
terra sia localmente piatta).
a) calcolare la distanza percorsa da ogni macchina;
b) ritornare le macchine ordinate per km percorsi;
c) Fornire un iteratore per scandire le macchine in ordine di
chilometri percorsi.*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class Message{
private:
    std::string id;
    int time;
    float lat;
    float lon;

public:
    Message() : time(0), lat(0.0f), lon(0.0f) { }
    Message(const std::string id_,
            const int time_,
            const float lat_,
            const float lon_) : 
            id(id_), time(time_), lat(lat_), lon(lon_) { }

    inline std::string GetId() const {return id;}
    inline int GetTime() const {return time;}
    inline float GetLat() const {return lat;}
    inline float GetLon() const {return lon;}
};

class Car{
private:
    typedef std::vector<Message> Messages;
    typedef std::map<std::string, Messages> Car2Message;
    Car2Message car2message;

public:
    Car() { }
    void ReceiveMessage(const Message& m){
        car2message[m.GetId()].push_back(m);
    }

    float GetDist(const std::string id) const {
        auto iter = car2message.find(id);
        if(iter == car2message.end()) {return 0.0f;}

        float dist = 0.0f;
        const Messages& messages = iter->second;
        for(unsigned int i=1; i<messages.size(); ++i){
            const Message& start = messages[i-1];
            const Message& m = messages[i];

            float dx = m.GetLon() - start.GetLon();
            float dy = m.GetLat() - start.GetLat();
            dist+=std::sqrt(dx*dx + dy*dy);
        }
        return dist;
    }

    class ConstIterator{
        private:
            unsigned int index = 0;
            const Messages* messages = nullptr;
        
        public:
            inline ConstIterator(const Messages& messages_) : messages(&messages_) { }
            inline const Message& GetNext() {
                return (*messages)[index++];
            }
            inline bool HasNext() const {
                return (index < messages->size());
            }
    };

    friend class ConstIterator;

    ConstIterator GetIterator(const std::string& id){
        auto iter = car2message.find(id);
        if(iter != car2message.end()){
            return ConstIterator(iter->second);
        }
        return ConstIterator(Messages());
    }

    static bool CompareByDistance(const std::pair<std::string, float> a, const std::pair<std::string, float> b){
        return a.second > b.second;
    }

    std::vector<std::pair<std::string, float>> CarSortedByDistance() const{
        std::vector<std::pair<std::string, float>> distVec;
        distVec.reserve(car2message.size());
        for(const auto& iter : car2message){
            distVec.emplace_back(iter.first, GetDist(iter.first));
        }
        std::sort(distVec.begin(), distVec.end(), CompareByDistance);
        return distVec;
    }

};

int main() {
    Car carManager;
    
    carManager.ReceiveMessage(Message("CarA", 1, 0.0f, 0.0f));
    carManager.ReceiveMessage(Message("CarA", 2, 3.0f, 4.0f)); // distance 5
    carManager.ReceiveMessage(Message("CarB", 1, 0.0f, 0.0f));
    carManager.ReceiveMessage(Message("CarB", 2, 1.0f, 1.0f)); // distance ≈1.414
    carManager.ReceiveMessage(Message("CarB", 3, 4.0f, 5.0f)); // additional distance ≈5
    carManager.ReceiveMessage(Message("CarC", 1, 2.0f, 2.0f)); // Only one message, 0 distance

    auto sortedCars = carManager.CarSortedByDistance();

    std::cout << "Macchine ordinate per chilometri percorsi:\n";
    for (const auto& p : sortedCars) {
        std::cout << p.first << ": " << p.second << " Km\n";
    }
    return 0;
}