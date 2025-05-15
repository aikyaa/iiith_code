

module Adder (a,b,c,Sum,Carry);
input a,b,c ;
output Sum,Carry;
wire I1,I2,I3;

// Let's Compute I1 = xor(a,b)
xor U1(I1,a,b);
// Let's Compute I2 = and(a,b)
and U2(I2,a,b);
// Let's Compute Sum = xor(I1,c)
xor U3(Sum,I1,c);
// Let's Compute I3 = and(I1,c)
and U4(I3,I1,c);
// Let's Compute Carry 
or  U5(Carry,I2,I3);

endmodule

module full_adder (
    input [63:0]A,
    input [63:0]B,
    input Cin,
    output [63:0] S,
    output wire C 
);

wire [64:0] Carry;
assign Carry[0] = Cin;

genvar i;
generate
    for (i=0; i<64; i=i+1) begin
        Adder inst (.a(A[i]), .b(B[i]), .c(Carry[i]), .Sum(S[i]), .Carry(Carry[i+1]));
    end
endgenerate
assign C = Carry[64];
endmodule

module AND ( 
    input [63:0]A,
    input [63:0]B,
    output [63:0] Y
);


genvar i;
generate
    for (i=0; i<64; i=i+1) begin
        and U1(Y[i], A[i], B[i]);
    end
endgenerate

endmodule

module OR ( 
    input [63:0]A,
    input [63:0]B,
    output [63:0] Y
);


genvar i;
generate
    for (i=0; i<64; i=i+1) begin
        or U1(Y[i], A[i], B[i]);
    end
endgenerate

endmodule

module XOR ( 
    input [63:0]A,
    input [63:0]B,
    output [63:0] Y
);


genvar i;
generate
    for (i=0; i<64; i=i+1) begin
        xor U1(Y[i], A[i], B[i]);
    end
endgenerate

endmodule

module Subtractor (
    input [63:0] A,
    input [63:0] B,
    output [63:0] D ,
    output wire C
);
     wire [63:0] B_complement;
     // Required 2's Complement of B
     // add 1 to inverting B
     wire C0 = 1'b1 ;
     genvar i;
     generate
           for(i = 0 ; i < 64 ; i = i + 1) begin
            not U1(B_complement[i] , B[i]) ;
           end
     endgenerate
     full_adder U2(.A(A), .B(B_complement), .Cin(C0) ,.S(D), .C(C)) ;
     
endmodule

module ALU (
    output reg [63:0] result,
    output reg zero,
    input wire [63:0] A,
    input wire [63:0] B,
    input wire [3:0] ALUcontrol
);

// generate
//     case (ALUcontrol)
//        4'b0000 : AND and_inst(.A(A), .B(B), .Y(result));
//        4'b0001 :  OR or_inst(.A(A), .B(B), .Y(result));
//        4'b0010 :  full_adder adder_inst(.A(A), .B(B), .Cin(1'b0), .S(result), .C(add_carry));
//        4'b0110 : Subtractor subtractor_inst(.A(A), .B(B), .D(result), .C(sub_carry));
//     endcase
// endgenerate
    
    // Internal wires for operation results
    wire [63:0] and_result;
    wire [63:0] or_result;
    wire [63:0] add_result;
    wire [63:0] sub_result;
    wire add_carry, sub_carry;

    // Instantiate all operation modules
    AND and_inst(
        .A(A),
        .B(B),
        .Y(and_result)
    );

    OR or_inst(
        .A(A),
        .B(B),
        .Y(or_result)
    );

    full_adder adder_inst(
        .A(A),
        .B(B),
        .Cin(1'b0),
        .S(add_result),
        .C(add_carry)
    );

    Subtractor subtractor_inst(
        .A(A),
        .B(B),
        .D(sub_result),
        .C(sub_carry)
    );

    always @(*) begin
        case(ALUcontrol)
            4'b0000: result = and_result;
            4'b0001: result = or_result;
            4'b0010: result = add_result;
            4'b0110: result = sub_result;
            
        endcase
        // If ALU_result is Zero set zero to 1 
        if (result == 64'd0) begin
            zero = 1'b1 ;
        end 
        else begin
            zero = 1'b0 ;
        end
    end
endmodule



