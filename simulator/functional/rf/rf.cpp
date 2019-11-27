/**
 * rf.cpp - Implementation of RF class
 */

#include <tuple>


#include <functional/rf/rf.h>


void RF::read_sources(std::shared_ptr<Instruction> instr) const
{
    const auto src1 = instr->get_src(0);
    const auto src2 = instr->get_src(1);
    const auto src3 = instr->get_src(2);

    if (src1.is_valid())
        instr->set_src1_value(register_array.at(src1.to_rf_index()));
    
    if (src2.is_valid())
        instr->set_src2_value(register_array.at(src2.to_rf_index()));

    if (src3.is_valid())
        instr->set_src3_value(register_array.at(src3.to_rf_index()));
}


void RF::write_dst(std::shared_ptr<Instruction> instr)
{
    const auto dst = instr->get_dst();

    if (dst.is_valid() && !dst.is_zero())
        register_array[dst.to_rf_index()] = instr->get_dst_value();
}