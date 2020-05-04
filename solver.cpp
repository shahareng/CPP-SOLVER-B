#include <iostream>
#include <complex>
#include "solver.hpp"

using namespace std;

namespace solver
{
    //// solve functions ////

    // I take the answer from: https://stackoverflow.com/questions/898076/solve-quadratic-equation-in-c

    double solve(const RealVariable& num)
    {
        double a = num.get_a();
        double b = num.get_b();
        double c = num.get_c();

        if(a == 0 && b == 0 && c == 0)
        {
            return 0;
        }        
        if(a == 0)
        {
            if(b != 0)
            {
                return (-c/b);
            }
            else if(c != 0)
            {
                throw runtime_error("There is no solution");
            }
        }
        double delta=b*b-4*a*c;
        if(delta>=0)
        {
            return (-b+sqrt(delta))/(2*a);
        }
        throw runtime_error("There is no solution");
    }

    complex<double> solve(const ComplexVariable& num)
    {
        complex<double> a = num.get_a();
        complex<double> b = num.get_b();
        complex<double> c = num.get_c();

        if(a == complex(0.0,0.0) && b == complex(0.0,0.0) && c == complex(0.0,0.0))
        {
            return 0;
        }        
        if(a == complex(0.0,0.0))
        {
            if(b != complex(0.0,0.0))
            {
                return (-c/b);
            }
            else if(c != complex(0.0,0.0))
            {
                throw runtime_error("There is no solution");
            }
        }
        complex<double> delta=b*b-complex(4.0,0.0)*a*c;
        return (-b+sqrt(delta))/(complex(2.0,0.0)*a);
    }

    string ComplexToString(const complex<double> solution)
    {
        return to_string(solution.real()) + "+" + to_string(solution.imag()) + "i";
    }

    //// RealVariable ////

    RealVariable operator*(const double num1, const RealVariable& num2)
    {
        return RealVariable(num2._a*num1, num2._b*num1, num2._c*num1);
    }

    RealVariable operator*(const RealVariable& num1, const double num2)
    {
        return num2*num1;
    }

