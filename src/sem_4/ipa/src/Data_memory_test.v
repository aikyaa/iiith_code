`timescale 1ns/1ps

module Data_memory_test;

// Testbench signals
reg Clk;
reg [63:0] address;
reg [63:0] Data_write;
reg MemWrite;
reg MemRead;
wire [63:0] Data_read;

// Clock generation (50% duty cycle)
always #5 Clk = ~Clk;

// Instantiate the Data_memory module
Data_memory dut (
    .Clk(Clk),
    .address(address),
    .Data_write(Data_write),
    .MemWrite(MemWrite),
    .MemRead(MemRead),
    .Data_read(Data_read)
);

// Test stimulus
initial begin
    Clk = 0;
    address = 64'h0;
    Data_write = 64'h0;
    MemWrite = 0;
    MemRead = 0;
    
    #20;

    // Test Case 1: Write Operation
    $display("Test Case 1: Write Operation");
    address = 64'h10;  // Byte address (word-aligned)
    Data_write = 64'hABCD_1234_5678_90AB;
    MemWrite = 1;
    MemRead = 0;
    #10;
    MemWrite = 0; // Stop writing

    // Test Case 2: Read Operation (Reading previously written data)
    #10;
    $display("Test Case 2: Read Operation");
    MemRead = 1;
    #10;
    if (Data_read === 64'hABCD_1234_5678_90AB)
        $display("Read Test Passed: Expected value matches read value");
    else
        $display("Read Test Failed: Expected %h, got %h", 64'hABCD_1234_5678_90AB, Data_read);
    MemRead = 0;

    // Test Case 3: Write to different location
    #10;
    $display("Test Case 3: Write to different location");
    address = 64'h20;  // Word-aligned
    Data_write = 64'hFFFF_0000_AAAA_5555;
    MemWrite = 1;
    #10;
    MemWrite = 0;

    // Test Case 4: Read from new location
    #10;
    $display("Test Case 4: Read from new location");
    MemRead = 1;
    #10;
    if (Data_read === 64'hFFFF_0000_AAAA_5555)
        $display("Read Test Passed: Expected value matches read value");
    else
        $display("Read Test Failed: Expected %h, got %h", 64'hFFFF_0000_AAAA_5555, Data_read);
    MemRead = 0;

    // Test Case 5: Read with MemRead disabled
    #10;
    $display("Test Case 5: Read with MemRead disabled");
    #10;
    if (Data_read === 64'h0)
        $display("Disabled Read Test Passed: Output is zero when MemRead is disabled");
    else
        $display("Disabled Read Test Failed: Expected 0, got %h", Data_read);

    // Test Case 6: Write and Read from boundary address
    #10;
    $display("Test Case 6: Write and Read from boundary address");
    address = 64'hFF;  // Last valid address
    Data_write = 64'h1111_2222_3333_4444;
    MemWrite = 1;
    MemRead = 0;
    #10;
    MemWrite = 0;
    MemRead = 1;
    #10;
    if (Data_read === 64'h1111_2222_3333_4444)
        $display("Boundary Test Passed: Expected value matches read value");
    else
        $display("Boundary Test Failed: Expected %h, got %h", 64'h1111_2222_3333_4444, Data_read);
    
    #100;
   
    $finish;
end

initial begin
    $dumpfile("data_memory_test.vcd");
    $dumpvars(0, Data_memory_test);
end

endmodule
