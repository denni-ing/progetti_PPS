#include <iostream>

using namespace std;

class String{
    private:
        int length = 0;
        char* str = nullptr;

    public:
        //constructor
        String(const int length_){
            length = length_;
            str = new char[length + 1];
            for(int i=0; i<length; i++){
                str[i] = ' ';
            }
            str[length] = '\0';
        }
        //copy constructor
        String(const String& str1){
            length = str1.length;
            str = new char[length + 1];
            for(int i=0; i<length; i++){
                str[i] = str1.str[i];
            }
            str[length] = '\0';
        }
        //destructor
        ~String(){
            delete[] str;
        }
        int Getlength(){
            return length;
        }
        void SetChar(const int i, const char c1){
            if(i>=0 && i<=length){
                str[i] = c1;
            }
            else{
                cerr << "Errore, indice non valido" << endl;
                return;
            }
        }
        void printString(){
            cout << endl;
            cout << str << endl;
            cout << endl;
        }
        void Concatena(const String s1){
            char* str1 = new char[length + s1.length];
            for(int i=0; i<length; i++){
                str1[i] = str[i];
            }
            for(int i=0; i<s1.length; i++){
                str1[i + length] = s1.str[i];
            }
            str1[length + s1.length] = '\0';
            delete[] str;
            str = str1;
            length += s1.length;
        }
};

int main(){

    String s(4); 
    char c1 = ' ';
    for(int i=0; i < s.Getlength(); i++){
        cout << "Inserisci carattere " << i << ": ";
        cin >> c1;
        s.SetChar(i, c1);
    }
    s.printString();

    String s2(s);
    s2.SetChar(1, 'B');
    s2.printString();

    s.Concatena(s2);
    s.printString();

    return 0;
}