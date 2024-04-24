#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

using std::vector;

// Define a polynomial structure with the derivative defined
template <typename Domain>
class Polynomial {
       public:
	// Initalizer
	explicit Polynomial(Domain temp_constant = 1, Domain temp_exponent = 1)
	    : constant{temp_constant}, exponent{temp_exponent} {};

	// Making this class a function (more like a monomial)
	constexpr Domain operator()(const Domain polynomial_input) const
	{
		return constant * std::pow(polynomial_input, exponent);
	}
	// Allowing you to take the derivitive of the monomial. Could later be
	// used more generally in a function class.
	constexpr void derivative()
	{
		auto tmp = exponent;
		--exponent;
		constant *= tmp;
	}

       private:
	Domain constant;
	Domain exponent;
};

// Takes the derivative of a long polynomial by taking the derivative of the
// polynomial structure. Maps poly -> poly, where poly is a functor.
template <typename Domain>
constexpr void derivative(vector<Polynomial<Domain>>& poly)
{
	std::for_each(
	    poly.begin(), poly.end(),
	    std::bind(&Polynomial<Domain>::derivative, std::placeholders::_1));
}

int main()
{
	// Creates a monomial 2x^3 and .5x^2
	Polynomial<double> mono_test_large(2, 3);
	Polynomial<double> mono_test_small(.5, 2);
	vector<Polynomial<double>> poly{mono_test_large, mono_test_small};

	derivative(poly);

	std::cout << poly[0](2) << " and " << poly[1](2) << '\n';

	return 0;
}
