module decode_stage (
    input [31:0] instruction,
    output reg [4:0] rs1,
    output reg [4:0] rs2,
    output reg [4:0] rd,
    output reg [31:0] immediate,
    output reg RegWrite,
    output reg ALUSrc,
    output reg MemWrite,
    output reg MemRead,
    output reg [2:0] ALUOp,
    output reg Branch,
    output reg MemtoReg,
    output reg [2:0] funct3,
    output reg [7:0] funct7
);

    // Extract opcode and funct fields
    wire [6:0] opcode = instruction[6:0];
    funct3 = instruction[14:12];
    funct7 = instruction[31:25];

    always @(*) begin
        // Default values
        immediate = 32'b0;
        RegWrite = 1'b0;
        ALUSrc = 1'b0;
        MemWrite = 1'b0;
        MemRead = 1'b0;
        ALUOp = 3'b000;
        Branch = 1'b0;
        MemtoReg = 1'b0;

        case (opcode)
            // R-type instructions (e.g., add, sub, and, or, etc.)
            7'b0110011: begin
                rs1 = instruction[19:15];
                rs2 = instruction[24:20];
                rd = instruction[11:7];
                ALUOp = {funct7[5], funct3};  // ALU operation based on funct7 and funct3
            end

            // I-type instructions (e.g., addi, lw, jalr)
            7'b0010011, 7'b0000011, 7'b1100111: begin
                rs1 = instruction[19:15];
                rd = instruction[11:7];
                ALUSrc = 1'b1;   // Use immediate as ALU input
                immediate = {{20{instruction[31]}}, instruction[31:20]}; // Sign-extended immediate
                ALUOp = funct3;  // ALU operation based on funct3

                // Special case for load instructions (lw, lb, lh, etc.)
                if (opcode == 7'b0000011) begin
                    MemRead = 1'b1;   // Read from memory
                    MemtoReg = 1'b1;  // Data memory to register
                end
            end

            // S-type instructions (e.g., sw, sb, sh)
            7'b0100011: begin
                rs1 = instruction[19:15];
                rs2 = instruction[24:20];
                ALUSrc = 1'b1;   // Use immediate as ALU input
                MemWrite = 1'b1;  // Write to memory
                immediate = {{20{instruction[31]}}, instruction[31:25], instruction[11:7]}; // Corrected sign-extended immediate
            end

            // B-type instructions (e.g., beq, bne, blt, bge)
            7'b1100011: begin
                rs1 = instruction[19:15];
                rs2 = instruction[24:20];
                Branch = 1'b1;    // Branch instruction
                immediate = {{19{instruction[31]}}, instruction[31], instruction[7], instruction[30:25], instruction[11:8], 1'b0}; // Corrected sign-extended immediate
                ALUOp = funct3;   // ALU operation based on funct3 (for comparison)
            end

            // Default case (unknown opcode or NOP)
            default: begin
                // Handle unknown opcodes or NOP
            end
        endcase
    end

endmodule
