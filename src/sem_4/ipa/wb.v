`timescale 1ns / 1ps

module writeback_stage (
    input MemToRegIn,
    input Branch,
    input [31:0] ALUResult,
    input [31:0] MemData,
    input [4:0] RdIn,
    output [31:0] WriteData,
    output RegWriteOut
);


    // Combinational logic for write data selection
    always @(*) begin
        WriteData = MemToRegIn ? MemData : ALUResult;
        if (!Branch && (RdIn != 5'b0)) begin
                RegWriteOut = 1'b1;
        end
    end

endmodule
