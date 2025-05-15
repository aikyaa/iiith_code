`timescale 1ns / 1ps

module Execute_test;
    
    // Testbench Signals
    reg [63:0] A, B, C, PC;
    reg [2:0] funct3;
    reg [6:0] funct7;
    reg [1:0] ALUOp;
    reg ALUSrc;
    wire Zero;
    wire [63:0] Target, ALU_result;
    
    // Instantiate the Execute module
    Execute uut (
        .A(A),
        .B(B),
        .C(C),
        .PC(PC),
        .funct3(funct3),
        .funct7(funct7),
        .ALUOp(ALUOp),
        .ALUSrc(ALUSrc),
        .Zero(Zero),
        .Target(Target),
        .ALU_result(ALU_result)
    );
    
    // Task to display results
    task display_results;
        begin
            $display("Time = %0t", $time);
            $display("A  = %b", A);
            $display("B  = %b", B);
            $display("C  = %b", C);
            $display("PC = %b", PC);
            $display("ALU_result = %b", ALU_result);
            $display("Target = %b", Target);
            $display("Zero = %b", Zero);
            $display("------------------------------------");
        end
    endtask
    
    initial begin
        $dumpfile("Execute_test.vcd");
        $dumpvars(0, Execute_test);
        
        // Test Case 1: Simple ADD operation (Register B selected)
        A = 64'd10; B = 64'd10; C = 64'd5; PC = 64'd100; ALUSrc = 0; ALUOp = 2'b10; funct3 = 3'b000; funct7 = 7'b0000000; #10;
        display_results();
        
        // Test Case 2: Simple ADD operation (Immediate C selected)
        A = 64'd30; B = 64'd15; C = 64'd5; PC = 64'd200; ALUSrc = 1; ALUOp = 2'b00; funct3 = 3'b000; funct7 = 7'b0000000; #10;
        display_results();
        
        // Test Case 3: OR operation
        A = 64'hF0F0; B = 64'h0F0F; C = 64'hAAAA; PC = 64'h300; ALUSrc = 0; ALUOp = 2'b10; funct3 = 3'b110; funct7 = 7'b0000000; #10;
        display_results();
        
        // Test Case 4: AND operation
        A = 64'hFFFF; B = 64'hAAAA; C = 64'h5555; PC = 64'h400; ALUSrc = 0; ALUOp = 2'b10; funct3 = 3'b111; funct7 = 7'b0000000; #10;
        display_results();
        
        // Test Case 5: Branch satisfy (Zero flag set)
        A = 64'h20; B = 64'h20; C = 64'h8; PC = 64'h500; ALUSrc = 0; ALUOp = 2'b01; funct3 = 3'b000; funct7 = 7'b0000000; #10;
        display_results();
        
        // Test Case 6: Branch not satisfy (Zero flag not set)
        A = 64'h10; B = 64'h30; C = 64'h8; PC = 64'h600; ALUSrc = 0; ALUOp = 2'b01; funct3 = 3'b000; funct7 = 7'b0000000; #10;
        display_results();
        
        // Finish simulation
        $finish;
    end
    
endmodule
