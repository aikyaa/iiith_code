`include "Fetch.v"
`include "Decode.v"
`include "Execute.v"
`include "Data_memory.v"
`include "Next_PC.v"
`include "WriteBack.v"

module main (
    input wire Clk ,
    input wire reset 
);

wire [63:0] pc_next ;
wire [63:0] PC ;
wire [31:0] Instruction ;

wire Branch ;
wire MemtoReg ;
wire MemWrite ;
wire MemRead ;
wire [1:0] ALUOp ;
wire ALUSrc ;
wire RegWrite ;

wire [63:0] A ; // Rs1 register stored value
wire [63:0] B ; // Rs2 register stored value
wire [63:0] C ; // Immediate block output 

wire Zero ;
wire [63:0] Target;
wire [63:0] ALU_result ;
wire [63:0] Data ;

wire [63:0] Write_data ;

Fetch U1 (.Clk(Clk), .reset(reset), .pc_next(pc_next), .PC(PC), .instruction(Instruction)) ;


Decode U2 (
        .Clk(Clk),
        .Instruction(Instruction),
        .write_data(Write_data),
        .RegWrite(RegWrite),
        .A(A),
        .B(B),
        .C(C),
        .Branch(Branch),
        .MemRead(MemRead),
        .MemtoReg(MemtoReg),
        .ALUOp(ALUOp),
        .MemWrite(MemWrite),
        .ALUSrc(ALUSrc)
    );

Execute U4 (.A(A), .B(B), .C(C), .PC(PC), .funct3(Instruction[14:12]), .funct7(Instruction[31:25]), .ALUOp(ALUOp),
            .ALUSrc(ALUSrc), .Zero(Zero), .Target(Target), .ALU_result(ALU_result)) ;

Data_memory U5 (.Clk(Clk), .address(ALU_result), .Data_write(B), .MemWrite(MemWrite), .MemRead(MemRead), .Data_read(Data)) ;

WriteBack U6 (.ALU_result(ALU_result), .Data(Data), .MemtoReg(MemtoReg), .Write_data(Write_data));

Next_PC U7 (.Branch(Branch), .Zero(Zero), .PC(PC), .Target(Target), .next_pc(pc_next)); 

endmodule

  