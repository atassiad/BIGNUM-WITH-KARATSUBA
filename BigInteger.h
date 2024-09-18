//
// Created by Athanasios Tassiadamis
//
//Note: Must be using GCC compiler as certain functions are implementation-defined

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <iostream>

class BigIntegerImp {
private:
    std::string integerAsString; //string used to represent large-digit integers

public:
    //constructors and destructor
    BigIntegerImp();
    explicit BigIntegerImp(std::string integer);
    ~BigIntegerImp() = default;

    //assignment operator overload
    BigIntegerImp& operator=(BigIntegerImp const &other);

    //arithmetic operator overloads
    BigIntegerImp operator+(BigIntegerImp other); //adds two objects using stringAddition helper function
    BigIntegerImp operator-(BigIntegerImp other); //subtracts two objects using stringSubtraction helper function
    BigIntegerImp operator*(BigIntegerImp other); //multiplies two objects using karatsuba helper function
    BigIntegerImp operator/(BigIntegerImp other); //divides two objects using stringDivision
    BigIntegerImp operator%(BigIntegerImp other);

    //logical operator overloads
    bool operator<(BigIntegerImp other);
    bool operator>(BigIntegerImp other);
    bool operator==(BigIntegerImp &other);
    bool operator<=(BigIntegerImp other);
    bool operator>=(BigIntegerImp other);


    //ostream overload
    friend std::ostream& operator<<(std::ostream &os, const BigIntegerImp &other);

    //getter and setter functions
    std::string getBigIntAsString(); //returns integerAsString as a string
    void setBigInt(std::string); //sets integerAsString to a passed string value

    //helper functions
    void prependZeros(BigIntegerImp &bObj); //prepends zeroes to make length of this.integerAsString and bObj.integerAsString same
    void prependZeros(std::string &sObj1, std::string &sObj2); //prepends zeroes to smaller string to match string lengths
    static bool checkIfStringNumeric(const std::string&); //ensures string is only numbers
    static void removeLeadingZeros(BigIntegerImp &bObj); //removes leading zeroes by calling same function w/ string param
    static void removeLeadingZeros(std::string&);
    std::string karatsuba(std::string, std::string); //used by * operator overload for large digit multiplication
    std::string stringAddition(std::string &s1, std::string &s2); //adds two strings
    std::string stringSubtraction(std::string, std::string); //subtracts two strings
    std::string stringDivision(std::string, std::string); //divides two strings, utilizes subtraction and addition helper functions
};


#endif //BIGINTEGER_H
