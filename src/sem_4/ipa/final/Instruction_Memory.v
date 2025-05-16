module Instruction_Memory(rst,A,RD);

  input rst;
  input [63:0]A;
  output [31:0]RD;

  reg [31:0] mem [1023:0]; //32-bit instructions
  
  assign RD = (rst == 1'b0) ? {32{1'b0}} : mem[A[31:2]]; //word aligned

  initial begin
    $readmemh("memfile2.hex",mem); //memfile2,3 also attached
    //instruction is fetched based on pc value
  end

endmodule