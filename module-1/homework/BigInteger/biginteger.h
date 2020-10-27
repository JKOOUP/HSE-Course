#include <iostream>
#include <string>
#include <vector>

class BigInteger {
public:

	BigInteger();

	BigInteger(const BigInteger& bigInt);
	
	BigInteger(int64_t _number);

	~BigInteger() = default;

	explicit operator bool();

	static void swap(BigInteger& a, BigInteger& b);

	std::string toString();

	BigInteger& operator=(const BigInteger& bigInt);

	BigInteger& operator+=(const BigInteger& bigInt);

	BigInteger& operator-=(const BigInteger& bigInt);
	
	BigInteger& operator*=(const BigInteger& bigInt);
	
	BigInteger& operator/=(const BigInteger& bigInt);
	
	BigInteger& operator%=(const BigInteger& bigInt);

	friend std::ostream& operator<<(std::ostream& out, const BigInteger& a);

	friend std::istream& operator>>(std::istream& in, BigInteger& a);

	friend const BigInteger operator+(const BigInteger& a, const BigInteger& b);

	friend const BigInteger operator-(const BigInteger& a, const BigInteger& b);
	
	friend const BigInteger operator-(const BigInteger& bigInt);

	friend const BigInteger operator*(const BigInteger& a, const BigInteger& b);

	friend const BigInteger operator/(const BigInteger& a, const BigInteger& b); 

	friend const BigInteger operator%(const BigInteger& a, const BigInteger& b);

	friend BigInteger& operator++(BigInteger& bigInt);

	friend BigInteger operator++(BigInteger& bigInt, int);

	friend BigInteger& operator--(BigInteger& bigInt);

	friend BigInteger operator--(BigInteger& bigInt, int);

	friend bool operator==(const BigInteger& a, const BigInteger& b);
	
	friend bool operator!=(const BigInteger& a, const BigInteger& b);

	friend bool operator<(const BigInteger& a, const BigInteger& b);

	friend bool operator>(const BigInteger& a, const BigInteger& b);

	friend bool operator<=(const BigInteger& a, const BigInteger& b);
	
	friend bool operator>=(const BigInteger& a, const BigInteger& b);

private:
	
	const std::size_t block_max;
	std::size_t number_size;
	std::vector <uint32_t> number;
	bool is_neg;

	static const BigInteger StringToBigInteger(std::string& strNumber);

	static std::string BigIntegerToString(const BigInteger& bigInt);

	static std::size_t get_real_size(const BigInteger& bigInt);
	
	static void set_number_size(BigInteger& bigInt);

	static void resize_number(BigInteger& bigInt);

	static void resize_number(BigInteger& bigInt, const std::size_t x);

	static const BigInteger abs_with_copy(const BigInteger& bigInt);

	static const BigInteger& sum_abs(BigInteger& a, const BigInteger& b);

	static std::size_t find_next_pos(const BigInteger& a, const std::size_t pos);

	static void make_sub(const std::size_t l, const std::size_t r, BigInteger& a, const BigInteger& b, bool rev);

	static const BigInteger& substraction_from_left(BigInteger& a, const BigInteger& b);

	static const BigInteger& substraction_from_right(BigInteger& a, const BigInteger& b);

	static const std::vector<BigInteger> split(const BigInteger& bitInt, const std::size_t size);	

	static const BigInteger mult10(const BigInteger& bigInt, const std::size_t exponent);

	static const BigInteger mult(const std::size_t size, BigInteger x, BigInteger y);

	static const BigInteger div2(const BigInteger& bigInt);

	static const BigInteger div_abs(const BigInteger& a, const BigInteger& b);

	static bool less(const BigInteger& a, const BigInteger& b);
};