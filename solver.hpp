#include <iostream>
#include <complex>
using namespace std;


namespace solver
{
    class RealVariable
    {
        public:

        double _a;
        double _b;
        double _c;
        
        RealVariable()
        {
            _a=0;
            _b=1;
            _c=0;
        }

        RealVariable(const double& a, const double& b, const double& c)
        {
            this->_a=a;
            this->_b=b;
            this->_c=c;
        }

        double get_a() const
        {
            return _a;
        }

        double get_b() const
        {
            return _b;
        }

        double get_c() const
        {
            return _c;
        }

        friend RealVariable operator*(const double, const RealVariable&);
        friend RealVariable operator*(const RealVariable&, const double);
        friend RealVariable operator*(const RealVariable&, const RealVariable&);

        friend RealVariable operator-(const RealVariable&, const double);
        friend RealVariable operator-(const double, const RealVariable&);
        friend RealVariable operator-(const RealVariable&, const RealVariable&);

        friend RealVariable operator+(const RealVariable&, const double);
        friend RealVariable operator+(const double, const RealVariable&);
        friend RealVariable operator+(const RealVariable&, const RealVariable&);

        friend RealVariable operator^(const RealVariable&, const double);

        friend RealVariable operator==(const RealVariable&, const double);
        friend RealVariable operator==(const double, const RealVariable&);
        friend RealVariable operator==(const RealVariable&, const RealVariable&);

        friend RealVariable operator/(const RealVariable&, const double);
        friend RealVariable operator/(const RealVariable&, const RealVariable&);

    };

    class ComplexVariable
    {
        public:

        complex<double> _a;
        complex<double> _b;
        complex<double> _c;

        ComplexVariable()
        {
            _a=0;
            _b=complex(1,0);
            _c=0;
        }

        ComplexVariable(const complex<double> a, const complex<double> b, const complex<double> c)
        {
            this->_a=complex(a);
            this->_b=complex(b);
            this->_c=complex(c);
        }

        complex<double> get_a() const
        {
            return _a;
        }

        complex<double> get_b() const
        {
            return _b;
        }

        complex<double> get_c() const
        {
            return _c;
        }

        friend ComplexVariable operator*(const ComplexVariable&, const complex<double>);
        friend ComplexVariable operator*(const complex<double>, const ComplexVariable&);
        friend ComplexVariable operator*(const ComplexVariable&, const ComplexVariable&);

        friend ComplexVariable operator-(const complex<double>, const ComplexVariable&);
        friend ComplexVariable operator-(const ComplexVariable&, const ComplexVariable&);
        friend ComplexVariable operator-(const ComplexVariable&, const complex<double>);

        friend ComplexVariable operator+(const ComplexVariable&, const ComplexVariable&);
        friend ComplexVariable operator+(const ComplexVariable&, const complex<double>);
        friend ComplexVariable operator+(const complex<double>, const ComplexVariable&);

        friend ComplexVariable operator^(const ComplexVariable&, const complex<double>);

        friend ComplexVariable operator==(const ComplexVariable&, const ComplexVariable&);
        friend ComplexVariable operator==(const ComplexVariable&, const complex<double>);
        friend ComplexVariable operator==(const complex<double>, const ComplexVariable&);

        friend ComplexVariable operator/(const ComplexVariable&, const complex<double>);
        friend ComplexVariable operator/(const ComplexVariable&, const ComplexVariable&);
    };

    double solve(const RealVariable&);
    complex<double> solve(const ComplexVariable&);

    string ComplexToString(const complex<double>);
    
};
