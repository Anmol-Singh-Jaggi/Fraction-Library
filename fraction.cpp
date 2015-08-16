#include<iostream>
#include<stdexcept>
using namespace std;

// FRACTION BEGINS

// Returns the GCD of numerator and denominator
template<typename T>
T GCD( const T& numerator, const T& denominator )
{
	if ( numerator % denominator == 0 )
	{
		return denominator;
	}
	return GCD( denominator, numerator % denominator );
}

// Class Forward Declaration
template<typename T> class Fraction;

// Routines without any attempt to prevent overflow
template<typename T> Fraction<T> operator +( const Fraction<T>& first, const Fraction<T>& second );
template<typename T> Fraction<T> operator -( const Fraction<T>& first, const Fraction<T>& second );
template<typename T> Fraction<T> operator *( const Fraction<T>& first, const Fraction<T>& second );
template<typename T> Fraction<T> operator /( const Fraction<T>& first, const Fraction<T>& second );

// Routines with an attempt to prevent overflow
// Assuming "first" and "second" are already in their Reduced form
template<typename T> Fraction<T> Add( Fraction<T> first, Fraction<T> second );
template<typename T> Fraction<T> Subtract( Fraction<T> first, Fraction<T> second );
template<typename T> Fraction<T> Multiply( Fraction<T> first, Fraction<T> second );
template<typename T> Fraction<T> Divide( Fraction<T> first, Fraction<T> second );

// Routines of a Fraction with an integer
template<typename T> Fraction<T> operator +( const Fraction<T>& first, const T& second );
template<typename T> Fraction<T> operator -( const Fraction<T>& first, const T& second );
template<typename T> Fraction<T> operator *( const Fraction<T>& first, const T& second );
template<typename T> Fraction<T> operator /( const Fraction<T>& first, const T& second );

// I/O operators for Fraction class
template<typename T> ostream& operator <<( ostream& out, const Fraction<T>& a );
template<typename T> istream& operator >>( istream& in, Fraction<T>& a );

// Class Definition begins
template<typename T>
class Fraction
{
	// Private Data Members
	T numerator, denominator;

public:

	// Constructor
	Fraction<T>( const T& numerator = 1, const T& denominator = 1 );

	// Reduce the Fraction to the lowest terms
	Fraction<T>& Reduce();

	// Returns the numerical value of the Fraction as a double
	double value() const;

	// Getters
	T GetNumerator() const;
	T GetDenominator() const;

	// Friend Functions necessary for successful compilation
	friend Fraction operator + <>( const Fraction& first, const Fraction& second );
	friend Fraction operator - <>( const Fraction& first, const Fraction& second );
	friend Fraction operator * <>( const Fraction& first, const Fraction& second );
	friend Fraction operator / <>( const Fraction& first, const Fraction& second );

	friend Fraction operator + <>( const Fraction& first, const T& second );
	friend Fraction operator - <>( const Fraction& first, const T& second );
	friend Fraction operator * <>( const Fraction& first, const T& second );
	friend Fraction operator / <>( const Fraction& first, const T& second );

	friend Fraction Add   <>( Fraction first, Fraction second );
	friend Fraction Subtract   <>( Fraction first, Fraction second );
	friend Fraction Multiply   <>( Fraction first, Fraction second );
	friend Fraction Divide   <>( Fraction first, Fraction second );

	friend ostream& operator << <>( ostream& out, const Fraction& fraction );
	friend istream& operator >> <>( istream& in, Fraction& fraction );
};
// Class Definition ends

// Member Function Definitions
template<typename T>
Fraction<T>::Fraction( const T& _numerator, const T& _denominator )
{
	this->numerator = _numerator;
	this->denominator = _denominator;
}

// Reduce the Fraction to the lowest terms
template<typename T>
Fraction<T>& Fraction<T>::Reduce()
{
	if ( denominator == 0 )
	{
		throw domain_error( "" );
	}

	T gcd = GCD( numerator, denominator );
	numerator /= gcd;
	denominator /= gcd;

	return *this;
}

template<typename T>
T Fraction<T>::GetNumerator() const
{
	return numerator;
}

template<typename T>
T Fraction<T>::GetDenominator() const
{
	return denominator;
}

template<typename T>
double Fraction<T>::value() const
{
	if ( denominator == 0 )
	{
		throw domain_error( "" );
	}
	return numerator / ( double )denominator;
}

