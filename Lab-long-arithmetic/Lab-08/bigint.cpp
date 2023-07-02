#include "bigint.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

bigint::bigint()
    : data(NULL), size(0), neg(false)
{
}

bigint::bigint(const bigint& obj)
{
    size = obj.size;
    neg = obj.neg;
    try {
      data = new char[size];
  } catch(...) {
      std::cerr << "Error allocating memory" << std::endl;
    exit(1);
  }

  for(size_t r=0; r<size; ++r)
      data[r] = obj.data[r];
}

bigint::~bigint()
{
  delete[] data;
    data = NULL;
}


bigint::bigint(long number){
    int i;
    unsigned long nm;
    neg = true;
    if (number >= 0) neg = false;
    nm = abs(number);
    for (i=0; nm > 0; i++)
        nm = nm / 10;
    size = i;
    if (number == 0) size = 1;
    number = abs(number);

    try {

        data = new char[size];
    } catch(...) {
        std::cerr << "Error allocating memory" << std::endl;
        exit(1);
    }
    for (i=0; i<size;i++){
        data[size-i-1] = (char)(((int)'0') + number%10);
        number /= 10;
    }


}
bigint::bigint(unsigned long number) {
    int i;
    unsigned long nm;
    neg = false;
    nm = number;
    for (i=0; nm > 0; i++)
        nm = nm / 10;
    size = i;
    if (number == 0) size = 1;


    try {

        data = new char[size];
    } catch(...) {
        std::cerr << "Error allocating memory" << std::endl;
        exit(1);
    }
    for (i=0; i<size;i++){
        data[size-i-1] = (char)(((int)'0') + number%10);
        number /= 10;
    }

}

bigint::bigint(const char *char_mas) {
    int i=0, sd=0;
    neg = false;
    if (char_mas[0] == '-') {
    neg = true;
    sd = 1;
    }
    size = strlen(char_mas)-sd;


    try {

        data = new char[size];
    } catch(...) {
        std::cerr << "Error allocating memory" << std::endl;
        exit(1);
    }
    for (i; i < size; i++) {
        data[i] = char_mas[i + sd];
    }

}

void bigint::print() const {
    if (neg) {
        cout << "-";
        for (int i = 0; i < size; i++)
            cout << data[i];
    }
    else {
        for (int i = 0; i < size; i ++)
            cout << data[i];
    }
    cout << endl;
}

bigint bigint::add(const bigint& left, const bigint& right) {
    size_t length= 0;
    int i, j;
    int *result_data, *data_l, *data_r;
    char *result;
    bool is_res_sign = true;
    int diff_zn = (2 * (int)(left.neg == right.neg)) - 1;

    if (left.size > right.size)
        length = left.size + 1;
    else
        length = right.size + 1;
    try{
    result_data = new int[length];
    data_l = new int[length-1];
    data_r = new int[length-1] ;
    result = new char[length] ;
    } catch (...) {
           std::cerr << "Memory allocation error" << std::endl;
        exit(1);
    }
    for (int i = 0; i < length-1; i++) {
        data_l[i] = 0;
        data_r[i] = 0;
        result_data[i] = 0;
    }
    result_data[length-1] = 0;

    for(i=left.size-1;i>=0;i--){
        data_l[left.size - 1 - i] = left.data[i] - '0';
    }
    for(i=right.size-1;i>=0;i--){
        data_r[right.size - 1 - i] = right.data[i] - '0';
    }

    for (int i = 0; i < length-1; i++)
    {
        result_data[i] += data_l[i] + diff_zn * data_r[i];

    }

    for (i = 0; i < length - 2 && result_data[length - 2 - i] == 0; ++ i);
    if (result_data[length - 2 - i] < 0  || (i == length - 2 && result_data[0] == 0 && left.neg && left.neg != right.neg)) {
        is_res_sign = false;

        for (i = 0; i < length - 1; ++ i) {

            result_data[i] = -result_data[i];
        }
    }

    for (i = 0; i < length - 1; ++ i) {
        if ((-diff_zn) * result_data[i] < (-((diff_zn + 1)/2) )*9) {

            result_data[i] -= (diff_zn * 10);
            result_data[i + 1] += diff_zn;
        }
    }
    for(i=0; i<length; i++){
        result[length -1 - i] = (char)(result_data[i] + '0');
    }
    for(i=0; i<length && result[i] == '0'; ++i);
    for(j=i;j < length; j++){
        result[j-i] = result[j];
    }
    delete result_data;
    delete data_l;
    delete data_r;
    if(length - i == 0){
        bigint result_obj((long)(0));
        delete result;
        result_obj.size =1;
        result_obj.neg = false;
        return  result_obj;
    }

    bigint result_obj(result);
    result_obj.size = length - i;
    delete result;


    result_obj.neg = is_res_sign == left.neg;
    return result_obj;
}

