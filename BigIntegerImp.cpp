//
// Created by atassiadamis on 9/16/2024.
//

#include "BigInteger.h"
#include <algorithm>

//default constructor - initializes integerAsString to 0
BigIntegerImp::BigIntegerImp(){
    integerAsString = "0";
}

BigIntegerImp::BigIntegerImp(std::string integer) {
    //if passed string only contains numbers, update integerAsString to passed value
    if (checkIfStringNumeric(integer)) {
        integerAsString = std::move(integer);
        return;
    }
    std::cout << "Error in constructor of BigInteger, string is not numeric" << std::endl;
}

std::ostream& operator<<(std::ostream &os, const BigIntegerImp &other) {
    os << other.integerAsString;
    return os;
}

BigIntegerImp& BigIntegerImp::operator=(BigIntegerImp const &other) {
    if (this != &other) {
        integerAsString = other.integerAsString;
    }
    return *this;
}

BigIntegerImp BigIntegerImp::operator+(BigIntegerImp rhs){
    //initialize BigInteger return object with the addition of rhs.integerAsString and current instance integerAsString
    BigIntegerImp returnObj(stringAddition(integerAsString, rhs.integerAsString));

    //remove excess zeroes from result
    removeLeadingZeros(returnObj);

    //return addition of rhs and this string members
    return returnObj;
}

BigIntegerImp BigIntegerImp::operator-(BigIntegerImp rhs) {
    //initialize BigInteger return object with the difference of current instance integerAsString and rhs.integerAsString
    BigIntegerImp returnObj(stringSubtraction(integerAsString, rhs.integerAsString));

    //remove excess zeroes from result
    removeLeadingZeros(returnObj);

    //return difference of this and rhs string members
    return returnObj;
}

BigIntegerImp BigIntegerImp::operator*(BigIntegerImp other) {
    //initialize BigInteger return obj with product of other and this string members
    BigIntegerImp returnObj(karatsuba(integerAsString, other.integerAsString));

    //return product, note*: excess zeroes are removed in karatsuba() call
    return returnObj;
}

void BigIntegerImp::prependZeros(BigIntegerImp &bObj) {
    //prepend zeros to match bObj and this string member length
    prependZeros(bObj.integerAsString, integerAsString);
}

void BigIntegerImp::prependZeros(std::string &sObj1, std::string &sObj2) {
    //prepend zeros to this objects string variable if it's length is less than bObj
    if (sObj1.length() > sObj2.length()) {
        while(sObj2.length() < sObj1.length()) {
            //sObj2.insert(0, 1, '0');
            sObj2 = "0" + sObj2;
        }
    }
    //prepend zeros to front of sObj1 string variable if its length is less than this
    else if (sObj1.length() < sObj2.length()) {
        while(sObj2.length() > sObj1.length()) {
            //sObj1.insert(0, 1, '0');
            sObj1 = "0" + sObj1;
        }
    }
}

bool BigIntegerImp::checkIfStringNumeric(const std::string &intAsString) {
    //check if each digit in passed string is a number
    for (int i = 0; i < intAsString.length(); i++) {
        if (!std::isdigit(intAsString[i])) {
            return false;
        }
    }
    return true;
}

std::string BigIntegerImp::getBigIntAsString() {
    return integerAsString;
}

void BigIntegerImp::setBigInt(std::string integer) {
    if (checkIfStringNumeric(integer)) {
        integerAsString = std::move(integer);
        return;
    }
    std::cout << "Passed string is not numeric" << std::endl;
}

void BigIntegerImp::removeLeadingZeros(BigIntegerImp &bObj) {
    removeLeadingZeros(bObj.integerAsString);
}

std::string BigIntegerImp::karatsuba(std::string s1, std::string s2) {
    // Ensure both strings are padded to the same length
    int n1 = s1.length();
    int n2 = s2.length();

    // If lengths are uneven, swap values
    if (n1 > n2) {
        std::swap(s1, s2);
    }

    // Pad the shorter string with leading zeros
    prependZeros(s1, s2);

    // Length of the strings
    int n = s1.length();

    // Base case - if either string is empty or length is one, handle appropriately
    if (n == 0) {
        return "0";
    }
    if (n == 1) {
        int answer = stoi(s1) * stoi(s2);
        return std::to_string(answer);
    }

    // If the length is odd, prepend a zero to both strings to make it even
    if (n % 2 == 1) {
        s1 = '0' + s1;
        s2 = '0' + s2;
        ++n;
    }

    // Split the strings into left and right halves
    std::string s1Left = s1.substr(0, n / 2);
    std::string s1Right = s1.substr(n / 2, n / 2);
    std::string s2Left = s2.substr(0, n / 2);
    std::string s2Right = s2.substr(n / 2, n / 2);

    // Find left and right product by recursively calling karatsuba
    std::string leftProduct = karatsuba(s1Left, s2Left);
    std::string rightProduct = karatsuba(s1Right, s2Right);

    // Calculate cross terms
    std::string sum1 = stringAddition(s1Left, s1Right);
    std::string sum2 = stringAddition(s2Left, s2Right);
    std::string middleProduct = stringSubtraction(
        karatsuba(sum1, sum2),
        stringAddition(leftProduct, rightProduct)
    );

    // Multiply leftProduct by 10^n
    for (int i = 0; i < n; i++) {
        leftProduct.append("0");
    }

    // Multiply middleProduct by 10^(n/2)
    for (int i = 0; i < n / 2; i++) {
        middleProduct.append("0");
    }

    // Final result: leftProduct + middleProduct + rightProduct
    std::string temp = stringAddition(rightProduct, middleProduct);
    std::string resultString = stringAddition(leftProduct, temp);

    // Remove leading zeros
    removeLeadingZeros(resultString);

    //return resultant string
    return resultString;
}

