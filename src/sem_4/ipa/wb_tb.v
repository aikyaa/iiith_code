`timescale 1ns / 1ps

module tb_writeback_stage;
    reg clk, rst;
    reg RegWriteIn, MemToRegIn;
    reg [31:0] ALUResult, MemData;
    reg [4:0] RdIn;
    wire [31:0] WriteData;
    wire [4:0] WriteReg;
    wire RegWriteOut;

    // Instantiate the writeback stage
    writeback_stage wb (
        .clk(clk), .rst(rst), .RegWriteIn(RegWriteIn),
        .MemToRegIn(MemToRegIn), .ALUResult(ALUResult),
        .MemData(MemData), .RdIn(RdIn),
        .WriteData(WriteData), .WriteReg(WriteReg),
        .RegWriteOut(RegWriteOut)
    );

    // Clock generation: 10ns period
    always #5 clk = ~clk;

    // Test sequence
    initial begin
        // Initialize signals
        clk = 0; rst = 1; RegWriteIn = 0; MemToRegIn = 0;
        ALUResult = 32'h0; MemData = 32'h0; RdIn = 5'b0;

        // Test 0: Reset state
        #10 rst = 0;
        $display("Test 0: After reset, WriteReg=%d, RegWriteOut=%b", WriteReg, RegWriteOut);

        // Test 1: Basic R-type write (x1 <- ALUResult)
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'hDEADBEEF; RdIn = 5'b00001;
        #10 $display("Test 1: R-type write, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 2: Load instruction (x2 <- MemData)
        #10;
        RegWriteIn = 1; MemToRegIn = 1; MemData = 32'hCAFEBABE; RdIn = 5'b00010;
        #10 $display("Test 2: Load write, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 3: Attempt to write to x0 (should fail)
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'h12345678; RdIn = 5'b00000;
        #10 $display("Test 3: Write to x0, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 4: Write to x31 (max register)
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'hFFFFFFFF; RdIn = 5'b11111;
        #10 $display("Test 4: Write to x31, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 5: No write (RegWriteIn = 0)
        #10;
        RegWriteIn = 0; MemToRegIn = 1; MemData = 32'hABCD1234; RdIn = 5'b00100;
        #10 $display("Test 5: No write, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 6: Reset during write (edge case)
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'h5555AAAA; RdIn = 5'b00101;
        #2 rst = 1;  // Reset asserted mid-cycle
        #8 rst = 0;  // Reset deasserted after one cycle
        #10 $display("Test 6: Reset during write, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 7: Back-to-back writes with source switch
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'h11111111; RdIn = 5'b00110;
        #10 $display("Test 7a: ALU write, WriteData=%h, WriteReg=%d", WriteData, WriteReg);
        RegWriteIn = 1; MemToRegIn = 1; MemData = 32'h22222222; RdIn = 5'b00111;
        #10 $display("Test 7b: Mem write, WriteData=%h, WriteReg=%d", WriteData, WriteReg);

        // Test 8: Rapid RegWriteIn toggle (pipeline stress)
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'h33333333; RdIn = 5'b01000;
        #2 RegWriteIn = 0;  // Quick toggle off
        #3 RegWriteIn = 1;  // Toggle back on
        #10 $display("Test 8: Toggle RegWriteIn, WriteData=%h, WriteReg=%d, RegWriteOut=%b", WriteData, WriteReg, RegWriteOut);

        // Test 9: Invalid RdIn (out of bounds, though constrained by 5 bits)
        #10;
        RegWriteIn = 1; MemToRegIn = 0; ALUResult = 32'h44444444; RdIn = 5'b11111;  // Max valid
        #10 $display("Test 9: Max valid RdIn, WriteData=%h, WriteReg=%d", WriteData, WriteReg);

        #10 $finish;
    end

endmodule