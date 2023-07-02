#ifndef fraction_h
#define fraction_h 20221203L
#include <cstddef>
#include <iostream>

class fraction {
    unsigned long int a;
    unsigned long int b;
    public:
        fraction();
        fraction(const fraction&);
        fraction(unsigned long int a, unsigned long int b);
        ~fraction();
        void print() const;
        fraction operator*(const fraction& r);
        fraction operator/ (const fraction&);
        fraction operator+ (const fraction&);
        fraction operator- (const fraction&);
        fraction operator* (unsigned long int r);
        fraction operator/ (unsigned long int r);
        double return_double() const;
        friend fraction operator*(unsigned long int, const fraction&);
        friend std::ostream& operator<<(std::ostream& o, const fraction& r);
        friend std::istream& operator>>(std::istream& i, fraction& r);
};

#endif /*fraction_h*/
