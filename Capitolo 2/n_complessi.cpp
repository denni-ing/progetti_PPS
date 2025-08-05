#include <stdio.h>
#include <iostream>

class NumeroComplesso{
    private:
        float re;
        float im;

    public:
        NumeroComplesso(){
            re = 0.0f;
            im = 0.0f;
        }
        NumeroComplesso(float re_, float im_){
            re = re_;
            im = im_;
        }
        float getRe(){
            return re;
        }
        float getIm(){
            return im;
        }
        void setRe(float re_){
            re = re_;
        }
        void setIm(float im_){
            im = im_;
        }
        float SumRe(NumeroComplesso n1, NumeroComplesso n2){ 
            return n1.getRe() + n2.getRe();
        }
        float SumIm(NumeroComplesso n1, NumeroComplesso n2){
            return n1.getIm() + n2.getIm();
        }
        float Moltiplica(NumeroComplesso n1, NumeroComplesso n2, float* risRe, float* risIm){
            *risRe = (n1.getRe() * n2.getRe()) - (n1.getIm() * n2.getIm());
            *risIm = (n1.getIm() * n2.getRe()) + (n1.getRe() * n2.getIm());
        }
};

int main(){

    NumeroComplesso n1(1.14f, 1.14f);
    std::cout << n1.getRe() << " " << n1.getIm() << std::endl;
    NumeroComplesso n2(2.0f, 2.0f);
    std::cout << n2.getRe() << " " << n2.getIm() << std::endl;
    NumeroComplesso ris(0.0f, 0.0f);
    std::cout << "Somma: " << ris.SumRe(n1, n2) << " + j" << ris.SumIm(n1, n2) << std::endl;

    float risRe = 0.0f;
    float risIm = 0.0f;
    ris.Moltiplica(n1, n2, &risRe, &risIm);
    std::cout << "Moltiplicazione: " << risRe << " + j" << risIm << std::endl;

    return 0;
}