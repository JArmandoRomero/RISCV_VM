#include <iostream>

#include "execute.hpp"
#include "alu.hpp"
#include "instruction.hpp"
#include <bitset>


std::string_view to_string(AluOp aluop) {
    switch (aluop) {
        case AluOp::Nop:   return "Nop";
        case AluOp::Add:   return "Add";
        case AluOp::Sub:   return "Sub";
        case AluOp::Mul:   return "Mul";
        case AluOp::Div:   return "Div";
        case AluOp::DivU:   return "DivU";
        case AluOp::Rem:   return "Rem";
        case AluOp::RemU:   return "RemU";
        case AluOp::LeftShift:   return "LeftShift";
        case AluOp::RightShiftA:   return "RightShiftA";
        case AluOp::RightShiftL:   return "RightShiftL";
        case AluOp::Or:   return "Or";
        case AluOp::Xor:   return "Xor";
        case AluOp::And:   return "And";
        case AluOp::Slt:   return "Slt";
        case AluOp::SltU:   return "SltU";
        case AluOp::Cmp:   return "Cmp";
    }
    return "Unknown";
}


void test_execute() {
    std::cout << "\nTesting Execute" << std::endl;
    std::cout << "===============\n" << std::endl;

    Instruction instruction{};

    // Test No Op
    instruction.left = 42;
    instruction.right = 8;
    instruction.aluop = AluOp::Nop;
    execute(instruction);
    std::cout << "Test No Op:" << std::endl;
    std::cout << "\tLeft: " << instruction.left << std::endl;
    std::cout << "\tRight: " << instruction.right << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult: " << instruction.result << std::endl;
    std::cout << "\tResult Should Be: 0 " << std::endl;

    // Test Addition
    instruction.left = 42;
    instruction.right = 8;
    instruction.aluop = AluOp::Add;
    execute(instruction);
    std::cout << "Test Add:" << std::endl;
    std::cout << "\tLeft: " << instruction.left << std::endl;
    std::cout << "\tRight: " << instruction.right << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult: " << instruction.result << std::endl;
    std::cout << "\tResult Should Be: 50 " << std::endl;

    // Test Subtract 
    // - Larger Left
    std::cout << "Test Subtract:" << std::endl;
    instruction.left = 42;
    instruction.right = 8;
    instruction.aluop = AluOp::Sub;
    execute(instruction);
    std::cout << "\tLarger Left:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 34" << std::endl;
    // - Larger Right
    instruction.left = 8;
    instruction.right = 42;
    instruction.aluop = AluOp::Sub;
    execute(instruction);
    std::cout << "\tLarger Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: -34" << std::endl;
    // Test Multiply
    instruction.left = 5;
    instruction.right = 4;
    instruction.aluop = AluOp::Mul;
    execute(instruction);
    std::cout << "Test Multiply:" << std::endl;
    std::cout << "\tLeft: " << instruction.left << std::endl;
    std::cout << "\tRight: " << instruction.right << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult: " << instruction.result << std::endl;
    std::cout << "\tResult Should Be: 20" << std::endl;
    // Test Divide 
    std::cout << "Test Divide:" << std::endl;
    // - Test positive left and right resulting in whole number
    instruction.left = 10;
    instruction.right = 2;
    instruction.aluop = AluOp::Div;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in whole number:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 5" << std::endl;
    // - Test positive left and right resulting in fraction 
    instruction.left = 5;
    instruction.right = 2;
    instruction.aluop = AluOp::Div;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in fraction:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 2" << std::endl;
    // - Test zero left
    instruction.left = 0;
    instruction.right = 2;
    instruction.aluop = AluOp::Div;
    execute(instruction);
    std::cout << "\tZero left:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test zero right
    instruction.left = 5;
    instruction.right = 0;
    instruction.aluop = AluOp::Div;
    execute(instruction);
    std::cout << "\tZero right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: -1" << std::endl;
    // - Test negative left, positive right 
    instruction.left = -10;
    instruction.right = 2;
    instruction.aluop = AluOp::Div;
    execute(instruction);
    std::cout << "\tNegative left, positive right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: -5" << std::endl;
    // Test Divide Unsigned
    std::cout << "Test Divide Unsigned:" << std::endl;
    // - Test positive left and right resulting in whole number
    instruction.left = 10;
    instruction.right = 2;
    instruction.aluop = AluOp::DivU;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in whole number:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 5" << std::endl;
    // - Test positive left and right resulting in fraction 
    instruction.left = 5;
    instruction.right = 2;
    instruction.aluop = AluOp::DivU;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in fraction:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 2" << std::endl;
    // - Test zero left
    instruction.left = 0;
    instruction.right = 2;
    instruction.aluop = AluOp::DivU;
    execute(instruction);
    std::cout << "\tZero left:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test zero right
    instruction.left = 5;
    instruction.right = 0;
    instruction.aluop = AluOp::DivU;
    execute(instruction);
    std::cout << "\tZero right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: -1" << std::endl;
    // - Test negative left, positive right 
    instruction.left = -10;
    instruction.right = 2;
    instruction.aluop = AluOp::DivU;
    execute(instruction);
    std::cout << "\tNegative left, positive right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 2147483643" << std::endl;
    // Test Reminder 
    std::cout << "Test Remainder:" << std::endl;
    // - Test positive left and right resulting in whole number
    instruction.left = 10;
    instruction.right = 2;
    instruction.aluop = AluOp::Rem;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in whole number:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test positive left and right resulting in fraction 
    instruction.left = 5;
    instruction.right = 2;
    instruction.aluop = AluOp::Rem;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in fraction:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 1" << std::endl;
    // - Test zero left
    instruction.left = 0;
    instruction.right = 2;
    instruction.aluop = AluOp::Rem;
    execute(instruction);
    std::cout << "\tZero left:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test zero right
    instruction.left = 5;
    instruction.right = 0;
    instruction.aluop = AluOp::Rem;
    execute(instruction);
    std::cout << "\tZero right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 5" << std::endl;
    // - Test negative left, positive right 
    instruction.left = -10;
    instruction.right = 4;
    instruction.aluop = AluOp::Rem;
    execute(instruction);
    std::cout << "\tNegative left, positive right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: -2" << std::endl;
    // Test Reminder Unsigned
    std::cout << "Test Remainder Unsigned:" << std::endl;
    // - Test positive left and right resulting in whole number
    instruction.left = 10;
    instruction.right = 2;
    instruction.aluop = AluOp::RemU;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in whole number:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test positive left and right resulting in fraction 
    instruction.left = 5;
    instruction.right = 2;
    instruction.aluop = AluOp::RemU;
    execute(instruction);
    std::cout << "\tPositive left and right resulting in fraction:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 1" << std::endl;
    // - Test zero left
    instruction.left = 0;
    instruction.right = 2;
    instruction.aluop = AluOp::RemU;
    execute(instruction);
    std::cout << "\tZero left:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test zero right
    instruction.left = 5;
    instruction.right = 0;
    instruction.aluop = AluOp::RemU;
    execute(instruction);
    std::cout << "\tZero right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 5" << std::endl;
    // - Test negative left, positive right 
    instruction.left = -10;
    instruction.right = 4;
    instruction.aluop = AluOp::RemU;
    execute(instruction);
    std::cout << "\tNegative left, positive right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 2" << std::endl;
    // Test Left Shift Logical
    instruction.left = 15;
    instruction.right = 2;
    instruction.aluop = AluOp::LeftShift;
    execute(instruction);
    std::cout << "Test Left Shift Logical:" << std::endl;
    std::cout << "\tLeft: " << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\tRight: " << instruction.right << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\tResult Should Be: 00000000000000000000000000111100" << std::endl;
    // Test Right Shift Arithmetic 
    std::cout << "Test Right Shift Arithmetic:" << std::endl;
    // - Test positive leading bit
    instruction.left = 15;
    instruction.right = 2;
    instruction.aluop = AluOp::RightShiftA;
    execute(instruction);
    std::cout << "\tPositive leading bit:" << std::endl;
    std::cout << "\t\tLeft: " << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 00000000000000000000000000000011" << std::endl;
    // - Test negative leading bit
    instruction.left = -15;
    instruction.right = 2;
    instruction.aluop = AluOp::RightShiftA;
    execute(instruction);
    std::cout << "\tNegative leading bit:" << std::endl;
    std::cout << "\t\tLeft: " << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 11111111111111111111111111111100" << std::endl;
    // Test Right Shift Logical
    std::cout << "Test Right Shift Logical:" << std::endl;
    // - Test positive leading bit
    instruction.left = 15;
    instruction.right = 2;
    instruction.aluop = AluOp::RightShiftL;
    execute(instruction);
    std::cout << "\tPositive leading bit:" << std::endl;
    std::cout << "\t\tLeft: " << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 00000000000000000000000000000011" << std::endl;
    // - Test negative leading bit
    instruction.left = -15;
    instruction.right = 2;
    instruction.aluop = AluOp::RightShiftL;
    execute(instruction);
    std::cout << "\tNegative leading bit:" << std::endl;
    std::cout << "\t\tLeft: " << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 00111111111111111111111111111100" << std::endl;
    // Test OR
    instruction.left = 0b00000000000000000000000000111100;
    instruction.right = 0b00000000000000000000000000001111;
    instruction.aluop = AluOp::Or;
    execute(instruction);
    std::cout << "Test OR:" << std::endl;
    std::cout << "\tLeft:\t" << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\tRight:\t" << std::bitset<32>(instruction.right) << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\tResult Should Be: 00000000000000000000000000111111" << std::endl;
    // Test XOR
    instruction.left = 0b00000000000000000000000000111100;
    instruction.right = 0b00000000000000000000000000001111;
    instruction.aluop = AluOp::Xor;
    execute(instruction);
    std::cout << "Test XOR:" << std::endl;
    std::cout << "\tLeft:\t" << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\tRight:\t" << std::bitset<32>(instruction.right) << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\tResult Should Be: 00000000000000000000000000110011" << std::endl;
    // Test AND
    instruction.left = 0b00000000000000000000000000111100;
    instruction.right = 0b00000000000000000000000000001111;
    instruction.aluop = AluOp::And;
    execute(instruction);
    std::cout << "Test AND:" << std::endl;
    std::cout << "\tLeft:\t" << std::bitset<32>(instruction.left) << std::endl;
    std::cout << "\tRight:\t" << std::bitset<32>(instruction.right) << std::endl;
    std::cout << "\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\tResult:           " << std::bitset<32>(instruction.result) << std::endl;
    std::cout << "\tResult Should Be: 00000000000000000000000000001100" << std::endl;
    // Test Set Less Than
    std::cout << "Test Set Less Than:" << std::endl;
    // - Test less than 
    instruction.left = 15;
    instruction.right = 42;
    instruction.aluop = AluOp::Slt;
    execute(instruction);
    std::cout << "\tLeft Less Than Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 1" << std::endl;
    // - Test greater than 
    instruction.left = 42;
    instruction.right = 15;
    instruction.aluop = AluOp::Slt;
    execute(instruction);
    std::cout << "\tLeft Greater Than Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test equal to 
    instruction.left = 42;
    instruction.right = 42;
    instruction.aluop = AluOp::Slt;
    execute(instruction);
    std::cout << "\tLeft Equal to Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test negative vals 
    instruction.left = -42;
    instruction.right = 42;
    instruction.aluop = AluOp::Slt;
    execute(instruction);
    std::cout << "\tLeft Negative:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 1" << std::endl;
    // Test Set Less Than Unsigned
    std::cout << "Test Set Less Than Unsigned:" << std::endl;
    // - Test less than 
    instruction.left = 15;
    instruction.right = 42;
    instruction.aluop = AluOp::SltU;
    execute(instruction);
    std::cout << "\tLeft Less Than Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 1" << std::endl;
    // - Test greater than 
    instruction.left = 42;
    instruction.right = 15;
    instruction.aluop = AluOp::SltU;
    execute(instruction);
    std::cout << "\tLeft Greater Than Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test equal to 
    instruction.left = 42;
    instruction.right = 42;
    instruction.aluop = AluOp::SltU;
    execute(instruction);
    std::cout << "\tLeft Equal to Right:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // - Test negative vals 
    instruction.left = -42;
    instruction.right = 42;
    instruction.aluop = AluOp::SltU;
    execute(instruction);
    std::cout << "\tLeft Negative:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult: " << instruction.result << std::endl;
    std::cout << "\t\tResult Should Be: 0" << std::endl;
    // Test Compare
    std::cout << "Test Compare:" << std::endl;
    // - Test equals
    instruction.left = 15;
    instruction.right = 15;
    instruction.aluop = AluOp::Cmp;
    execute(instruction);
    std::cout << "\tTest Equals:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<3>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 001" << std::endl;
    // - Test less than
    instruction.left = -15;
    instruction.right = 15;
    instruction.aluop = AluOp::Cmp;
    execute(instruction);
    std::cout << "\tTest Less Than Signed and Greater Than Unsigned:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<3>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 010" << std::endl;
    // - Test greater than
    instruction.left = 15;
    instruction.right = -15;
    instruction.aluop = AluOp::Cmp;
    execute(instruction);
    std::cout << "\tTest Grreater Than Signed and Less Than Unsigned:" << std::endl;
    std::cout << "\t\tLeft: " << instruction.left << std::endl;
    std::cout << "\t\tRight: " << instruction.right << std::endl;
    std::cout << "\t\tAluOp: " << to_string(instruction.aluop) << std::endl;
    std::cout << "\t\tResult:           " << std::bitset<3>(instruction.result) << std::endl;
    std::cout << "\t\tResult Should Be: 100" << std::endl;
}


int main()
{
    test_execute();

    return 0;
}

