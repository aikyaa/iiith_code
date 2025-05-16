
module Sign_Extend (In,ImmSrc,Imm_Ext);
    input [31:0] In;
    input [1:0] ImmSrc;
    output [63:0] Imm_Ext;

    assign Imm_Ext = (ImmSrc == 2'b00) ? {{52{In[31]}}, In[31:20]} :  // I-Type
                     (ImmSrc == 2'b01) ? {{52{In[31]}}, In[31:25], In[11:7]} :  // S-Type
                     64'h0000000000000000;  // Default case
endmodule


module ALU_Decoder(ALUOp,funct3,funct7,op,ALUControl);

    input [1:0]ALUOp;
    input [2:0]funct3;
    input [6:0]funct7,op;
    output reg [2:0] ALUControl;

     always @(*) begin
        case (ALUOp)
            2'b00: ALUControl = 3'b000; // Default for ALUOp = 00 (ld, sd, etc.)
            2'b01: ALUControl = 3'b001; // Default for ALUOp = 01 (Branch)
            2'b10: begin
                case (funct3)
                    3'b000: begin
                        if ({op[5], funct7[5]} == 2'b11)
                            ALUControl = 3'b001; // SUB
                        else
                            ALUControl = 3'b000; // ADD
                    end
                    3'b110: ALUControl = 3'b011; // OR
                    3'b111: ALUControl = 3'b010; // AND
                    default: ALUControl = 3'b000; // Default for unsupported funct3
                endcase
            end
            default: ALUControl = 3'b000; // Default for unsupported ALUOp
        endcase
    end                                                             
endmodule


module Main_Decoder(Op,RegWrite,ImmSrc,ALUSrc,MemWrite,ResultSrc,Branch,ALUOp);
    input [6:0]Op;
    output reg RegWrite,ALUSrc,MemWrite,ResultSrc,Branch;
    output reg[1:0]ImmSrc,ALUOp;

    always @(*) begin
    // Default values to avoid latches
    RegWrite = 1'b0;
    ImmSrc = 2'b00;
    ALUSrc = 1'b0;
    MemWrite = 1'b0;
    ResultSrc = 1'b0;
    Branch = 1'b0;
    ALUOp = 2'b00;

    case (Op)
        7'b0000011: begin // Load instructions (ld, lw, etc.)
            case (funct3)
                3'b000: begin // lb (Load Byte)
                    RegWrite = 1'b1;
                    ALUSrc = 1'b1;
                    ResultSrc = 1'b1;
                    ImmSrc = 2'b00; // I-type immediate
                end
                3'b010: begin // lw (Load Word)
                    RegWrite = 1'b1;
                    ALUSrc = 1'b1;
                    ResultSrc = 1'b1;
                    ImmSrc = 2'b00; // I-type immediate
                end
                3'b011: begin // ld (Load Doubleword)
                    RegWrite = 1'b1;
                    ALUSrc = 1'b1;
                    ResultSrc = 1'b1;
                    ImmSrc = 2'b00; // I-type immediate
                end
                default: begin
                    // Handle other load instructions (e.g., lh, lbu, lhu)
                end
            endcase
        end

        7'b0100011: begin // Store instructions (sd, sw, etc.)
            case (funct3)
                3'b010: begin // sw (Store Word)
                    ImmSrc = 2'b01; // S-type immediate
                    ALUSrc = 1'b1;
                    MemWrite = 1'b1;
                end
                3'b011: begin // sd (Store Doubleword)
                    ImmSrc = 2'b01; // S-type immediate
                    ALUSrc = 1'b1;
                    MemWrite = 1'b1;
                end
                default: begin
                    // Handle other store instructions (e.g., sh, sb)
                end
            endcase
        end

        7'b0110011: begin // R-type instructions
            RegWrite = 1'b1;
            ALUOp = 2'b10;
        end

        7'b0010011: begin // I-type ALU instructions
            RegWrite = 1'b1;
            ALUSrc = 1'b1;
            ImmSrc = 2'b00; // I-type immediate
        end

        7'b1100011: begin // Branch instructions
            ImmSrc = 2'b10; // B-type immediate
            Branch = 1'b1;
            ALUOp = 2'b01;
        end

        default: begin
            // Defaults are already set at the beginning
        end
    endcase
end
endmodule

module Control_Unit_Top(Op,RegWrite,ImmSrc,ALUSrc,MemWrite,ResultSrc,Branch,funct3,funct7,ALUControl);

    input [6:0]Op,funct7;
    input [2:0]funct3;
    output RegWrite,ALUSrc,MemWrite,ResultSrc,Branch;
    output [1:0]ImmSrc;
    output [2:0]ALUControl;

    wire [1:0]ALUOp;

    Main_Decoder Main_Decoder(
                .Op(Op),
                .RegWrite(RegWrite),
                .ImmSrc(ImmSrc),
                .MemWrite(MemWrite),
                .ResultSrc(ResultSrc),
                .Branch(Branch),
                .ALUSrc(ALUSrc),
                .ALUOp(ALUOp)
    );

    ALU_Decoder ALU_Decoder(
                            .ALUOp(ALUOp),
                            .funct3(funct3),
                            .funct7(funct7),
                            .op(Op),
                            .ALUControl(ALUControl)
    );

endmodule

module decode_cycle(clk, rst, InstrD, PCD, PCPlus4D, RegWriteW, RDW, ResultW, RegWriteE, ALUSrcE, MemWriteE, ResultSrcE,
    BranchE,  ALUControlE, RD1_E, RD2_E, Imm_Ext_E, RD_E, PCE, PCPlus4E, RS1_E, RS2_E);

    // Declaring I/O
    input clk, rst, RegWriteW;
    input [4:0] RDW;
    input [31:0] InstrD;
    input [63:0] PCD, PCPlus4D, ResultW;

    output RegWriteE,ALUSrcE,MemWriteE,ResultSrcE,BranchE;
    output [2:0] ALUControlE;
    output [63:0] RD1_E, RD2_E, Imm_Ext_E;
    output [4:0] RS1_E, RS2_E, RD_E;
    output [63:0] PCE, PCPlus4E;

    wire RegWriteD,ALUSrcD,MemWriteD,ResultSrcD,BranchD;
    wire [1:0] ImmSrcD;
    wire [2:0] ALUControlD;
    wire [63:0] RD1_D, RD2_D, Imm_Ext_D;

    reg RegWriteD_r,ALUSrcD_r,MemWriteD_r,ResultSrcD_r,BranchD_r;
    reg [2:0] ALUControlD_r;
    reg [63:0] RD1_D_r, RD2_D_r, Imm_Ext_D_r;
    reg [4:0] RD_D_r, RS1_D_r, RS2_D_r;
    reg [64:0] PCD_r, PCPlus4D_r;


    // Initiate the modules
    // Control Unit
    Control_Unit_Top control (
                            .Op(InstrD[6:0]),
                            .RegWrite(RegWriteD),
                            .ImmSrc(ImmSrcD),
                            .ALUSrc(ALUSrcD),
                            .MemWrite(MemWriteD),
                            .ResultSrc(ResultSrcD),
                            .Branch(BranchD),
                            .funct3(InstrD[14:12]),
                            .funct7(InstrD[31:25]),
                            .ALUControl(ALUControlD)
                            );

    // Register File
    Register_File rf (
                        .clk(clk),
                        .rst(rst),
                        .WE3(RegWriteW),
                        .WD3(ResultW),
                        .A1(InstrD[19:15]),
                        .A2(InstrD[24:20]),
                        .A3(RDW),
                        .RD1(RD1_D),
                        .RD2(RD2_D)
                        );

    // Sign Extension
    Sign_Extend extension (
                        .In(InstrD[31:0]),
                        .Imm_Ext(Imm_Ext_D),
                        .ImmSrc(ImmSrcD)
                        );

    // Declaring Register Logic
    always @(posedge clk or negedge rst) begin
        if(rst == 1'b0) begin
            RegWriteD_r <= 1'b0;
            ALUSrcD_r <= 1'b0;
            MemWriteD_r <= 1'b0;
            ResultSrcD_r <= 1'b0;
            BranchD_r <= 1'b0;
            ALUControlD_r <= 3'b000;
            RD1_D_r <= 64'h00000000; 
            RD2_D_r <= 64'h00000000; 
            Imm_Ext_D_r <= 64'h00000000;
            RD_D_r <= 5'h00;
            PCD_r <= 64'h00000000; 
            PCPlus4D_r <= 64'h00000000;
            RS1_D_r <= 5'h00;
            RS2_D_r <= 5'h00;
        end
        else begin
            RegWriteD_r <= RegWriteD;
            ALUSrcD_r <= ALUSrcD;
            MemWriteD_r <= MemWriteD;
            ResultSrcD_r <= ResultSrcD;
            BranchD_r <= BranchD;
            ALUControlD_r <= ALUControlD;
            RD1_D_r <= RD1_D; 
            RD2_D_r <= RD2_D; 
            Imm_Ext_D_r <= Imm_Ext_D;
            RD_D_r <= InstrD[11:7];
            PCD_r <= PCD; 
            PCPlus4D_r <= PCPlus4D;
            RS1_D_r <= InstrD[19:15];
            RS2_D_r <= InstrD[24:20];
        end
    end

    // Output asssign statements
    assign RegWriteE = RegWriteD_r;
    assign ALUSrcE = ALUSrcD_r;
    assign MemWriteE = MemWriteD_r;
    assign ResultSrcE = ResultSrcD_r;
    assign BranchE = BranchD_r;
    assign ALUControlE = ALUControlD_r;
    assign RD1_E = RD1_D_r;
    assign RD2_E = RD2_D_r;
    assign Imm_Ext_E = Imm_Ext_D_r;
    assign RD_E = RD_D_r;
    assign PCE = PCD_r;
    assign PCPlus4E = PCPlus4D_r;
    assign RS1_E = RS1_D_r;
    assign RS2_E = RS2_D_r;

endmodule
