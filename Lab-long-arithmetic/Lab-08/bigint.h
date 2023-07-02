#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED
#include <cstddef>
#include <iostream>

class bigint {
    char   *data;
    size_t  size;
    bool    neg;

  public:
    bigint();
    bigint(const bigint&);
    ~bigint();
    void operator = (const bigint& right);
    explicit bigint(long);
    explicit bigint(unsigned long);
    explicit bigint(const char*);

    void print() const;

    bool is_null();

    static bigint add(const bigint& left, const bigint& right);
    static bigint sub(const bigint& left, const bigint& right);
    static bigint mul(const bigint& left, const bigint& right);
    static bigint div(const bigint& left, const bigint& right);
    static bigint div(const bigint& left, const bigint& right, bigint& rest);
    // Lab-06
    static bigint gcd(const bigint& a, const bigint& b);
    static unsigned long Eratosthenes(bigint *sieve, unsigned long size);
    static bigint sqrt(const bigint& value);

    friend bigint operator*(const bigint& left, const bigint& right);
    friend bigint operator/ (const bigint& left, const bigint& right);
    friend bigint operator+ (const bigint& left, const bigint& right);
    friend bigint operator- (const bigint& left, const bigint& right);
    friend bigint operator% (const bigint& left, const bigint& right);

    friend bigint operator*(const bigint& left, unsigned long right);
    friend bigint operator+ (const bigint& left, unsigned long right);
    friend bigint operator/ (const bigint& left, unsigned long right);
    friend bigint operator% (const bigint& left, unsigned long right);


    friend bool operator> (const bigint& left, const bigint& right);
    friend bool operator< (const bigint& left, const bigint& right);
    friend bool operator== (const bigint& left, const bigint& right);
    friend bool operator!= (const bigint& left, const bigint& right);


    friend bool operator== (const bigint& left, unsigned long right);
    friend bool operator> (const bigint& left, unsigned long right);
    friend bool operator< (const bigint& left, unsigned long right);
    friend bool operator<= ( unsigned long left, const bigint& right);

    friend std::ostream& operator<<(std::ostream& o, const bigint& r);

};

#endif // BIGINT_H_INCLUDED
