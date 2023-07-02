#include "bigint.h"
#include "fraction.h"
#include "BigFraction.h"
#include <iostream>



int main(){
    bigint f_ch("123");
    bigint f_zn("532");
    bigint s_ch("223");
    bigint s_zn("3123");
    unsigned long int  c = 3;
    BigFraction f1(f_ch, f_zn);
    BigFraction f2(s_ch, s_zn);
    BigFraction f3(f1 * c);

    //std::cout<<(f1+f2)<<std::endl;
    f3.print();
    return 0;
}