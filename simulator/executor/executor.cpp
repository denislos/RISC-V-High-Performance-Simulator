/**
 * executor.cpp - Implementation of Executor class
 */

#include <executor/executor.h>
#include <top/base_instruction.h>
#include <infra/utils.h>

const std::unordered_map<InstrType, Executor::Callback> Executor::callbacks = {
    #define DEFINSTR(name, mnemonic) \
        { Instr_Type_##name, execute_##name },

    #include <risc-v/risc-v-instructions.def>

        { Instr_Type_MAX, execute_dummy }

    #undef DEFINSTR
};


void Executor::assign_executor(Instruction* instr)
{
    instr->set_executor(callbacks.at(instr->get_type()));
}


void Executor::execute_beq(Instruction* instr) { 
    instr->is_taken = instr->v_src1 == instr->v_src2;
    instr->new_PC = instr->is_taken ? (instr->PC + instr->v_imm) : instr->PC;
}
void Executor::execute_bne(Instruction* instr) { 
    instr->is_taken = instr->v_src1 != instr->v_src2;
    instr->new_PC = instr->is_taken ? (instr->PC + instr->v_imm) : instr->PC;
}
void Executor::execute_blt(Instruction* instr) { 
    instr->is_taken = instr->v_src1 < instr->v_src2;
    instr->new_PC = instr->is_taken ? (instr->PC + instr->v_imm) : instr->PC;
}
void Executor::execute_bge(Instruction* instr) { 
    instr->is_taken = instr->v_src1 >= instr->v_src2;
    instr->new_PC = instr->is_taken ? (instr->PC + instr->v_imm) : instr->PC;
}
void Executor::execute_bltu(Instruction* instr) { 
    instr->is_taken = static_cast<uint32>(instr->v_src1) < static_cast<uint32>(instr->v_src2);
    instr->new_PC = instr->is_taken ? (instr->PC + instr->v_imm) : instr->PC;
}
void Executor::execute_bgeu(Instruction* instr) { 
    instr->is_taken = static_cast<uint32>(instr->v_src1) >= static_cast<uint32>(instr->v_src2);
    instr->new_PC = instr->is_taken ? (instr->PC + instr->v_imm) : instr->PC;
}
void Executor::execute_jalr(Instruction* instr) {
    instr->is_taken = true;
    instr->target = instr->new_PC = (instr->v_src1 + instr->v_imm) & (-2);
    instr->v_dst = instr->PC + 4;
 }
void Executor::execute_jal(Instruction* instr) { 
    instr->is_taken = true;
    instr->new_PC = instr->PC + instr->v_imm;
    instr->v_dst = instr->PC + 4;
}
void Executor::execute_lui(Instruction* instr) { 
    instr->v_dst = (instr->v_imm << 12);
}
void Executor::execute_auipc(Instruction* instr) { 
    instr->v_dst = instr->PC + (instr->v_imm << 12);
}
void Executor::execute_addi(Instruction* instr) { 
    instr->v_dst = instr->v_src1 + instr->v_imm;
}
void Executor::execute_slli(Instruction* instr) { 
    instr->v_dst = (static_cast<uint32>(instr->v_src1) << static_cast<uint32>(instr->v_imm));
}
void Executor::execute_slti(Instruction* instr) { 
    instr->v_dst = instr->v_src1 < instr->v_imm;
}
void Executor::execute_sltiu(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) < static_cast<uint32>(instr->v_imm);
}
void Executor::execute_xori(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) ^ static_cast<uint32>(instr->v_imm);
}
void Executor::execute_srli(Instruction* instr) { 
    instr->v_dst = (static_cast<uint32>(instr->v_src1) >> static_cast<uint32>(instr->v_imm)); 
}
void Executor::execute_srai(Instruction* instr) { 
    instr->v_dst = (instr->v_src1 >> instr->v_imm); 
}
void Executor::execute_ori(Instruction* instr) { 
    instr->v_dst = instr->v_src1 | instr->v_imm;
}
void Executor::execute_andi(Instruction* instr) { 
    instr->v_dst = instr->v_src1 & instr->v_imm;
}
void Executor::execute_add(Instruction* instr) { 
    instr->v_dst = instr->v_src1 + instr->v_src2;
}
void Executor::execute_sub(Instruction* instr) { 
    instr->v_dst = instr->v_src1 - instr->v_src2;
}
void Executor::execute_sll(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) << instr->v_src2;
}
void Executor::execute_slt(Instruction* instr) { 
    instr->v_dst = instr->v_src1 < instr->v_src2;
}
void Executor::execute_sltu(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) < static_cast<uint32>(instr->v_src2);
}
void Executor::execute_xor(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) ^ static_cast<uint32>(instr->v_src2);
}
void Executor::execute_srl(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) >> instr->v_src2;
}
void Executor::execute_sra(Instruction* instr) { 
    instr->v_dst = instr->v_src1 >> instr->v_src2;
}
void Executor::execute_or(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) | static_cast<uint32>(instr->v_src2);
}
void Executor::execute_and(Instruction* instr) { 
    instr->v_dst = static_cast<uint32>(instr->v_src1) & static_cast<uint32>(instr->v_src2);
}
void Executor::execute_addiw(Instruction* instr) { }
void Executor::execute_slliw(Instruction* instr) { }
void Executor::execute_srliw(Instruction* instr) { }
void Executor::execute_sraiw(Instruction* instr) { }
void Executor::execute_addw(Instruction* instr) { }
void Executor::execute_subw(Instruction* instr) { }
void Executor::execute_sllw(Instruction* instr) { }
void Executor::execute_srlw(Instruction* instr) { }
void Executor::execute_sraw(Instruction* instr) { }
void Executor::execute_lb(Instruction* instr) { }
void Executor::execute_lh(Instruction* instr) { }
void Executor::execute_lw(Instruction* instr) { 
    instr->mem_access_size = 4;
    instr->mem_addr = instr->v_src1 + instr->v_imm;
    instr->is_memory_read = true;
}
void Executor::execute_ld(Instruction* instr) { }
void Executor::execute_lbu(Instruction* instr) { }
void Executor::execute_lhu(Instruction* instr) { }
void Executor::execute_lwu(Instruction* instr) { }
void Executor::execute_sb(Instruction* instr) { }
void Executor::execute_sh(Instruction* instr) { }
void Executor::execute_sw(Instruction* instr) { 
    instr->mem_access_size = 4;
    instr->mem_addr = instr->v_src1 + instr->v_imm;
    instr->store_data = instr->v_src2;
    instr->is_memory_write = true;
}
void Executor::execute_sd(Instruction* instr) { }
void Executor::execute_fence(Instruction* instr) { }
void Executor::execute_fence_i(Instruction* instr) { }
void Executor::execute_mul(Instruction* instr) { }
void Executor::execute_mulh(Instruction* instr) { }
void Executor::execute_mulhsu(Instruction* instr) { }
void Executor::execute_mulhu(Instruction* instr) { }
void Executor::execute_div(Instruction* instr) { }
void Executor::execute_divu(Instruction* instr) { }
void Executor::execute_rem(Instruction* instr) { }
void Executor::execute_remu(Instruction* instr) { }
void Executor::execute_mulw(Instruction* instr) { }
void Executor::execute_divw(Instruction* instr) { }
void Executor::execute_divuw(Instruction* instr) { }
void Executor::execute_remw(Instruction* instr) { }
void Executor::execute_remuw(Instruction* instr) { }
void Executor::execute_amoadd_w(Instruction* instr) { }
void Executor::execute_amoxor_w(Instruction* instr) { }
void Executor::execute_amoor_w(Instruction* instr) { }
void Executor::execute_amoand_w(Instruction* instr) { }
void Executor::execute_amomin_w(Instruction* instr) { }
void Executor::execute_amomax_w(Instruction* instr) { }
void Executor::execute_amominu_w(Instruction* instr) { }
void Executor::execute_amomaxu_w(Instruction* instr) { }
void Executor::execute_amoswap_w(Instruction* instr) { }
void Executor::execute_lr_w(Instruction* instr) { }
void Executor::execute_sc_w(Instruction* instr) { }
void Executor::execute_amoadd_d(Instruction* instr) { }
void Executor::execute_amoxor_d(Instruction* instr) { }
void Executor::execute_amoor_d(Instruction* instr) { }
void Executor::execute_amoand_d(Instruction* instr) { }
void Executor::execute_amomin_d(Instruction* instr) { }
void Executor::execute_amomax_d(Instruction* instr) { }
void Executor::execute_amominu_d(Instruction* instr) { }
void Executor::execute_amomaxu_d(Instruction* instr) { }
void Executor::execute_amoswap_d(Instruction* instr) { }
void Executor::execute_lr_d(Instruction* instr) { }
void Executor::execute_sc_d(Instruction* instr) { }
void Executor::execute_ecall(Instruction* instr) { }
void Executor::execute_ebreak(Instruction* instr) { }
void Executor::execute_uret(Instruction* instr) { }
void Executor::execute_sret(Instruction* instr) { }
void Executor::execute_mret(Instruction* instr) { }
void Executor::execute_dret(Instruction* instr) { }
void Executor::execute_sfence_vma(Instruction* instr) { }
void Executor::execute_wfi(Instruction* instr) { }
void Executor::execute_csrrw(Instruction* instr) { }
void Executor::execute_csrrs(Instruction* instr) { }
void Executor::execute_csrrc(Instruction* instr) { }
void Executor::execute_csrrwi(Instruction* instr) { }
void Executor::execute_csrrsi(Instruction* instr) { }
void Executor::execute_csrrci(Instruction* instr) { }
void Executor::execute_hfence_vvma(Instruction* instr) { }
void Executor::execute_hfence_gvma(Instruction* instr) { }
void Executor::execute_fadd_s(Instruction* instr) { }
void Executor::execute_fsub_s(Instruction* instr) { }
void Executor::execute_fmul_s(Instruction* instr) { }
void Executor::execute_fdiv_s(Instruction* instr) { }
void Executor::execute_fsgnj_s(Instruction* instr) { }
void Executor::execute_fsgnjn_s(Instruction* instr) { }
void Executor::execute_fsgnjx_s(Instruction* instr) { }
void Executor::execute_fmin_s(Instruction* instr) { }
void Executor::execute_fmax_s(Instruction* instr) { }
void Executor::execute_fsqrt_s(Instruction* instr) { }
void Executor::execute_fadd_d(Instruction* instr) { }
void Executor::execute_fsub_d(Instruction* instr) { }
void Executor::execute_fmul_d(Instruction* instr) { }
void Executor::execute_fdiv_d(Instruction* instr) { }
void Executor::execute_fsgnj_d(Instruction* instr) { }
void Executor::execute_fsgnjn_d(Instruction* instr) { }
void Executor::execute_fsgnjx_d(Instruction* instr) { }
void Executor::execute_fmin_d(Instruction* instr) { }
void Executor::execute_fmax_d(Instruction* instr) { }
void Executor::execute_fcvt_s_d(Instruction* instr) { }
void Executor::execute_fcvt_d_s(Instruction* instr) { }
void Executor::execute_fsqrt_d(Instruction* instr) { }
void Executor::execute_fadd_q(Instruction* instr) { }
void Executor::execute_fsub_q(Instruction* instr) { }
void Executor::execute_fmul_q(Instruction* instr) { }
void Executor::execute_fdiv_q(Instruction* instr) { }
void Executor::execute_fsgnj_q(Instruction* instr) { }
void Executor::execute_fsgnjn_q(Instruction* instr) { }
void Executor::execute_fsgnjx_q(Instruction* instr) { }
void Executor::execute_fmin_q(Instruction* instr) { }
void Executor::execute_fmax_q(Instruction* instr) { }
void Executor::execute_fcvt_s_q(Instruction* instr) { }
void Executor::execute_fcvt_q_s(Instruction* instr) { }
void Executor::execute_fcvt_d_q(Instruction* instr) { }
void Executor::execute_fcvt_q_d(Instruction* instr) { }
void Executor::execute_fsqrt_q(Instruction* instr) { }
void Executor::execute_fle_s(Instruction* instr) { }
void Executor::execute_flt_s(Instruction* instr) { }
void Executor::execute_feq_s(Instruction* instr) { }
void Executor::execute_fle_d(Instruction* instr) { }
void Executor::execute_flt_d(Instruction* instr) { }
void Executor::execute_feq_d(Instruction* instr) { }
void Executor::execute_fle_q(Instruction* instr) { }
void Executor::execute_flt_q(Instruction* instr) { }
void Executor::execute_feq_q(Instruction* instr) { }
void Executor::execute_fcvt_w_s(Instruction* instr) { }
void Executor::execute_fcvt_wu_s(Instruction* instr) { }
void Executor::execute_fcvt_l_s(Instruction* instr) { }
void Executor::execute_fcvt_lu_s(Instruction* instr) { }
void Executor::execute_fmv_x_w(Instruction* instr) { }
void Executor::execute_fclass_s(Instruction* instr) { }
void Executor::execute_fcvt_w_d(Instruction* instr) { }
void Executor::execute_fcvt_wu_d(Instruction* instr) { }
void Executor::execute_fcvt_l_d(Instruction* instr) { }
void Executor::execute_fcvt_lu_d(Instruction* instr) { }
void Executor::execute_fmv_x_d(Instruction* instr) { }
void Executor::execute_fclass_d(Instruction* instr) { }
void Executor::execute_fcvt_w_q(Instruction* instr) { }
void Executor::execute_fcvt_wu_q(Instruction* instr) { }
void Executor::execute_fcvt_l_q(Instruction* instr) { }
void Executor::execute_fcvt_lu_q(Instruction* instr) { }
void Executor::execute_fmv_x_q(Instruction* instr) { }
void Executor::execute_fclass_q(Instruction* instr) { }
void Executor::execute_fcvt_s_w(Instruction* instr) { }
void Executor::execute_fcvt_s_wu(Instruction* instr) { }
void Executor::execute_fcvt_s_l(Instruction* instr) { }
void Executor::execute_fcvt_s_lu(Instruction* instr) { }
void Executor::execute_fmv_w_x(Instruction* instr) { }
void Executor::execute_fcvt_d_w(Instruction* instr) { }
void Executor::execute_fcvt_d_wu(Instruction* instr) { }
void Executor::execute_fcvt_d_l(Instruction* instr) { }
void Executor::execute_fcvt_d_lu(Instruction* instr) { }
void Executor::execute_fmv_d_x(Instruction* instr) { }
void Executor::execute_fcvt_q_w(Instruction* instr) { }
void Executor::execute_fcvt_q_wu(Instruction* instr) { }
void Executor::execute_fcvt_q_l(Instruction* instr) { }
void Executor::execute_fcvt_q_lu(Instruction* instr) { }
void Executor::execute_fmv_q_x(Instruction* instr) { }
void Executor::execute_flw(Instruction* instr) { }
void Executor::execute_fld(Instruction* instr) { }
void Executor::execute_flq(Instruction* instr) { }
void Executor::execute_fsw(Instruction* instr) { }
void Executor::execute_fsd(Instruction* instr) { }
void Executor::execute_fsq(Instruction* instr) { }
void Executor::execute_fmadd_s(Instruction* instr) { }
void Executor::execute_fmsub_s(Instruction* instr) { }
void Executor::execute_fnmsub_s(Instruction* instr) { }
void Executor::execute_fnmadd_s(Instruction* instr) { }
void Executor::execute_fmadd_d(Instruction* instr) { }
void Executor::execute_fmsub_d(Instruction* instr) { }
void Executor::execute_fnmsub_d(Instruction* instr) { }
void Executor::execute_fnmadd_d(Instruction* instr) { }
void Executor::execute_fmadd_q(Instruction* instr) { }
void Executor::execute_fmsub_q(Instruction* instr) { }
void Executor::execute_fnmsub_q(Instruction* instr) { }
void Executor::execute_fnmadd_q(Instruction* instr) { }


void Executor::execute_dummy(Instruction* instr) { }