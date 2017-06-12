/*
BigInteger.h: Header file for BigInteger structure
By Anthony Enem
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include<stdio.h>

using namespace std;
#define endl '\n'


class BigInteger
{
	typedef long long int BaseType;
private:
	std::vector<BaseType> m_Mag;
	int m_sign;

	/*PRIVATE HELPER METHODS*/

	//Add BigIntegers
	void sum_Magnitudes(const BigInteger&, BigInteger&) const;

	//Multiply BigIntegers
	void multiply(const BigInteger&, BigInteger&) const;

	//Compare BigIntegers
	int compare(const BigInteger&) const;

	//Subtract BigIntegers
	void diff_Magnitudes(const BigInteger&, BigInteger&, int) const;

	int comp_Magnitudes(const BigInteger&) const;

public:
	static const int DIGITS_PER_INDEX = 9;
	static const BaseType MOD_VAL = 1000000000;

	//default constructor
	BigInteger();

	BigInteger(BaseType integer);

	BigInteger(const char*);

	//copy constructor
	BigInteger(const BigInteger&);

	//Destructor
	~BigInteger();

	bool isNegative() const;

	BigInteger Abs() const;

	bool isZero() const;

	/*OVERLOADED OPERATORS*/

	//Addition
	BigInteger operator+(const BigInteger&) const;
	BigInteger& operator+=(const BigInteger&);

	//Negate operator
	BigInteger operator-(void) const;

	//Subtraction
	BigInteger operator-(const BigInteger&) const;
	BigInteger& operator-=(const BigInteger&);

	//Multiplication
	BigInteger operator *(const BigInteger&) const;
	BigInteger& operator*=(const BigInteger&);

	//Greater than
	bool operator>(const BigInteger&) const;
	bool operator >=(const BigInteger&) const;

	//Less than
	bool operator<(const BigInteger&) const;
	bool operator<=(const BigInteger&) const;

	//Equals
	bool operator==(const BigInteger&) const;
	bool operator!=(const BigInteger&) const;

	//Assignment operator
	BigInteger& operator=(const BigInteger&);

	friend std::ostream& operator<<(std::ostream&, const BigInteger&);

	//Increment
	BigInteger& operator++(); //prefix
	BigInteger operator++(int); //postfix

								//Decrement
	BigInteger& operator--();
	BigInteger operator--(int);

};

//Default constructor
BigInteger::BigInteger()
{
	m_Mag.resize(1);
	m_sign = 1;
}

//Destructor
BigInteger::~BigInteger()
{
	m_Mag.clear();
}

//string parameterized constructor
BigInteger::BigInteger(const char* rhsDigits)
{
	if (!rhsDigits || strlen(rhsDigits) == 0) {
		*this = BaseType(+0);
		return;
	}

	const char* rhs = isdigit(rhsDigits[0]) ? rhsDigits : rhsDigits + 1;

	size_t len_rhs = strlen(rhs), copied_len = 0;
	char* digits = new char[DIGITS_PER_INDEX + 1];
	BaseType ll_val;

	//assign BigInteger sign
	if (len_rhs && len_rhs) {
		m_sign = rhs[0] == '-' ? -1 : 1;
	}

	//parse digits
	while (copied_len+DIGITS_PER_INDEX <= len_rhs) {
		//Copy next set of digits from end of rhs
		strncpy(digits, rhs + len_rhs - (DIGITS_PER_INDEX + copied_len), DIGITS_PER_INDEX);
		//convert to integer
		ll_val = std::stoll(digits);
		copied_len += DIGITS_PER_INDEX;
		//push to magnitude vector
		m_Mag.push_back(ll_val);
	}
	if (copied_len < len_rhs) {
		std::fill(digits, digits + DIGITS_PER_INDEX, '.'); //replace old digits with non numeric characters
		m_Mag.push_back(std::stoll(strncpy(digits, rhs, len_rhs - copied_len))); //Push last set of digits
	}
	//vector must have a value
	if (m_Mag.size() == 0) {
		m_Mag.resize(1); m_sign = 1;
	}

	delete[](digits);
}

//Parameterized constructor for integers
BigInteger::BigInteger(BaseType integer)
{
	this->m_sign = integer < 0 ? -1 : 1;
	if (integer == 0) {
		m_Mag.resize(1);
		return;
	}
	//Split integer into vector
	integer = abs(integer);
	while (integer > 0)
	{
		m_Mag.push_back(integer % MOD_VAL);
		integer /= MOD_VAL;
	}
}

//copy constructor
BigInteger::BigInteger(const BigInteger& other)
{
	m_Mag.clear();
	m_Mag.resize(other.m_Mag.size());
	m_Mag = other.m_Mag;
	m_sign = other.m_sign;
}

