#include "execute.hpp"
#include "alu.hpp"

Instruction execute(Instruction instr)
{
    switch (instr.aluop)
    {
        case Nop:
            break;

        case Add:
            instr.result = instr.left + instr.right;
            break;

        case Sub:
            instr.result = instr.left - instr.right;
            break;

        case Mul:
            instr.result = instr.left * instr.right;
            break;

        case Div:
            if (instr.right != 0)
                instr.result = instr.left / instr.right;
            break;

        case DivU:
            if (instr.right != 0)
                instr.result = (uint32_t)instr.left / (uint32_t)instr.right;
            break;

        case Rem:
            if (instr.right != 0)
                instr.result = instr.left % instr.right;
            break;

        case RemU:
            if (instr.right != 0)
                instr.result = (uint32_t)instr.left % (uint32_t)instr.right;
            break;

        case LeftShift:
            instr.result = instr.left << (instr.right & 0x1F);
            break;

        case RightShiftA:
            instr.result = instr.left >> (instr.right & 0x1F);
            break;

        case RightShiftL:
            instr.result = (uint32_t)instr.left >> (instr.right & 0x1F);
            break;

        case Or:
            instr.result = instr.left | instr.right;
            break;

        case Xor:
            instr.result = instr.left ^ instr.right;
            break;

        case And:
            instr.result = instr.left & instr.right;
            break;

        case Slt:
            instr.result = (instr.left < instr.right);
            break;

        case SltU:
            instr.result = ((uint32_t)instr.left < (uint32_t)instr.right);
            break;

        case Cmp:
        {
            uint32_t res = 0;

            // bit 0: equal
            if (instr.left == instr.right)
                res |= (1 << 0);

            // bit 1: signed less than
            if (instr.left < instr.right)
                res |= (1 << 1);

            // bit 2: unsigned less than
            if ((uint32_t)instr.left < (uint32_t)instr.right)
                res |= (1 << 2);

            instr.result = res;
            break;
        }
    }

    return instr;
}