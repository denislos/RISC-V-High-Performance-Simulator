#include <top/base_instruction.h>

Instruction::Instruction(std::string name, std::string type,
                         uint32 rd, uint32 rs1, uint32 rs2,
                         uint32 rs3, uint32 rm , int32 imm12,
                         int32 imm20, int32 jimm20, int32 storeimm,
                         int32 bimm, int32 aqrl, int32 shamt,
                         int32 shamtw, int32 pred, int32 succ,
                         int32 fm)
: name(name), type(type), rd(rd), rs1(rs1), rs2(rs2), rs3(rs3), rm(rm),
  imm12(imm12), imm20(imm20), jimm20(jimm20), storeimm(storeimm), bimm(bimm),
  aqrl(aqrl), shamt(shamt), shamtw(shamtw), pred(pred), succ(succ), fm(fm)
{}

