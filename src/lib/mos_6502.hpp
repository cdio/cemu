/*
 * Copyright (C) 2020-2022 Claudio Castiglia
 *
 * This file is part of CAIO.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see http://www.gnu.org/licenses/
 */
#pragma once

#include <array>
#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <utility>

#include "aspace.hpp"
#include "clock.hpp"
#include "logger.hpp"
#include "name.hpp"
#include "pin.hpp"
#include "types.hpp"
#include "utils.hpp"

#include "mos_6502_monitor.hpp"


namespace caio {

/**
 * MOS 6502 emulator.
 */
class Mos6502 : public Clockable, public Name {
public:
    constexpr static const char *TYPE    = "MOS6502";
    constexpr static const char *LABEL   = "CPU";

    constexpr static const addr_t vNMI   = 0xFFFA;
    constexpr static const addr_t vRESET = 0xFFFC;
    constexpr static const addr_t vIRQ   = 0xFFFE;

    constexpr static const addr_t S_base = 0x0100;

    using breakpoint_cb_t = std::function<void(Mos6502 &, void *)>;

    enum AddressingMode {
        MODE_NONE,
        MODE_IMM,
        MODE_ZP,
        MODE_ZP_X,
        MODE_ZP_Y,
        MODE_ABS,
        MODE_ABS_X,
        MODE_ABS_Y,
        MODE_IND_X,
        MODE_IND_Y,
        MODE_REL,
        MODE_IND
    };

    enum Flags {
        N = 0x80,                           /* Negative          */
        V = 0x40,                           /* Overflow          */
        _ = 0x20,                           /* Unused (always 1) */
        B = 0x10,                           /* Break             */
        D = 0x08,                           /* Decimal Mode      */
        I = 0x04,                           /* IRQ Disable       */
        Z = 0x02,                           /* Zero              */
        C = 0x01                            /* Carry             */
    };

    struct Instruction {
        const char *format;                 /* Mnemonic format string (*=00, ^=0000, +=rel) */
        void (*fn)(Mos6502 &, addr_t arg);  /* Instruction callback                         */
        AddressingMode mode;                /* Addressing mode                              */
        size_t cycles;                      /* Clock cycles consumed by this instruction    */
        size_t size;                        /* Size of the instruction (in bytes)           */
    };

    struct Registers {
        uint8_t A;
        uint8_t X;
        uint8_t Y;
        addr_t  PC;
        uint8_t S;
        uint8_t P;

        std::string to_string() const;

        static std::string to_string(Flags fl);
    };

    /**
     * Initialise this CPU.
     * @param type  CPU type (usually the model name);
     * @param label CPU label (usually an arbitrary instance name).
     * @see ASpace
     */
    Mos6502(const std::string &type = TYPE, const std::string &label = LABEL);

    /**
     * Initialise this CPU.
     * @param mmap  System mappings;
     * @param type  CPU type (usually the model name);
     * @param label CPU label (usually an arbitrary instance name).
     * @see ASpace
     */
    Mos6502(const std::shared_ptr<ASpace> &mmap, const std::string &type = TYPE, const std::string &label = LABEL);

    virtual ~Mos6502();

    /**
     * Initialise a monitor for this CPU.
     * This CPU must be properly initialised (system mappings set) before this method can be called.
     * The CPU monitor is initialised and a breakpoint is added at the reset address (vRESET),
     * the monitor takes control as soon as this CPU is started.
     * @param is Input stream used to receive commands from the user;
     * @param os Output stream used to send responses to the user.
     * @exception InvalidArgument if the system mappings are not set.
     * @see reset()
     */
    void init_monitor(std::istream &is, std::ostream &os);

    /**
     * Reinitialise this CPU.
     * @param mmap System mappings.
     */
    void reset(const std::shared_ptr<ASpace> &mmap = {});

    /**
     * Set the single-step log level.
     * @param lvs Log level string to set.
     * @see Logger::loglevel(const std::string &)
     */
    void loglevel(const std::string &lvs);

    /**
     * @return The current single-step log level.
     */
    Logger::Level loglevel() const;

