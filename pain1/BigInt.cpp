#include "BigInt.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Logger.h"

//========== Constructors ==========


// Define a global logger for the entire BigInt class
Logger bigIntLogger(LogLevel::Debug, "bigint_operations.log");

/**
 * @brief Default constructor initializing BigInt to zero.
 */
BigInt::BigInt() : number("0"), isNegative(false) {}

/**
 * @brief Integer constructor initializing BigInt with an integer value.
 * @param num Integer value to initialize BigInt.
 */
BigInt::BigInt(int num) : number(std::to_string(std::abs(num))), isNegative(num < 0) {}

/**
 * @brief String constructor initializing BigInt from a string representation.
 * @param num String representation of an integer.
 * @throws std::invalid_argument If the string is not a valid integer representation.
 */
BigInt::BigInt(const std::string &num) {
    if (num.empty()) {
        number = "0";
        isNegative = false;
    } else {
        // Determine if the number is negative and store the corresponding boolean value
        isNegative = num[0] == '-';
        // Extract the numeric part of the string, excluding any sign
        number = isNegative ? num.substr(1) : num;

        // Check if the number string is a valid representation
        if (!isValid(number)) {
            bigIntLogger.log("Invalid string argument provided to constructor.", LogLevel::Error);
            throw std::invalid_argument("Invalid BigInt initialization string: " + num);
        } else {
            // Remove any leading zeros to normalize the representation
            removeLeadingZeros();

            // After removing leading zeros, adjust for cases like "-0" or "0"
            if (number.empty() || number == "0") {
                number = "0";
                isNegative = false;
            }
        }
    }
}

//========== Copy and Move Constructors ==========

/**
 * @brief Copy constructor.
 * @param other BigInt instance to copy.
 */
BigInt::BigInt(const BigInt &other) : number(other.number), isNegative(other.isNegative) {}

/**
 * @brief Move constructor.
 * @param other BigInt instance to move from.
 */
BigInt::BigInt(BigInt &&other) noexcept: number(std::move(other.number)), isNegative(other.isNegative) {
    other.isNegative = false;  // Reset the moved-from object to a default state
}

//========== Destructor ==========

/**
 * @brief Destructor. No dynamic memory is allocated, so no cleanup is required.
 */
BigInt::~BigInt() {
    // If any dynamic allocation or resources were to be released, it would be done here.
}

//========== Assignment Operators ==========

/**
 * @brief Copy assignment operator.
 * @param other BigInt instance to copy from.
 * @return Reference to the current instance.
 */
BigInt &BigInt::operator=(const BigInt &other) {
    if (this != &other) {  // Protect against self-assignment
        number = other.number;
        isNegative = other.isNegative;
    }
    return *this;
}

/**
 * @brief Move assignment operator.
 * @param other BigInt instance to move from.
 * @return Reference to the current instance.
 */
BigInt &BigInt::operator=(BigInt &&other) noexcept {
    if (this != &other) {  // Protect against self-assignment
        number = std::move(other.number);
        isNegative = other.isNegative;
        other.isNegative = false;  // Reset the moved-from object to a default state
    }
    return *this;
}

//========== Private Methods ==========

/**
 * @brief Removes leading zeros from the number string.
 */
void BigInt::removeLeadingZeros() {
    size_t firstNotZero = number.find_first_not_of('0');
    if (firstNotZero != std::string::npos) {
        number = number.substr(firstNotZero);
    } else {
        number = "0";
    }
    if (number == "0") {
        isNegative = false;
    }
}

//========== Input/Output Stream Overloads ==========

/**
 * @brief Overloads the output stream operator for BigInt.
 * @param out The output stream.
 * @param bigInt The BigInt object to output.
 * @return Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const BigInt &bigInt) {
    if (bigInt.isNegative) {  // If BigInt is negative, output a negative sign
        out << '-';
    }
    out << bigInt.number;  // Output the number part
    return out;  // Return the output stream
}

/**
 * @brief Overloads the input stream operator for BigInt.
 * @param in The input stream.
 * @param b The BigInt object to store the input.
 * @return Reference to the input stream.
 */
std::istream &operator>>(std::istream &in, BigInt &b) {
    std::string input;
    in >> input;  // Read input into a string
    b = BigInt(input);  // Convert the string to BigInt and store it
    return in;  // Return the input stream
}

//========== Arithmetic Operators ==========

/**
 * @brief Addition operator for BigInt.
 * @param other The BigInt to add.
 * @return The result of the addition.
 */
