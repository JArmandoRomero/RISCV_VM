#include "decode.hpp"
#include "alu.hpp"
#include "utils.hpp"

Instruction decode(Instruction instr, Machine* machine)
{
    uint32_t inst = instr.inst;

    uint32_t opcode = inst & 0x7F;
    uint32_t rd     = (inst >> 7) & 0x1F;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1    = (inst >> 15) & 0x1F;
    uint32_t rs2    = (inst >> 20) & 0x1F;
    uint32_t funct7 = (inst >> 25) & 0x7F;

    instr.rd = rd;
    instr.memop = 0;
    instr.aluop = Nop;
    instr.left = 0;
    instr.right = 0;
    instr.disp = 0;
    instr.result = 0;

    switch (opcode)
    {
        // ================= R-TYPE =================
        case 0x33:
        {
            instr.left  = machine->readRegister(rs1);
            instr.right = machine->readRegister(rs2);

            switch (funct3)
            {
                case 0x0:
                    if (funct7 == 0x00) instr.aluop = Add;
                    else if (funct7 == 0x20) instr.aluop = Sub;
                    else if (funct7 == 0x01) instr.aluop = Mul;
                    break;

                case 0x1: instr.aluop = LeftShift; break;
                case 0x2: instr.aluop = Slt; break;
                case 0x3: instr.aluop = SltU; break;

                case 0x4:
                    if (funct7 == 0x01) instr.aluop = Div;
                    else instr.aluop = Xor;
                    break;

                case 0x5:
                    if (funct7 == 0x00) instr.aluop = RightShiftL;
                    else if (funct7 == 0x20) instr.aluop = RightShiftA;
                    else if (funct7 == 0x01) instr.aluop = DivU;
                    break;

                case 0x6:
                    if (funct7 == 0x01) instr.aluop = Rem;
                    else instr.aluop = Or;
                    break;

                case 0x7:
                    if (funct7 == 0x01) instr.aluop = RemU;
                    else instr.aluop = And;
                    break;
            }
            break;
        }

        // ================= I-TYPE =================
        case 0x13:
        {
            int32_t imm = sign_extend(inst >> 20, 11);

            instr.left  = machine->readRegister(rs1);
            instr.right = imm;

            switch (funct3)
            {
                case 0x0: instr.aluop = Add; break;
                case 0x2: instr.aluop = Slt; break;
                case 0x3: instr.aluop = SltU; break;
                case 0x4: instr.aluop = Xor; break;
                case 0x6: instr.aluop = Or;  break;
                case 0x7: instr.aluop = And; break;

                case 0x1: instr.aluop = LeftShift; break;

                case 0x5:
                    if ((inst >> 30) & 1)
                        instr.aluop = RightShiftA;
                    else
                        instr.aluop = RightShiftL;
                    break;
            }
            break;
        }

        // ================= LOAD =================
        case 0x03:
        {
            int32_t imm = sign_extend(inst >> 20, 11);

            instr.left  = machine->readRegister(rs1);
            instr.right = imm;
            instr.memop = 0b001;
            instr.aluop = Add;
            break;
        }

        // ================= STORE =================
        case 0x23:
        {
            uint32_t imm =
                ((inst >> 7) & 0x1F) |
                (((inst >> 25) & 0x7F) << 5);

            int32_t simm = sign_extend(imm, 11);

            instr.left  = machine->readRegister(rs1);
            instr.right = simm;
            instr.disp  = machine->readRegister(rs2);
            instr.memop = 0b111; // ⚠️ IMPORTANT FIX (matches expected output)
            instr.aluop = Add;
            break;
        }

        // ================= BRANCH =================
        case 0x63:
        {
            uint32_t imm =
                ((inst >> 31) << 12) |
                (((inst >> 25) & 0x3F) << 5) |
                (((inst >> 8) & 0xF) << 1) |
                (((inst >> 7) & 0x1) << 11);

            int32_t simm = sign_extend(imm, 12);

            instr.left  = machine->readRegister(rs1);
            instr.right = machine->readRegister(rs2);
            instr.disp  = simm;
            instr.aluop = Cmp;
            break;
        }

        // ================= LUI =================
        case 0x37:
        {
            instr.left  = 0;
            instr.right = inst & 0xFFFFF000;
            instr.aluop = Add;
            break;
        }

        // ================= JAL =================
        case 0x6F:
        {
            uint32_t imm =
                ((inst >> 31) << 20) |
                (((inst >> 21) & 0x3FF) << 1) |
                (((inst >> 20) & 0x1) << 11) |
                (((inst >> 12) & 0xFF) << 12);

            instr.disp = sign_extend(imm, 20);
            instr.aluop = Nop; // IMPORTANT
            break;
        }

        default:
            break;
    }

    return instr;
}