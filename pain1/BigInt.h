#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

/**
 * @brief A class to represent large integers (beyond built-in data types range).
 */
class BigInt {
public:
    //=================== Constructors ===================
    /**
     * @brief Default constructor that initializes the BigInt to zero.
     */
    BigInt();

    /**
     * @brief Constructor that initializes the BigInt with an integer value.
     * @param num An integer to initialize the BigInt with.
     */
    BigInt(int num);

    /**
     * @brief Constructor that initializes the BigInt with a string representation of an integer.
     * @param num A string representation of an integer.
     * @throws std::invalid_argument If the string is not a valid representation of an integer.
     */
    BigInt(const std::string &num);

    /**
     * @brief Copy constructor.
     * @param other A BigInt instance to copy the value from.
     */
    BigInt(const BigInt &other);

    /**
     * @brief Move constructor.
     * @param other A BigInt instance to move the value from.
     */
    BigInt(BigInt &&other) noexcept;

    //=================== Destructor ===================
    /**
     * @brief Destructor to clean up resources, if any.
     */
    ~BigInt();

    //=================== Assignment Operators ===================
    /**
     * @brief Copy assignment operator.
     * @param other A BigInt instance to copy the value from.
     * @return A reference to the updated BigInt instance.
     */
    BigInt &operator=(const BigInt &other);

    /**
     * @brief Move assignment operator.
     * @param other A BigInt instance to move the value from.
     * @return A reference to the updated BigInt instance.
     */
    BigInt &operator=(BigInt &&other) noexcept;

    //=================== Arithmetic Operators ===================
    BigInt operator+(const BigInt &other) const;

    BigInt operator-(const BigInt &other) const;

    BigInt operator*(const BigInt &other) const;

    BigInt &operator+=(const BigInt &other);

    BigInt &operator-=(const BigInt &other);

    BigInt &operator*=(const BigInt &other);

    //=================== Division and Remainder Operators ===================
    BigInt operator/(const BigInt &other) const;

    BigInt operator%(const BigInt &other) const;

    BigInt &operator/=(const BigInt &other);

    BigInt &operator%=(const BigInt &other);

    //=================== Unary Operators ===================
    BigInt operator+() const;

    BigInt operator-() const;

    //=================== Increment and Decrement Operators ===================
    BigInt &operator++();    // Prefix
    BigInt operator++(int);  // Postfix
    BigInt &operator--();    // Prefix
    BigInt operator--(int);  // Postfix

    //=================== Comparison Operators ===================
    bool operator==(const BigInt &other) const;

    bool operator!=(const BigInt &other) const;

    bool operator<(const BigInt &other) const;

    bool operator<=(const BigInt &other) const;

    bool operator>(const BigInt &other) const;

    bool operator>=(const BigInt &other) const;

    //=================== Additional Operations ===================
    BigInt operator/(int other) const;

    BigInt &operator/=(int other);

    BigInt operator%(int other) const;

    BigInt &operator%=(int other);

    BigInt pow(int exponent) const;

    std::string toString() const;

    //=================== I/O Stream Overloads ===================
    friend std::ostream &operator<<(std::ostream &out, const BigInt &b);

    friend std::istream &operator>>(std::istream &in, BigInt &b);

private:
    std::string number;
    bool isNegative;

    // Helper functions
    void removeLeadingZeros();

    bool isValid(const std::string &str) const;

    std::string addStrings(const std::string &a, const std::string &b) const;

    std::string subtractStrings(const std::string &a, const std::string &b) const;

    std::string multiplyStrings(const std::string &a, const std::string &b) const;

    std::pair<BigInt, BigInt> divide(const BigInt &other) const;

    std::string karatsubaMultiply(const BigInt &x, const BigInt &y) const;

    bool isSmaller(const std::string &a, const std::string &b) const;
};

#endif // BIGINT_H