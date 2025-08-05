#include <iostream>

class Matrix{
    typedef float T;
    private:
        int N = 0;
        int M = 0;
        T** matrix = nullptr;
        //implementazione interna
        friend Matrix& operator--(Matrix& mat); //pre-decremento
        friend Matrix operator--(Matrix& mat, int); //post-decremento
        friend Matrix operator-(const Matrix& left, const Matrix& right);
        friend Matrix& operator*=(Matrix& left, const T val);
        friend bool operator==(const Matrix& left, const Matrix& right);
        friend std::istream& operator>>(std::istream& in, const Matrix& mat);

    public:
        //Overload interno, Implementazione esterna
        Matrix& operator++();
        Matrix operator++(int);
        Matrix operator+(const Matrix& right);
        Matrix& operator+=(const Matrix& right);
        Matrix& operator=(const Matrix& right);
        std::ostream& operator<<(std::ostream& out, const Matrix& mat);

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
        void printMatrix() {
            std::cout << std::endl;
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    std::cout << getElement(i, j) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        static bool checkSize(const Matrix& mat1, const Matrix& mat2){
            if(mat1.N != mat2.N || mat1.M != mat2.M){
                std::cerr << "Matrices size don't match!" << std::endl;
                return false;
            }else{
                return true;
            }
        }
};

//-----------------------------------------OPERATORI UNARI---------------------------------------------------------------------
//pre-incremento (def interna)
Matrix& Matrix::operator++(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            matrix[i][j]++;
        }
    }
    return *this;
}
//pre-decremento (def esterna)
Matrix& operator--(Matrix& mat){
    for(int i=0; i<mat.N; i++){
        for(int j=0; j<mat.M; j++){
            mat.matrix[i][j]--;
        }
    }
    return mat;
}
//post-incremento (def interna)
Matrix Matrix::operator++(int){
    Matrix tmp = *this;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            matrix[i][j]++;
        }
    }
    return tmp;
}
//post-decremento (def esterna)
Matrix operator--(Matrix& mat, int){
    Matrix tmp = mat;
    for(int i=0; i<mat.N; i++){
        for(int j=0; j<mat.M; j++){
            mat.matrix[i][j]--;
        }
    }
    return tmp;
}
//--------------------------------------------OPERATORI BINARI-----------------------------------------------------
Matrix operator-(const Matrix& left, const Matrix& right){
    if(!Matrix::checkSize(left, right)){
        return Matrix(0,0);
    }
    Matrix res(left.N, left.M);
    for(int i=0; i<left.N; i++){
        for(int j=0; j<left.M; j++){
            res.matrix[i][j] = left.matrix[i][j] - right.matrix[i][j];
        }
    }
    return res;
}
Matrix Matrix::operator+(const Matrix& right){
    if(!Matrix::checkSize(*this, right)){
        return Matrix(0,0);
    }
    Matrix res(this->N, this->M);
    for(int i=0; i<this->N; i++){
        for(int j=0; j<this->M; j++){
            res.matrix[i][j] = this->matrix[i][j] + right.matrix[i][j];
        }
    }
    return res;
}
Matrix& operator*=(Matrix& left, const Matrix::T val){
    for(int i=0; i<left.N; i++){
        for(int j=0; j<left.M; j++){
            left.matrix[i][j] = left.matrix[i][j] * val;
        }
    }
    return left;
}
Matrix& Matrix::operator+=(const Matrix& right){
    if(!Matrix::checkSize(*this, right)){
        return *this;
    }
    for(int i=0; i<this->N; i++){
        for(int j=0; j<this->M; j++){
            this->matrix[i][j] = this->matrix[i][j] + right.matrix[i][j];
        }
    }
    return *this;
}
bool operator==(const Matrix& left, const Matrix& right){
    if(!Matrix::checkSize(left, right)){
        return false;
    }
    bool equal = true;
    for(int i=0; i<left.N; i++){
        for(int j=0; j<left.M; j++){
            if(left.matrix[i][j] != right.matrix[i][j]){
                equal = false;
            }
        }
    }
    return equal;
}
Matrix& Matrix::operator=(const Matrix& right){
    if(this==&right){
        return *this;
    }
    if(this->matrix){
        for(int i=0; i<N; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    this->N = right.N;
    this->M = right.M;
    this->matrix = new Matrix::T*[this->N]();
    for(int i=0; i<this->N; i++){
        this->matrix[i] = new Matrix::T[this->N]();
        for(int j=0; j<this->M; j++){
            this->matrix[i][j] = right.matrix[i][j];
        }
    }
    return *this;
}
//-----------------------------------------------I/O---------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const Matrix& mat){
    N = mat.getN();
    M = mat.getM();
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            out << mat.getElement(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}
std::istream& operator>>(std::istream& is, const Matrix& mat){
    for(int i=0; i<mat.N; i++){
        for(int j=0; j<mat.M; j++){
            is >> mat.data[i][j];
        }
    }
    return is;
}

//----------------------------------------------MAIN---------------------------------------------------------------
int main(){

    int N = 2;
    int M = 3;
    Matrix mat(N,M);
    Matrix mat2(mat);
    ++mat;
    mat2 = ++mat;
    mat.printMatrix();
    mat2.printMatrix();
    --mat;
    mat--;
    mat.printMatrix();
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            mat2.setElement(i,j,i+j);
            mat.setElement(i,j,i*j);
        }
    }
    mat.printMatrix();
    mat2.printMatrix();
    Matrix res = mat-mat2;
    Matrix res2 = mat+mat2;
    res.printMatrix();
    res2.printMatrix();
    res2*=3;
    res2.printMatrix();
    res2+=mat;
    res2.printMatrix();
    if(mat2==mat){
        std::cout << "Equal Matrices" << std::endl;
    }
    else{
        std::cout << "Different Matrices" << std::endl;
    }
    std::cout << "Mat before assignment" << std::endl;
    mat.printMatrix();
    mat = res2;
    std::cout << "Mat after assignment" << std::endl;
    mat.printMatrix();
    //std::cout << mat << std::endl;

    mat.moltiplyAlpha(3);
    mat.printMatrix();
    mat.sum(mat2);
    mat.printMatrix();
    Matrix mat3 = Matrix::sumNP(mat,mat2);
    mat3.printMatrix();

    Matrix m4(3,5);
    m4.setElement(1,1,3);
    m4.setElement(1,2,4);
    m4.setElement(1,3,2);
    Matrix m5 = Matrix::prodMatrix(mat2,m4);
    m5.printMatrix();

    Matrix matin(2,2);
    std::cout << "Insert matrix values:" << std::endl;
    std::cin >> matin;
    std::cout << matin;

    return 0;
}
