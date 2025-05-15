`timescale 1ns/1ps

`include "fetch.v"
`include "id.v"
`include "execute.v"
`include "mem.v"
`include "wb.v"
`include "regfile.v"

module main (
    input wire clk ,
    input wire reset 
);

wire [63:0] pc ;
wire [31:0] Instruction ;

wire Branch ;
wire MemtoReg ;
wire MemWrite ;
wire MemRead ;
wire [1:0] ALUOp ;
wire ALUSrc ;
wire RegWrite ;
wire [2:0] funct3;
wire [6:0] funct7;

wire [63:0] read_data1 ; // Rs1 register stored value
wire [63:0] read_data2 ; // Rs2 register stored value
wire [63:0] immediate ; // Immediate block output 

wire [4:0] rs1 ;
wire [4:0] rs2 ;
wire [4:0] rd;

wire Zero ;
wire [63:0] branch_target;
wire [63:0] alu_result ;
wire [63:0] Data_read ;

wire [63:0] write_data ;

fetch_stage U1 (.clk(clk), .rst(reset), .pc(pc), .prev_branch_bool(Branch), .branch_target(branch_target), .pc_next(pc), .instruction(Instruction)) ;

decode_stage U2 (.instruction(Instruction), .rs1(rs1), .rs2(rs2), .rd(rd), .immediate(immediate), .RegWrite(RegWrite), .ALUSrc(ALUSrc), .MemWrite(MemWrite), .MemRead(MemRead), .ALUOp(ALUOp), .Branch(Branch), .MemtoReg(MemtoReg), .funct3(funct3), .funct7(funct7)) ;

reg_file U3 (.clk(clk), .RegWrite(RegWrite), .rs1(rs1), .rs2(rs2), .rd(rd), .write_data(write_data), .read_data1(read_data1), .read_data2(read_data2));

execute U4 ( .pc_id_ex(pc), .read_data1(read_data1), .read_data2(read_data2), 
.sign_extended_imm(immediate), .funct3(funct3), .funct7(funct7), 
.ALUOp(ALUOp), .ALUSrc(ALUSrc), .Branch(Branch), .alu_result(alu_result), 
.zero(zero), .branch_target(branch_target), .read_data2_out(read_data2) );

Data_memory U5 (.Clk(clk), .address(alu_result), .Data_write(alu_result), .MemWrite(MemWrite), .MemRead(MemRead), .Data_read(Data_read));

writeback_stage U6 (.MemToRegIn(MemtoReg), .Branch(Branch), .ALUResult(alu_result), .MemData(Data_read), .RdIn(rd), .WriteData(write_data), .RegWriteOut(RegWrite));

endmodule
