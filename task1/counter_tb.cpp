#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i;
    int clk;
    int j=0;
    Verilated::commandArgs(argc,argv);
//  initialise top verilog instance
    Vcounter* top = new Vcounter;
// initialise trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp,99);
    tfp->open("counter.vcd");

    // initialise simulation outputs
    top->clk =1;
    top->rst=0;
    top->en = 1;
    
    // run simulation for i clock cycles
    for(int i=0;i< 200; i++){
    //dum variables into VCD file and toggle clocks
        for(clk=0;clk<2;clk++){// this for loop toggles the clock it and outputs the trace for each half of the clock cycle and force the model to evaluate on both edges of the clock
            // in picosecods
            tfp->dump (2*i+clk);
            // falling edge
            top->clk = !top->clk;
            top->eval ();
        }
        if(top->count==9){
            if(j==2){
                top->rst=1;
                top->en=1;
                j=0;
            }
            else{
                top->en=0;
                 j+=1;
            }
        }
        else{
            top->rst=0;
        }
      
    

        if(Verilated::gotFinish()) exit(0);
        
    }
    tfp->close();
    exit(0);

}