    /**
     * Trigger an IRQ.
     * This method must be called twice by external peripherals, the first time to activate
     * the IRQ pin and a second time to de-activate it when the interrupt is served.
     * @param active true to generate an interrupt; false to de-activate a previous interrupt request.
     */
    IRQPin &irq_pin();

    /**
     * Trigger an NMI interrupt.
     * @param active true to generate an interrupt; false to de-activate.
     */
    IRQPin &nmi_pin();

    /**
     * Set the RDY line.
     * @param active true to activate the RDY line; false otherwise.
     * @see single_step()
     */
    InputPin &rdy_pin();

    /**
     * External breakpoint.
     * Force a return back to the monitor on the next clock tick,
     * if the monitor is not active a system halt is requested.
     */
    void ebreak();

    /**
     * Add a breakpoint on a memory address.
     * @param addr Address;
     * @parma cb   Method to call when the breakpoint hits.
     */
    void bpadd(addr_t addr, const breakpoint_cb_t &cb, void *arg);

    /**
     * Delete a breakpoint on a memory address.
     * @param addr Address.
     */
    void bpdel(addr_t addr);

    /**
     * @return The register values.
     */
    const Registers &regs() const;

    /**
     * Disassembler.
     * @param os      Output stream;
     * @param addr    Start address with the machine code to disassemble;
     * @param count   Number of instructions to disassemble.
     * @param show_pc true if the position of the PC must be marked in the disassembled code; false otherwise (default).
     */
    void disass(std::ostream &os, addr_t start, size_t count, bool show_pc = false);

    /**
     * Read an address from an address.
     * @param addr Address to read from.
     * @return The 16 bits value.
     * @exception InvalidReadAddress
     * @see read()
     */
    addr_t read_addr(size_t addr) const;

    /**
     * Write an address into an address.
     * @param addr  Address to write to;
     * @param value 16 bits value to write.
     * @exception InvalidWriteAddress
     * @see write()
     */
    void write_addr(addr_t addr, addr_t data);

    /**
     * @see ASpace::read()
     */
    virtual uint8_t read(addr_t addr) const;

    /**
     * @see ASpace::write()
     */
    virtual void write(addr_t addr, uint8_t data);

private:
    /**
     * Tick event method.
     * This method is called by the clock and executes a single CPU instruction.
     * If the monitor is not running the current instruction is executed.
     * If the monitor is running and a monitor-breakpoint is set on the current PC address
     * the monitor's run method is called instead.
     * @param clk The caller clock.
     * @return The number of clock cycles consumed by the executed instruction;
     *         Clockable::HALT if the halt instruction was executed.
     * @see single_step()
     * @see Mos6502Monitor::run()
     */
    size_t tick(const Clock &clk) override;

    /**
     * Disassemble a single instruction located at a specified address.
     * @param addr    Address to disassemble (after disassembly this value is
     *                incremented with the position of the next instruction);
     * @param show_pc true if the position of the PC must be marked in the disassembled code;
     *                false otherwise.
     * @return A string with the disassembled instruction.
     */
    std::string disass(addr_t &addr, bool show_pc = false);

    /**
     * Execute a single instruction located at the current PC address.
     * If the RDY pin input is active the instruction located at the current PC
     * address is executed and the PC is updated to point to the next instruction.
     * If the RDY pin input is not active this method does nothing.
     * @return The clock cycles that must pass until the clock is allowd to call
     *         this method again (clock cycles consumed by the executed instruction);
     *         clockable::HALT if the KIL (HALT) instruction was executed.
     */
    size_t single_step();

    void flag(uint8_t bits, bool act = true) {
        _regs.P = (act ? (_regs.P | bits) : (_regs.P & (~bits))) | Flags::_;
    }

    void flag_N(bool act) {
        flag(Flags::N, act);
    }

    void flag_V(bool act) {
        flag(Flags::V, act);
    }

    void flag_Z(bool act) {
        flag(Flags::Z, act);
    }

    void flag_B(bool act) {
        flag(Flags::B, act);
    }