std::string BigIntegerImp::stringAddition(std::string &s1, std::string &s2) {
    //ensure strings are of same length (avoids indexing out of range)
    prependZeros(s1, s2);

    //initalize carry (tracks whether addition value of each digit is >9) and returnString (difference of s1 and s2)
    int carry = 0;
    std::string returnString;

    //iterate through both strings from the end and keep track of the carry
    for (int i = s1.length() - 1; i >= 0; i--) {
        //initalize summation character with ascii char value of the sum
        char sumChar = s1[i] + s2[i] - '0' + carry;

        //if the summation of two digits is greater than 9 add the ones digit to result and increase carry to 1
        if (sumChar > '9') {
            returnString.push_back(sumChar - 10);
            carry = 1;
        }
        else {
            returnString.push_back(sumChar);
            carry = 0;
        }
    }

    if (carry) {
        returnString.push_back('1');
    }

    //reverse returnString to put it in correct order
    std::reverse(returnString.begin(), returnString.end());

    return returnString;
}

std::string BigIntegerImp::stringSubtraction(std::string s1, std::string s2) {
    //ensure both strings are of same length
    prependZeros(s1, s2);

    //initialize biginteger return object
    std::string returnString;
    int carry = 0;

    //iterate through string and perform subtraction
    for (int i = s1.length() - 1; i >= 0; i--) {
        int digit1 = s1[i] - '0';
        int digit2 = s2[i] - '0' + carry;

        if (digit1 < digit2) {
            digit1 += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        //append difference of strings to returnString
        returnString.push_back((digit1 - digit2) + '0');
    }

    //reverse string to return it in correct order
    std::reverse(returnString.begin(), returnString.end());

    return returnString;
}

std::string BigIntegerImp::stringDivision(std::string dividend, std::string divisor) {
    std::string quotientString = "0"; //stores final quotient
    std::string currentDividend;  // Holds part of the dividend for each step
    int dividendLength = dividend.length();
    int position = 0;  // Pointer to the current character in the dividend

    // Process each part of the dividend
    while (position < dividendLength) {
        // Add the next digit from the dividend to currentDividend
        currentDividend += dividend[position++];

        // Remove leading zeros from currentDividend
        removeLeadingZeros(currentDividend);

        // Compare the currentDividend with the divisor and find the quotient for this step
        prependZeros(currentDividend, divisor); //prepend zeroes to support comparison
        int currentQuotient = 0;
        while (currentDividend >= divisor) {
            currentDividend = stringSubtraction(currentDividend, divisor);
            currentQuotient++;
        }

        // Add the current quotient to the total quotient string
        quotientString += std::to_string(currentQuotient);
    }

    // Remove leading zeros from the final quotient
    removeLeadingZeros(quotientString);

    return quotientString;

    /*
    //brute force (for fun)
    std::string resultString;
    std::string one = "1";
    while (dividend >= divisor) {
        dividend = stringSubtraction(dividend, divisor);
        resultString = stringAddition(resultString, one);
    }

    return resultString;
    */
}

BigIntegerImp BigIntegerImp::operator/(BigIntegerImp divisor) {
    //case: divisor is multiple zeroes i.e. "0000", remove them for error checking
    removeLeadingZeros(divisor.integerAsString);

    //if divisor is larger than dividend or is 0
    if (divisor.integerAsString == "0" || divisor > *this) {
        std::cout << "Dividend is greater than divisor or divisor is zero, division canceled! ";
        return BigIntegerImp();
    }

    BigIntegerImp resultObj(stringDivision(integerAsString, divisor.integerAsString));

    return resultObj;
}

BigIntegerImp BigIntegerImp::operator%(BigIntegerImp other) {
    BigIntegerImp returnObj = *this - other*(*this / other);

    return returnObj;
}

void BigIntegerImp::removeLeadingZeros(std::string &sObj) {
    //find position of first nonzero value
    int firstNonZero = sObj.find_first_not_of('0');

    //if position is within the range of the string update the string to its new value
    if (firstNonZero >= 0 && firstNonZero <= sObj.length()) {
        sObj = sObj.substr(firstNonZero);
    }
    //else position is not in range meaning string is filled with all zeroes so return just 0
    else {
        sObj = "0";
    }
}

bool BigIntegerImp::operator==(BigIntegerImp &other) {
    prependZeros(other.integerAsString, integerAsString);
    if (other.integerAsString == integerAsString) {
        return true;
    }
    return false;
}

bool BigIntegerImp::operator>(BigIntegerImp other) {
    //make sure strings are equal length to support lexicographically comparison
    prependZeros(other.integerAsString, integerAsString);

    //c++ compiler will compare lexicographically giving the biggest value
    if (integerAsString > other.integerAsString) {
        return true;
    }
    return false;
}

bool BigIntegerImp::operator<(BigIntegerImp other) {
    //make sure strings are equal length to support lexicographically comparison
    prependZeros(other.integerAsString, integerAsString);

    //if integerAsString is less than other, return true
    if (integerAsString < other.integerAsString) {
        return true;
    }
    return false;
}

bool BigIntegerImp::operator<=(BigIntegerImp other) {
    if (other == *this || other > *this) {
        return true;
    }
    return false;
}

bool BigIntegerImp::operator>=(BigIntegerImp other) {
    if (other == *this || other < *this) {
        return true;
    }
    return false;
}