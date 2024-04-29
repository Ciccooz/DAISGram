#include <iostream>
#include <string>
#include <random>
#include <math.h>
#include <fstream>

#include "dais_exc.h"
#include "tensor.h"

#define PI 3.141592654
#define FLT_MAX 3.402823466e+38F /* max value */
#define FLT_MIN 1.175494351e-38F /* min positive value */

using namespace std;

Tensor::Tensor(){
    data = nullptr;

    r = 0;
    c = 0;
    d = 0;
}

Tensor::Tensor(int r, int c, int d, float v){
    this -> r = r;
    this -> c = c;
    this -> d = d;

    data = new float **[d];
  
    for(int i = 0; i < d; i++){
        data[i] = new float* [r];
      
        for(int j = 0; j < r; j++)
            data[i][j] = new float[c];
    }  

    for(int i = 0; i < d; i++)
        for(int j = 0; j < r; j++)
            for(int l = 0; l < c; l++)
                 data[i][j][l] = v;
}

Tensor::~Tensor(){
    for(int i = 0; i < d; i++){
        for(int j = 0; j < r; j++)
            delete[] data[i][j];
          
        delete[] data[i];
    }
  
    delete[] data;
}

float Tensor::operator()(int i, int j, int k) const{
    if( (k>= 0 && k < d) && (i>= 0 && i < r) && (j>= 0 && j < c) ) 
        return data[k][i][j];
  
    else
        throw(index_out_of_bound());
}

float& Tensor::operator()(int i, int j, int k){
    if((k>= 0 && k < d) && (i>= 0 && i < r) && (j>= 0 && j < c)) 
        return data[k][i][j];
  
    else
        throw(index_out_of_bound());
}

Tensor::Tensor(const Tensor& that){
    //erase all elements
    this -> ~Tensor();

    r = that.r;
    c = that.c;
    d = that.d;

    data = new float **[d];
  
    for(int i = 0; i < d; i++){
        data[i] = new float* [r];
      
        for(int j = 0; j < r; j++)
            data[i][j] = new float[c];
    }  

    for(int i = 0; i < d; i++)
        for(int j = 0; j < r; j++)
            for(int l = 0; l < c; l++)
                 data[i][j][l] = that.data[i][j][l];
}

bool Tensor::operator==(const Tensor& rhs) const{
    if(r == rhs.r && c == rhs.c && d == rhs.d){
        for(int i = 0; i < d; i++)
            for(int j = 0; j < r; j++)
                for(int l = 0; l < c; l++)
                    if(data[i][j][l] != rhs.data[i][j][l])
                        return false;
        
        return true;
    }
  
    else
        return false;
}

Tensor Tensor::operator-(const Tensor &rhs) const{
    if(data != nullptr && rhs.data != nullptr){
        if((r == rhs.r) && (c == rhs.c) && (d == rhs.d)) {  //aggiungere metodo confronto dimensioni con rows, cols
            Tensor result(r, c, d, 0);

            for(int depth = 0; depth < d; depth++)
                for(int row = 0; row < r; row++)
                    for(int col = 0; col < c; col++)
                        result.data[depth][row][col] = this -> data[depth][row][col] - rhs.data[depth][row][col];

            return result;
        }

        else
            throw(dimension_mismatch());
    }
  
    else 
        throw(tensor_not_initialized());
}

Tensor Tensor::operator+(const Tensor &rhs) const{
    if(data != nullptr && rhs.data != nullptr){
        if((r == rhs.r) && (c == rhs.c) && (d == rhs.d)) {  //aggiungere metodo confronto dimensioni
            Tensor result(r, c, d, 0);
          
            for(int depth = 0; depth < d; depth++)
                for(int row = 0; row < r; row++)
                    for(int col = 0; col < c; col++)
                        result.data[depth][row][col] = this -> data[depth][row][col] + rhs.data[depth][row][col];

            return result;
        }

        else 
            throw(dimension_mismatch());
    }

    else
        throw(tensor_not_initialized());
}

Tensor Tensor::operator*(const Tensor &rhs) const{
    if(data != nullptr && rhs.data != nullptr){
        if((r == rhs.r) && (c == rhs.c) && (d == rhs.d)) {  //aggiungere metodo confronto dimensioni
                Tensor result(r, c, d, 0);

                for(int depth = 0; depth < d; depth++)
                    for(int row = 0; row < r; row++)
                        for(int col = 0; col < c; col++)
                            result.data[depth][row][col] = this -> data[depth][row][col] * rhs.data[depth][row][col];

                return result;
        }

        else 
            throw(dimension_mismatch());
    }

    else
       throw(tensor_not_initialized());
}

