// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vclock.h for the primary calling header

#include "Vclock__pch.h"
#include "Vclock__Syms.h"
#include "Vclock___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vclock___024root___dump_triggers__act(Vclock___024root* vlSelf);
#endif  // VL_DEBUG

void Vclock___024root___eval_triggers__act(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk50) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk50__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk50__0 = vlSelf->clk50;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vclock___024root___dump_triggers__act(vlSelf);
    }
#endif
}
