#include "biginteger.h"

std::size_t max(const std::size_t a, const std::size_t b) {
	return (a < b ? b : a);
}

std::size_t min(const std::size_t a, const std::size_t b) {
	return (a < b ? a : b);
}

void reverse(std::string& str) {
	for (std::size_t i = 0; i < str.size() / 2; i++) {
		char c = str[i];
		str[i] = str[str.size() - i - 1];
		str[str.size() - i - 1] = c;
	}
}

void BigInteger::get_number_size(BigInteger& bigInt) {
	std::size_t real_size = 1;
	for (std::size_t i = 0; i < bigInt.number_size; i++)
		if (bigInt.number[i] > 0)
			real_size = static_cast<uint32_t>(i + 1);

	bigInt.number_size = real_size;
}

std::size_t BigInteger::get_real_size(const BigInteger& bigInt) {
	std::size_t real_size = 1;
	for (std::size_t i = 0; i < bigInt.number_size; i++)
		if (bigInt.number[i] > 0)
			real_size = static_cast<uint32_t>(i + 1);

	return real_size;
}

void BigInteger::set_number_size(BigInteger& bigInt) {
	BigInteger::get_number_size(bigInt);
	bigInt.number.resize(bigInt.number_size);
}

void BigInteger::set_number_size(BigInteger& bigInt, std::size_t x) {
	bigInt.number_size = x;
	bigInt.number.resize(x);
}

const BigInteger BigInteger::abs_with_copy(const BigInteger& bigInt) {
	BigInteger result = bigInt;
	result.is_neg = false;
	return result;
}

const BigInteger& BigInteger::sum_abs(BigInteger& a, const BigInteger& b) {
	uint32_t currSum = 0;
	for (std::size_t i = 0; i < a.number_size; i++) {
		uint64_t tmp = static_cast<uint64_t>(currSum) + static_cast<uint64_t>(a.number[i]);
		if (i < b.number_size)
			 tmp += static_cast<uint64_t>(b.number[i]);
		
		currSum = static_cast<uint32_t>(tmp / a.block_max);
		a.number[i] = static_cast<uint32_t>(tmp % a.block_max);
	}


	BigInteger::set_number_size(a);
	return a;
}

std::size_t BigInteger::find_next_pos(const BigInteger& a, const std::size_t pos) {
	std::size_t next = 0;
	for (std::size_t i = pos + 1; i < a.number_size; i++)
		if (a.number[i] > 0) {
			next = i;
			break;
		}
	return next;
}

void BigInteger::make_sub(const std::size_t l, const std::size_t r, BigInteger& a, const BigInteger& b, bool rev) {
	for (std::size_t i = l; i < r; i++)
		if (rev == false)
			a.number[i] = static_cast<uint32_t>(1e9 - 1) - (i < b.number_size ? b.number[i] : 0);
		else
			a.number[i] = static_cast<uint32_t>(1e9 - 1) - a.number[i]; 
}

const BigInteger& BigInteger::substraction_from_left(BigInteger& a, const BigInteger& b) {
	for (std::size_t i = 0; i < b.number_size; i++) {
		if (a.number[i] >= b.number[i]) {
			a.number[i] -= b.number[i];
			continue;
		}

		std::size_t next = BigInteger::find_next_pos(a, i);
		BigInteger::make_sub(i + 1, next, a, b, false);

		a.number[i] = static_cast<uint32_t>(1e9) - b.number[i] + a.number[i];
		a.number[next]--;
		i = next - 1;
	}

	BigInteger::set_number_size(a);
	return a;
}

const BigInteger& BigInteger::substraction_from_right(BigInteger& a, const BigInteger& b) {
	for (std::size_t i = 0; i < b.number_size; i++) {
		if (b.number[i] >= a.number[i]) {
			a.number[i] = b.number[i] - a.number[i];
			continue;
		}

		std::size_t next = BigInteger::find_next_pos(b, i);
		BigInteger::make_sub(i + 1, next, a, b, true);

		a.number[i] = static_cast<uint32_t>(1e9) - a.number[i] + b.number[i];
		a.number[next]++;
		i = next - 1;
	}

	BigInteger::set_number_size(a);
	return a;
}

const std::vector<BigInteger> BigInteger::split(const BigInteger& bigInt, const std::size_t size) {
	BigInteger first, second;
	BigInteger::set_number_size(first, (bigInt.number_size > size / 2 ? bigInt.number_size - size / 2 : size / 2));
	BigInteger::set_number_size(second, size / 2);

	std::size_t real_size = BigInteger::get_real_size(bigInt);
	for (std::size_t i = 0; i < size / 2; i++)
		second.number[i] = (i < real_size ? bigInt.number[i] : 0);

	for (std::size_t i = size / 2; i < bigInt.number_size; i++)
		first.number[i - size / 2] = (i < real_size ? bigInt.number[i] : 0);

	BigInteger::set_number_size(first);
	BigInteger::set_number_size(second);

	std::vector <BigInteger> result = {first, second};
	return result;
}

