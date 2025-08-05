#include <iostream>

class Vector{
    private:
        int length = 0;
        float* data = nullptr;

    public:
        Vector(const int length_){
            length = length_;
            data = new float[length]();
        }
        Vector(const Vector& v1){
            length = v1.length;
            data = new float[length];
            for(int i=0; i<length; i++){
                data[i] = v1.data[i];
            }
        }
        ~Vector(){
            delete[] data;
        }
        float GetElement(const int i){
            if(i>=0 && i<=length){
                return data[i];
            }
            else{
                std::cerr << "Errore, indice non corretto" << std::endl;
                return 1;
            }
        }
        void SetElement(const int i, const float val){
            if(i>=0 && i<=length){
                data[i] = val;
            }
            else{
                std::cerr << "Errore, indice non corretto" << std::endl;
                return;
            }
        }
        void printVector(){
            std::cout << std::endl;
            std::cout << "Vector: " << std::endl;
            for(int i=0; i<length; i++){
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
};

int main(){

    Vector s1(4);
    s1.SetElement(0, 0.1);
    s1.SetElement(1, 0.2);
    s1.SetElement(2, 0.3);
    s1.SetElement(3, 0.4);
    s1.printVector();

    Vector s2(3);
    s2.SetElement(0, 1);
    s2.SetElement(1, 11.234);
    s2.SetElement(2, 0);
    s2.printVector();

    Vector s3(s1);
    s3.printVector();

    return 0;
}