    void flag_D(bool act) {
        flag(Flags::D, act);
    }

    void flag_I(bool act) {
        flag(Flags::I, act);
    }

    void flag_C(bool act) {
        flag(Flags::C, act);
    }

    void set_N(uint8_t value) {
        flag_N(value & 0x80);
    }

    void set_Z(uint8_t value) {
        flag_Z(value == 0);
    }

    bool test_flags(uint8_t bits) const {
        return (_regs.P & bits);
    }

    bool test_N() const {
        return test_flags(Flags::N);
    }

    bool test_V() const {
        return test_flags(Flags::V);
    }

    bool test_Z() const {
        return test_flags(Flags::Z);
    }

    bool test_D() const {
        return test_flags(Flags::D);
    }

    bool test_B() const {
        return test_flags(Flags::B);
    }

    bool test_I() const {
        return test_flags(Flags::I);
    }

    bool test_C() const {
        return test_flags(Flags::C);
    }

    bool is_irq_enabled() const {
        return (!test_I());
    }

    void push(uint8_t value) {
        write(S_base + _regs.S--, value);
    }

    uint8_t pop() {
        return read(S_base + (++_regs.S));
    }

    void push_addr(addr_t value) {
        uint8_t hi = (value >> 8) & 0xff;
        uint8_t lo = value & 0xff;
        push(hi);
        push(lo);
    }

    addr_t pop_addr() {
        uint8_t lo = pop();
        addr_t hi = pop();
        addr_t addr = (hi << 8) | lo;
        return addr;
    }

    void push_P() {
        push(_regs.P);
    }

    void pop_P() {
        _regs.P = pop() | Flags::_;
    }

    Logger                          _log{};
    std::unique_ptr<Mos6502Monitor> _monitor{};
    Registers                       _regs{};
    std::shared_ptr<ASpace>         _mmap{};
    IRQPin                          _irq_pin{};
    IRQPin                          _nmi_pin{};
    InputPin                        _rdy_pin{};

    std::atomic_bool _break{};
    std::map<addr_t, std::pair<breakpoint_cb_t, void *>> _breakpoints{};

    static const std::array<Instruction, 256> instr_set;

    /**
     * Relative branch helper.
     * @param rel Address to jump relative to the current PC position.
     */
    void take_branch(int8_t rel) {
        _regs.PC += rel;
    }

    /**
     * AND helper.
     * Flags: N Z
     * @return v1 & v2
     */
    uint8_t logic_and(uint8_t v1, uint8_t v2) {
        uint8_t r = v1 & v2;
        set_N(r);
        set_Z(r);
        return r;
    }

    /**
     * OR helper.
     * Flags: N Z
     * @return v1 | v2.
     */
    uint8_t logic_or(uint8_t v1, uint8_t v2) {
        uint8_t r = v1 | v2;
        set_N(r);
        set_Z(r);
        return r;
    }

    /**
     * EOR helper.
     * Flags: N Z
     * @return v1 ^ v2
     */
    uint8_t logic_eor(uint8_t v1, uint8_t v2) {
        uint8_t r = v1 ^ v2;
        set_N(r);
        set_Z(r);
        return r;
    }

    /**
     * ASL helper: Shift left 1 bit with carry.
     * Flags: N Z C
     * @return The shifted value.
     */
    uint8_t logic_shl(uint8_t v) {
        flag_C(v & 0x80);
        v <<= 1;
        set_N(v);
        set_Z(v);
        return v;
    }

    /**
     * ROL helper: Rotate left 1 bit with carry.
     * Flags: N Z C
     * @return The rotated value.
     */
    uint8_t logic_rol(uint8_t v) {
        uint8_t c = (test_C() ? 1 : 0);
        flag_C(v & 0x80);
        v = (v << 1) | c;
        set_N(v);
        set_Z(v);
        return v;
    }

    /**
     * LSR helper: Shift right 1 bit with carry.
     * Flags: N Z C
     * @return The shifted value.
     */
    uint8_t logic_shr(uint8_t v) {
        flag_C(v & 0x01);
        v >>= 1;
        flag_N(false);
        set_Z(v);
        return v;
    }

