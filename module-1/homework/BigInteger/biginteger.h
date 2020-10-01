#include <iostream>
#include <string>
#include <vector>

class BigInteger {
private:
	
	const uint32_t block_max;
	const uint32_t block_count;
	uint32_t leftNull;

	static void set_left_null(BigInteger& bigInt);

	static const BigInteger abs_with_copy(const BigInteger& bigInt);

	static const BigInteger sum_abs(const BigInteger& a, const BigInteger& b);

	static const BigInteger substraction_abs(const BigInteger& a, const BigInteger& b);

	static const std::vector<BigInteger> split(const BigInteger& bitInt, const std::size_t& size);	

	static const BigInteger mult10(const BigInteger& bigInt, const std::size_t& exponent);

	static const BigInteger mult(const std::size_t size, BigInteger x, BigInteger y);

	static const BigInteger div2(const BigInteger& bigInt);

	static const BigInteger div_abs(const BigInteger& a, const BigInteger& b);

	static bool less(const BigInteger& a, const BigInteger& b);

public:
	
	std::vector <uint32_t> number;
	bool is_neg;

	BigInteger(): block_max(static_cast<uint32_t>(1e9)), block_count(128), leftNull(0), number(128, 0), is_neg(false) {};

	BigInteger(const BigInteger& Int): block_max(Int.block_max), block_count(Int.block_count), leftNull(Int.leftNull), number(Int.number), is_neg(Int.is_neg) {};
	
	BigInteger(int64_t _number): block_max(static_cast<uint32_t>(1e9)), block_count(128), leftNull(0) {
		number.assign(128, 0);
		number[1] = static_cast<uint32_t>(std::abs(_number)) / block_max;
		number[0] = static_cast<uint32_t>(std::abs(_number)) % block_max;

		is_neg = (_number < 0);
		BigInteger::set_left_null(*this);
	};

	~BigInteger() = default;

	explicit operator bool() const {
		return (this->leftNull != 0);
	}

	static void swap(BigInteger& a, BigInteger& b);

	static const BigInteger StringToBigInteger(std::string& strNumber);

	static std::string BigIntegerToString(const BigInteger& bigInt);

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
};