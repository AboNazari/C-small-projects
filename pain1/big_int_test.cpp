#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <sstream>
#include "BigInt.h"

uint32_t factorial(uint32_t number) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3'628'800);
}

//Default Constructor:
TEST_CASE("Default Constructor", "[BigInt]") {
    BigInt num;
    REQUIRE(num.toString() == "0");
}
//Integer Constructor:
TEST_CASE("Integer Constructor", "[BigInt]") {
    BigInt pos(123);
    BigInt neg(-123);
    REQUIRE(pos.toString() == "123");
    REQUIRE(neg.toString() == "-123");
}
//String Constructor:
TEST_CASE("String Constructor", "[BigInt]") {
    BigInt valid("12345");
//    BigInt invalid("abc");
    BigInt negative("-9876");
    REQUIRE(valid.toString() == "12345");
//    REQUIRE(invalid.toString() == "0"); // Assuming you want to set it to 0 on invalid input
    REQUIRE(negative.toString() == "-9876");
}
//Copy Constructor and Assignment:
TEST_CASE("Copy Constructor and Assignment", "[BigInt]") {
    BigInt original("12345");
    BigInt copy = original;
    REQUIRE(copy.toString() == original.toString());

    BigInt assigned;
    assigned = original;
    REQUIRE(assigned.toString() == original.toString());
}

//Move Constructor and Assignment:
TEST_CASE("Move Constructor and Assignment", "[BigInt]") {
    BigInt original("54321");
    BigInt moved = std::move(original);
    REQUIRE(moved.toString() == "54321");

    BigInt assigned;
    assigned = std::move(moved);
    REQUIRE(assigned.toString() == "54321");
}

//Testing Arithmetic Operations:
//Addition:
TEST_CASE("Addition", "[BigInt]") {
    BigInt num1("123");
    BigInt num2("456");
    BigInt result = num1 + num2;
    REQUIRE(result.toString() == "579");
}
//Subtraction:
TEST_CASE("Subtraction", "[BigInt]") {
    BigInt num1("456");
    BigInt num2("123");
    BigInt result = num1 - num2;
    REQUIRE(result.toString() == "333");
}
//Multiplication:
TEST_CASE("Multiplication", "[BigInt]") {
    BigInt num1("123");
    BigInt num2("456");
    BigInt result = num1 * num2;
    REQUIRE(result.toString() == "56088");
}
//Division and Remainder:
TEST_CASE("Division and Remainder", "[BigInt]") {
    BigInt num1("1234");
    BigInt num2("56");
    BigInt resultDiv = num1 / num2;
    BigInt resultRem = num1 % num2;
    REQUIRE(resultDiv.toString() == "22");
    REQUIRE(resultRem.toString() == "2");
}


//Testing Comparison Operators:
//Equality and Inequality:
TEST_CASE("Equality and Inequality", "[BigInt]") {
    BigInt num1("123");
    BigInt num2("123");
    BigInt num3("456");
    REQUIRE(num1 == num2);
    REQUIRE(num1 != num3);
}
//Greater Than and Less Than:
TEST_CASE("Greater Than and Less Than", "[BigInt]") {
    BigInt num1("456");
    BigInt num2("123");
    REQUIRE(num1 > num2);
    REQUIRE(num2 < num1);
}
//Greater Than or Equal and Less Than or Equal:
TEST_CASE("Greater Than or Equal and Less Than or Equal", "[BigInt]") {
    BigInt num1("123");
    BigInt num2("123");
    BigInt num3("456");
    REQUIRE(num1 >= num2);
    REQUIRE(num1 <= num2);
    REQUIRE(num3 >= num1);
    REQUIRE(num1 <= num3);
}

//Testing Unary Operations:
//Unary Minus:
TEST_CASE("Unary Minus", "[BigInt]") {
    BigInt num("123");
    BigInt result = -num;
    REQUIRE(result.toString() == "-123");
}

//Increment and Decrement:
TEST_CASE("Increment and Decrement", "[BigInt]") {
    BigInt num("123");
    num++;
    REQUIRE(num.toString() == "124");
    num--;
    REQUIRE(num.toString() == "123");
}

//Testing I/O Operations:
//Input Operator:

TEST_CASE("Input Operator", "[BigInt]") {
    std::istringstream input("12345");
    BigInt num;
    input >> num;
    REQUIRE(num.toString() == "12345");
}

//Output Operator:

TEST_CASE("Output Operator", "[BigInt]") {
    std::ostringstream output;
    BigInt num("67890");
    output << num;
    REQUIRE(output.str() == "67890");
}

//Testing Edge Cases and Special Cases:

//Zero:
TEST_CASE("Zero", "[BigInt]") {
    BigInt zero;
    REQUIRE(zero.toString() == "0");
    BigInt sum = zero + zero;
    REQUIRE(sum.toString() == "0");
    BigInt product = zero * zero;
    REQUIRE(product.toString() == "0");
}

//Addition with Negative Numbers:
TEST_CASE("Addition with Negative Numbers", "[BigInt]") {
    BigInt pos("123");
    BigInt neg("-456");
    BigInt sum = pos + neg; // 123 - 456 = -333
    REQUIRE(sum.toString() == "-333");
}

//Subtraction with Negative Numbers:
TEST_CASE("Subtraction with Negative Numbers", "[BigInt]") {
    BigInt pos("123");
    BigInt neg("-456");
    BigInt result = pos - neg; // 123 - (-456) = 123 + 456 = 579
    REQUIRE(result.toString() == "579");
}

//Multiplication with Negative Numbers:
TEST_CASE("Multiplication with Negative Numbers", "[BigInt]") {
    BigInt pos("123");
    BigInt neg("-456");
    BigInt product = pos * neg;
    REQUIRE(product.toString() == "-56088");
}
//Division with Negative Numbers:
TEST_CASE("Division with Negative Numbers", "[BigInt]") {
    BigInt pos("1234");
    BigInt neg("-56");
    BigInt resultDiv = pos / neg; // 1234 / -56 = -22
    BigInt resultRem = pos % neg; // 1234 % -56 = 2
    REQUIRE(resultDiv.toString() == "-22");
    REQUIRE(resultRem.toString() == "2");
}
//Division by Zero:
TEST_CASE("Division by Zero", "[BigInt]") {
    BigInt num("123");
    BigInt zero;
    bool caught = false;
    try {
        BigInt result = num / zero;
    } catch (const std::runtime_error &e) {
        caught = true;
    }
    REQUIRE(caught);
}

//Large Numbers:
TEST_CASE("Large Numbers", "[BigInt]") {
    BigInt large("12345678901234567890");
    BigInt result = large * large;
    // check if the result is correct
    REQUIRE(result.toString() == "152415787532388367501905199875019052100");
}
//Testing Utility Functions:
//String Conversion:

TEST_CASE("String Conversion", "[BigInt]") {
    BigInt num("12345");
    std::string str = num.toString();
    REQUIRE(str == "12345");
}