BigInt BigInt::operator+(const BigInt &other) const {
    bigIntLogger.log("Adding two BigInts.", LogLevel::Debug);
    BigInt result;  // To store the result
    if (isNegative == other.isNegative) {  // If both BigInts have the same sign
        result.number = addStrings(number, other.number);
        result.isNegative = isNegative;
    } else {  // If BigInts have different signs
        if (isSmaller(number, other.number)) {
            result.number = subtractStrings(other.number, number);
            result.isNegative = other.isNegative;
        } else {
            result.number = subtractStrings(number, other.number);
            result.isNegative = isNegative;
        }
    }

    // Handle -0 edge case
    if (result.number == "0") {
        result.isNegative = false;
    }
    return result;
}

/**
 * @brief Addition assignment operator for BigInt.
 * @param other The BigInt to add.
 * @return The current instance after addition.
 */
BigInt &BigInt::operator+=(const BigInt &other) {
    *this = *this + other;  // Use operator+ to perform addition
    return *this;
}

/**
 * @brief Subtraction operator for BigInt.
 * @param other The BigInt to subtract.
 * @return The result of the subtraction.
 */
BigInt BigInt::operator-(const BigInt &other) const {
    bigIntLogger.log("Subtracting two BigInts.", LogLevel::Debug);
    BigInt result;  // To store the result
    // Handle various cases based on the signs of the BigInts
    if (isNegative && other.isNegative) {
        // -a - (-b) = b - a
        if (isSmaller(number, other.number)) {
            result.number = subtractStrings(other.number, number);
        } else {
            result.number = subtractStrings(number, other.number);
            result.isNegative = true;
        }
    } else if (!isNegative && other.isNegative) {
        // a - (-b) = a + b
        result.number = addStrings(number, other.number);
    } else if (isNegative && !other.isNegative) {
        // -a - b = -(a + b)
        result.number = addStrings(number, other.number);
        result.isNegative = true;
    } else {
        // a - b
        if (isSmaller(number, other.number)) {
            result.number = subtractStrings(other.number, number);
            result.isNegative = true;
        } else {
            result.number = subtractStrings(number, other.number);
        }
    }

    // Handle -0 edge case
    if (result.number == "0") {
        result.isNegative = false;
    }
    return result;
}

/**
 * @brief Subtraction assignment operator for BigInt.
 * @param other The BigInt to subtract.
 * @return The current instance after subtraction.
 */
BigInt &BigInt::operator-=(const BigInt &other) {
    *this = *this - other;  // Use operator- to perform subtraction
    return *this;
}

/**
 * @brief Unary plus operator for BigInt.
 * @return The current instance.
 */
BigInt BigInt::operator+() const {
    return *this;  // Return the current instance as it is
}

/**
 * @brief Unary minus operator for BigInt.
 * @return The negated BigInt.
 */
BigInt BigInt::operator-() const {
    BigInt result = *this;  // Make a copy of the current instance
    if (result.number != "0") {  // Check to ensure we don't negate zero
        result.isNegative = !result.isNegative;  // Flip the sign
    }
    return result;
}
//========== Increment and Decrement Operators ==========

/**
 * @brief Prefix increment operator. Increments the current BigInt by one.
 * @return Reference to the current instance after incrementing.
 */
BigInt &BigInt::operator++() {
    *this += 1;  // Add one to the current BigInt
    return *this;  // Return the current instance
}

/**
 * @brief Postfix increment operator. Increments the current BigInt by one.
 * @return The BigInt before incrementing.
 */
BigInt BigInt::operator++(int) {
    BigInt temp = *this;  // Make a copy of the current BigInt
    ++(*this);  // Increment the current BigInt
    return temp;  // Return the copy made before incrementing
}

/**
 * @brief Prefix decrement operator. Decrements the current BigInt by one.
 * @return Reference to the current instance after decrementing.
 */
BigInt &BigInt::operator--() {
    *this -= 1;  // Subtract one from the current BigInt
    return *this;  // Return the current instance
}

/**
 * @brief Postfix decrement operator. Decrements the current BigInt by one.
 * @return The BigInt before decrementing.
 */
BigInt BigInt::operator--(int) {
    BigInt temp = *this;  // Make a copy of the current BigInt
    --(*this);  // Decrement the current BigInt
    return temp;  // Return the copy made before decrementing
}

//========== Multiplication Operators ==========

