module FetchUnit (
    input wire Clk,              // Clock signal
    input wire reset,            // Reset signal
    input wire [63:0] pc_next,  // Next program counter value
    output reg [63:0] PC,        // Current program counter value
    output reg [31:0] instruction // Fetched instruction
);

    // Internal signals
    reg [63:0] instruction_address; // Address to fetch instruction
    reg [31:0] memory [255:0];     // Instruction memory (256 words of 32 bits each)

    // Initialize the program counter and instruction address to 0
    initial begin
        PC <= 64'd0;
        instruction_address <= 64'd0;
    end

    // Initialize instruction memory with predefined instructions
    initial begin
        // Instruction format: [funct7][rs2][rs1][funct3][rd][opcode]

        // ADD x1, x2, x3  (x1 = x2 + x3)
        memory[0] = 32'h00620167;

        // ADD x4, x5, x6  (x4 = x5 + x6)
        memory[1] = 32'h00A30233;

        // SUB x7, x4, x1  (x7 = x4 - x1)
        memory[2] = 32'h402083B3;

        // AND x4, x5, x6  (x4 = x5 & x6)
        memory[3] = 32'h00C2F233;

        // OR x7, x8, x9   (x7 = x8 | x9)
        memory[4] = 32'h012473B3;

        // BEQ x14, x7, 4  (Branch if x14 == x7)
        memory[5] = 32'h01C3A267;

        // AND x4, x5, x6  (x4 = x5 & x6)
        memory[6] = 32'h00C2F233;

        // SW x5, 16(x10)  (Store x5 at address x10 + 16)
        memory[7] = 32'h01D52983;

        // LD x7, 16(x10)  (Load x7 from address x10 + 16)
        memory[8] = 32'h01052387;

        // OR x15, x7, x8  (x15 = x7 | x8)
        memory[9] = 32'h00E477B3;
    end

    // Program Counter Logic
    always @(posedge Clk or posedge reset) begin
        if (reset) begin
            PC <= 64'd0;               // Reset the program counter
            instruction_address <= 64'd0; // Reset the instruction address
        end else begin
            PC <= pc_next;             // Update to the next program counter value
            instruction_address <= pc_next; // Update the instruction address
        end
    end

    // Instruction Fetch Logic
    always @(*) begin
        instruction = memory[instruction_address[63:2]]; // Fetch instruction
    end

endmodule