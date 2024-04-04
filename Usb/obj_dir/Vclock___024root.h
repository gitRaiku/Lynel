// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vclock.h for the primary calling header

#ifndef VERILATED_VCLOCK___024ROOT_H_
#define VERILATED_VCLOCK___024ROOT_H_  // guard

#include "verilated.h"


class Vclock__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vclock___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk50,0,0);
    VL_IN8(rst_n,0,0);
    VL_OUT8(clk12,0,0);
    CData/*4:0*/ cligger12__DOT__div;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk50__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vclock__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vclock___024root(Vclock__Syms* symsp, const char* v__name);
    ~Vclock___024root();
    VL_UNCOPYABLE(Vclock___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
