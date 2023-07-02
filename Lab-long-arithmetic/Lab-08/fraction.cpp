#include "fraction.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl;
using std::cerr;

fraction::fraction()
  : a(0), b(1)
{}

fraction::fraction(const fraction& obj)
  : a(obj.a), b(obj.b)
{}

fraction::fraction(unsigned long int a_cur, unsigned long int b_cur) {
    if (b_cur == 0) {
        cerr << "Error division by zero" << endl;
        exit(1);
    }
    if (a_cur == 0) {
        b = 1;
        a = 0;
    }
    else {
        for (unsigned long int i = 2; i <= (a_cur + b_cur) / 2; ++i) {
            while ((a_cur % i == 0) && (b_cur % i == 0)) {
                a_cur = a_cur / i;
                b_cur = b_cur / i;
            }
        }
        a = a_cur;
        b = b_cur;
    }
}

fraction::~fraction()
{}

void fraction::print() const
{
    cout << a << '/' << b << endl;
}

fraction fraction::operator*(const fraction& r) {
    fraction ans(a*r.a, b*r.b);
    return ans;
}

fraction fraction::operator/(const fraction& r) {
    fraction ans(a*r.b, b*r.a);
    return ans;
}

fraction fraction::operator+(const fraction& r) {
    fraction ans(a*r.b + b*r.a, b*r.b);
    return ans;
}

fraction fraction::operator-(const fraction& r) {
    if (a*r.b < b*r.a) {
        cerr << "Error sub < 0" << endl;
        exit(1);
    }
    fraction ans(a*r.b - b*r.a, b*r.b);
    return ans;
}

fraction fraction::operator*(unsigned long int r) {
    fraction ans(a*r, b);
    return ans;
}

fraction fraction::operator/(unsigned long int r) {
    fraction ans(a, b*r);
    return ans;
}

double fraction::return_double() const {
    return (double)(a) / (double)(b);
}

std::ostream& operator<<(std::ostream &out, const fraction& r) {
    out << r.a << '/' << r.b;
    return out;
}

std::istream& operator>>(std::istream &inp, fraction& r) {
    char syms[30];
    inp >> syms;
    int i = 0, toback = 0, full = 0;
    while ((syms[i] != '\0') && (syms[i] != '\n')) {
        if (syms[i] == '/') {
            toback = i;
        }
        i++;
    }
    full = i;
    r.a = 0;
    for (i = 0; i < toback; ++i) {
        r.a += (syms[toback - 1 - i] - '0') * pow(10, i);
    }
    r.b=0;
    for (i = full-1; i > toback; --i) {
        r.b += (syms[i]-'0') * pow(10, full-1-i);
    }
    if (r.b==0) {
        cerr << "Error division by zero" << endl;
        exit(1);
    }
    if (r.a == 0) {
        r.b = 1;
        r.a = 0;
    }
    else {
        for (unsigned long int i = 2; i <= (r.a+r.b)/2; ++i) {
            while ((r.a % i == 0) && (r.b % i == 0)) {
                r.a = r.a / i;
                r.b = r.b / i;
            }
        }
    }
    return inp;
}

fraction operator*(unsigned long int l, const fraction& r) {
    fraction ans(r.a*l, r.b);
    return ans;
}
