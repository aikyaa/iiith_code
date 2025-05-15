module Data_memory (
  input wire Clk,
  input wire [63:0] address,      
  input wire [63:0] Data_write, 
  input wire MemWrite,      
  input wire MemRead,       
  output reg [63:0] Data_read 
);


  reg [7:0] storage [0:1023]; 
  

  integer i;
  initial begin
    for (i = 0; i < 1024; i = i + 1) begin
      storage[i] = 8'd0;  // Initialize all memory to 0
    end
  end
  // Memory write operation (store)
  always @(posedge Clk) begin
    if (MemWrite) begin
    
      storage[address]     <= Data_write[7:0];
      storage[address+1]   <= Data_write[15:8];
      storage[address+2]   <= Data_write[23:16];
      storage[address+3]   <= Data_write[31:24];
      storage[address+4]   <= Data_write[39:32];
      storage[address+5]   <= Data_write[47:40];
      storage[address+6]   <= Data_write[55:48];
      storage[address+7]   <= Data_write[63:56];
    end
  end
  
  // Memory read operation (load)
  always @(*) begin
    if (MemRead) begin
     
      Data_read  = {
        storage[address+7], storage[address+6], storage[address+5], storage[address+4],
        storage[address+3], storage[address+2], storage[address+1], storage[address]
      };
    end else begin
      Data_read = 64'd0;
    end
  end

endmodule