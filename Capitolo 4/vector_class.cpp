class Vector{
    private:
        float* data = nullptr;
        int N;

    public:
        Vector(const int N_){
            N = N_;
            data = new float [N]();
        }
        Vector(const Vector& vec){
            N = vec.N; 
            data = new float [N]();
            for(int i=0; i<N; i++){
                data[i] = vec.data[i];
            }
        }
        ~Vector(){
            delete[] data;
        }
        float getElement(const int i){
            return data[i];
        }
        void setElement(const int i, const float val){
            data[i] = val;
        }
};

int main(){
    return 0;
}