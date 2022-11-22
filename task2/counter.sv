module counter #(
    parameter WIDTH = 8
)(
    input  logic clk,
    input  logic rst,
    input  logic en,
    output logic [WIDTH-1:0] count
);

always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}}; // if the reset value is true count is set to 8-bits of 0
    else     count <= count + {{WIDTH-1{1'b0}}, en}; // otherwise count is added to the concatenation of {0000000,en}
    //which results in the addition of 1 if en is high

endmodule

