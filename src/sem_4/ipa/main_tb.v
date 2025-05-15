`timescale 1ns/1ps

module main_tb;
    reg clk, reset;
    
    // Instantiate main module
    main uut (
        .clk(clk),
        .reset(reset)
    );
    
    // Clock generation
    always #5 clk = ~clk; // 10ns clock period
    
    initial begin
        // Initialize signals
        clk = 0;
        reset = 1;
        
        // Reset pulse
        #10 reset = 0;
        
        // Test Case 1: ADD
        // Expected Output: WriteData = 10 + 5 = 15
        #10 uut.reg_file.registers[1] = 10; 
            uut.reg_file.registers[2] = 5;
        #10;
        
        // Test Case 2: SUB
        // Expected Output: WriteData = 10 - 5 = 5
        #10 uut.reg_file.registers[1] = 10;
            uut.reg_file.registers[2] = 5;
        #10;
        
        // Test Case 3: AND
        // Expected Output: WriteData = 10 & 5 = 0
        #10 uut.reg_file.registers[1] = 10;
            uut.reg_file.registers[2] = 5;
        #10;
        
        // Test Case 4: OR
        // Expected Output: WriteData = 10 | 5 = 15
        #10 uut.reg_file.registers[1] = 10;
            uut.reg_file.registers[2] = 5;
        #10;
        
        // Test Case 5: LD (Load Data)
        // Expected Output: Data_read contains value from memory
        #10 uut.Data_memory.U5.reg_file[10] = 55;
        #10;
        
        // Test Case 6: SD (Store Data)
        // Expected Output: Memory location should be updated
        #10 uut.reg_file.registers[3] = 99;
        #10;
        
        // Test Case 7: BEQ (Branch if Equal)
        // Expected Output: Branch should be taken if values are equal
        #10 uut.reg_file.registers[1] = 20;
            uut.reg_file.registers[2] = 20;
        #10;
        
        // End simulation
        #100;
        $stop;
    end
    
    initial begin
        $monitor("Time=%0t, PC=%h, Instruction=%h, WriteData=%h", $time, uut.pc, uut.Instruction, uut.write_data);
    end
endmodule