Tensor Tensor::operator/(const Tensor &rhs) const{
    if(data != nullptr && rhs.data != nullptr){
        if((r == rhs.r) && (c == rhs.c) && (d == rhs.d)) {  //aggiungere metodo confronto dimensioni con rows, cols
                Tensor result(r, c, d, 0);

                for(int depth = 0; depth < d; depth++)
                    for(int row = 0; row < r; row++)
                        for(int col = 0; col < c; col++){
                            if(rhs.data[depth][row][col] != 0)
                                result.data[depth][row][col] = this -> data[depth][row][col] / rhs.data[depth][row][col];
                            else
                                throw(unknown_exception());
                        }

                return result;
        }

        else 
            throw(dimension_mismatch());
    }
  
    else 
        throw(tensor_not_initialized());
}


Tensor Tensor::operator-(const float &rhs)const{
     if(data != nullptr){
        Tensor result(r, c, d, 0);

        for(int depth = 0; depth < d; depth++)
            for(int row = 0; row < r; row++)
                for(int col = 0; col < c; col++)
                    result.data[depth][row][col] = this -> data[depth][row][col] - rhs;

        return result;
    }
  
    else 
        throw(tensor_not_initialized());
}

Tensor Tensor::operator+(const float &rhs) const{
    if(data != nullptr){
        Tensor result(r, c, d, 0);

        for(int depth = 0; depth < d; depth++)
            for(int row = 0; row < r; row++)
                for(int col = 0; col < c; col++)
                    result.data[depth][row][col] = this -> data[depth][row][col] + rhs;

        return result;
    }

    else
        throw(tensor_not_initialized());
}

Tensor Tensor::operator*(const float &rhs) const{
   if(data != nullptr){
        Tensor result(r, c, d, 0);

        for(int depth = 0; depth < d; depth++)
            for(int row = 0; row < r; row++)
                for(int col = 0; col < c; col++)
                    result.data[depth][row][col] = this -> data[depth][row][col] * rhs;

        return result;
    }
    else
        throw(tensor_not_initialized());
}
  
Tensor Tensor::operator/(const float &rhs)const{
    if(data != nullptr){
        if(rhs == 0)
            throw(unknown_exception());

        Tensor result(r, c, d, 0);

        for(int depth = 0; depth < d; depth++)
            for(int row = 0; row < r; row++)
                for(int col = 0; col < c; col++)
                    result.data[depth][row][col] = this -> data[depth][row][col] / rhs;

        return result;
    }
    else
        throw(tensor_not_initialized());
}

Tensor& Tensor::operator=(const Tensor &other){
    //if equal
    if((r == other.r) && (c == other.c) && (d == other.d)){
        for(int i = 0; i < d; i++)
            for(int j = 0; j < r; j++)
                for(int l = 0; l < c; l++)
                    data[i][j][l] = other.data[i][j][l];
    }

    //not equal or nullptr
    else{
        this -> ~Tensor();
        r = other.r;
        c = other.c;
        d = other.d;

        data = new float **[d];
        for(int i = 0; i < d; i++){
            data[i] = new float* [r];
          
            for(int j = 0; j < r; j++)
                data[i][j] = new float[c];
        }  

        for(int i = 0; i < d; i++)
            for(int j = 0; j < r; j++)
                for(int l = 0; l < c; l++)
                    data[i][j][l] = other.data[i][j][l];
    }

    return *this;
}

/**
 * Random Initialization
 * 
 * Perform a random initialization of the tensor
 * 
 * @param mean The mean
 * @param std  Standard deviation
 */
void Tensor::init_random(float mean, float std){
    if(data){
        std::default_random_engine generator;
        std::normal_distribution<float> distribution(mean,std);

        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                for(int k = 0; k < d; k++)
                    this -> operator()(i, j, k) = distribution(generator);

    }
  
    else
        throw(tensor_not_initialized());
}

void Tensor::init(int r, int c, int d, float v){
    if(this -> r != r || this -> c != c || this -> d != d){

        if(data != nullptr)
            this -> ~Tensor();  //CANCELLO TUTTO
        
        this -> r = r;
        this -> c = c;
        this -> d = d;

            //ASSEGNAMENTO MEMORIA
        data = new float **[d];

        for(int i = 0; i < d; i++){
            data[i] = new float* [r];

            for(int j = 0; j < r; j++)
                data[i][j] = new float[c];
        }   
    }

    for(int i = 0; i < d; i++)
        for(int j = 0; j < r; j++)
            for(int l = 0; l < c; l++)
                    data[i][j][l] = v;
}