/**
 * @brief Multiplication operator for BigInt.
 * @param other The BigInt to multiply with.
 * @return The result of the multiplication.
 */
BigInt BigInt::operator*(const BigInt &other) const {
    // Edge Case: Multiplying by 0
    if (this->number == "0" || other.number == "0") {
        return BigInt();  // Return 0
    }

    BigInt result;
    // Perform multiplication using the Karatsuba algorithm
    result.number = karatsubaMultiply(BigInt(this->number), BigInt(other.number));

    // Determine the sign of the result
    result.isNegative = this->isNegative != other.isNegative;

    return result;
}

/**
 * @brief Multiplication assignment operator for BigInt.
 * @param other The BigInt to multiply with.
 * @return Reference to the current instance after multiplication.
 */
BigInt &BigInt::operator*=(const BigInt &other) {
    *this = *this * other;  // Use operator* to perform multiplication
    return *this;
}

//========== Division and Remainder Operators ==========

/**
 * @brief Division operator for BigInt with integer divisor.
 * @param other The integer to divide by.
 * @return The result of the division.
 */
BigInt BigInt::operator/(int other) const {
    return *this / BigInt(other);  // Convert int to BigInt and perform division
}

/**
 * @brief Division assignment operator for BigInt with integer divisor.
 * @param other The integer to divide by.
 * @return Reference to the current instance after division.
 */
BigInt &BigInt::operator/=(int other) {
    *this = *this / BigInt(other);  // Convert int to BigInt and perform division
    return *this;
}

/**
 * @brief Remainder operator for BigInt with integer divisor.
 * @param other The integer to divide by.
 * @return The remainder after division.
 */
BigInt BigInt::operator%(int other) const {
    return *this % BigInt(other);  // Convert int to BigInt and perform remainder operation
}

/**
 * @brief Remainder assignment operator for BigInt with integer divisor.
 * @param other The integer to divide by.
 * @return Reference to the current instance after calculating the remainder.
 */
BigInt &BigInt::operator%=(int other) {
    *this = *this % BigInt(other);  // Convert int to BigInt and perform remainder operation
    return *this;
}

/**
 * @brief Division operator for BigInt.
 * @param other The BigInt to divide by.
 * @return The result of the division.
 */
BigInt BigInt::operator/(const BigInt &other) const {
    if (other == 0) {
        throw std::runtime_error("Division by zero");  // Division by zero is undefined
    }
    return divide(other).first;  // Perform division and return the quotient
}

/**
 * @brief Division assignment operator for BigInt.
 * @param other The BigInt to divide by.
 * @return Reference to the current instance after division.
 */
BigInt &BigInt::operator/=(const BigInt &other) {
    if (other == 0) {
        throw std::runtime_error("Division by zero");  // Division by zero is undefined
    }
    *this = divide(other).first;  // Perform division and update the current instance
    return *this;
}

/**
 * @brief Remainder operator for BigInt.
 * @param other The BigInt to divide by.
 * @return The remainder after division.
 */
BigInt BigInt::operator%(const BigInt &other) const {
    if (other == 0) {
        throw std::runtime_error("Division by zero");  // Division by zero is undefined
    }
    return divide(other).second;  // Perform division and return the remainder
}

/**
 * @brief Remainder assignment operator for BigInt.
 * @param other The BigInt to divide by.
 * @return Reference to the current instance after calculating the remainder.
 */
BigInt &BigInt::operator%=(const BigInt &other) {
    if (other == 0) {
        throw std::runtime_error("Division by zero");  // Division by zero is undefined
    }
    *this = divide(other).second;  // Perform division and update the current instance
    return *this;
}

//========== Comparison Operators ==========

/**
 * @brief Equality operator for BigInt.
 * @param other The BigInt to compare with.
 * @return True if both BigInts are equal, otherwise false.
 */
bool BigInt::operator==(const BigInt &other) const {
    return (this->isNegative == other.isNegative) && (this->number == other.number);
}

/**
 * @brief Not equal operator for BigInt.
 * @param other The BigInt to compare with.
 * @return True if the BigInts are not equal, otherwise false.
 */
bool BigInt::operator!=(const BigInt &other) const {
    return !(*this == other);
}

/**
 * @brief Less than operator for BigInt.
 * @param other The BigInt to compare with.
 * @return True if the current BigInt is less than the other BigInt, otherwise false.
 */
