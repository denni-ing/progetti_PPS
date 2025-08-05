#include <iostream>

class Matrix{
    typedef float T;
    private:
        int N = 0;
        int M = 0;
        T** matrix = nullptr;

    public:
        //constructor
        Matrix(const int N_, const int M_){
            N = N_;
            M = M_;
            matrix = new T*[N];
            for(int i=0; i<N; i++){
                matrix[i] = new T[M]();
            }
        }
        //copy constructor
        Matrix(const Matrix& mat){
            N = mat.N; 
            M = mat.M; 
            matrix = new T*[mat.N];
            for(int i=0; i<N; i++){
                matrix[i] = new T[M]();
                for(int j=0; j<M; j++){
                    matrix[i][j] = mat.matrix[i][j];
                }
            }
        }
        //Distructor
        ~Matrix(){
            for(int i=0; i<N; i++){
                delete[] matrix[i];
            }
            delete[] matrix;
        }
        inline T getElement(const int i, const int j) const{
            return matrix[i][j];
        }
        inline int getN() const{
            return N;
        }
        inline int getM() const{
            return M;
        }
        inline void setElement(const int i, const int j, const int val){
            matrix[i][j] = val;
        }
        void moltiplyAlpha(const int a){
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    //matrix[i][j] = matrix[i][j] * a; //oppure chiamare setElement
                    setElement(i, j, matrix[i][j]*a);
                }
            }
        }
        bool sum(const Matrix& mat){
            if(mat.N != N || mat.M != M){
                std::cout << "Matrices size don't match!" << std::endl;
                return false;
            }
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    setElement(i,j, matrix[i][j]+ mat.getElement(i,j));
                }
            }
            return true;
        }
        static Matrix sumNP(const Matrix& m1, const Matrix& m2){  //sum non in place
            if(m1.N != m2.N || m1.M != m2.M){
                std::cout << "Matrices size don't match!" << std::endl;
                return Matrix(0,0);
            }
            else{
                Matrix m3(m1.N, m1.M);
                for(int i=0; i<m3.N; i++){
                    for(int j=0; j<m3.M; j++){
                        m3.setElement(i, j, m1.getElement(i, j) + m2.getElement(i, j));
                    }
                }
                return m3;
            }
        }
        static Matrix prodMatrix(const Matrix& m1, const Matrix& m2){
            if(m1.M != m2.N){
                std::cout << "Matrices size don't match!" << std::endl;
                return Matrix(0,0);
            }
            else{
                Matrix m4(m1.N, m2.M);
                T ris=0;
                for(int i=0; i<m1.N; i++){
                    for(int j=0; j<m2.M; j++){
                        for(int k=0; k<m1.M; k++){
                            ris += m1.matrix[i][k] * m2.matrix[k][j];
                        }
                        m4.setElement(i, j, ris);
                        ris = 0;
                    }
                }
                return m4;
            }
        }
        void printMatrix() const{
            std::cout << std::endl;
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    std::cout << getElement(i, j) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
};

int main(){

    int N = 3;
    int M = 3;

    Matrix m1(N, M);
    for(int i=0; i<m1.getN(); i++){
        for(int j=0; j<m1.getM(); j++){
            m1.setElement(i,j, i*j);
        }
    }

    m1.printMatrix();

    int a = 0;
    std::cout << "Valore di alpha = 2" << std::endl;
    m1.moltiplyAlpha(2);
    m1.printMatrix();

    Matrix m2(N, M);
    for(int i=0; i<m2.getN(); i++){
        for(int j=0; j<m2.getM(); j++){
            m2.setElement(i,j, i+j);
        }
    }
    m2.printMatrix();

    const Matrix m3 = Matrix::sumNP(m1, m2);
    std::cout << "sum m1 + m2: " << std::endl;
    m3.printMatrix();

    const Matrix m4 = Matrix::prodMatrix(m1, m2);
    std::cout << "matrix product: " << std::endl;
    m4.printMatrix();

    m1.sum(m2);
    std::cout << "Sum inline m1 = m1 + m2: " << std::endl;
    m1.printMatrix();

    return 0;
}