    /**
     * ROR helper: Rotate right 1 bit with carry.
     * Flags: N Z C
     * @return The rotated value.
     */
    uint8_t logic_ror(uint8_t v) {
        uint8_t c = (test_C() ? 0x80 : 0);
        flag_C(v & 0x01);
        v = (v >> 1) | c;
        set_N(v);
        set_Z(v);
        return v;
    }

    /**
     * CMP helper.
     * Flags: N Z C
     */
    void cmp(uint8_t v1, uint8_t v2) {
        int sum = v1 - v2;
        uint8_t r = static_cast<uint8_t>(sum & 0xFF);
        set_N(r);
        set_Z(r);
        flag_C(v1 >= v2);
    }

    /**
     * Signed arithmetic addition helper.
     */
    uint8_t adc_bin(uint8_t v1, uint8_t v2);

    /**
     * Packed BCD addition helper.
     * Flags: N V C Z
     * @param v1 Packed BCD;
     * @param v2 Packed BCD.
     * @return The result of the addition formatted as a packed BCD.
     */
    uint8_t adc_bcd(uint8_t v1, uint8_t v2);

    /**
     * ADC helper.
     * Depending on D flag, perform a signed binary addition or a packed BCD addition.
     * Flags: N V Z C
     * @return v1 + v2 + C
     */
    uint8_t adc(uint8_t v1, uint8_t v2);

    /**
     * Signed binary substraction helper.
     * Flags: N V Z C
     * @return v1 - v2 - ~C
     */
    uint8_t sbc_bin(uint8_t v1, uint8_t v2);

    /**
     * BCD substraction helper.
     * Flags: N V Z C
     * @return v1 - v2 - ~C
     */
    uint8_t sbc_bcd(uint8_t v1, uint8_t v2);

    /**
     * SBC helper.
     * Depending on D flag, permor a signed binary substraction or a packed BCD substraction.
     * Flags: N V Z C
     * @return v1 - v2 - ~C
     */
    uint8_t sbc(uint8_t v1, uint8_t v2);

    /*
     * Instruction callbacks: Logical and Arithmetic operations.
     */
    static void i_AND_imm   (Mos6502 &, addr_t);
    static void i_AND       (Mos6502 &, addr_t);

    static void i_BIT       (Mos6502 &, addr_t);

    static void i_ORA_imm   (Mos6502 &, addr_t);
    static void i_ORA       (Mos6502 &, addr_t);

    static void i_EOR_imm   (Mos6502 &, addr_t);
    static void i_EOR       (Mos6502 &, addr_t);

    static void i_ADC_imm   (Mos6502 &, addr_t);
    static void i_ADC       (Mos6502 &, addr_t);

    static void i_SBC_imm   (Mos6502 &, addr_t);
    static void i_SBC       (Mos6502 &, addr_t);

    static void i_CMP_imm   (Mos6502 &, addr_t);
    static void i_CMP       (Mos6502 &, addr_t);

    static void i_CPX_imm   (Mos6502 &, addr_t);
    static void i_CPX       (Mos6502 &, addr_t);

    static void i_CPY_imm   (Mos6502 &, addr_t);
    static void i_CPY       (Mos6502 &, addr_t);

    static void i_DEC       (Mos6502 &, addr_t);
    static void i_DEX       (Mos6502 &, addr_t);
    static void i_DEY       (Mos6502 &, addr_t);

    static void i_INC       (Mos6502 &, addr_t);
    static void i_INX       (Mos6502 &, addr_t);
    static void i_INY       (Mos6502 &, addr_t);

    static void i_ASL_acc   (Mos6502 &, addr_t);
    static void i_ASL       (Mos6502 &, addr_t);

    static void i_ROL_acc   (Mos6502 &, addr_t);
    static void i_ROL       (Mos6502 &, addr_t);

    static void i_LSR_acc   (Mos6502 &, addr_t);
    static void i_LSR       (Mos6502 &, addr_t);

