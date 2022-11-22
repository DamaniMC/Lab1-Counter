#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;


    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace 
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open("counter.vcd");

    //open and initalise vbuddy connection
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");
    //set init variables
    top->clk = 1;
    top->rst = 0;
    top->en = 1;

    // run the simulation over 300 clk cycles
    for (i = 0; i<300; i++) {
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }

        // Send count value to Vbuddy
        vbdHex(4,(int(top->count)>>16)&0xF);
        vbdHex(3,(int(top->count)>>8)& 0xF);
        vbdHex(2,(int(top->count)>>4)&0xF);
        vbdHex(1,(int(top->count)>>4)&0xF);
        vbdCycle(i+1);

        top->en = (i < 9) | (i >= 11);
        top->en = vbdFlag();
        if(Verilated::gotFinish()) exit(0);
    }
    vbdClose();
    tfp->close();
    exit(0);
}   