const BigInteger BigInteger::mult10(const BigInteger& bigInt, const std::size_t exponent) {
	BigInteger result;
	BigInteger::set_number_size(result, exponent + bigInt.number_size);

	for (std::size_t i = exponent; i < exponent + bigInt.number_size; i++)
		result.number[i] = bigInt.number[i - exponent]; 

	BigInteger::set_number_size(result);
	return result;
} 

const BigInteger BigInteger::mult(const std::size_t size, BigInteger x, BigInteger y) {
	if (!x or !y)
		return 0;
	
	if (size == 1) {
		BigInteger result;

		uint64_t temp = static_cast<uint64_t>(x.number[0]) * static_cast<uint64_t>(y.number[0]);
		result.number[0] = static_cast<uint32_t>(temp % result.block_max);
		result.number[1] = static_cast<uint32_t>(temp / result.block_max);

		BigInteger::set_number_size(result);
		return result;
	}

	std::vector <BigInteger> splitted_x = BigInteger::split(x, size);
	std::vector <BigInteger> splitted_y = BigInteger::split(y, size);

	BigInteger a = splitted_x[0];
	BigInteger b = splitted_x[1];
	BigInteger c = splitted_y[0];
	BigInteger d = splitted_y[1];

	BigInteger first_factor = mult(max(a.number_size, c.number_size), a, c);
	BigInteger third_factor = mult(max(b.number_size, d.number_size), b, d);
	BigInteger second_factor = mult(max((a + b).number_size, (c + d).number_size), a + b, c + d) - first_factor - third_factor;
	
	BigInteger shifted_first_factor = BigInteger::mult10(first_factor, 2 * (size / 2));
	BigInteger shifted_second_factor = BigInteger::mult10(second_factor, size / 2);
	BigInteger result = shifted_first_factor + shifted_second_factor + third_factor;

	BigInteger::set_number_size(result);
	return result;
}

const BigInteger BigInteger::div2(const BigInteger& bigInt) {
	BigInteger result;
	BigInteger::set_number_size(result, bigInt.number_size);

	uint32_t remainder = 0;
	for (int32_t i = static_cast<int32_t>(bigInt.number_size) - 1; i >= 0; i--) {
		result.number[i] = (remainder * static_cast<uint32_t>(1e9) + bigInt.number[i]) / 2;
		remainder = (remainder * static_cast<uint32_t>(1e9) + bigInt.number[i]) % 2;
	}

	BigInteger::set_number_size(result);
	return result;
}

const BigInteger BigInteger::div_abs(const BigInteger& a, const BigInteger& b) {
	BigInteger l = 0, r = BigInteger::abs_with_copy(a) + 1;
	while (r - l > 1) {
		BigInteger m = div2(l + r);
		if (BigInteger::abs_with_copy(a) >= m * BigInteger::abs_with_copy(b))
			l = m;
		else
			r = m;
	}

	BigInteger::set_number_size(l);
	return l;
}

bool BigInteger::less(const BigInteger& a, const BigInteger& b) {
	if (BigInteger::get_real_size(a) != BigInteger::get_real_size(b))
		return BigInteger::get_real_size(a) < BigInteger::get_real_size(b);

	for (int32_t i = static_cast<int32_t>(BigInteger::get_real_size(a)) - 1; i >= 0; i--)
		if (a.number[i] != b.number[i])
			return a.number[i] < b.number[i];

	return false;
}

BigInteger::BigInteger(): 
	block_max(static_cast<uint32_t>(1e9)),  
	number_size(2), 
	number(2, 0), 
	is_neg(false) 
{};

BigInteger::BigInteger(const BigInteger& bigInt): 
	block_max(bigInt.block_max), 
	number_size(bigInt.number_size), 
	number(bigInt.number), 
	is_neg(bigInt.is_neg) 
{};

BigInteger::operator bool() {
	return (*this != 0);
}

BigInteger::BigInteger(int64_t _number): block_max(static_cast<uint32_t>(1e9)) {
	number.assign(128, 0);
	number[1] = static_cast<uint32_t>(std::abs(_number) / block_max);
	number[0] = static_cast<uint32_t>(std::abs(_number) % block_max);
	number_size = 1 + (static_cast<uint32_t>(std::abs(_number)) / block_max > 0);
	is_neg = (_number < 0);
};

void BigInteger::swap(BigInteger& a, BigInteger& b) {
	std::swap(a.number, b.number);
	std::swap(a.is_neg, b.is_neg);
	std::swap(a.number_size, b.number_size);
}

const BigInteger BigInteger::StringToBigInteger(std::string& strNumber) {
	BigInteger result;
	BigInteger::set_number_size(result, strNumber.size() / 9 + 1);

	if (strNumber[0] == '-') {
		result.is_neg = 1;
		strNumber.erase(0, 1);
	}

	reverse(strNumber);
	uint32_t currNumber = 0;
	for (std::size_t i = 0; i < strNumber.size(); i += 9) {
		std::string currStr = strNumber.substr(i, min(9, static_cast<int32_t>(strNumber.size()) - static_cast<int32_t>(i)));

		reverse(currStr);
		currNumber += std::stoi(currStr);

		result.number[i / 9] = static_cast<uint32_t>(currNumber % result.block_max);
		currNumber /= static_cast<uint32_t>(result.block_max);
	}

	BigInteger::set_number_size(result);
	return result;
}

