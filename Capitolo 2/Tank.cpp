#include <stdio.h>
#include <iostream>

class Serbatoio{
    private:
        float level;

    public:
        Serbatoio(){
            level = 0.0f;
        }
        Serbatoio(float level_){
            level = level_;
        }
        float Getlevel(){
            return level;
        }
        void Setlevel(float level_){
            if (level <= 0.0f){
                printf("ERROR, can not initialize negative fuel\n");
            }else{
                level = level_;
            }
        }
        void refill(float delta){
            level += delta;
        }
        void consume(float delta){
            if (delta > level){
                printf("ERROR, can not use not available fuel\n");
            }else{
                level -= delta;
            }
        }
};

int main(){
    Serbatoio s1(10.0f);
    s1.refill(2.0f);
    std::cout << "fuel level: " << s1.Getlevel() << std::endl;
    s1.consume(9.0f);
    std::cout << "fuel level: " << s1.Getlevel() << std::endl;
    s1.consume(4.0f);
    std::cout << "fuel level: " << s1.Getlevel() << std::endl;

    return 0;
}