void Tensor::clamp(float low, float high){
    if (data){
        for(int depth = 0; depth < this-> d; depth++){
            for(int row = 0; row < this->r ; row++){
                for(int col = 0;col < this->c; col++){

                    if ( this -> data[depth][row][col] < low)  this -> data[depth][row][col]=low;
                    else if ( this -> data[depth][row][col] > high)  this -> data[depth][row][col]=high; 
                }
            }
        }
    }
    else
        throw(tensor_not_initialized());
}

void Tensor::rescale(float new_max){
    bool flag = false;
  
    if(data){
        for(int i = 0; i < d ;i++){
            for(int j = 0; j < r; j++){
                for(int k = 0; k < c; k++){
                    if((getMin(i) != getMax(i)) && flag == false)
                        data[i][j][k] = ((data[i][j][k] - getMin(i)) / (getMax(i) - getMin(i))) * new_max;
                  
                    else{
                        flag = true;
                        data[i][j][k] = new_max;
                    }
                }
            }
        }    

    }
  
    else
        throw(tensor_not_initialized());
}

Tensor Tensor::padding(int pad_h, int pad_w) const{
    if (data){
        Tensor result = Tensor((this->r) + (2 * pad_h),(this->c) + (2 * pad_w),this->d,0.0);

        for(int depth = 0; depth < this-> d; depth++){
            for(int row = 0; row < this->r ; row++){
                for(int col = 0; col < this->c; col++){
                    result.data[depth][row+pad_w][col+pad_h] = this -> data[depth][row][col];
                }
            }
        }    
        return result;
    }
    else
        throw(tensor_not_initialized());
}

Tensor Tensor::subset(unsigned int row_start, unsigned int row_end, unsigned int col_start, unsigned int col_end, unsigned int depth_start, unsigned int depth_end) const{
    if (data){
    Tensor result = Tensor(row_end-row_start, col_end-col_start, depth_end-depth_start, 0.0);

        for(int depth = depth_start; depth < depth_end; depth++){
            for(int row = row_start; row < row_end; row++){
                for(int col = col_start; col < col_end; col++){ 
                    result.data[depth-depth_start][row-row_start][col-col_start] = this -> data[depth][row][col];
                }
            }
        }
        return result;
    }
     else
        throw(tensor_not_initialized());
}

Tensor Tensor::concat(const Tensor &rhs, int axis) const{
    if(data){
        if (axis==0){
            if(this->c==rhs.c){//controllo colonne (forse depth?)
                int rowresult = rhs.r + this->r;
                Tensor result = Tensor(rowresult ,this->c, this->d, 0.0);

                for(int depth = 0; depth < this-> d; depth++){
                    for(int row = 0; row < rowresult ; row++){
                        for(int col = 0; col < this->c; col++){

                        if( row < this->r ) result.data[depth][row][col] = this -> data[depth][row][col];
                        else result.data[depth][row][col] = rhs.data[depth][row-this->r][col];
                        }
                    }
                }
                return result;
            }
            else throw(concat_wrong_dimension());
        }
        else{ //controllo righe (forse depth?)
            if(this->r==rhs.r){
                int colresult = rhs.c + this->c;
                Tensor result = Tensor(this->r  ,colresult, this->d, 0.0);

                for(int depth = 0; depth < this-> d; depth++){
                    for(int row = 0; row < this->r ; row++){
                        for(int col = 0; col < colresult; col++){
                            
                        if( col < this->c ) result.data[depth][row][col] = this -> data[depth][row][col];
                        else result.data[depth][row][col] = rhs.data[depth][row][col - (this->c)];
                        }
                    }
                }
                return result;
            }
            else throw(concat_wrong_dimension());

        }
    
    }
     else
        throw(tensor_not_initialized());
}

