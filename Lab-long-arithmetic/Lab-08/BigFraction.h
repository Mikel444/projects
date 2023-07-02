#ifndef BIG_FRACTION_H_INCLUDED
#define BIG_FRACTION_H_INCLUDED
#include <cstddef>
#include "fraction.h"
#include "bigint.h"

class BigFraction : public fraction {
    bigint a;
    bigint b;
  public:
    BigFraction();
    BigFraction(const bigint& a_in,const bigint& b_in);
    BigFraction(const fraction& f);
    BigFraction(const BigFraction& f);
    ~BigFraction();
    void operator= (const BigFraction& right);
    void print();

    friend BigFraction operator* (const BigFraction& left, const BigFraction& right);
    friend BigFraction operator/ (const BigFraction& left, const BigFraction& right);
    friend BigFraction operator+ (const BigFraction& left, const BigFraction& right);
    friend BigFraction operator- (const BigFraction& left, const BigFraction& right);
    friend BigFraction operator* (const BigFraction& left, unsigned long int right);
    friend BigFraction operator/ (const BigFraction& left, unsigned long int right);
};

#endif // BIG_FRACTION_H_INCLUDED
