`timescale 1ns / 1ps

module mem_stage_tb;

    // Inputs
    reg clk;
    reg rst;
    reg memread;
    reg memwrite;
    reg [2:0] mem_size;
    reg [63:0] address;
    reg [63:0] write_data;

    // Outputs
    wire [63:0] read_data;
    wire mem_exception;

    // Instantiate the Unit Under Test (UUT)
    mem_stage uut (
        .clk(clk),
        .rst(rst),
        .memread(memread),
        .memwrite(memwrite),
        .mem_size(mem_size),
        .address(address),
        .write_data(write_data),
        .read_data(read_data),
        .mem_exception(mem_exception)
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
        memread = 0;
        memwrite = 0;
        mem_size = 3'b000;
        address = 64'h0;
        write_data = 64'h0;

        // Reset the system
        #10;
        rst = 0;

        // Test 1: Write byte (SB) to address 0
        #10;
        memread = 0;
        memwrite = 1;
        mem_size = 3'b000; // Byte
        address = 64'h0;
        write_data = 64'hA5;
        #10;
        memwrite = 0;
        $display("Test 1: SB to addr 0, WriteData=%h", write_data);

        // Test 2: Read byte (LB) from address 0
        #10;
        memread = 1;
        mem_size = 3'b000; // Byte
        #10;
        $display("Test 2: LB from addr 0, ReadData=%h, MemException=%b (expect A5, 0)", read_data, mem_exception);

        // Test 3: Write halfword (SH) to address 2
        #10;
        memread = 0;
        memwrite = 1;
        mem_size = 3'b001; // Halfword
        address = 64'h2;
        write_data = 64'h1234;
        #10;
        memwrite = 0;
        $display("Test 3: SH to addr 2, WriteData=%h", write_data);

        // Test 4: Read halfword (LH) from address 2
        #10;
        memread = 1;
        mem_size = 3'b001; // Halfword
        #10;
        $display("Test 4: LH from addr 2, ReadData=%h, MemException=%b (expect 1234, 0)", read_data, mem_exception);

        // Test 5: Write word (SW) to address 4
        #10;
        memread = 0;
        memwrite = 1;
        mem_size = 3'b010; // Word
        address = 64'h4;
        write_data = 64'hDEADBEEF;
        #10;
        memwrite = 0;
        $display("Test 5: SW to addr 4, WriteData=%h", write_data);

        // Test 6: Read word (LW) from address 4
        #10;
        memread = 1;
        mem_size = 3'b010; // Word
        #10;
        $display("Test 6: LW from addr 4, ReadData=%h, MemException=%b (expect DEADBEEF, 0)", read_data, mem_exception);

        // Test 7: Misaligned word read (LW) from address 5
        #10;
        mem_size = 3'b010; // Word
        address = 64'h5; // Misaligned
        #10;
        $display("Test 7: LW from addr 5, ReadData=%h, MemException=%b (expect 0, 1)", read_data, mem_exception);

        // End simulation
        #10;
        $stop;
    end

    // Dumpfile generation
    initial begin
        $dumpfile("mem_stage_tb.vcd");
        $dumpvars(0, mem_stage_tb);
    end

    // Monitor signals
    initial begin
        $monitor("Time=%t, clk=%b, rst=%b, memread=%b, memwrite=%b, mem_size=%b, address=%h, write_data=%h, read_data=%h, mem_exception=%b", 
                 $time, clk, rst, memread, memwrite, mem_size, address, write_data, read_data, mem_exception);
    end

endmodule