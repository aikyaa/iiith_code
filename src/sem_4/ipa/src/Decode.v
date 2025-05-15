module Decode (
    input wire Clk,  // Instruction from FetchUnit
    input [63:0] write_data, // Data to be written to the register file 
    input [31:0] Instruction,         // Register write enable signal
    output [63:0] A,         // Read data 1 (rs1)
    output [63:0] B,         // Read data 2 (rs2)
    output reg [63:0] C,         // Immediate value
    output reg Branch,
    output reg MemRead,
    output reg MemtoReg,
    output reg [1:0] ALUOp,
    output reg MemWrite,
    output reg ALUSrc,
    output reg RegWrite       // Register write output signal
);

    // Internal signals
    wire [4:0] rs1, rs2, rd;
    assign rs1 = Instruction[19:15]; // Extract rs1 from instruction
    assign rs2 = Instruction[24:20]; // Extract rs2 from instruction
    assign rd = Instruction[11:7];   // Extract rd from instruction

    // Control Unit Logic
    always @(*) begin
        // Default control signals
        Branch = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        ALUOp = 2'b00;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b0;

        case (Instruction[6:0]) // Decode based on opcode
            // R-Type instructions
            7'b0110011: begin
                ALUOp = 2'b10;
                RegWrite = 1'b1;
            end
            // Load instructions
            7'b0000011: begin
                MemRead = 1'b1;
                MemtoReg = 1'b1;
                ALUSrc = 1'b1;
                RegWrite = 1'b1;
            end
            // Store instructions
            7'b0100011: begin
                MemWrite = 1'b1;
                ALUSrc = 1'b1;
            end
            // Branch instructions
            7'b1100011: begin
                Branch = 1'b1;
                ALUOp = 2'b01;
            end
            // Default case (invalid opcode)
            default: begin
                // All control signals remain at their default values
            end
        endcase
    end

    // Immediate Generator Logic
    always @(*) begin
        case (Instruction[6:0]) // Decode based on opcode
            // I-Type: ALU immediate or load
            7'b0010011, 7'b0000011: begin
                C = {{52{Instruction[31]}}, Instruction[31:20]};
            end
            // S-Type: Store
            7'b0100011: begin
                C = {{52{Instruction[31]}}, Instruction[31:25], Instruction[11:7]};
            end
            // B-Type: Branch
            7'b1100011: begin
                C = {{52{Instruction[31]}}, Instruction[7], Instruction[30:25], Instruction[11:8], 1'b0};
            end
            // Default case
            default: begin
                C = 64'b0;
            end
        endcase
    end

    // Register File Logic
    reg [63:0] registers [0:31]; // Register file (32 registers of 64 bits each)

    // Initialize registers with default values
    initial begin
        registers[0] = 64'd0;
        registers[1] = 64'd1;
        registers[2] = 64'd2;
        registers[3] = 64'd3;
        registers[4] = 64'd4;
        registers[5] = 64'd5;
        registers[6] = 64'd6;
        registers[7] = 64'd7;
        registers[8] = 64'd8;
        registers[9] = 64'd9;
        registers[10] = 64'd2;
        registers[11] = 64'd11;
        registers[12] = 64'd12;
        registers[13] = 64'd6;
        registers[14] = 64'd9;
        registers[15] = 64'd15;
        registers[16] = 64'd16;
        registers[17] = 64'd17;
    end

    // Read data from registers
    assign A = registers[rs1];
    assign B = registers[rs2];

    // Write data to register file on the negative edge of the clock
    always @(negedge Clk) begin
        if (RegWrite && (rd != 5'd0)) begin
            registers[rd] <= write_data;
        end
    end

endmodule