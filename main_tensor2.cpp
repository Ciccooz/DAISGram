#include <stdio.h>
#include <string.h>
#include <math.h>
#include "tensor.h"


int main (int argc, char * argv[]) {

    cout<<"******************************************"<<endl;
    cout<<"Constructor default"<<endl;
    Tensor a;
    cout<<a<<endl;

    cout<<"2Constructor Tensor(3, 3, 3, 35.7)"<<endl;
    Tensor b(3,3,3, 35.7);
    cout<<b<<endl;

    cout<<"Copy-Constructor z{b}"<<endl;
    cout<<"b"<<endl;
    cout<<b<<endl;
    cout<<"z"<<endl;
    Tensor z{b};
    cout<<z<<endl;
    Tensor arca = z;
    cout<<arca<<endl;

    cout<<"******************************************"<<endl;
    cout<<"Operator=    [from empty]"<<endl;
    cout<<"a, size: ";
    a.showSize();
    cout<<a<<endl;
    cout<<"b, size: ";
    b.init_random(3,3);
    b.showSize();
    cout<<b<<endl;
    if (a==b)        
        cout<<"Operator==: Uguali"<<endl;
    else
        cout<<"Operator==: Diversi"<<endl;
    cout<<endl;
    cout<<"a=b"<<endl;
    a = b;
    cout<<a<<endl;
    if (a==b)        
        cout<<"Operator==: Uguali"<<endl;
    else
        cout<<"Operator==: Diversi"<<endl;

    cout<<endl;
    cout<<"Operator=    [from not empty, same dimension] "<<endl;
    Tensor d(2,2,2);
    d.init_random(10,5);
    cout<<"d, size: ";d.showSize();
    cout<<d<<endl;
    Tensor x(2,2,2);
    x.init_random(5,10);
    cout<<"x, size: ";x.showSize();
    cout<<x<<endl;
    cout<<"x=d"<<endl;
    x = d;
    cout<<x<<endl;

    cout<<"Operator=    [from not empty, different dimension (overwrite)] "<<endl;
    d.init_random(4,6);
    Tensor r(1,1,2,7.4657);
    cout<<"d, size: "; d.showSize();
    cout<<d<<endl;
    cout<<"r, size: "; 
    r.showSize();
    cout<<r<<endl;
    cout<<"d=r"<<endl;
    d = r;
    cout<<d<<endl;

    cout<<"******************"<<endl;
    cout<<"getMin() and getMax()"<<endl;
    cout<<a<<endl;
    cout<<"Min(0): "<<a.getMin(0)<<endl;
    cout<<"Max(0): "<<a.getMax(0)<<endl;
    cout<<"Min(1): "<<a.getMin(1)<<endl;
    cout<<"Max(1): "<<a.getMax(1)<<endl;
    cout<<"Min(2): "<<a.getMin(2)<<endl;
    cout<<"Max(2): "<<a.getMax(2)<<endl;
    cout<<endl;
    //cout<<"Max(2): "<<a.getMax(3)<<endl;

    cout<<"******************"<<endl;
    cout<<"rescale of 3"<<endl;
    cout<<a<<endl;
    a.rescale(3);
    cout<<a<<endl;

    cout<<"******************"<<endl;
    cout<<"Mathematical Operators"<<endl;
    Tensor tens1, tens2;
    tens1.read_file("/home/mattia/labprog2020-2021/tensors/t_4_3_2_progressive.txt");
    tens2.read_file("/home/mattia/labprog2020-2021/tensors/t_4_3_2_progressive.txt");
    tens1.showSize();
    cout<<tens1<<endl;
    tens2.showSize();
    cout<<tens2<<endl;
    
    cout<<"operators"<<endl;
    cout<<"+"<<endl;
    cout<<tens1+tens2<<endl;
    cout<<"-"<<endl;
    cout<<tens1-tens2<<endl;
    cout<<"*"<<endl;
    cout<<tens1*tens2<<endl;
   // cout<<"/"<<endl;
   // cout<<tens1/tens2<<endl;
    cout<<"operators with constant"<<endl;
    cout<<"+"<<endl;
    cout<<tens1+2.3<<endl;
    cout<<"-"<<endl;
    cout<<tens1-2.3<<endl;
    cout<<"*"<<endl;
    cout<<tens1*2.3<<endl;
    cout<<"/"<<endl;
    cout<<tens1/2.3<<endl;    
    
    cout<<"******************"<<endl;
    cout<<"Operator()"<<endl;
    Tensor bracket(3, 3, 3, 1);
    cout<<bracket(0, 0, 0)<<endl;
    //cout<<bracket(-1, -1, -1);

    cout<<"******************"<<endl;
    cout<<"read_file and write_file"<<endl;
    Tensor rwInit(3, 3, 3, 0);
    Tensor rwNotInit;

    //INITIALIZED
    cout<<"reading.."<<endl;
    rwInit.read_file("/home/mattia/labprog2020-2021/tensors/t_4_3_2_progressive.txt");
    cout<<"writing.."<<endl;
    rwInit.write_file("out.txt");
    cout<<"initialized:"<<endl;
    cout<<rwInit<<endl;

    //NOT INITIALIZED
    rwNotInit.read_file("/home/mattia/labprog2020-2021/tensors/t_4_3_2_progressive.txt");
    rwNotInit.write_file("res.txt");
    cout<<"not initialized:"<<endl;
    cout<<rwNotInit<<endl;

    cout<<"******************"<<endl;
    cout<<"init"<<endl;
    Tensor initInit(3, 3, 3, 0);
    Tensor initNotInit;

    //INIZIALIZZATO
    initInit.init(2, 2, 2, 0);
    cout<<"initialized:"<<endl;
    cout<<initInit<<endl;

    //NON INIZIALIZZATO
    initNotInit.init(2, 2, 2, 0);
    cout<<"not initialized:"<<endl;
    cout<<initNotInit<<endl;

    cout<<"**"<<endl;
    cout<<"Clamp"<<endl;
    cout<<rwInit<<endl;
    rwInit.clamp(0, 20);
    cout<<rwInit<<endl;

    cout<<"Padding"<<endl;
    //tens2=tens1.padding(2,2);
    cout<<tens2<<endl;

    cout<<"Subset"<<endl;
    Tensor tens3;
    tens3=tens1.subset(2,3,1,3,1,2);
    cout<<tens3<<endl;

    //rileggere tensori in modo da fare più prove
/*
   cout<<"Concat dimensioni diverse"<<endl;
    Tensor tens4;
    tens4=tens1.concat(tens3, 1);
    cout<<tens4<<endl;
*/
    cout<<"Concat dimensioni uguale (su righe)"<<endl;
    Tensor tens5;
    cout<<"TENSOR 1:\n\n";
    cout<<tens1<<endl;

    cout<<"TENSOR2\n\n";
    cout<<tens2<<endl;
    tens2.showSize();
    tens1.showSize();
    tens5=tens1.concat(tens2, 0);
    cout<<tens5<<endl;

    cout<<"Concat dimensioni uguale (su colonne)"<<endl;
    Tensor tens6;
    tens6=tens2.concat(tens1, 1);
    cout<<tens6<<endl;
   
    Tensor filter(3, 3, 3, 1);
    Tensor conv(3, 3, 3, 2);
    cout<<conv.convolve(filter)<<endl;
    return 0; /* ciao a tutti!*/
}
