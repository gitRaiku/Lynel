// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vclock__pch.h"

//============================================================
// Constructors

Vclock::Vclock(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vclock__Syms(contextp(), _vcname__, this)}
    , clk50{vlSymsp->TOP.clk50}
    , rst_n{vlSymsp->TOP.rst_n}
    , clk12{vlSymsp->TOP.clk12}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vclock::Vclock(const char* _vcname__)
    : Vclock(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vclock::~Vclock() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vclock___024root___eval_debug_assertions(Vclock___024root* vlSelf);
#endif  // VL_DEBUG
void Vclock___024root___eval_static(Vclock___024root* vlSelf);
void Vclock___024root___eval_initial(Vclock___024root* vlSelf);
void Vclock___024root___eval_settle(Vclock___024root* vlSelf);
void Vclock___024root___eval(Vclock___024root* vlSelf);

void Vclock::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vclock::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vclock___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vclock___024root___eval_static(&(vlSymsp->TOP));
        Vclock___024root___eval_initial(&(vlSymsp->TOP));
        Vclock___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vclock___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vclock::eventsPending() { return false; }

uint64_t Vclock::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vclock::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vclock___024root___eval_final(Vclock___024root* vlSelf);

VL_ATTR_COLD void Vclock::final() {
    Vclock___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vclock::hierName() const { return vlSymsp->name(); }
const char* Vclock::modelName() const { return "Vclock"; }
unsigned Vclock::threads() const { return 1; }
void Vclock::prepareClone() const { contextp()->prepareClone(); }
void Vclock::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vclock::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vclock::trace()' called on model that was Verilated without --trace option");
}
