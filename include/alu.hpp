#ifndef ALU_HPP
#define ALU_HPP

enum AluOp {
    Nop,
    Add,
    Sub,
    Mul,
    Div,
    DivU,
    Rem,
    RemU,
    LeftShift,
    RightShiftA,
    RightShiftL,
    Or,
    Xor,
    And,
    Slt,
    SltU,
    Cmp
};

#endif