bigint bigint::sub(const bigint& left, const bigint& right){
    bigint new_right(right);
    new_right.neg = !new_right.neg;
    return add(left, new_right);
}

bigint bigint::mul(const bigint& left, const bigint& right){
    size_t  length = left.size + right.size;
    int *result_data, *data_l, *data_r;
    int i, j;
    char *result;
    try{
        result_data = new int[length];
        data_l = new int[length-1];
        data_r = new int[length-1] ;
        result = new char[length] ;
    } catch (...) {
        std::cerr << "Memory error" << std::endl;
        exit(1);
    }
    for (int i = 0; i < length-1; i++) {
        data_l[i] = 0;
        data_r[i] = 0;
        result_data[i] = 0;
    }
    result_data[length-1] = 0;

    for(i=left.size-1;i>=0;i--){
        data_l[left.size - 1 - i] = left.data[i] - '0';

    }
    for(i=right.size-1;i>=0;i--){
        data_r[right.size - 1 - i] = right.data[i] - '0';
    }

    for (i = 0; i < left.size; i++)
    {
        for(j = 0; j < right.size; j++) {
            result_data[i+j] += data_l[i] * data_r[j];
        }
    }

    for(i=0; i < length; i++){
        result_data[i+1] += result_data[i] / 10;
        result_data[i] = result_data[i] % 10;
    }

    for(i=0; i<length; i++){
        result[length -1 - i] = (char)(result_data[i] + '0');
    }
    for(i=0; i<length && result[i] == '0'; ++i);
    for(j=i;j < length; j++){
        result[j-i] = result[j];
    }

    delete result_data;
    delete data_l;
    delete data_r;
    if(length - i == 0){
        bigint result_obj(result);
        delete result;
        result_obj.size =1;
        result_obj.neg = false;
        return  result_obj;
    }

    bigint result_obj(result);
    result_obj.size = length - i;
    delete result;


    result_obj.neg = right.neg != left.neg;
    return  result_obj;

}


bigint bigint::div(const bigint& left, const bigint& right) {
    bigint new_left(left);
    new_left.neg = false;
    int i,j;

    bigint new_right (right);
    new_right.neg = false;
    bool is_left_zero = true;
    bool is_right_zero = true;
    for (i = 0; i < left.size; ++i) {
        if(left.data[i] != '0'){
            is_left_zero = false;
            break;
        }
    }
    for (i = 0; i < right.size; ++i) {
        if(right.data[i] != '0'){
            is_right_zero = false;
            break;
        }
    }

    if(is_left_zero){
        bigint result_obj(left);
        result_obj.size =1;
        result_obj.neg = false;
        return  result_obj;
    }
    if(is_right_zero){
        //std::cerr<<"ZeroDivisionError"<<std::endl;
        bigint result_obj(right);
        result_obj.size =1;
        result_obj.neg = false;
        return  result_obj;
    }

    bigint div_result(new_left);
    div_result.size = new_left.size;
    for (i = 0; i < div_result.size; ++ i)
        div_result.data[i] = '0';

    for (i = 0; i < new_left.size ; ++i) {
        int counter_in = 9;
        for(counter_in = 9; counter_in >= 0; counter_in --){
            div_result.data[ i] = (char)(counter_in + '0');
            bigint curr_res = bigint::sub(new_left, bigint::mul(div_result, new_right));
            if (!curr_res.neg)
                break;
        }
    }

    for(i=0; i<div_result.size && div_result.data[i] == '0'; ++i);
    for(j=i;j < div_result.size; j++){
        div_result.data[j-i] = div_result.data[j];
    }


    if(div_result.size - i == 0){
        div_result.size =1;
        div_result.neg = false;
        return  div_result;
    }
    div_result.size = div_result.size - i;
    div_result.neg = right.neg != left.neg;
    return  div_result;

}

bigint bigint::div(const bigint& left, const bigint& right, bigint& rest) {
    bigint div_res(div(left, right));
    bigint* buff = new bigint(bigint::sub(left, bigint::mul(div_res, right)));

    rest.data = buff -> data;
    rest.size = buff -> size;
    rest.neg = buff -> neg;

    buff -> data = NULL;
    delete buff;
    return div_res;


}