Tensor Tensor::convolve(const Tensor &f) const{
    if(data != nullptr && f.data != nullptr){
        if( f.d != d )
            throw(dimension_mismatch());

        if((f.c % 2 != 0) && (f.r % 2 != 0) ) { //controllo stessa depth e dimensioni dispari
            Tensor result(r, c, d, 0);

            Tensor padded;
            Tensor supp;

            float el = 0;

            int height = (f.r - 1) / 2;
            int width  = (f.c - 1) / 2;

            padded = this -> padding(height, width);

            for(int j = 0; j < this -> r; j++){
                for(int l = 0; l < this -> c; l++){
                    supp = padded.subset(j, (j + f.r), l, (l + f.c), 0, f.d);
                    supp = supp * f;

                    for(int m = 0; m < f.d; m++){
                        for(int n = 0; n < f.r; n++)
                            for(int o = 0; o < f.c; o++)
                                el += supp.data[m][n][o];

                        result.data[m][j][l] = el;
                        el = 0;
                    }    
                }
            }
            
            return result;
        }
        else
            throw(filter_odd_dimensions());
    }

    else
        throw(tensor_not_initialized());
}

int Tensor::rows() const{
    return r;
}

int Tensor::cols() const{
    return c;
}

int Tensor::depth() const{
    return d;
}

float Tensor::getMin(int k) const{
    if(!data)
        throw(tensor_not_initialized());
    if(k< 0 || k >= d)
        throw(index_out_of_bound());
  
    float min = data[k][0][0];

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(data[k][i][j] < min)
                min = data[k][i][j];
        }
    }

    return min;
}

float Tensor::getMax(int k) const{
    if(!data)
        throw(tensor_not_initialized());
    if(k< 0 || k >= d)
        throw(index_out_of_bound());

    float max = data[k][0][0];

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(data[k][i][j] > max)
                max = data[k][i][j];
        }
    }

    return max;
}

void Tensor::showSize()const{
    cout<<r<<" x "<<c<<" x "<<d<<endl;
}
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++
ostream& operator<< (ostream& stream, const Tensor & obj){
    if(obj.data){
        stream<<"[";
        for(int r; r<obj.c; r++){
            stream<<"col_"<<r<<" ; ";
        }
        stream<<"layer]"<<endl;
        
        int cnt=0;
        for(int i=0; i<obj.d; i++){
            stream<<"[";
            for(int j=0; j<obj.r; j++){
                for(int l=0; l<obj.c; l++){
                    stream<<obj.data[i][j][l]<<" ";
                }
                stream<<"; ";
            }
            stream<<i<<"]";
            stream<<endl;
        }
    }
    else{
        stream<<"[nullptr]"<<endl;
    }

    return stream;
}

void Tensor::read_file(string filename){
    ifstream file;
    file.open(filename);

    string str;

    int row;
    int col;
    int depth;

    if(file.is_open()){
        for(int cnt = 0; cnt < 3; cnt++){
            if(getline(file, str)){
                //controlli su stringa iniziale
                if(str.empty())
                    throw (unknown_exception());
                for(auto c: str){
                    if(c<'0' || c>'9'){
                        throw (unknown_exception());
                    }
                }
                switch (cnt){
                    case 0: row = stoi(str);
                            break;
                    
                    case 1: col = stoi(str);
                            break;

                    case 2: depth = stoi(str);
                            break;
                }
            }
        }

        if(this -> r != row || this -> c != col || this -> d != depth){

            if(data != nullptr)
                this -> ~Tensor();  //CANCELLO TUTTO
            
            this -> r = row;
            this -> c = col;
            this -> d = depth;

            //ASSEGNAMENTO MEMORIA
            data = new float **[depth];

            for(int i = 0; i < depth; i++){
                data[i] = new float* [row];

                for(int j = 0; j < row; j++)
                    data[i][j] = new float[col];
            }

        }

        for(int i = 0; i < depth; i++)
            for(int j = 0; j < row; j++)
                for(int l = 0; l < col; l++)
                    if(getline(file, str)){
                        //controlli su stringa iniziale
                        if(str.empty())
                            throw (unknown_exception());
                        for(auto c: str){
                            if(c<'0' || c>'9'){
                                throw (unknown_exception());
                            }
                        }

                        data[i][j][l] = stof(str);
                    }
                        

        file.close();
    }

    else
        throw(unable_to_read_file());
}

void Tensor::write_file(string filename){
    ofstream file;
    file.open(filename);
    
    if(file.is_open()){
        file << r << endl;
        file << c << endl;
        file << d << endl;

        for(int i = 0; i < d; i++){
            for(int j = 0; j < r; j++){
                for(int l = 0; l < c; l++){
                    if((i != (d - 1)) || (j != (r - 1)) || (l != (c - 1)))
                        file << data[i][j][l] << endl;

                    else
                        file << data[i][j][l];
                }
            }
        }

        file.close();
    }
}
