#include <iostream>
#include <string>

#include "dais_exc.h"
#include "tensor.h"
#include "libbmp.h"
#include "DAISGram.h"

using namespace std;

DAISGram::DAISGram(){

}

DAISGram::~DAISGram(){

}

/**
 * Load a bitmap from file
 *
 * @param filename String containing the path of the file
 */
void DAISGram::load_image(string filename){
    BmpImg img = BmpImg();

    img.read(filename.c_str());

    const int h = img.get_height();
    const int w = img.get_width();

    data = Tensor(h, w, 3, 0.0);

    for(int i=0;i<img.get_height();i++){
        for(int j=0;j<img.get_width();j++){ 
            data(i,j,0) = (float) img.red_at(j,i);
            data(i,j,1) = (float) img.green_at(j,i);    
            data(i,j,2) = (float) img.blue_at(j,i);   
        }                
    }
}


/**
 * Save a DAISGram object to a bitmap file.
 * 
 * Data is clamped to 0,255 before saving it.
 *
 * @param filename String containing the path where to store the image.
 */
void DAISGram::save_image(string filename){

    data.clamp(0,255);

    BmpImg img = BmpImg(getCols(), getRows());

    img.init(getCols(), getRows());

    for(int i=0;i<getRows();i++){
        for(int j=0;j<getCols();j++){
            img.set_pixel(j,i,(unsigned char) data(i,j,0),(unsigned char) data(i,j,1),(unsigned char) data(i,j,2));                   
        }                
    }

    img.write(filename);

}

int DAISGram::getRows(){
    return this->data.rows();
}

int DAISGram::getCols(){
    return this->data.cols();
}

int DAISGram::getDepth(){
    return this->data.depth();    
}

DAISGram DAISGram::brighten(float bright){
    DAISGram result;
    result.data = data + bright;
    result.data.clamp(0, 255);

    return result;
}

//Grayscale = (R + G + B ) / 3.
DAISGram DAISGram::grayscale(){
    DAISGram dais;
    dais.data = this->data;

    float average=0;
    float sum =0;
    int n = dais.getDepth();

    for(int i = 0; i < dais.getRows(); i++){
        for(int j = 0; j < dais.getCols(); j++){
            for(int k = 0; k < n; k++){
                sum += dais.data(i,j,k);
            }
            
            if(n>0){
                average = sum/(float)n;
                sum=0;
            }
            else
                throw(tensor_not_initialized());
            for(int k = 0; k < n; k++){
                dais.data(i,j,k) = average;
            }
        }
    }
   
    return dais;

}

DAISGram DAISGram::warhol(){
    DAISGram result;

    Tensor topLeft, topRight, botLeft, botRight, top, bot;
    topLeft = topRight = botLeft = botRight = data;
    
    for(int l = 0; l < data.depth(); l++){
        for(int i = 0; i < data.rows(); i++){
            for(int j = 0; j < data.cols(); j++){
                if(l == 0){
                    topRight(i, j, 1) = data(i, j, l);
                    botRight(i, j, 2) = data(i, j, l);
                }

                if(l == 1){
                    topRight(i, j, 0) = data(i, j, l);
                    botLeft(i, j, 2)  = data(i, j, l);
                }

                if(l == 2){
                    botRight(i, j, 0) = data(i, j, l);
                    botLeft(i, j, 1)  = data(i, j, l);
                }
            }
        }
    }

    top = topLeft.concat(topRight, 1);
    bot = botLeft.concat(botRight, 1);

    result.data = top.concat(bot, 0);
    
    return result;
}

DAISGram DAISGram::sharpen(){
   DAISGram dais;

    Tensor filter;
    filter.read_file("filters/f_3_3_3_sharpen.txt");
    
    Tensor conv = this->data.convolve(filter);
    
    conv.clamp(0,255);

    dais.data = conv;

    return dais;

}
/*
* filter[3][3]
*    -2 -1  0
*    -1  1  1
*     0  1  2
*/
DAISGram DAISGram::emboss(){
    DAISGram dais;

    Tensor filter;
    filter.read_file("filters/f_3_3_3_emboss.txt");
    
    Tensor conv = this->data.convolve(filter);
    
    conv.clamp(0,255);

    dais.data = conv;

    return dais;
}

DAISGram DAISGram::smooth(int h){
    DAISGram dais;
    float value = 1 / float(h*h);
    Tensor filter(3, 3, 3, value);

    Tensor smooth = this -> data.convolve(filter);
    smooth.clamp(0,255);

    dais.data = smooth;

    return dais;

}