// Binary Arithmetic Function Definitions
template<typename T>
Fraction<T> operator +( const Fraction<T>& first, const Fraction<T>& second )
{
	Fraction<T> fraction;

	fraction.numerator = first.numerator * second.denominator + second.numerator * first.numerator;
	fraction.denominator = first.denominator * second.denominator;

	return fraction;
}

template<typename T>
Fraction<T> operator -( const Fraction<T>& first, const Fraction<T>& second )
{
	Fraction<T> fraction;

	fraction.numerator = first.numerator * second.denominator - second.numerator * first.numerator;
	fraction.denominator = first.denominator * second.denominator;

	return fraction;
}

template<typename T>
Fraction<T> operator *( const Fraction<T>& first, const Fraction<T>& second )
{
	Fraction<T> fraction;

	fraction.numerator = first.numerator * second.numerator;
	fraction.denominator = first.denominator * second.denominator;

	return fraction;
}

template<typename T>
Fraction<T> operator /( const Fraction<T>& first, const Fraction<T>& second )
{
	Fraction<T> fraction;

	fraction.numerator = first.numerator * second.denominator;
	fraction.denominator = first.denominator * second.numerator;

	return fraction;
}


template<typename T>
Fraction<T> Add( Fraction<T> first, Fraction<T> second )
{
	Fraction<T> fraction;

	T lcm = ( first.denominator * second.denominator ) / GCD( first.denominator, second.denominator );
	fraction.denominator = lcm;
	first.numerator *= lcm / first.denominator;
	second.numerator *= lcm / second.denominator;
	fraction.numerator = first.numerator + second.numerator;

	return fraction;
}

template<typename T>
Fraction<T> Subtract( Fraction<T> first, Fraction<T> second )
{
	Fraction<T> fraction;

	T lcm = ( first.denominator * second.denominator ) / GCD( first.denominator, second.denominator );
	fraction.denominator = lcm;
	first.numerator *= lcm / first.denominator;
	second.numerator *= lcm / second.denominator;
	fraction.numerator = first.numerator - second.numerator;

	return fraction;
}

template<typename T>
Fraction<T> Multiply( Fraction<T> first, Fraction<T> second )
{
	Fraction<T> fraction;

	T gcd = GCD( second.numerator, first.denominator );
	second.numerator /= gcd;
	first.denominator /= gcd;
	gcd = GCD( first.numerator, second.denominator );
	first.numerator /= gcd;
	second.denominator /= gcd;
	fraction.numerator = first.numerator * second.numerator;
	fraction.denominator = first.denominator * second.denominator;

	return fraction;
}

template<typename T>
Fraction<T> Divide( Fraction<T> first, Fraction<T> second )
{
	std::swap( second.numerator, second.denominator );

	Fraction<T> fraction;

	T gcd = GCD( second.numerator, first.denominator );
	second.numerator /= gcd;
	first.denominator /= gcd;
	gcd = GCD( first.numerator, second.denominator );
	first.numerator /= gcd;
	second.denominator /= gcd;
	fraction.numerator = first.numerator * second.numerator;
	fraction.denominator = first.denominator * second.denominator;

	return fraction;
}


template<typename T>
Fraction<T> operator +( const Fraction<T>& first, const T& second )
{
	return first + Fraction<T>( second, 1 );
}

template<typename T>
Fraction<T> operator -( const Fraction<T>& first, const T& second )
{
	return first - Fraction<T>( second, 1 );
}

template<typename T>
Fraction<T> operator *( const Fraction<T>& first, const T& second )
{
	return Fraction<T>( first.GetNumerator() * second, first.GetDenominator() );
}

template<typename T>
Fraction<T> operator /( const Fraction<T>& first, const T& second )
{
	return Fraction<T>( first.GetNumerator(), first.GetDenominator() * second );
}


//  I/O Operator Definitions
template<typename T>
ostream& operator <<( ostream& out, const Fraction<T>& fraction )
{
	out << fraction.numerator << "/" << fraction.denominator;
	return out;
}

template<typename T>
istream& operator >>( istream& in, Fraction<T>& fraction )
{
	in >> fraction.numerator >> fraction.denominator;
	return in;
}

// FRACTION ENDS


// Usage
int main()
{
	Fraction<int> fraction1( 6, 5 );
	Fraction<int> fraction2( 5, 2 );

	Fraction<int> fraction3 = fraction1 * fraction2;
	cout << fraction3 << endl;

	fraction3.Reduce();
	cout << fraction3 << endl;
}
