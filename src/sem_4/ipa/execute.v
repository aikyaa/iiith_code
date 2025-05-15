`include "ALU.v"
module execute (
    input [63:0] pc_id_ex,
    input [63:0] read_data1,
    input [63:0] read_data2,
    input [63:0] sign_extended_imm,
    input [3:0] funct3,
    input [6:0] funct7,
    input [1:0] ALUOp,
    input ALUSrc,
    input Branch,
    output reg [63:0] alu_result,
    output reg zero,
    output reg [63:0] branch_target,
    output reg [63:0] read_data2_out
);
    wire [63:0] alu_input2;
    wire [3:0] alu_control;
    wire [63:0] alu_out;
    alu_control_unit acu (
        .ALUOp(ALUOp),
        .funct3(funct3),
        .funct7(funct7),
        .alu_control(alu_control)
    );
    assign alu_input2 = ALUSrc ? sign_extended_imm : read_data2;
    ALU alu (
        .control(alu_control),
        .a(read_data1),
        .b(alu_input2),
        .result(alu_out)
    );
    wire [63:0] branch_offset;
    adder64 add_pc (
        .a(pc_id_ex),
        .b(sign_extended_imm),
        .cin(1'b0),
        .sum(branch_offset),
        .cout()
    );
    wire zero_flag;
    assign zero_flag = (alu_out == 64'b1);
    always @(*) begin
        alu_result = alu_out;
        zero = zero_flag;
        branch_target = branch_offset;
        read_data2_out = read_data2;
    end

endmodule
module alu_control_unit (
    input [1:0] ALUOp,
    input [2:0] funct3,
    input [6:0] funct7,
    output reg [3:0] alu_control
);
    always @(*) begin
        case (ALUOp)
            2'b00: begin// ld/sd(address calculation)
                alu_control = 4'b0000;//add
            end
            2'b01: begin//beq
                alu_control = 4'b1010;
            end
            2'b10: begin//R-type
                case (funct3)
                    3'b000: begin
                        if (funct7 == 7'b0000000)
                            alu_control = 4'b0000;//add
                        else if (funct7 == 7'b0100000)
                            alu_control = 4'b0001;//sub
                        else
                            alu_control = 4'b0000;
                    end
                    3'b010: alu_control = 4'b0010;//slt
                    3'b011: alu_control = 4'b0011;//sltu
                    3'b111: alu_control = 4'b0100;//and
                    3'b110: alu_control = 4'b0101;//or
                    3'b100: alu_control = 4'b0110;//xor
                    3'b001: alu_control = 4'b0111;//sll
                    3'b101: begin
                        if (funct7 == 7'b0000000)
                            alu_control = 4'b1000;//srl
                        else if (funct7 == 7'b0100000)
                            alu_control = 4'b1001;//sra
                        else
                            alu_control = 4'b1000;
                    end
                    default: alu_control = 4'b0000;
                endcase
            end
            default: alu_control = 4'b0000;
        endcase
    end

endmodule