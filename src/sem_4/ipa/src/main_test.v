`timescale 1ns/1ps

module Processor_test;
  reg Clk;
  reg reset;
  
  // Instantiate the Processor
  main uut (
    .Clk(Clk),
    .reset(reset)
  );
  
  // Clock generation
  always #5 Clk = ~Clk; // 10ns clock period
  
  // Task to display results
  task display_results;
    begin
      $display("Time = %0t", $time);
      $display("Current PC = %b", uut.PC);
      $display("C  (immediate_gen_out) = %d", uut.C);
      $display("C  = %b", uut.C);
      $display("Instruction = %b", uut.Instruction);
      $display("A (rs1) = %d", uut.A);
      $display("A  = %b", uut.A);
      $display("B (rs2) = %d", uut.B);
       $display("B  = %b", uut.B);
      $display("ALU_result = %b", uut.ALU_result);
      $display("Target Address = %d", uut.Target);
      $display("Target Address= %b", uut.Target);
      $display("Data into Register (Write back data) = %b", uut.Write_data);
      $display("pc_next = %b", uut.pc_next);
      $display("------------------------------------");
    end
  endtask
  
  initial begin
    $dumpfile("Processorst.vcd");
    $dumpvars(0, Processor_test);
    
    // Initialize signals
    Clk = 0;
    reset = 1;
    
    // Hold reset for a few cycles
    #10;
    display_results();
    reset = 0;
    
    // Run the test and display results at different cycles
    #10 display_results();
    #10 display_results();
    #10 display_results();
    #10 display_results();
    #10 display_results();
    #10 display_results();
     #10 display_results();
      #10 display_results();
    // End simulation
    #50;
    $finish;
  end

endmodule
