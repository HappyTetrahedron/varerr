
#ifndef VARERR_HDR
#define VARERR_HDR

class Varerr: public Unit {
    public:
        Varerr();
        Varerr(const Unit&, double);
        Varerr(const Unit&, const Unit&);
        Varerr(const Varerr&);

        double getError(void) const;
        double getErrorAbs(void) const;
        
        const Varerr operator*(const Varerr&) const;
        const Varerr operator/(const Varerr&) const;

        const Varerr operator+(const Varerr&) const;
        const Varerr operator+(const Unit&) const;
        const Varerr operator+(double) const;

        friend const Varerr operator+(const Unit&, const Varerr&);
        friend const Varerr operator+(double, const Varerr&);

        const Varerr operator-(const Varerr&) const;
        const Varerr operator-(const Unit&) const;
        const Varerr operator-(double) const;

        friend const Varerr operator-(const Unit&, const Varerr&);
        friend const Varerr operator-(double, const Varerr&);

        const Varerr operator^(const Varerr&) const;
        const Varerr operator^(const Unit&) const;
        const Varerr operator^(double) const;

        friend const Varerr operator^(const Unit&, const Varerr&);
        friend const Varerr operator^(double, const Varerr&);

        std::string toString(void) const;

        void operator=(const Varerr&) const;

    private:
        const double e;
};

#endif
