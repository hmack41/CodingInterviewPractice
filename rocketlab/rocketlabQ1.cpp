// C++ Software Engineering Interview Test 

// Task 1: Examine how you can succintly solve a numerical Problem using C++
// Write a C++ program that will complete the following steps:
// 1) Prompt the user to enter an integer from 0 to 99999999 

#include <iostream>
#include <vector> 
#include <cstdint>


class BigInt {
private:
    std::vector<uint8_t> digits;

public: 
    // Default Constructor
    BigInt() { digits.push_back(0); }

    // Constructor
    BigInt(int base, int power){
        if (power == 0) {
            digits.push_back(1);
            return;
        }
        if (base == 0) {
            digits.push_back(0);
            return;
        }
        digits.push_back(1);
        for (int i = 0; i < power; i++) {
            multiply(base);
        }
    }
    
    // Function Multiply: Multiplies two numbers the long way that we learned in school
    void multiply(int x){
        uint32_t carry = 0;
        for (std::size_t i = 0; i < digits.size(); i++) {
            uint32_t prod = digits[i] * static_cast<uint32_t>(x) + carry;
            digits[i] = static_cast<uint8_t>(prod % 10);
            carry = prod / 10;
        }
        while (carry) {
            digits.push_back(static_cast<uint8_t>(carry % 10));
            carry /= 10;
        }
    }
    // Print reversed digits
    void print() const {
        for (std::size_t i = digits.size(); i > 0; i--){
            std::cout << static_cast<int>(digits[i -1]);
        }
    }
};
class NumberUtility {
public:
// Function flip_number: Takes int input and returns an integer containing the input number flipped
    static int flip_number(int number_input){
        int final_digit;
        int flipped_number = 0;
        while(number_input > 0){
            final_digit = number_input % 10;
            flipped_number = (flipped_number *10) + final_digit;
            number_input /= 10;
        }
        return flipped_number;
    }
};

int main() {
    int number_input = -1;
    while (number_input < 0 || number_input > 99999){
        std::cout << "Enter a number (0-99999): ";
        std::cin >> number_input;
    }
    int flipped_number = NumberUtility::flip_number(number_input);
    std::cout << "Result: " << number_input << "^" <<flipped_number << " is...\n";
    BigInt result(number_input, flipped_number);
    result.print();
    return 0;
}