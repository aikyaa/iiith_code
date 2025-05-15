`timescale 1ns / 1ps

module fetch_stage (
    input wire clk,
    input wire rst,
    input reg pc,
    input wire prev_branch_bool,
    input wire [63:0] branch_target,
    output reg [63:0] pc_next,
    output reg [31:0] instruction
);

    // Internal instruction memory (ROM)
    reg [31:0] instr_mem [0:1023];

    // Initialize instruction memory with some test instructions
    initial begin
        instr_mem[0] = 32'h00000033;  // ADD x0, x0, x0
        instr_mem[1] = 32'h00108093;  // ADDI x1, x1, 1
        instr_mem[2] = 32'h00210113;  // ADDI x2, x2, 2
        instr_mem[10] = 32'h00318193; // ADDI x3, x3, 3
        instr_mem[20] = 32'h00420213; // ADDI x4, x4, 4
        instr_mem[30] = 32'h00528293; // ADDI x5, x5, 5
    end

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            pc <= 64'h0000000000000000;
            instruction <= 32'h00000013; // NOP (ADDI x0, x0, 0)
        end else begin
            instruction <= instr_mem[pc[11:2]]; // Fetch instruction (word aligned)
            if (prev_branch_bool) begin
                pc_next <= branch_target; // Branch target address
            end else begin
                pc_next <= pc + 4; // Default PC increment
            end
        end
    end
endmodule