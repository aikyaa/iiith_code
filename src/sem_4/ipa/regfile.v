module reg_file (
    input clk,
    input RegWrite,
    input [4:0] rs1,
    input [4:0] rs2,
    input [4:0] rd,
    input [31:0] write_data,
    output reg [31:0] read_data1,
    output reg [31:0] read_data2
);

    // 32 registers (R0 to R31)
    reg [31:0] registers [63:0];
    
    // Read registers
    always @(*) begin
        read_data1 = registers[rs1];
        read_data2 = registers[rs2];
    end

    // Write register on the positive clock edge
    always @(posedge clk) begin
        if (RegWrite && rd != 5'b00000) // Register 0 is hardwired to 0
            registers[rd] <= write_data;
    end

endmodule
