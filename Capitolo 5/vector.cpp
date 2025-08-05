#include <iostream>

class Vector{
    typedef float T;
    private:
        int len = 0;
        T* data = nullptr;

    public:
        Vector(const int len_){
            len = len_;
            data = new T[len]();
        }
        Vector(const Vector& v1){
            len = v1.len;
            data = new T[v1.len]();
            for(int i=0; i<len; i++){
                data[i] = v1.data[i];
            }
        }
        ~Vector(){
            delete[] data;
        }
        inline T GetElement(const int i) const{
            if(IndexControl(i)){
                return data[i];
            }else{
                std::cerr << "Errore, index not valid" << std::endl;
                return 0;
            }
        }
        inline int GetLen() const{
            return len;
        }
        inline void SetElement(const int i, const T val){
            if(IndexControl(i)){
                data[i] = val;
            }else{
                std::cerr << "Errore, index not valid" << std::endl;
            }
        }
        bool IndexControl(const int i) const{
            if(i>=0 && i<len){
                return true;
            }
            else{
                return false;
            }
        }
        void Print() const{
            std::cout << std::endl;
            for(int i=0; i<len; i++){
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
        static Vector Sum(const Vector& v1, const Vector& v2){
            if(v1.len != v2.len){
                std::cerr << "Error, len not match" << std::endl;
                return Vector(0);
            }else{
                Vector v3(v1.len);
                for(int i=0; i<v3.len; i++){
                    v3.SetElement(i, v1.data[i] + v2.data[i]);
                }
                return v3;
            }
        }
        static Vector ProdAlpha(const Vector& v1, const T alpha){
            Vector v4(v1.len);
            for(int i=0; i<v4.len; i++){
                v4.SetElement(i, v1.data[i] * alpha);
            }
            return v4;
        }
};


int main(){

    Vector v1(3);
    v1.SetElement(0, 1);
    v1.SetElement(1, 2);
    v1.SetElement(2, 3);
    v1.Print();
    
    Vector v2(3);
    for(int i=0; i<v2.GetLen(); i++){
        v2.SetElement(i, i+i);
    }
    v2.Print();

    const Vector v3 = Vector::Sum(v1, v2);
    std::cout << std::endl <<"Vector 3: ";
    v3.Print();

    float alpha = 2;
    const Vector v4 = Vector::ProdAlpha(v1, alpha);
    std::cout << std::endl << "Vector 4: ";
    v4.Print();

    return 0;
}