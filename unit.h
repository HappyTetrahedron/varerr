#ifndef UNIT_HDR 
#define UNIT_HDR


class Unit {
    public:
        Unit();
        Unit(int);
        Unit(double, const double *);
        Unit(const Unit&);

        const class Varerr operator<<(const Unit&) const;
        const class Varerr operator<<(double) const;

        const Unit operator-(void) const;

        const Unit operator+(const Unit&) const;
        const Unit operator+(double) const;

        friend const Unit operator+(double, const Unit&);

        const Unit operator-(const Unit&) const;
        const Unit operator-(double) const;

        friend const Unit operator-(double, const Unit&);

        const Unit operator*(const Unit&) const;
        const Unit operator*(double) const;

        friend const Unit operator*(double, const Unit&);

        const Unit operator/(const Unit&) const;
        const Unit operator/(double) const;

        friend const Unit operator/(double, const Unit&);

        const Unit operator^(const Unit&) const;
        const Unit operator^(double) const;

        friend const Unit operator^(double, const Unit&);

        double getValue(void) const;

        double getValueInUnit(const Unit& u) const;

        const double *getUnit(void) const;
        double getUnit(int) const;

        bool operator==(const Unit&) const;

        bool hasSameUnitAs(const Unit&) const;
        bool hasUnit(void) const;

        const Unit getBaseUnit(void) const;

        std::string toString(void) const;

    protected:
        const double fac;
        const double exp[6];
};

namespace bu {
    const Unit kg = Unit(0);
    const Unit g = kg/1000;

    const Unit m = Unit(1);
    const Unit cm = m/100.0;
    const Unit km = 1000.0 * m;
    const Unit mm = cm/10.0;
    const Unit mym = mm/1000;
    const Unit nm = mym/1000;

    const Unit s = Unit(2);
    const Unit min = 60.0 * s;
    const Unit h = 60.0 * min;
    const Unit d = 24 * h;

    const Unit K = Unit(3);

    const Unit A = Unit(4);

    const Unit mol = Unit(5);

    const Unit C = A * s;
    const Unit N = kg * m/(s^2);
    const Unit J = N * m;
    const Unit W = J/s;
    const Unit V = W/A;
    const Unit Pa = N/(m^2);


    const Unit bar = 100000 * Pa;
    const Unit mbar = bar/1000;
    const Unit e = 1.602177E-19 * C;
    const Unit eV = e * V;
    const Unit mmHg = 0.0075 * Pa;

    const Unit NU = Unit();
}


#endif
