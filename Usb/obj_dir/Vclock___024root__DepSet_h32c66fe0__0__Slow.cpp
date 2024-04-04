// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vclock.h for the primary calling header

#include "Vclock__pch.h"
#include "Vclock___024root.h"

VL_ATTR_COLD void Vclock___024root___eval_static(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vclock___024root___eval_initial(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk50__0 = vlSelf->clk50;
}

VL_ATTR_COLD void Vclock___024root___eval_final(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vclock___024root___eval_settle(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vclock___024root___dump_triggers__act(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk50)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vclock___024root___dump_triggers__nba(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk50)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vclock___024root___ctor_var_reset(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk50 = VL_RAND_RESET_I(1);
    vlSelf->rst_n = VL_RAND_RESET_I(1);
    vlSelf->clk12 = VL_RAND_RESET_I(1);
    vlSelf->cligger12__DOT__div = VL_RAND_RESET_I(5);
    vlSelf->__Vtrigprevexpr___TOP__clk50__0 = VL_RAND_RESET_I(1);
}