bool BigInt::operator<(const BigInt &other) const {
    if (this->isNegative && !other.isNegative) return true;
    if (!this->isNegative && other.isNegative) return false;

    bool bothAreNegative = this->isNegative && other.isNegative;

    if (this->number.length() != other.number.length()) {
        return (this->number.length() < other.number.length()) != bothAreNegative;
    }

    return (this->number < other.number) != bothAreNegative;
}

/**
 * @brief Less than or equal operator for BigInt.
 * @param other The BigInt to compare with.
 * @return True if the current BigInt is less than or equal to the other BigInt, otherwise false.
 */
bool BigInt::operator<=(const BigInt &other) const {
    return (*this < other) || (*this == other);
}

/**
 * @brief Greater than operator for BigInt.
 * @param other The BigInt to compare with.
 * @return True if the current BigInt is greater than the other BigInt, otherwise false.
 */
bool BigInt::operator>(const BigInt &other) const {
    return !(*this <= other);
}

/**
 * @brief Greater than or equal operator for BigInt.
 * @param other The BigInt to compare with.
 * @return True if the current BigInt is greater than or equal to the other BigInt, otherwise false.
 */
bool BigInt::operator>=(const BigInt &other) const {
    return (*this > other) || (*this == other);
}

//========== Private Utility Methods ==========

/**
 * @brief Check if the given string is a valid representation of a BigInt.
 * @param str The string to check.
 * @return True if the string is valid, otherwise false.
 */
bool BigInt::isValid(const std::string &str) const {
    if (str.empty()) {
        return false;
    }

    size_t start = 0;
    if (str[0] == '-') {
        // Handle negative numbers
        if (str.size() == 1) {
            // String is just "-"
            return false;
        }
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            // Found a non-digit character
            return false;
        }
    }

    return true;
}

/**
 * @brief Add two strings representing non-negative integers.
 * @param a The first string.
 * @param b The second string.
 * @return The sum of the two strings.
 */
std::string BigInt::addStrings(const std::string &a, const std::string &b) const {
    std::string result;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = i >= 0 ? a[i] - '0' : 0;
        int digitB = j >= 0 ? b[j] - '0' : 0;
        int sum = digitA + digitB + carry;
        result = std::to_string(sum % 10) + result;
        carry = sum / 10;
        i--;
        j--;
    }

    // Remove leading zeros (if any)
    size_t startpos = result.find_first_not_of("0");
    return startpos != std::string::npos ? result.substr(startpos) : "0";
}

/**
 * @brief Subtract the second string representing a non-negative integer from the first one.
 * @param a The first string.
 * @param b The second string.
 * @return The result of the subtraction.
 */
std::string BigInt::subtractStrings(const std::string &a, const std::string &b) const {
    std::string result;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = i >= 0 ? a[i] - '0' : 0;
        int digitB = j >= 0 ? b[j] - '0' : 0;
        int sub = digitA - digitB - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result = std::to_string(sub) + result;
        i--;
        j--;
    }

    // Remove leading zeros (if any)
    size_t startpos = result.find_first_not_of("0");
    return startpos != std::string::npos ? result.substr(startpos) : "0";
}

/**
 * @brief Multiply two strings representing non-negative integers.
 * @param a The first string.
 * @param b The second string.
 * @return The product of the two strings.
 */
std::string BigInt::multiplyStrings(const std::string &a, const std::string &b) const {
    int lenA = a.size();
    int lenB = b.size();
    std::string result(lenA + lenB, '0');

    for (int i = lenA - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = lenB - 1; j >= 0; j--) {
            int product = (a[i] - '0') * (b[j] - '0') + carry + (result[i + j + 1] - '0');
            carry = product / 10;
            result[i + j + 1] = product % 10 + '0';
        }
        result[i] += carry;
    }

    // Remove leading zeros
    size_t startpos = result.find_first_not_of("0");
    if (std::string::npos != startpos) {
        result = result.substr(startpos);
    }

    return result;
}

/**
 * @brief Divides two BigInts.
 * @param other The divisor.
 * @return A pair containing the quotient and remainder.
 */