    RealVariable operator*(const RealVariable& num1, const RealVariable& num2)
    {
        if(num1._a != 0 && num2._a != 0)
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num1._a != 0 && num2._b != 0)
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num1._b != 0 && num2._a != 0)
        {
            throw runtime_error("The power is greater than 2");
        }

        return RealVariable((num1._a*num2._c)+(num1._b*num2._b)+(num1._c*num1._a), (num1._b*num2._c)+(num1._c*num2._b), num1._c*num2._c);
    }
    
    RealVariable operator-(const RealVariable& num1, const double num2)
    {
        return RealVariable(num1._a, num1._b, num1._c-num2);
    }

    RealVariable operator-(const double num1, const RealVariable& num2)
    {
        return RealVariable(-num2._a, -num2._b, -num2._c+num1);
    }

    RealVariable operator-(const RealVariable& num1, const RealVariable& num2)
    {
        return RealVariable(num1._a-num2._a, num1._b-num2._b, num1._c-num2._c);
    }

    RealVariable operator+(const RealVariable& num1, const double num2)
    {
        return RealVariable(num1._a, num1._b, num1._c+num2);
    }

    RealVariable operator+(const double num1, const RealVariable& num2)
    {
        return num2+num1;
    }

    RealVariable operator+(const RealVariable& num1, const RealVariable& num2)
    {
        return RealVariable(num1._a+num2._a, num1._b+num2._b, num1._c+num2._c);
    }

    RealVariable operator^(const RealVariable& num1, const double num2)
    {
        if(num2 == 1)
        {
            return num1;
        }
        if(num2 == 0)
        {
            return RealVariable(0, 0, 1);
        }
        if(num1._a != 0)
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num2 < 0)
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num2 > 2)
        {
            if(num1._b != 0)
            {
                throw runtime_error("The power is greater than 2");
            }
            else
            {
                return RealVariable(0, 0, pow(num1._c, num2));
            }
        }
        return num1*num1;
    }

    RealVariable operator==(const RealVariable& num1, const double num2)
    {
        return num1-num2;
    }

    RealVariable operator==(const double num1, const RealVariable& num2)
    {
        return num2-num1;
    }

    RealVariable operator==(const RealVariable& num1, const RealVariable& num2)
    {
        return num1-num2;
    }

    RealVariable operator/(const RealVariable& num1, const double num2)
    {
        if(num2 == 0)
        {
            throw runtime_error("You can't divide by 0!");
        }
        return RealVariable(num1._a/num2, num1._b/num2, num1._c/num2);
    }

    RealVariable operator/(const RealVariable& num1, const RealVariable& num2)
    {
        if(num2._a == 0 && num2._b == 0 && num2._c == 0)
        {
            throw runtime_error("You can't divide by 0!");
        }
        if((num1._a == 0 && num2._a != 0) || (num1._a == 0 && num1._b == 0 && num2._b != 0))
        {
            throw runtime_error("The power is less than 0");
        }
        RealVariable result = num1-num2;
        if(result._a == 0 && result._b == 0 && result._c == 0)
        {
            return RealVariable(0, 0, 1);
        }
        if(num1._a != 0 && num1._b == 0 && num1._c == 0 && num2._a != 0 && num2._b == 0 && num2._c == 0)
        { // num1 = a*(x^2), num2 = b*(x^2)
            return RealVariable(0,0,num1._a/num2._a);
        }
        if(num1._a != 0 && num1._b == 0 && num1._c == 0 && num2._a == 0 && num2._b != 0 && num2._c == 0)
        { // num1 = a*(x^2), num2 = b*x
            return RealVariable(0,num1._a/num2._b, 0);
        }
        if(num1._a == 0 && num1._b != 0 && num1._c == 0 && num2._a == 0 && num2._b != 0 && num2._c == 0)
        { // num1 = a*x, num2 = b*x
            return RealVariable(0,0,num1._b/num2._b);
        }
        if(num1._a != 0 && num1._b != 0 && num1._c == 0 && num2._a == 0 && num2._b != 0 && num2._c == 0)
        { // num1 = a*(x^2)+b*x, num2 = c*x
            return RealVariable(0, num1._a/num2._c, num1._b/num2._c);
        }
        if(num2._a == 0 && num2._b == 0)
        { // num2 = c;
            return num1/num2._c;
        }
        throw runtime_error("It's too hard");
    }

    //// ComplexVariable ////

    ComplexVariable operator*(const complex<double> num1, const ComplexVariable& num2)
    {
        return ComplexVariable(num2._a*num1, num2._b*num1, num2._c*num1);
    }

    ComplexVariable operator*(const ComplexVariable& num1, const complex<double> num2)
    {
        return num2*num1;
    }

    ComplexVariable operator*(const ComplexVariable& num1, const ComplexVariable& num2)
    {
        if(num1._a != complex(0.0,0.0) && num2._a != complex(0.0,0.0))
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num1._a != complex(0.0,0.0) && num2._b != complex(0.0,0.0))
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num1._b != complex(0.0,0.0) && num2._a != complex(0.0,0.0))
        {
            throw runtime_error("The power is greater than 2");
        }
        return ComplexVariable((num1._a*num2._c)+(num1._b*num2._b)+(num1._c*num1._a), (num1._b*num2._c)+(num1._c*num2._b), num1._c*num2._c);
    }

    ComplexVariable operator-(const ComplexVariable& num1, const ComplexVariable& num2)
    {
        return ComplexVariable(num1._a-num2._a, num1._b-num2._b, num1._c-num2._c);
    }

    ComplexVariable operator-(const ComplexVariable& num1, const complex<double> num2)
    {
        return ComplexVariable(num1._a, num1._b, num1._c-num2);
    }

    ComplexVariable operator-(const complex<double> num1, const ComplexVariable& num2)
    {
        return ComplexVariable(-num2._a, -num2._b, -num2._c+num1);
    }

    ComplexVariable operator+(const ComplexVariable& num1, const ComplexVariable& num2)
    {
        return ComplexVariable(num1._a+num2._a, num1._b+num2._b, num1._c+num2._c);
    }

    ComplexVariable operator+(const ComplexVariable& num1, const complex<double> num2)
    {
        return ComplexVariable(num1._a, num1._b, num1._c+num2);
    }

    ComplexVariable operator+(const complex<double> num1, const ComplexVariable& num2)
    {
        return num2+num1;
    }

    ComplexVariable operator^(const ComplexVariable& num1, const complex<double> num2)
    {
        if(num2.imag() != 0)
        {
            throw runtime_error("Invalid");
        }
        if(num2.real() == 0)
        {
            return ComplexVariable(0, 0, 1);
        }
        if(num2.real() == 1)
        {
            return num1;
        }
        if(num1._a != complex(0.0,0.0))
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num2.real() < 0)
        {
            throw runtime_error("The power is greater than 2");
        }
        if(num2.real() > 2)
        {
            if(num1._b != complex(0.0,0.0))
            {
                throw runtime_error("The power is greater than 2");
            }
            else
            {
                complex<double> po = pow(num1._c, num2);
                return ComplexVariable(0, 0, po);
            }
        }
        return num1*num1;
    }

    ComplexVariable operator==(const ComplexVariable& num1, const ComplexVariable& num2)
    {
        return num1-num2;
    }

    ComplexVariable operator==(const complex<double> num1, const ComplexVariable& num2)
    {
        return num2-num1;
    }

    ComplexVariable operator==(const ComplexVariable& num1, const complex<double> num2)
    {
        return num1-num2;
    }

    ComplexVariable operator/(const ComplexVariable& num1, const complex<double> num2)
    {
        if(num2.real() == 0 && num2.imag() == 0)
        {
            throw runtime_error("You can't divide by 0!");
        }
        return ComplexVariable(num1._a/num2, num1._b/num2, num1._c/num2);
    }

    ComplexVariable operator/(const ComplexVariable& num1, const ComplexVariable& num2)
    {
        if(num2._a == complex(0.0,0.0) && num2._b == complex(0.0,0.0) && num2._c == complex(0.0,0.0))
        {
            throw runtime_error("You can't divide by 0!");
        }
        if((num1._a == complex(0.0,0.0) && num2._a != complex(0.0,0.0)) || (num1._a == complex(0.0,0.0) && num1._b == complex(0.0,0.0) && num2._b != complex(0.0,0.0)))
        {
            throw runtime_error("The power is less than 0");
        }
        ComplexVariable result = num1-num2;
        if(result._a == complex(0.0,0.0) && result._b == complex(0.0,0.0) && result._c == complex(0.0,0.0))
        {
            return ComplexVariable(0, 0, 1);
        }
        if(num1._a != complex(0.0,0.0) && num1._b == complex(0.0,0.0) && num1._c == complex(0.0,0.0) && num2._a != complex(0.0,0.0) && num2._b == complex(0.0,0.0) && num2._c == complex(0.0,0.0))
        { // num1 = a*(x^2), num2 = b*(x^2)
            return ComplexVariable(0,0,num1._a/num2._a);
        }
        if(num1._a != complex(0.0,0.0) && num1._b == complex(0.0,0.0) && num1._c == complex(0.0,0.0) && num2._a == complex(0.0,0.0) && num2._b != complex(0.0,0.0) && num2._c == complex(0.0,0.0))
        { // num1 = a*(x^2), num2 = b*x
            return ComplexVariable(0,num1._a/num2._b, 0);
        }
        if(num1._a == complex(0.0,0.0) && num1._b != complex(0.0,0.0) && num1._c == complex(0.0,0.0) && num2._a == complex(0.0,0.0) && num2._b != complex(0.0,0.0) && num2._c == complex(0.0,0.0))
        { // num1 = a*x, num2 = b*x
            return ComplexVariable(0,0,num1._b/num2._b);
        }
        if(num1._a != complex(0.0,0.0) && num1._b != complex(0.0,0.0) && num1._c == complex(0.0,0.0) && num2._a == complex(0.0,0.0) && num2._b != complex(0.0,0.0) && num2._c == complex(0.0,0.0))
        { // num1 = a*(x^2)+b*x, num2 = c*x
            return ComplexVariable(0, num1._a/num2._c, num1._b/num2._c);
        }
        if(num2._a == complex(0.0,0.0) && num2._b == complex(0.0,0.0))
        { // num2 = c;
            return num1/num2._c;
        }
        throw runtime_error("It's too hard");
    }
};