#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>

#include "unit.h"
#include "varerr.h"

#define IN(n) [n] = (n == i)
#define IN2(n) IN(n), IN(n+1), IN(n+2) 
#define IN3(n) IN2(n), IN2(n+3)

Unit::Unit (): 
    fac(1), 
    exp{0, 0, 0, 0, 0, 0} {} 

Unit::Unit (int i): 
    fac(1), 
    exp{IN3(0)} {}

Unit::Unit (double fac, const double *exp): 
    fac(fac), 
    exp{exp[0], exp[1], exp[2], exp[3], exp[4], exp[5]} {}

Unit::Unit (const Unit& u):
    Unit(u.getValue(), u.getUnit()) {}

// util

const char *LOOKUP [] = {"kg", "m", "s", "K", "A", "mol"};

// -

const Unit Unit::operator-(void) const {
    return (*this) * (-1);
}

// +

const Unit Unit::operator+(const Unit& u) const {
    if (!this->hasSameUnitAs(u)) {
        std::cerr << "Not the same units in operator +";
        throw 1;
    }
    return Unit(this->fac + u.getValue(), exp);
}
const Unit Unit::operator+(double d) const {
    if (this->hasUnit()) {
        std::cerr << "Not the same units in operator +";
        throw 1;
    }
    return Unit(this->fac + d, exp);
}
const Unit operator+(double d, const Unit& u) {
    return u + d;
}

// -

const Unit Unit::operator-(const Unit& u) const {
    return (*this) + (-u);
}
const Unit Unit::operator-(double d) const {
    return (*this) + (-d);
}
const Unit operator-(double d, const Unit& u) {
    return u - d;
}

// *

const Unit Unit::operator*(const Unit& u) const{
    double exp[6];
    int j;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] + u.getUnit()[j];
    return Unit(this->fac * u.getValue(), exp);
}
const Unit Unit::operator*(double d) const{
    return Unit(this->fac * d, this->exp);
}
const Unit operator*(double d, const Unit& u) {
    return u * d;
}

// /
const Unit Unit::operator/(const Unit& u) const{
    double exp[6];
    int j;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] - u.getUnit(j);
    return Unit(this->fac / u.getValue(), exp);
}
const Unit Unit::operator/(double d) const{
    return Unit(this->fac / d, this->exp);
}
const Unit operator/(double d, const Unit& u) {
    return (d*bu::NU)/u;
}

// ^

const Unit Unit::operator^(double d) const{
    double exp[6];
    int j;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] * d;
    return Unit(std::pow(this->fac, d), exp);
}
const Unit Unit::operator^(const Unit& u) const{
    double exp[6];
    int j;
    if (u.hasUnit())
        throw 1;
    for (j = 0; j < 6; j++)
        exp[j] = this->exp[j] * u.getValue();
    return Unit(std::pow(this->fac, u.getValue()), exp);
}
const Unit operator^(double d, const Unit& u) {
    if (u.hasUnit()) 
        throw 1;
    return std::pow(d, u.getValue()) * bu::NU;
}

// misc

double Unit::getValue(void) const{
    return this->fac;
}

double Unit::getValueInUnit(const Unit& u) const{
    return this->fac/u.getValue();
}

const Varerr Unit::operator<<(const Unit& u) const {
    if (!this->hasSameUnitAs(u))
        throw 1;
    return Varerr(*this, (this->fac == 0.0 ? 0.0 : u.getValue()/this->fac));
}

const Varerr Unit::operator<<(double e) const {
    return Varerr(*this, e);
}


bool Unit::operator==(const Unit& u) const{
    return (this->fac == u.getValue()) && this->hasSameUnitAs(u);
}


const double *Unit::getUnit(void) const {
    return this->exp;
}

double Unit::getUnit(int i) const {
    return this->exp[i];
}

bool Unit::hasSameUnitAs(const Unit& u) const {
    bool res = true;
    int j;
    for (j=0; j < 6; j++)
        res &= (this->exp[j] == u.getUnit()[j]);
    return res;
}

const Unit Unit::getBaseUnit(void) const {
    return Unit(1, this->getUnit());
}


bool Unit::hasUnit(void) const {
    return !Unit::hasSameUnitAs(bu::NU);
} 

std::string Unit::toString(void) const {
    int j;
    char c[100];
    double d = this->getValue();
    std::string s("");
    size_t len = sprintf(c, "%.10e", d);
    c[len] = '\0';
    s += c;
    for (j = 0; j < 6; j++) {
        if (!this->getUnit(j) == 0) {
            s = s + LOOKUP[j] ;
            s = s + "^" ;
            d = this->getUnit(j);
            if (d == (int) d) 
                s = s + std::to_string((int) d);
            else
                s = s + std::to_string(d);
        }
    }
    return s;
}

void Unit::operator=(const Unit& u) {
    int i;
    this->fac = u.getValue();
    for(i=0; i<6; i++)
        this->exp[i] = u.getUnit(i);
}
void Unit::operator=(double d) {
    int i;
    this->fac = d;
    for(i=0; i<6; i++)
        this->exp[i] = 0;
}
