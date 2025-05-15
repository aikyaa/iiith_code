`timescale 1ns / 1ps

module decode_stage_tb;

    // Inputs
    reg clk;
    reg rst;
    reg [31:0] Instruction;
    reg RegWrite;
    reg [4:0] WriteReg;
    reg [31:0] WriteData;

    // Outputs
    wire [31:0] ReadData1, ReadData2;
    wire [31:0] Imm;
    wire [4:0] Rs1, Rs2, Rd;
    wire [2:0] Funct3;
    wire [6:0] Funct7, Opcode;
    wire RegWriteOut, MemReadOut, MemWriteOut, MemToRegOut, ALUSrcOut, BranchOut;
    wire [1:0] ALUOpOut;

    // Instantiate the decode stage
    decode_stage uut (
        .clk(clk),
        .rst(rst),
        .Instruction(Instruction),
        .RegWrite(RegWrite),
        .WriteReg(WriteReg),
        .WriteData(WriteData),
        .ReadData1(ReadData1),
        .ReadData2(ReadData2),
        .Imm(Imm),
        .Rs1(Rs1),
        .Rs2(Rs2),
        .Rd(Rd),
        .Funct3(Funct3),
        .Funct7(Funct7),
        .Opcode(Opcode),
        .RegWriteOut(RegWriteOut),
        .MemReadOut(MemReadOut),
        .MemWriteOut(MemWriteOut),
        .MemToRegOut(MemToRegOut),
        .ALUSrcOut(ALUSrcOut),
        .BranchOut(BranchOut),
        .ALUOpOut(ALUOpOut)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // Toggle clock every 5 time units
    end

    // Testbench logic
    initial begin
        // Initialize inputs
        rst = 1;
        Instruction = 32'h00000000;
        RegWrite = 0;
        WriteReg = 5'b0;
        WriteData = 32'b0;

        // Reset the system
        #10;
        rst = 0;
        #10;
        rst = 1;

        // Test Case 1: R-type instruction (add a0, a1, a2)
        Instruction = 32'h00C58533;  // add a0, a1, a2
        #10;
        $display("Test 1: add a0, a1, a2");
        $display("Opcode: %b, Funct3: %b, Funct7: %b", Opcode, Funct3, Funct7);
        $display("rs1: %b, rs2: %b, rd: %b", Rs1, Rs2, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 2: R-type instruction (sub a0, a1, a2)
        Instruction = 32'h40C58533;  // sub a0, a1, a2
        #10;
        $display("Test 2: sub a0, a1, a2");
        $display("Opcode: %b, Funct3: %b, Funct7: %b", Opcode, Funct3, Funct7);
        $display("rs1: %b, rs2: %b, rd: %b", Rs1, Rs2, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 3: I-type instruction (ld a0, 0(a1))
        Instruction = 32'h0005A503;  // ld a0, 0(a1)
        #10;
        $display("Test 3: ld a0, 0(a1)");
        $display("Opcode: %b, Funct3: %b", Opcode, Funct3);
        $display("rs1: %b, rd: %b", Rs1, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 4: S-type instruction (sd a0, 8(a1))
        Instruction = 32'h00A5A423;  // sd a0, 8(a1)
        #10;
        $display("Test 4: sd a0, 8(a1)");
        $display("Opcode: %b, Funct3: %b", Opcode, Funct3);
        $display("rs1: %b, rs2: %b", Rs1, Rs2);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 5: B-type instruction (beq a1, a0, 4)
        Instruction = 32'h00A58263;  // beq a1, a0, 4
        #10;
        $display("Test 5: beq a1, a0, 4");
        $display("Opcode: %b, Funct3: %b", Opcode, Funct3);
        $display("rs1: %b, rs2: %b", Rs1, Rs2);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 6: Edge Case - rs1 = 0 (x0)
        Instruction = 32'h000502B3;  // add t0, x0, a1
        #10;
        $display("Test 6: add t0, x0, a1");
        $display("Opcode: %b, Funct3: %b, Funct7: %b", Opcode, Funct3, Funct7);
        $display("rs1: %b, rs2: %b, rd: %b", Rs1, Rs2, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 7: Edge Case - rs2 = 0 (x0)
        Instruction = 32'h000582B3;  // add t0, a1, x0
        #10;
        $display("Test 7: add t0, a1, x0");
        $display("Opcode: %b, Funct3: %b, Funct7: %b", Opcode, Funct3, Funct7);
        $display("rs1: %b, rs2: %b, rd: %b", Rs1, Rs2, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 8: Edge Case - rd = 0 (x0)
        Instruction = 32'h00C50033;  // add x0, a1, a2
        #10;
        $display("Test 8: add x0, a1, a2");
        $display("Opcode: %b, Funct3: %b, Funct7: %b", Opcode, Funct3, Funct7);
        $display("rs1: %b, rs2: %b, rd: %b", Rs1, Rs2, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 9: Edge Case - Large Immediate (I-type)
        Instruction = 32'hFFFFF503;  // ld a0, -1(a1)
        #10;
        $display("Test 9: ld a0, -1(a1)");
        $display("Opcode: %b, Funct3: %b", Opcode, Funct3);
        $display("rs1: %b, rd: %b", Rs1, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // Test Case 10: Invalid Instruction
        Instruction = 32'hFFFFFFFF;  // Invalid opcode
        #10;
        $display("Test 10: Invalid Instruction");
        $display("Opcode: %b, Funct3: %b", Opcode, Funct3);
        $display("rs1: %b, rs2: %b, rd: %b", Rs1, Rs2, Rd);
        $display("Imm: %h", Imm);
        $display("-----------------------------");

        // End simulation
        $stop;
    end

endmodule