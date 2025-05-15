`include "ALU.v"

module Execute (
    input [63:0] A ,
    input [63:0] B ,
    input [63:0] C ,
    input [63:0] PC ,
    input [2:0] funct3 ,
    input [6:0] funct7 ,
    input [1:0] ALUOp ,
    input ALUSrc ,
    output reg Zero ,
    output reg [63:0] Target ,
    output reg [63:0] ALU_result 
) ;

 wire [3:0] ALUcontrol ;
// ALU Control Caluculations using Gates
alu_control U1 (.ALUOp(ALUOp) , .Funct7(funct7) ,.Funct3(funct3) ,.Operation(ALUcontrol)) ;
 

wire [63:0] Y ;
wire [63:0] Solution ;
wire  [63:0] result ;
wire Zo ;
// Second input to ALU is it immediate value or value from  Register 2

MUX_21 alu_mux ( .B(B) , .C(C) , .ALUSrc(ALUSrc) , .Y(Y)) ;
ALU U3 (.result(result), .zero(Zo) , .A(A) ,.B(Y) ,.ALUcontrol(ALUcontrol) ) ;

// Need to calculate Branch Address 
// First need to shift immediate left by 1 

wire branch_carry ;
wire [63:0] S ;
Shiftleft U4 (.C(C) ,.S(S)) ;
full_adder target_address (.A(S) , .B(PC) ,.Cin(1'b0) , .S(Solution) ,.C(branch_carry)) ;

always @(*) begin
    ALU_result = result ;
    Target = Solution ;
    Zero = Zo ;
end


endmodule 

module MUX_21 (
    input wire [63:0] B,     
    input wire [63:0] C,      
    input wire ALUSrc,          
    output reg [63:0] Y      
);

    always @(*) begin
        if (ALUSrc)
            Y = C;   // Select immediate C
        else
            Y = B;   // Select register B
    end

endmodule

module Shiftleft (
    input [63:0] C,
    output reg [63:0] S
);
    integer j;
    
    always @(*) begin
        S = 64'b0;  // Initialize output
        for (j = 0; j < 63; j = j + 1) begin
            S[j+1] = C[j];  // Shift left by 1
        end
    end
endmodule

module alu_control(
    input [1:0] ALUOp,      // ALUOp1 and ALUOp0
    input [6:0] Funct7,
    input [2:0] Funct3,
    output reg [3:0] Operation
);


    always @(*) begin

        Operation[3] = 1'b0;
        
        case(ALUOp)
            2'b00: begin // Load/Store instruction
                Operation[3:0] = 4'b0010; 
            end
            
            2'b01: begin // Branch instruction
                Operation[3:0] = 4'b0110; 
            end
            
            2'b10: begin // R type instructions
                case(Funct3)
                    3'b000: begin // ADD/SUB
                        if (Funct7[5] == 1'b1)
                           Operation[3:0] = 4'b0110; // SUB
                        else
                            Operation[3:0] = 4'b0010; // ADD
                    end
                    
                    3'b110: begin // OR
                        if (Funct7[5] == 1'b0)
                            Operation[3:0] = 4'b0001; // OR
                        else
                            Operation[3:0] = 4'b0000; // (Invalid Operation)
                    end
                    
                    3'b111: begin // AND
                        if (Funct7[5] == 1'b0)
                            Operation[3:0] = 4'b0000; // AND
                        else
                        Operation[3:0] = 4'b0000; //(Invalid Operation)
                    end
                endcase
            end
            
            default: begin
                Operation[2:0] = 3'b000; // Default operation
            end
        endcase
    end

endmodule

