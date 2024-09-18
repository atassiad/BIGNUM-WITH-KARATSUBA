#include <iostream>
#include "BigInteger.h"

//driver code
int main() {
    std::cout << "--- TEST 1 ---\n";
    BigIntegerImp a("9999");
    BigIntegerImp b("1000");

    std:: cout << a << " + " << b << " = " << a + b << std::endl;
    std:: cout << a << " - " << b << " = " << a - b << std::endl;
    std:: cout << a << " * " << b << " = " << a * b << std::endl;
    std:: cout << a << " / " << b << " = " << a / b << std::endl;
    std::cout << a << " % " << b << " = " << a % b <<std::endl;

    std::cout << "--- TEST 2 ---\n";
    a.setBigInt("789798");
    b.setBigInt("0");

    std:: cout << a << " + " << b << " = " << a + b << std::endl;
    std:: cout << a << " - " << b << " = " << a - b << std::endl;
    std:: cout << a << " * " << b << " = " << a * b << std::endl;
    std:: cout << a << " / " << b << " = " << a / b << std::endl;
    std::cout << a << " % " << b << " = " << a % b <<std::endl;

    std::cout << "--- TEST 3 ---\n";
    a.setBigInt("4273895632498573249865983245");
    b.setBigInt("81032751728057810239085902");

    std:: cout << a << " + " << b << " = " << a + b << std::endl;
    std:: cout << a << " - " << b << " = " << a - b << std::endl;
    std:: cout << a << " * " << b << " = " << a * b << std::endl;
    std:: cout << a << " / " << b << " = " << a / b << std::endl;
    std::cout << a << " % " << b << " = " << a % b <<std::endl;

    return 0;
}