std::string BigInteger::BigIntegerToString(const BigInteger& bigInt) {
	if (bigInt == 0)
		return "0";

	std::string result = (bigInt.is_neg ? "-" : "");
	for (int32_t i = static_cast<int32_t>(bigInt.number_size) - 1; i >= 0; i--) {
		std::string add = std::to_string(bigInt.number[i]);
		
		while (add.size() < 9 and i < static_cast<int32_t>(bigInt.number_size) - 1)
			add = "0" + add;
		
		result += add;
	}

	return result;
}

std::string BigInteger::toString() {
	return BigInteger::BigIntegerToString(*this);
}

BigInteger& BigInteger::operator=(const BigInteger& bigInt) {
	if (this == &bigInt)
		return *this;

	this->number = bigInt.number;
	this->is_neg = bigInt.is_neg;
	this->number_size = bigInt.number_size;
	return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& bigInt) {
	BigInteger::set_number_size(*this, max(this->number_size, bigInt.number_size) + 1);
	if (this->is_neg == bigInt.is_neg)
		return *this = BigInteger::sum_abs(*this, bigInt);

	bool sgn = BigInteger::less(*this, bigInt);
	if (sgn)
		BigInteger::substraction_from_right(*this, bigInt);
	else
		BigInteger::substraction_from_left(*this, bigInt);
	
	this->is_neg = sgn;
	if (!bigInt.is_neg)
		this->is_neg ^= 1;

	BigInteger::set_number_size(*this);
	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& bigInt) {
	BigInteger::set_number_size(*this, max(this->number_size, bigInt.number_size) + 1);
	if (this->is_neg != bigInt.is_neg)
		return *this = BigInteger::sum_abs(*this, bigInt);

	bool sgn = BigInteger::less(*this, bigInt);
	if (sgn)
		BigInteger::substraction_from_right(*this, bigInt);
	else
		BigInteger::substraction_from_left(*this, bigInt);

	this->is_neg = sgn;
	if (bigInt.is_neg)
		this->is_neg ^= 1;

	BigInteger::set_number_size(*this);
	return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& bigInt) {
	bool sgn = this->is_neg ^ bigInt.is_neg;
	std::size_t size = max(this->number_size, bigInt.number_size);
	BigInteger::set_number_size(*this, bigInt.number_size + this->number_size + 1);

	*this = BigInteger::mult(size, *this, bigInt);
	this->is_neg = sgn;

	BigInteger::set_number_size(*this);
	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& bigInt) {
	bool sgn = this->is_neg ^ bigInt.is_neg;
	*this = BigInteger::div_abs(*this, bigInt);
	this->is_neg = sgn;

	BigInteger::set_number_size(*this);
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& bigInt) {
	*this -= bigInt * (*this / bigInt);	
	BigInteger::set_number_size(*this);
	return *this;
}

std::istream& operator>>(std::istream& in, BigInteger& bigInt) {
	std::string strNumber;	
	in >> strNumber;
	bigInt = BigInteger::StringToBigInteger(strNumber);
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& bigInt) {
	out << BigInteger::BigIntegerToString(bigInt);
	return out;
}

const BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result += b;
	return result;
}

const BigInteger operator-(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result -= b;
	return result;
}

const BigInteger operator-(const BigInteger& bigInt) {
	BigInteger result = bigInt;
	result.is_neg ^= 1;
	return result;
}

const BigInteger operator*(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result *= b;
	return result;
}

const BigInteger operator/(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result /= b;
	return result;
}

const BigInteger operator%(const BigInteger& a, const BigInteger& b) {
	BigInteger result = a;
	result %= b;
	return result;
}

BigInteger& operator++(BigInteger& bigInt) {
	bigInt += 1;
	return bigInt;
}

BigInteger operator++(BigInteger& bigInt, int) {
	BigInteger oldBigInt = bigInt;
	++bigInt;
	return oldBigInt;
}

BigInteger& operator--(BigInteger& bigInt) {
	bigInt -= 1;
	return bigInt;
}

BigInteger operator--(BigInteger& bigInt, int) {
	BigInteger oldBigInt = bigInt;
	--bigInt;
	return oldBigInt;
}

bool operator<(const BigInteger& a, const BigInteger& b) {
	if (a.is_neg == b.is_neg)
		return (a.is_neg == 0 ? BigInteger::less(a, b) : BigInteger::less(b, a));
	return a.is_neg;
}	

bool operator>(const BigInteger& a, const BigInteger& b) {
	return (b < a);
}

bool operator==(const BigInteger& a, const BigInteger& b) {
	return !(a < b) && !(b < a);
}

bool operator!=(const BigInteger& a, const BigInteger& b) {
	return !(a == b);
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
	return !(a > b);
}

bool operator>=(const BigInteger& a, const BigInteger& b) {
	return !(a < b);
}