`timescale 1ns / 1ps

module if_stage (
    input wire clk,
    input wire rst,
    
);

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            pc <= 64'h0000000000000000;
            instruction <= 32'h00000013; // NOP (ADDI x0, x0, 0)
        end else begin
            if (prev_branch_bool) begin
                pc <= branch_target; // Branch target address
            end else begin
                pc <= pc + 4; // Default PC increment
            end
        end
    end
endmodule