/*PRIVATE HELPER METHODS*/

//Get sum of BigInteger magnitudes
void BigInteger::sum_Magnitudes(const BigInteger& other, BigInteger& result) const
{
	result.m_Mag.resize(std::max(m_Mag.size(), other.m_Mag.size()));

	BaseType firstVal, secondVal, sumVal;
	int idx, carry = 0;

	for (idx = 0; idx < result.m_Mag.size(); ++idx)
	{
		firstVal = secondVal = 0;

		if (idx < m_Mag.size()) {
			firstVal = m_Mag[idx];
		}
		if (idx < other.m_Mag.size()) {
			secondVal = other.m_Mag[idx];
		}
		sumVal = firstVal + secondVal + carry;
		result.m_Mag[idx] = sumVal % MOD_VAL;
		carry = sumVal / MOD_VAL;
	}

	//if carry exists, add to BigInteger
	if (carry) {
		result.m_Mag.push_back(carry);
	}
}

//Get difference of BigInteger Magnitudes
void BigInteger::diff_Magnitudes(const BigInteger& other, BigInteger& result, int lhs_greater) const
{
	BaseType carry = 0;
	const BigInteger *first = this, *second = &other;

	//assign first pointer to BigInteger with bigger Magnitude, second pointer to smaller
	if (lhs_greater == -1) {
		first = &other;
		second = this;
	}

	result.m_Mag.resize(std::max(m_Mag.size(), other.m_Mag.size()));
	int index, lastNonZeroIdx = -1;
	BaseType first_val, second_val;

	for (index = 0; index < first->m_Mag.size(); ++index) {
		first_val = first->m_Mag[index] + carry;
		second_val = 0;
		//assign second value if it exists
		if (index < second->m_Mag.size()) {
			second_val = second->m_Mag[index];
		}
		//calculate result and assign appropriate carry
		if (first_val >= second_val) {
			result.m_Mag[index] = first_val - second_val;
			carry = 0;
		}
		else {
			result.m_Mag[index] = MOD_VAL + first_val - second_val;
			carry = -1;
		}

		if (result.m_Mag[index] != 0) {
			lastNonZeroIdx = index;
		}
	}
	//shrink result's magnitude to exclude leading zeros
	result.m_Mag.resize(std::max(lastNonZeroIdx + 1, 1));
}

//Multiply BigIntegers
void BigInteger::multiply(const BigInteger& other, BigInteger& result) const
{
	//if either multiplicand or multiplier is zero, return zero
	if (this->isZero() || other.isZero()) {
		result = BaseType(+0);
		return;
	}

	BaseType current_value, carry = 0;
	int offset_idx = 0, result_index;

	//loop through second BigInt
	for (const BaseType& other_val : other.m_Mag) {
		result_index = offset_idx++;
		//loop through first BigInt
		for (const BaseType& this_val : this->m_Mag) {
			//multiply value at index of second to index of first, add carry from previous calculation
			current_value = (other_val * this_val) + carry;

			if (result_index < result.m_Mag.size()) { //if result fits
				current_value += result.m_Mag[result_index];
				result.m_Mag[result_index] = (current_value % MOD_VAL);
			}
			else
				result.m_Mag.push_back(current_value % MOD_VAL); //need to expand result
			carry = current_value / MOD_VAL; //compute new carry
			++result_index;
		}
		//if carry is left, expand result
		if (carry) {
			result.m_Mag.push_back(carry);
			carry = 0;
		}
	}

	result.m_sign = m_sign * other.m_sign;
}

//Compare BigIntegers
//0 for equal, 1 for greater, -1 for less
int BigInteger::compare(const BigInteger& other) const
{
	//Check signs
	if (m_sign > other.m_sign)
		return 1;
	if (other.m_sign > m_sign)
		return -1;
	//check vector sizes
	if (m_Mag.size() > other.m_Mag.size())
		return 1;
	if (m_Mag.size() < other.m_Mag.size())
		return -1;

	//BigIntegers have same signs and vector size. check Magnitudes
	return comp_Magnitudes(other);
}

//Compare just magnitudes of both BigIntegers
int BigInteger::comp_Magnitudes(const BigInteger& other) const
{
	for (int i = m_Mag.size() - 1; i != -1; --i)
	{
		if (m_Mag[i] * m_sign > other.m_Mag[i] * other.m_sign)
			return 1;
		if (m_Mag[i] * m_sign < other.m_Mag[i] * other.m_sign)
			return -1;
	}
	return 0;
}

/*OVERLOADED OPERATORS*/

//Multiplication
BigInteger BigInteger::operator *(const BigInteger& other) const
{
	BigInteger result;
	multiply(other, result);
	return result;
}

