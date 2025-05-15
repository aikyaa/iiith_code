`timescale 1ns/1ps

module riscv_processor_tb;

    // Inputs
    reg clk;
    reg rst;

    // Instantiate the processor
    riscv_processor uut (
        .clk(clk),
        .rst(rst)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 10ns clock period
    end

    // Test sequence
    initial begin
        // Initialize memory with test program
        uut.instr_mem[0] = 32'h002081b3; // ADD x3, x1, x2
        uut.instr_mem[1] = 32'h40308233; // SUB x4, x1, x3
        uut.instr_mem[2] = 32'h0041a023; // SW x4, 0(x3)
        uut.instr_mem[3] = 32'h0001a203; // LW x4, 0(x3)
        uut.instr_mem[4] = 32'h00418263; // BEQ x3, x4, 4
        uut.instr_mem[5] = 32'h00c000ef; // JAL x1, 12
        uut.instr_mem[6] = 32'h00000013; // NOP
        uut.instr_mem[7] = 32'h00000013; // NOP

        // Initialize registers
        uut.registers[1] = 32'h00000005; // x1 = 5
        uut.registers[2] = 32'h00000003; // x2 = 3

        // Reset the processor
        rst = 1;
        #20;
        rst = 0;

        // Run for 100 clock cycles
        #1000;

        // Display final register values
        $display("Final Register Values:");
        for (integer i = 0; i < 32; i = i + 1) begin
            $display("x%0d = %h", i, uut.registers[i]);
        end

        // Display memory contents
        $display("Memory Contents:");
        for (integer i = 0; i < 10; i = i + 1) begin
            $display("Mem[%0d] = %h", i, uut.data_mem[i]);
        end

        // End simulation
        $finish;
    end

    // VCD dump file generation
    initial begin
        $dumpfile("riscv_processor_tb.vcd");
        $dumpvars(0, riscv_processor_tb);
    end

endmodule