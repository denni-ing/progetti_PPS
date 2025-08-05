#include <iostream>
#include <vector>

template<typename T>
class Matrix{
    private:
        int N;
        int M;
        std::vector<std::vector<T> > data;

    public:
        // Constructor
        Matrix(const int N_, const int M_){
            N=N_;
            M=M_;
            if(N<=0 || M<=0){return;}
            const std::vector<T> row(M);
            data = std::vector<std::vector<T> >(N, row);
        }

        void print() const{
            std::cout << "--------- Mat -------" << std::endl;
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    std::cout << data[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "---------------------" << std::endl;
        }
        // Getter
        inline float getElement(int i, int j) const{
            return data[i][j];
        }
        // Setter
        inline void setElement(int i, int j, T val){
            data[i][j] = val;
        }
        // Scalar Product
        void scalarProd(const T c){
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    setElement(i,j,data[i][j]*c);
                }
            }
        }
        // sum in place
        bool sum(const Matrix& mat){
            if(mat.N != N || mat.M != M){
                std::cout << "Matrices size don't match!" << std::endl;
                return false;
            }
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    setElement(i,j, data[i][j]+ mat.getElement(i,j));
                    //data[i][j] += mat.data[i][j];
                }
            }
            return true;
        }
        // sum non in place static
        static Matrix sumNP(const Matrix& mat1, const Matrix& mat2){
            if(mat1.N != mat2.N || mat1.M != mat2.M){
                std::cout << "Matrices size don't match!" << std::endl;
                return Matrix(0,0); //matrice vuota
            }
            Matrix result(mat1.N,mat1.M);
            for(int i=0; i<mat1.N; i++){
                for(int j=0; j<mat1.M; j++){
                    result.setElement(i,j, mat1.data[i][j]+ mat2.data[i][j]);
                }
            }
            return result;
        }
};

int main(){
    int N = 2;
    int M = 3;
    Matrix<float> mat(N,M);
    Matrix<float> mat2(mat);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            mat2.setElement(i,j,i+j);
            mat.setElement(i,j,i*j);
        }
    }
    mat.print();
    mat2.print();
    mat.scalarProd(3);
    mat.print();
    mat.sum(mat2);
    mat.print();
    Matrix<float> mat3 = Matrix<float>::sumNP(mat,mat2);
    mat3.print();
    
    return 0;
}