BigInteger& BigInteger::operator*=(const BigInteger& other)
{
	BigInteger result;
	multiply(other, result);
	*this = std::move(result);

	return *this;
}

//Greater than
bool BigInteger::operator>(const BigInteger& other) const
{
	if (compare(other) == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool BigInteger::operator >=(const BigInteger& other) const
{
	if (compare(other) != -1) {
		return true;
	}
	else {
		return false;
	}
}

//Less than
bool BigInteger::operator<(const BigInteger& other) const
{
	if (compare(other) == -1) {
		return true;
	}
	else {
		return false;
	}
}

bool BigInteger::operator<=(const BigInteger& other) const
{
	if (compare(other) != 1) {
		return true;
	}
	else {
		return false;
	}
}

//Equals
bool BigInteger::operator==(const BigInteger& other) const
{
	if (compare(other) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool BigInteger::operator!=(const BigInteger& other) const
{
	return !(this->operator==(other));
}

//Assignment operator
BigInteger& BigInteger::operator=(const BigInteger& other)
{
	m_Mag.clear();
	m_Mag.resize(other.m_Mag.size());
	m_Mag = other.m_Mag;
	m_sign = other.m_sign;

	return *this;
}

//Negate operator
BigInteger BigInteger::operator-(void) const
{
	BigInteger result = *this;
	result.m_sign *= -1;
	return result;
}

bool BigInteger::isNegative() const
{
	return m_sign == -1;
}

BigInteger BigInteger::Abs() const
{
	BigInteger result = *this;
	result.m_sign = 1;
	return result;
}

//Equivalent to BigInteger == 0 to be used for special cases
bool BigInteger::isZero() const
{
	return m_Mag.size() == 1 && m_Mag.back() == 0;
}

//Addition operator
BigInteger BigInteger::operator+(const BigInteger& other) const
{
	BigInteger result;
	//Get Magnitude comparison result
	int comp_Mag = comp_Magnitudes(other);
	//if both are of the same signs, sum their magnitudes
	if (m_sign == other.m_sign) {
		sum_Magnitudes(other, result);
		result.m_sign = m_sign;
	}
	else {
		//get Magnitude difference, assign appropriate sign
		diff_Magnitudes(other, result, comp_Mag);
		//if negative BigInteger has bigger magnitude, result's sign is negative, else positive
		//if((m_sign == -1 && comp_Mag == 1) || (other.m_sign == -1 && comp_Mag == -1))

		result.m_sign = (m_sign * comp_Mag) | 1;
	}
	return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& other)
{
	*this = std::move(this->operator+(other));
	return *this;
}

//Subtraction
BigInteger BigInteger::operator-(const BigInteger& other) const
{
	BigInteger result;
	int comp_Mag = comp_Magnitudes(other);
	//if both BigIntegers have opposite signs, sum their magnitudes. resulting sign
	//is sign of lhs
	if (this->m_sign != other.m_sign) {
		sum_Magnitudes(other, result);
		result.m_sign = m_sign;
	}
	else {
		//get difference of magnitudes and assign appropriate sign
		diff_Magnitudes(other, result, comp_Mag);
		//if ((this->isNegative() && comp_Mag == 1) || (other.isNegative() && comp_Mag == -1))
		result.m_sign = (m_sign * comp_Mag) | 1;
	}
	return result;
}

BigInteger& BigInteger::operator-=(const BigInteger& other)
{
	*this = std::move(this->operator-(other));
	return *this;
}

//Increment
BigInteger& BigInteger::operator++() //prefix
{
	*this += 1;
	return *this;
}

BigInteger BigInteger::operator++(int) //postfix
{
	BigInteger temp = *this;
	*this += 1;
	return temp;
}

//Decrement
BigInteger& BigInteger::operator--()
{
	*this -= 1;
	return *this;
}

BigInteger BigInteger::operator--(int)
{
	BigInteger temp = *this;
	*this -= 1;
	return temp;
}

//Overloaded insertion operator for ostream
std::ostream& operator<<(std::ostream& os, const BigInteger &bg)
{
	if (bg.m_sign == -1) {
		os << '-';
	}
	os << bg.m_Mag.back();
	for_each(bg.m_Mag.rbegin() + 1, bg.m_Mag.rend(), [&bg, &os](const BigInteger::BaseType& val) {
		os << std::setfill('0') << std::setw(bg.DIGITS_PER_INDEX) << val;
	});
	return os;
}

int main()
{
	freopen("data.dat", "r", stdin);
	freopen("out.dat", "w", stdout);
	
	ios_base::sync_with_stdio(false); cin.tie(0);

	string a, b;
	BigInteger A, B, C;

	while (cin >> a >> b)
	{
		A = a.c_str();
		B = b.c_str();

		C = A*B;
		cout << C << endl;
	}
}