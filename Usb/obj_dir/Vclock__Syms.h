// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCLOCK__SYMS_H_
#define VERILATED_VCLOCK__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vclock.h"

// INCLUDE MODULE CLASSES
#include "Vclock___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vclock__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vclock* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vclock___024root               TOP;

    // CONSTRUCTORS
    Vclock__Syms(VerilatedContext* contextp, const char* namep, Vclock* modelp);
    ~Vclock__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
