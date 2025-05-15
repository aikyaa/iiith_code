`timescale 1ns / 1ps

module if_stage_tb;

    // Inputs
    reg clk;
    reg rst;
    reg pc_stall;
    reg branch_taken;
    reg [63:0] branch_target;

    // Outputs
    wire [63:0] pc;
    wire [31:0] instruction;

    // Instantiate the Unit Under Test (UUT)
    if_stage uut (
        .clk(clk),
        .rst(rst),
        .pc_stall(pc_stall),
        .branch_taken(branch_taken),
        .branch_target(branch_target),
        .pc(pc),
        .instruction(instruction)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10ns clock period
    end

    // Test stimulus
    initial begin
        // Initialize inputs
        rst = 1;
        pc_stall = 0;
        branch_taken = 0;
        branch_target = 64'h0;

        // Test 1: Reset
        #10;
        rst = 0;
        #10;
        $display("Test 1: After reset, PC=%h, Instruction=%h (expect 0, 00000013)", pc, instruction);

        // Test 2: Normal PC increment (fetch next instruction)
        #10;
        $display("Test 2: Normal increment, PC=%h, Instruction=%h (expect 4, 00108093)", pc, instruction);

        // Test 3: Normal PC increment again
        #10;
        $display("Test 3: Normal increment, PC=%h, Instruction=%h (expect 8, 00210113)", pc, instruction);

        // Test 4: PC stall
        #10;
        pc_stall = 1;
        #10;
        $display("Test 4: PC stall, PC=%h, Instruction=%h (expect 8, 00210113)", pc, instruction);
        pc_stall = 0;

        // Test 5: Branch taken
        #10;
        branch_taken = 1;
        branch_target = 64'h28; // Jump to address 0x28 (instr_mem[10])
        #10;
        branch_taken = 0;
        $display("Test 5: Branch taken, PC=%h, Instruction=%h (expect 28, 00318193)", pc, instruction);

        // Test 6: Normal increment after branch
        #10;
        $display("Test 6: Normal increment, PC=%h, Instruction=%h (expect 2C, <next instruction>)", pc, instruction);

        // Test 7: Branch to another address
        #10;
        branch_taken = 1;
        branch_target = 64'h50; // Jump to address 0x50 (instr_mem[20])
        #10;
        branch_taken = 0;
        $display("Test 7: Branch taken, PC=%h, Instruction=%h (expect 50, 00420213)", pc, instruction);

        // End simulation
        #10;
        $stop;
    end

    // Dumpfile generation
    initial begin
        $dumpfile("if_stage_tb.vcd");  // Output VCD file
        $dumpvars(0, if_stage_tb);     // Dump all variables in the testbench
    end

    // Monitor signals
    initial begin
        $monitor("Time=%t, clk=%b, rst=%b, pc_stall=%b, branch_taken=%b, branch_target=%h, pc=%h, instruction=%h", 
                 $time, clk, rst, pc_stall, branch_taken, branch_target, pc, instruction);
    end

endmodule