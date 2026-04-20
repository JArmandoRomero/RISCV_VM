#include "execute.hpp"
#include "alu.hpp"
#include <cstdint>

void execute(Instruction& instruction) {
    switch (instruction.aluop) {

        case AluOp::Nop:
            instruction.result = 0;
            break;

        case AluOp::Add:
            instruction.result = instruction.left + instruction.right;
            break;

        case AluOp::Sub:
            instruction.result = instruction.left - instruction.right;
            break;

        case AluOp::Mul:
            instruction.result = instruction.left * instruction.right;
            break;

        case AluOp::Div:
            if (instruction.right == 0)
                instruction.result = -1;
            else
                instruction.result = instruction.left / instruction.right;
            break;

        case AluOp::DivU:
            if (instruction.right == 0)
                instruction.result = -1;
            else
                instruction.result =
                    static_cast<uint32_t>(instruction.left) /
                    static_cast<uint32_t>(instruction.right);
            break;

        case AluOp::Rem:
            if (instruction.right == 0)
                instruction.result = instruction.left;
            else
                instruction.result = instruction.left % instruction.right;
            break;

        case AluOp::RemU:
            if (instruction.right == 0)
                instruction.result = instruction.left;
            else
                instruction.result =
                    static_cast<uint32_t>(instruction.left) %
                    static_cast<uint32_t>(instruction.right);
            break;

        case AluOp::LeftShift:
            instruction.result = instruction.left << instruction.right;
            break;

        case AluOp::RightShiftA:
            instruction.result = instruction.left >> instruction.right;
            break;

        case AluOp::RightShiftL:
            instruction.result =
                static_cast<uint32_t>(instruction.left) >> instruction.right;
            break;

        case AluOp::Or:
            instruction.result = instruction.left | instruction.right;
            break;

        case AluOp::Xor:
            instruction.result = instruction.left ^ instruction.right;
            break;

        case AluOp::And:
            instruction.result = instruction.left & instruction.right;
            break;

        case AluOp::Slt:
            instruction.result = (instruction.left < instruction.right) ? 1 : 0;
            break;

        case AluOp::SltU:
            instruction.result =
                (static_cast<uint32_t>(instruction.left) <
                 static_cast<uint32_t>(instruction.right)) ? 1 : 0;
            break;

        case AluOp::Cmp:
            if (instruction.left == instruction.right)
                instruction.result = 0b001;  // equal
            else if (instruction.left < instruction.right)
                instruction.result = 0b010;  // less than (signed)
            else
                instruction.result = 0b100;  // greater than (signed)
            break;
    }
}