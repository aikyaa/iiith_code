`timescale 1ns/1ps

module alu_tb;
    reg [2:0] funct3;
    reg [6:0] funct7;
    reg [63:0] rs1, rs2;
    wire [63:0] rd;

    alu uut (
        .funct3(funct3),
        .funct7(funct7),
        .rs1(rs1),
        .rs2(rs2),
        .rd(rd)
    );

    initial begin
        $dumpfile("alu_tb.vcd");
        $dumpvars(0, alu_tb);
        
        // Test ADD
        rs1 = 64'd10; rs2 = 64'd15;
        funct3 = 3'b000; funct7 = 7'b0000000;
        #10;
        $display("ADD: %d + %d = %d", rs1, rs2, rd);

        // Test SUB
        rs1 = 64'd20; rs2 = 64'd5;
        funct3 = 3'b000; funct7 = 7'b0010100;
        #10;
        $display("SUB: %d - %d = %d", rs1, rs2, rd);

        // Test AND
        rs1 = 64'hFFFF; rs2 = 64'h0F0F;
        funct3 = 3'b111; funct7 = 7'b0000000;
        #10;
        $display("AND: %h & %h = %h", rs1, rs2, rd);

        // Test OR
        rs1 = 64'hAAAA; rs2 = 64'h5555;
        funct3 = 3'b110; funct7 = 7'b0000000;
        #10;
        $display("OR: %h | %h = %h", rs1, rs2, rd);

        // Test XOR
        rs1 = 64'hFFFF; rs2 = 64'hAAAA;
        funct3 = 3'b100; funct7 = 7'b0000000;
        #10;
        $display("XOR: %h ^ %h = %h", rs1, rs2, rd);

        // Test SLL (Logical Shift Left)
        rs1 = 64'h1; rs2 = 64'd2;
        funct3 = 3'b001; funct7 = 7'b0000000;
        #10;
        $display("SLL: %h << %d = %h", rs1, rs2[4:0], rd);

        // Test SRL (Logical Shift Right)
        rs1 = 64'h8; rs2 = 64'd1;
        funct3 = 3'b101; funct7 = 7'b0000000;
        #10;
        $display("SRL: %h >> %d = %h", rs1, rs2[4:0], rd);

        // Test SRA (Arithmetic Shift Right)
        rs1 = 64'h8000000000000000; rs2 = 64'd2;
        funct3 = 3'b101; funct7 = 7'b0010100;
        #10;
        $display("SRA: %h >>> %d = %h", rs1, rs2[4:0], rd);

        // Test SLT (Set Less Than)
        rs1 = 64'd10; rs2 = 64'd20;
        funct3 = 3'b010; funct7 = 7'b0000000;
        #10;
        $display("SLT: %d < %d = %h", rs1, rs2, rd);

        // Test SLTU (Set Less Than Unsigned)
        rs1 = 64'hFFFFFFFFFFFFFFF0; rs2 = 64'h0F;
        funct3 = 3'b011; funct7 = 7'b0000000;
        #10;
        $display("SLTU: %h < %h = %h", rs1, rs2, rd);

        $finish;
    end
endmodule