DAISGram DAISGram::edge(){
    DAISGram dais;

    Tensor filter;
    filter.read_file("filters/f_3_3_3_edge.txt");

    *this = this->grayscale();
    
    Tensor conv = this->data.convolve(filter);
    
    conv.clamp(0,255);

    dais.data = conv;

    return dais;
}

DAISGram DAISGram::blend(const DAISGram & rhs, float alpha){
 	DAISGram dais;
   	dais.data = this->data;


	if ((this->getRows()==rhs.data.rows()) && (this->getCols()==rhs.data.cols()) && (this->getDepth()==rhs.data.depth()))
    {
		for(int i = 0; i < dais.getRows(); i++){
            for(int j = 0; j < dais.getCols(); j++){
				for(int k = 0; k < dais.getDepth(); k++){
					dais.data(i,j,k)=this->data(i,j,k) * alpha + rhs.data(i,j,k) * (1-alpha);
				}
			}
		}
	}
	else  throw(dimension_mismatch());

	
	return dais;
}

DAISGram DAISGram::greenscreen(DAISGram & bkg, int rgb[], float threshold[]){
    DAISGram dais;
   	dais.data = this->data; //image
    bool check = 1;

    for(int i = 0; i < dais.getRows(); i++){
        for(int j = 0; j < dais.getCols(); j++){
            for(int k = 0; k < dais.getDepth(); k++){
                float pixel = dais.data(i,j,k);
                check = check && ( (pixel >= rgb[k] - threshold[k]) && (pixel <= rgb[k] + threshold[k]) ); 
            }
            
            if(check == 1){
                for(int k = 0; k < dais.getDepth(); k++){
                    dais.data(i,j,k) = bkg.data(i,j,k); //background
                }
            }

            check = 1; //reset check
        }
    }

    return dais;
}

//equalize function
float funz(float cdf, float cdfmin, int M, int N, int intensity){
    return round( ((cdf-cdfmin) * (intensity-1))/(M*N - cdfmin) ) ;
}


DAISGram DAISGram::equalize(){
    DAISGram dais;
    dais.data = this->data;

    int num = 256;
    int col = 4;
    float tab[num][col][data.depth()]; //256 righe, 3 colonne, canale

    //inizializzazione
    for(int i = 0; i < num; i++){
        for(int j = 0; j < col; j++){
            for(int k = 0; k < data.depth(); k++){
                tab[i][j][k] = 0;
            }
        }
    }

    //inizializzazione 1 colonna 
    for(int i = 0; i<num; i++){
        for(int k = 0; k < data.depth(); k++){
            tab[i][0][k] = i;
        }
    }

    //frequenza (2 colonna)
    for(int l = 0; l < data.depth(); l++){
        for(int i = 0; i < data.rows(); i++){
            for(int j = 0; j < data.cols(); j++){
                tab[(int)data(i,j,l)][1][l]++;  //frequenza relativa
            }
        }
    }

    //prima riga frequenza cumulativa
    for(int k = 0; k < data.depth(); k++){
        tab[0][2][k] = tab[0][1][k];
    }
    //frequenza cumulativa
    bool flag = true;
    int min[data.depth()];
    float prev=0;
    for(int k = 0; k < data.depth(); k++){
        for(int i = 1; i<num; i++){
            if(tab[i][1][k] != 0){
                tab[i][2][k] = tab[i][1][k] + prev; //se è
                prev = tab[i][2][k];
                if(flag){
                    flag = false;
                    min[k] = tab[i][1][k];
                }
            }
        }
        flag = true;
        prev = 0;
    }
    
    //funzione
    for(int k = 0; k < data.depth(); k++){
        for(int i = 0; i < num; i++){
            tab[i][3][k] = funz(tab[i][2][k], min[k], data.rows(), data.cols(), num);
        }
    }

    //print
    /*for(int k = 0; k < data.depth(); k++){
        cout<<"Canale: "<<k<<endl;
        for(int i = 0; i < num; i++){
            for(int j = 0; j < col; j++){        
                cout<<tab[i][j][k]<<" ";
            }
            cout<<endl;
        }
        
    }*/

    //sostituzione pixel 
    for(int l = 0; l < data.depth(); l++){
        for(int i = 0; i < data.rows(); i++){
            for(int j = 0; j < data.cols(); j++){
                dais.data(i,j,l) = tab[(int)data(i,j,l)][3][l];
            }
        }
    }

    return dais;

}

/**
 * Generate Random Image
 * 
 * Generate a random image from nois
 * 
 * @param h height of the image
 * @param w width of the image
 * @param d number of channels
 * @return returns a new DAISGram containing the generated image.
 */  
void DAISGram::generate_random(int h, int w, int d){
    data = Tensor(h,w,d,0.0);
    data.init_random(128,50);
    data.rescale(255);
}
