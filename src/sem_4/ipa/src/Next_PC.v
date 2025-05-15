// `include "ALU.v"

module Next_PC (
    input Branch,
    input Zero,
    input [63:0] PC,
    input [63:0] Target,
    output reg [63:0] next_pc
);
    wire w1;
    wire carry;
    wire [63:0] PC_4;
    wire [63:0] Solution;

    // AND gate for Branch & Zero
    and U1(w1, Branch, Zero);

    // Full Adder for PC + 4
    full_adder general_address (
        .A(PC),
        .B(64'd4),
        .Cin(1'b0),
        .S(PC_4),
        .C(carry)
    );

    // MUX to choose next PC
    MUX U2 (
        .B(PC_4),
        .C(Target),
        .Sel(w1),
        .Y(Solution)
    );

    always @(*) begin
        next_pc = Solution;
    end
endmodule

module MUX (
    input wire [63:0] B,     
    input wire [63:0] C,      
    input wire Sel,          
    output reg [63:0] Y      
);
    always @(*) begin
        if (Sel)
            Y = C;   
        else
            Y = B;   
    end
endmodule
