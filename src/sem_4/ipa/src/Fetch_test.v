`timescale 1ns/1ps

module Fetch_test;
    reg Clk, reset;
    reg [63:0] pc_next;
    wire [31:0] instruction;

    // Instantiate the IF module
    Fetch uut (
        .Clk(Clk),
        .reset(reset),
        .pc_next(pc_next),
        .instruction(instruction)
    );

    // Clock generation
    always #5 Clk = ~Clk;

    initial begin
        // Initialize signals
        Clk = 0;
        reset = 1;
        pc_next = 0;
        
        // Apply reset
        #10 reset = 0;
        
        // Test case 1: Fetch first instruction (memory[0])
        pc_next = 0;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // Test case 2: Fetch second instruction (memory[1])
        pc_next = 64'd4;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // Test case 3: Fetch third instruction (memory[2])
        pc_next = 64'd8;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // Test case 4: Fetch fourth instruction (memory[3])
        pc_next = 64'd12;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // Test case 5: Fetch fifth instruction (memory[4])
        pc_next = 64'd16;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // Test case 6: Fetch sixth instruction (memory[5])
        pc_next = 64'd20;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // Test case 7: Fetch seventh instruction (memory[6])
        pc_next = 64'd24;
        #10;
        $display("Instruction at PC = %d: %b", pc_next, instruction);
        
        // End simulation
        #10;
        $finish;
    end
endmodule
