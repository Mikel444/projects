#include "bigint.h"
#include "fraction.h"
#include "BigFraction.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

BigFraction::BigFraction(): fraction(){
		a = bigint("0");
		b = bigint("1");
	}

BigFraction::BigFraction(const bigint& a_cur,const bigint& b_cur) {
    bigint ac = a_cur;
    bigint bc = b_cur;
    if (bc == 0) {
        cerr << "Error division by zero" << endl;
        exit(1);
    }
    for (unsigned long i = 2; i <= (ac + bc) / 2; ++i) {
        while ((ac % i == 0) && (bc % i == 0)) {
            ac = ac / i;
            bc = bc / i;
        }
    }
    a = ac;
    b = bc;
}

void BigFraction::print(){
    cout << a << "/" << b << endl;
}
	

BigFraction::BigFraction(const BigFraction& f){
        a = bigint(f.a);
        b = bigint(f.b);
}


BigFraction operator*(const BigFraction& left, const BigFraction& right) {
        BigFraction ans(left.a*right.a, left.b*right.b);
	   return ans;
}

BigFraction operator/(const BigFraction& left, const BigFraction& right) {
    BigFraction ans(left.a*right.b, left.b*right.a);
    return ans;
}

BigFraction operator+(const BigFraction& left, const BigFraction& right) {
    BigFraction ans(left.a*right.b + left.b*right.a, left.b*right.b);
    ans.print();
    return ans;
}

BigFraction operator-(const BigFraction& left, const BigFraction& right) {
    if ((left.a*right.b - left.b*right.a) < 0) {
        cerr << "Error sub < 0" << endl;
	   exit(1);
    }
    BigFraction ans(left.a*right.b - left.b*right.a, left.b*right.b);
    return ans;
}

BigFraction operator*(const BigFraction& left, unsigned long int right) {
    BigFraction ans(left.a*right, left.b);
    return ans;
}

BigFraction operator/(const BigFraction& left, unsigned long int right) {
    BigFraction ans(left.a, left.b*right);
    return ans;
}

void BigFraction::operator=(const BigFraction& right){
    a = bigint(right.a);
    b = bigint(right.b);
    a.print();
    b.print();
}

BigFraction::~BigFraction()
{}

	