    static void i_ROR_acc   (Mos6502 &, addr_t);
    static void i_ROR       (Mos6502 &, addr_t);

    /*
     * Instruction callbacks: Move operations.
     */
    static void i_LDA_imm   (Mos6502 &, addr_t);
    static void i_LDA       (Mos6502 &, addr_t);

    static void i_LDX_imm   (Mos6502 &, addr_t);
    static void i_LDX       (Mos6502 &, addr_t);

    static void i_LDY_imm   (Mos6502 &, addr_t);
    static void i_LDY       (Mos6502 &, addr_t);

    static void i_STA       (Mos6502 &, addr_t);
    static void i_STX       (Mos6502 &, addr_t);
    static void i_STY       (Mos6502 &, addr_t);

    static void i_TAX       (Mos6502 &, addr_t);
    static void i_TXA       (Mos6502 &, addr_t);
    static void i_TAY       (Mos6502 &, addr_t);
    static void i_TYA       (Mos6502 &, addr_t);

    static void i_TSX       (Mos6502 &, addr_t);
    static void i_TXS       (Mos6502 &, addr_t);

    static void i_PLA       (Mos6502 &, addr_t);
    static void i_PHA       (Mos6502 &, addr_t);

    static void i_PLP       (Mos6502 &, addr_t);
    static void i_PHP       (Mos6502 &, addr_t);

    /*
     * Instruction callbacks: Branch/Jump.
     */
    static void i_BPL       (Mos6502 &, addr_t);
    static void i_BMI       (Mos6502 &, addr_t);

    static void i_BVC       (Mos6502 &, addr_t);
    static void i_BVS       (Mos6502 &, addr_t);

    static void i_BCC       (Mos6502 &, addr_t);
    static void i_BCS       (Mos6502 &, addr_t);

    static void i_BNE       (Mos6502 &, addr_t);
    static void i_BEQ       (Mos6502 &, addr_t);

    static void i_BRK       (Mos6502 &, addr_t);
    static void i_RTI       (Mos6502 &, addr_t);

    static void i_JSR       (Mos6502 &, addr_t);
    static void i_RTS       (Mos6502 &, addr_t);

    static void i_JMP       (Mos6502 &, addr_t);

    static void i_NOP       (Mos6502 &, addr_t);

    /*
     * Instruction callbacks: Flags.
     */
    static void i_CLC       (Mos6502 &, addr_t);
    static void i_SEC       (Mos6502 &, addr_t);

    static void i_CLI       (Mos6502 &, addr_t);
    static void i_SEI       (Mos6502 &, addr_t);

    static void i_CLV       (Mos6502 &, addr_t);

    static void i_CLD       (Mos6502 &, addr_t);
    static void i_SED       (Mos6502 &, addr_t);

    /*
     * Instruction callbacks: Illegal Instructions.
     */
    static void i_SLO       (Mos6502 &, addr_t);
    static void i_RLA       (Mos6502 &, addr_t);
    static void i_SRE       (Mos6502 &, addr_t);
    static void i_RRA       (Mos6502 &, addr_t);
    static void i_SAX       (Mos6502 &, addr_t);
    static void i_LAX_imm   (Mos6502 &, addr_t);
    static void i_LAX       (Mos6502 &, addr_t);
    static void i_DCP       (Mos6502 &, addr_t);
    static void i_ISC       (Mos6502 &, addr_t);
    static void i_ANC_imm   (Mos6502 &, addr_t);
    static void i_ALR_imm   (Mos6502 &, addr_t);
    static void i_ARR_imm   (Mos6502 &, addr_t);
    static void i_XAA_imm   (Mos6502 &, addr_t);
    static void i_AXS_imm   (Mos6502 &, addr_t);
    static void i_AHX       (Mos6502 &, addr_t);
    static void i_SHY       (Mos6502 &, addr_t);
    static void i_SHX       (Mos6502 &, addr_t);
    static void i_TAS       (Mos6502 &, addr_t);
    static void i_LAS       (Mos6502 &, addr_t);

    static void i_KIL       (Mos6502 &, addr_t);

    friend class Mos6502Monitor;
};

}