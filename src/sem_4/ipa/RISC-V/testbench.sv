`timescale 1ns / 1ps

module RISC_V_Processor_tb;

  // Inputs
  reg clk;
  reg reset;
  reg [63:0] element1;
  reg [63:0] element2;
  reg [63:0] element3;
  reg [63:0] element4;
  reg [63:0] element5;
  reg [63:0] element6;
  reg [63:0] element7;
  reg [63:0] element8;
  reg stall;
  reg flush;

  // Instantiate the Unit Under Test (UUT)
  RISC_V_Processor uut (
    .clk(clk),
    .reset(reset),
    .element1(element1),
    .element2(element2),
    .element3(element3),
    .element4(element4),
    .element5(element5),
    .element6(element6),
    .element7(element7),
    .element8(element8),
    .stall(stall),
    .flush(flush)
  );

  // Clock generation
  always #5 clk = ~clk;

  initial begin
    // Initialize Inputs
    clk = 0;
    reset = 1;
    stall = 0;
    flush = 0;
    element1 = 64'h0000000000000001;
    element2 = 64'h0000000000000002;
    element3 = 64'h0000000000000003;
    element4 = 64'h0000000000000004;
    element5 = 64'h0000000000000005;
    element6 = 64'h0000000000000006;
    element7 = 64'h0000000000000007;
    element8 = 64'h0000000000000008;

    // Wait for global reset to finish
    #100;
    reset = 0;

    // Test ADD instruction
    // Assume instruction memory is preloaded with ADD x1, x2, x3
    #100;

    // Test SUB instruction
    // Assume instruction memory is preloaded with SUB x4, x5, x6
    #100;

    // Test AND instruction
    // Assume instruction memory is preloaded with AND x7, x8, x1
    #100;

    // Test OR instruction
    // Assume instruction memory is preloaded with OR x2, x3, x4
    #100;

    // Test BEQ instruction
    // Assume instruction memory is preloaded with BEQ x1, x2, offset
    #100;

    // Test LD instruction
    // Assume instruction memory is preloaded with LD x3, offset(x4)
    #100;

    // Test SD instruction
    // Assume instruction memory is preloaded with SD x5, offset(x6)
    #100;

    // End simulation
    $finish;
  end

  // Monitor the outputs
  initial begin
    $monitor("Time: %0t | PC: %h | Instruction: %h | RegWrite: %b | WriteData: %h",
             $time, uut.pc_out, uut.instruction, uut.regwrite, uut.write_data);
  end

endmodule