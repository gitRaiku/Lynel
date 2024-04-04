// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vclock.h for the primary calling header

#include "Vclock__pch.h"
#include "Vclock___024root.h"

void Vclock___024root___eval_act(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_act\n"); );
}

extern const VlUnpacked<CData/*1:0*/, 64> Vclock__ConstPool__TABLE_h0d8bd729_0;
extern const VlUnpacked<CData/*0:0*/, 64> Vclock__ConstPool__TABLE_h0494eb38_0;
extern const VlUnpacked<CData/*4:0*/, 64> Vclock__ConstPool__TABLE_h547469c9_0;

VL_INLINE_OPT void Vclock___024root___nba_sequent__TOP__0(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*5:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = (((IData)(vlSelf->cligger12__DOT__div) 
                     << 1U) | (IData)(vlSelf->rst_n));
    if ((1U & Vclock__ConstPool__TABLE_h0d8bd729_0[__Vtableidx1])) {
        vlSelf->clk12 = Vclock__ConstPool__TABLE_h0494eb38_0
            [__Vtableidx1];
    }
    vlSelf->cligger12__DOT__div = Vclock__ConstPool__TABLE_h547469c9_0
        [__Vtableidx1];
}

void Vclock___024root___eval_nba(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vclock___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vclock___024root___eval_triggers__act(Vclock___024root* vlSelf);

bool Vclock___024root___eval_phase__act(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vclock___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vclock___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vclock___024root___eval_phase__nba(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vclock___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vclock___024root___dump_triggers__nba(Vclock___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vclock___024root___dump_triggers__act(Vclock___024root* vlSelf);
#endif  // VL_DEBUG

void Vclock___024root___eval(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vclock___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("clock.v", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vclock___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("clock.v", 1, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vclock___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vclock___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vclock___024root___eval_debug_assertions(Vclock___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vclock__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vclock___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk50 & 0xfeU))) {
        Verilated::overWidthError("clk50");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
}
#endif  // VL_DEBUG