std::pair<BigInt, BigInt> BigInt::divide(const BigInt &other) const {
    // Make copies of dividend and divisor and make them positive
    BigInt dividend = *this;
    dividend.isNegative = false;

    BigInt divisor = other;
    divisor.isNegative = false;

    BigInt quotient;
    BigInt remainder;

    // Handle division by zero
    if (divisor == 0) {
        throw std::runtime_error("Division by zero in divideStrings");
    }

    // If dividend < divisor or dividend == 0, set remainder to dividend
    if (dividend < divisor || dividend == 0) {
        remainder = dividend;
    } else if (divisor == 1) {
        // If divisor is 1, quotient is the dividend
        quotient = dividend;
    } else {
        // Perform division using subtraction
        while (dividend >= divisor) {
            BigInt tempDivisor = divisor;
            BigInt tempQuotient = 1;

            // Optimize division by doubling divisor until it's less than dividend
            while (dividend >= (tempDivisor + tempDivisor)) {
                tempDivisor += tempDivisor;
                tempQuotient += tempQuotient;
            }

            // Subtract the found multiple from the dividend
            dividend -= tempDivisor;
            quotient += tempQuotient;
        }

        // Set the remainder
        remainder = dividend;
    }

    // Set the sign for the quotient based on original signs
    if ((this->isNegative && !other.isNegative) || (!this->isNegative && other.isNegative)) {
        quotient.isNegative = true;
    }

    // Remainder will always take the sign of the dividend
    remainder.isNegative = this->isNegative;

    return std::make_pair(quotient, remainder);
}

/**
 * @brief Multiplies two BigInts using the Karatsuba algorithm.
 * @param x The first BigInt.
 * @param y The second BigInt.
 * @return The product as a string.
 */
std::string BigInt::karatsubaMultiply(const BigInt &x, const BigInt &y) const {
    // Convert BigInts to strings
    std::string xStr = x.number;
    std::string yStr = y.number;

    // Base case for recursion
    if (xStr.size() == 1 && yStr.size() == 1) {
        int product = std::stoi(xStr) * std::stoi(yStr);
        return std::to_string(product);
    }

    // Pad the shorter number with zeros
    while (xStr.size() < yStr.size()) {
        xStr = "0" + xStr;
    }
    while (yStr.size() < xStr.size()) {
        yStr = "0" + yStr;
    }

    // Calculate size of the numbers
    int n = xStr.size();
    int mid = n / 2;

    // Split the input numbers into halves
    BigInt x1 = BigInt(xStr.substr(0, mid));
    BigInt x0 = BigInt(xStr.substr(mid, n - mid));
    BigInt y1 = BigInt(yStr.substr(0, mid));
    BigInt y0 = BigInt(yStr.substr(mid, n - mid));

    // 3 recursive calls to calculate the products
    BigInt z2 = x1 * y1;  // z2 = x1 * y1
    BigInt z0 = x0 * y0;  // z0 = x0 * y0
    BigInt z1 = (x1 + x0) * (y1 + y0) - z2 - z0;  // z1 = (x1 + x0) * (y1 + y0) - z2 - z0

    // Assemble the product from the computed pieces
    z2.number += std::string(2 * (n - mid), '0');  // z2 * 10^(2 * mid)
    z1.number += std::string(n - mid, '0');  // z1 * 10^mid

    BigInt result = z2 + z1 + z0;  // result = z2 * 10^(2 * mid) + z1 * 10^mid + z0

    return result.number;
}

/**
 * @brief Calculates the BigInt raised to the power of an integer exponent.
 * @param exponent The exponent.
 * @return The result of the exponentiation.
 */
BigInt BigInt::pow(int exponent) const {
    if (exponent < 0) {
        throw std::invalid_argument("Negative exponent is not supported for BigInt");
    }

    BigInt result = 1;
    BigInt base = *this;

    // Exponentiation by squaring
    while (exponent > 0) {
        // If exponent is odd, multiply the result by base
        if (exponent % 2 == 1) {
            result *= base;
        }

        // Square the base
        base *= base;

        // Divide exponent by 2
        exponent /= 2;
    }

    return result;
}

/**
 * @brief Compares if string a is smaller than string b, treating them as numbers.
 * @param a First string.
 * @param b Second string.
 * @return True if a < b, false otherwise.
 */
bool BigInt::isSmaller(const std::string &a, const std::string &b) const {
    int n1 = a.length(), n2 = b.length();

    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;

    for (int i = 0; i < n1; i++) {
        if (a[i] < b[i])
            return true;
        else if (a[i] > b[i])
            return false;
    }

    return false;
}

/**
 * @brief Converts BigInt to string.
 * @return The string representation of BigInt.
 */
std::string BigInt::toString() const {
    if (isNegative) {
        return "-" + number;
    }
    return number;
}