bigint bigint::gcd(const bigint &a, const bigint &b) {
    bigint *curr_rest= new bigint();
    bigint *last_rest = new bigint();
    bigint *buffer = new bigint();

    if (!bigint::sub(a, b).neg) {
        last_rest = new bigint(b);
        bigint::div(a, b, *curr_rest);
        }
    else {
        last_rest = new bigint(a);
        bigint::div(b, a, *curr_rest);
    }
   while (true){
       bigint::div(*last_rest, *curr_rest, *buffer);
       if((!bigint::add(*buffer, bigint((long)(1))).neg)&&(bigint::sub(*buffer, bigint((long)(1))).neg)){
           return *curr_rest;
       }
        last_rest = new bigint(*curr_rest);
        curr_rest = new bigint(*buffer);
    }
}

bigint bigint::sqrt(const bigint& value) {
    bigint diver((long)(0));
    bigint *res = new bigint((long)(0));
    if (value.neg) {
        std::cerr<<"Sqrt of minus"<<std::endl;
        bigint res((long)(0));
        return res;
    }
    while(true){
        res = new bigint(bigint::add(*res, bigint((long)(1))));
        if(bigint::sub(value, bigint::mul(*res, *res)).neg) break;
    }
    res = new bigint(bigint::sub(*res, bigint((long)(1))));
    return *res;
}




unsigned long bigint::Eratosthenes(bigint *sieve, unsigned long size) {
    bigint *diver = new bigint((long)(1));
    size_t result[size];
    bool flag = true;
    unsigned long result_r = 0;
    bigint *max= new bigint(sieve[0]);
    for (unsigned long i = 0; i < size; ++i) {
        if(bigint::sub(*max, sieve[i]).neg)
            max = new bigint(sieve[i]);
        result[i] = 1;
    }

    while(flag){
        diver = new bigint(bigint::add(*diver, bigint((long)(1))));
        if (bigint::sub(bigint::sub(*max, *diver),bigint((long)(1))).neg) break;
        for (unsigned long i = 0; i < size; ++i) {
            if (bigint::sub(bigint::sub(sieve[i], *diver),bigint((long)(1))).neg) continue;
            if (!bigint::sub(bigint::gcd(*diver, sieve[i]), bigint((long)(2))).neg){
                result[i] = 0;
            }
        }
    }
    for (unsigned long i = 0; i < size; ++i) {
        result_r += result[i];
    }
    return result_r;

}


bool bigint::is_null(){
    if(data[0] == 0 && size == 1) return true;
    return false;
}

bigint operator+(const bigint& left, const bigint& right) {
    return bigint::add(left,right);
}

bigint operator-(const bigint& left, const bigint& right) {
    return bigint::sub(left,right);
}
bigint operator/(const bigint& left, const bigint& right) {
    return bigint::div(left,right);
}
bigint operator*(const bigint& left, const bigint& right) {
    return bigint::mul(left,right);
}

bigint operator%(const bigint& left, const bigint& right){
    bigint a;
    bigint::div(left, right, a);
    return a;
}

bigint operator/(const bigint& left, unsigned long right){
    return left / bigint(right);
}



bigint operator%(const bigint& left, unsigned long right){
    return left % bigint(right);
}
bigint operator+(const bigint& left, unsigned long right){
    return left + bigint(right);
}

bigint operator*(const bigint& left, unsigned long right){
    return left * bigint(right);
}


void bigint::operator=(const bigint& right){
    data = new char[right.size];
    size = right.size;
    neg = right.neg;
    for (int i = 0; i < right.size; ++i)
    {
        data[i] = right.data[i];
    }
}

bool operator>(const bigint& left, const bigint& right){
    bigint res = left - right;
    if(res.neg || res.is_null()){
        return false;
    } 
    return true;
}

bool operator<(const bigint& left, const bigint& right){
     bigint res = left - right;
    if(res.neg){
        return true;
    } 
    return false;
}

bool operator==(const bigint& left, const bigint& right){
    bool flag = true;
    if(left.size == right.size){

        for (unsigned long i = 0; i < left.size; ++i)
        {
            if(left.data[i] != right.data[i])
                flag = false;
        }
    }else flag = false;
    return flag;
}

bool operator!= (const bigint& left, const bigint& right){
    return !(left == right);
}

bool operator==(const bigint& left, unsigned long right){
   bigint buf = left - bigint(right);
   if (buf.is_null())
   {
       return true;
   }
   return false;
}

bool operator>(const bigint& left,  unsigned long right){
    bigint res = left - bigint(right);
    if(res.neg || res.is_null()){
        return false;
    } 
    return true;
}

bool operator<(const bigint& left, unsigned long right){
     bigint res = left - bigint(right);
    if(res.neg){
        return true;
    } 
    return false;
}


bool operator<=(unsigned long left, const bigint& right){
    return (!(right > left) || right == left);
}


std::ostream& operator<<(std::ostream &out, const bigint& r){
    if(r.neg) out << "-";
    for (int i = 0; i < r.size; ++i)
    {
        out << r.data[i];
    }
     
     return out;
}