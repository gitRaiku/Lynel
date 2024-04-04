// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vclock.h for the primary calling header

#include "Vclock__pch.h"
#include "Vclock__Syms.h"
#include "Vclock___024root.h"

void Vclock___024root___ctor_var_reset(Vclock___024root* vlSelf);

Vclock___024root::Vclock___024root(Vclock__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vclock___024root___ctor_var_reset(this);
}

void Vclock___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vclock___024root::~Vclock___024root() {
}
