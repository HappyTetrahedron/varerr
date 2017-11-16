#include <cmath>
#include <iostream>
#include <string>

#include "unit.h"
#include "varerr.h"

// util

double sqrts(double d1, double d2) {
    return std::sqrt(d1*d1 + d2*d2);
}

//


Varerr::Varerr(): Unit(), e(0) {}

Varerr::Varerr(const Unit &u): Varerr(u, 0) {}

Varerr::Varerr(const Unit& v, double e): 
    Unit(v.getValue(), v.getUnit()), 
    e(std::abs(e)) {}

Varerr::Varerr(const Unit& v, const Unit& e): 
    Unit(v.getValue(), v.getUnit()), 
    e(e.getValue()/v.getValue())
{
    if(!v.hasSameUnitAs(e))
        throw 1;
}

Varerr::Varerr(const Varerr& ve): 
    Unit(ve.getValue(), ve.getUnit()), 
    e(ve.getError()) {}

double Varerr::getError() const {
    return this->e;
}

double Varerr::getErrorAbs() const {
    return this->getValue()*this->e;
}

// *

const Varerr Varerr::operator*(const Varerr& ve) const {
    return Varerr(Unit::operator*(ve), this->e + ve.getError());
}
const Varerr Varerr::operator*(const Unit& u) const {
    return Varerr(Unit::operator*(u), this->e);
}
const Varerr Varerr::operator*(double d) const {
    return Varerr(Unit::operator*(d), this->e);
}
const Varerr operator*(const Unit& u, const Varerr& ve) {
    return ve * u;
}
const Varerr operator*(double d, const Varerr& ve) {
    return ve * d;
}

// /

const Varerr Varerr::operator/(const Varerr& ve) const {
    return Varerr(Unit::operator/(ve), this->e + ve.getError());
}
const Varerr Varerr::operator/(const Unit& u) const {
    return Varerr(Unit::operator/(u), this->e);
}
const Varerr Varerr::operator/(double d) const {
    return Varerr(Unit::operator/(d), this->e);
}
const Varerr operator/(const Unit& u, const Varerr& ve) {
    return Varerr(u/static_cast<const Unit&>(ve), ve.getError());
}
const Varerr operator/(double d, const Varerr& ve) {
    return Varerr(operator/(d, static_cast<const Unit&>(ve)), ve.getError());
}

// +

const Varerr Varerr::operator+(const Varerr& ve) const {
    double s = ve.getValue() + this->fac;
    return Varerr(Unit::operator+(ve), ( s == 0 ? 0.0 :
        sqrts(this->getErrorAbs()/s, ve.getErrorAbs()/s)));
}
const Varerr Varerr::operator+(const Unit& u) const {
    double s = u.getValue() + this->fac;
    return Varerr(Unit::operator+(u), ( s == 0 ? 0.0 : 
        this->getErrorAbs()/s));
}
const Varerr Varerr::operator+(double d) const {
    double s = d + this->fac;
    return Varerr(Unit::operator+(d), (s == 0 ? 0.0 : 
        this->getErrorAbs()/s));
}
const Varerr operator+(const Unit& u, const Varerr& ve) {
    return ve + u;
}
const Varerr operator+(double d, const Varerr& ve) {
    return ve + d;
}

// -

const Varerr Varerr::operator-(const Varerr& ve) const {
    double s = ve.getValue() - this->fac;
    return Varerr(Unit::operator-(ve), 
        sqrts(this->getErrorAbs()/s, ve.getErrorAbs()/s));
}
const Varerr Varerr::operator-(const Unit& u) const {
    double s = u.getValue() - this->fac;
    return Varerr(Unit::operator-(u), this->getErrorAbs()/s);
}
const Varerr Varerr::operator-(double d) const {
    double s = d - this->fac;
    return Varerr(Unit::operator-(d), this->getErrorAbs()/s);
}
const Varerr operator-(const Unit& u, const Varerr& ve) {
    return -1*(ve - u);
}
const Varerr operator-(double d, const Varerr& ve) {
    return -1*(ve - d);
}

// ^

const Varerr Varerr::operator^(const Varerr& ve) const {
    double d1 = ve.getValue() * (std::pow(this->fac, ve.getValue() - 1)) 
        * this->getErrorAbs();
    double d2 = std::log(this->fac) * std::pow(this->fac, ve.getValue()) 
        * ve.getErrorAbs();
    return Varerr(Unit::operator^(ve), 
        sqrts(d1, d2)/std::pow(this->fac, ve.getValue()));
}
const Varerr Varerr::operator^(const Unit& u) const {
    double d1 = u.getValue() * (std::pow(this->fac, u.getValue() - 1)) 
        * this->getErrorAbs();
    return Varerr(Unit::operator^(u), d1);
}
const Varerr Varerr::operator^(double d) const {
    double d1 = d * (std::pow(this->fac, d - 1)) 
        * this->getErrorAbs();
    return Varerr(Unit::operator^(d), d1);
}
const Varerr operator^(const Unit& u, const Varerr& ve) {
    return Varerr(u, 0) ^ ve;
}
const Varerr operator^(double d, const Varerr& ve) {
    double d1 = std::log(ve.getValue()) * std::pow(ve.getValue(), d) 
        * ve.getErrorAbs();
    return Varerr(operator^(d, static_cast<Unit>(ve)), d1);
}

// misc

std::string Varerr::toString(void) const {
    std::string s("");
    s = s + Unit::toString();
    s = s + " +-"; 
    s = s + std::to_string(this->getError() * 100);
    s = s + "%";
    return s;
}

void Varerr::operator=(const Varerr& ve) {
    Unit::operator=(ve);
    this->e = ve.e;
}
void Varerr::operator=(const Unit& u) {
    Unit::operator=(u);
    this->e = 0;
}
void Varerr::operator=(double d) {
    Unit::operator=(d);
    this->e = 0;
}


