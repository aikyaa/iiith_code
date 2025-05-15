`timescale 1ns/1ps

module cla_4 (
    input wire [3:0] a,
    input wire [3:0] b,
    input wire Cin,
    output [3:0] s,
    output Cout 
);

    wire G[3:0], P[3:0];
    wire AxB[3:0];
    
    wire C0, C0not, C1, C2, C3, C4, Gout, c1b, c2b, c3b, c4b;
    wire c1bnot, c2midnor, c2midand, c3midnor, c3midand, midnor, midand,midor;
    wire c2midnand, c3midnand, midnand,c2midor, c3midor,Pout;

    
    nand (G[3], a[3], b[3]);
    nand (G[2], a[2], b[2]);
    nand (G[1], a[1], b[1]);
    nand (G[0], a[0], b[0]);

    nor (P[3], a[3], b[3]);
    nor (P[2], a[2], b[2]);
    nor (P[1], a[1], b[1]);
    nor (P[0], a[0], b[0]);

    xor (AxB[3], a[3], b[3]);
    xor (AxB[2], a[2], b[2]);
    xor (AxB[1], a[1], b[1]);
    xor (AxB[0], a[0], b[0]);


    assign C0 = Cin;
    
    not (C0not, C0);               
    or (c1b, P[0], C0not);               
    nand (C1, G[0], c1b); 

    or (c2b, P[1], G[0]);                 
    nand (c2midnand, G[1], c2b);        
    nor (c2midnor, P[0], P[1]);             
    and (c2midand, C0, c2midnor);     
    or (C2, c2midnand, c2midand); 

    nor (c3midnor, P[2], P[1]);           
    or (c3midor, P[2], G[1]);             
    nand (c3midnand, G[2], c3midor);    
    and (c3midand, C1, c3midnor);            
    or (C3, c3midnand, c3midand);  

    nor (midnor, P[3], P[2]);
    or (midor, P[3], G[2]);
    nand (midnand, G[3], midor);
    and ( midand, c2midnand, midnor);
    or (Gout, midnand, midand);
    nand (Pout, c2midnor, midnor);

    nor (c4b,Pout, C0not);
    or (Cout, Gout, c4b);  

    xor (s[3], AxB[3], C3);          
    xor (s[2], AxB[2], C2);             
    xor (s[1], AxB[1], C1);              
    xor (s[0], AxB[0], C0);     

endmodule

module cla_64(
    input wire [63:0] a,
    input wire [63:0] b,
    input wire Cin,
    output [63:0] s,
    output Cout
);
    wire [15:0] ci;
    assign ci[0] = 0;
    genvar i;
    generate
        for (i=0; i<16;i=i+1) begin
            cla_4 cla4(a[i*4 +: 4], b[i*4 +: 4], ci[i], s[i*4 +: 4], ci[i+1]);
        end
    endgenerate
    assign Cout = ci[15];
endmodule

 
module sub(
    input wire [63:0] a,
    input wire [63:0] b,
    output [63:0] s
);

    wire [63:0]bc;
    wire cout;
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin
            not n1(bc[i], b[i]);
        end
    endgenerate
    cla_64 cla64(a, bc, 1'b1, s, cout);
endmodule

module xorop(
    input wire [63:0] a,
    input wire [63:0] b,
    output wire [63:0] s
);
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin
            xor x1(s[i], b[i], a[i]);
        end
    endgenerate
endmodule

module andop(
    input wire [63:0] a,
    input wire [63:0] b,
    output wire [63:0] s
);
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin
            and a1(s[i], b[i], a[i]);
        end
    endgenerate
endmodule

module orop(
    input wire [63:0] a,
    input wire [63:0] b,
    output wire [63:0] s
);
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin
            or o1(s[i], b[i], a[i]);
        end
    endgenerate
endmodule

module sll(
    input wire [63:0] a,
    input wire [4:0] amt,
    output reg [63:0] s
);
    integer i;
    always @(*) begin
        s=a;
        for (i = 0; i < amt; i = i + 1) begin
                s = {s[62:0], 1'b0};
        end
    end
endmodule

module srl(
    input wire [63:0] a,
    input wire [4:0] amt,
    output reg [63:0] s
);
    integer i;
    always @(*) begin
        s=a;
        for (i = 0; i < amt; i = i + 1) begin
                s = {1'b0, s[63:1]};
        end
    end
endmodule

module sra(
    input wire [63:0] a,
    input wire [4:0] amt,
    output reg [63:0] s
);
    integer i;
    always @(*) begin
        s=a;
        for (i = 0; i < amt; i = i + 1) begin
                s = {s[63], s[63:1]};
        end
    end
endmodule

module slt(
    input wire [63:0] a,
    input wire [63:0] b,
    output wire [63:0] s
);
    wire [63:0] temp;
    sub s1(a, b, temp);
    assign s = {63'b0, temp[63]};
endmodule

module alu(
    input wire [2:0] funct3,
    input wire [6:0] funct7,
    input wire [63:0] rs1,
    input wire [63:0] rs2,
    output reg [63:0] rd
);
    wire temp;
    always @(*) begin
        case ({funct7, funct3})

            {7'b0000000, 3'b000}: begin // ADD
                cla_64 adder(rs1, rs2, 1'b0, rd, temp);
            end
            {7'b0010100, 3'b000}: begin // SUB
                sub s0(rs1, rs2, rd);
            end

            {7'b0000000, 3'b111}: begin // AND
                andop modand(rs1,rs2,rd);
            end
            {7'b0000000, 3'b110}: begin // OR
                orop modor(rs1,rs2,rd);
            end
            {7'b0000000, 3'b100}: begin // XOR
                xorop modxor(rs1, rs2, rd);
            end

            {7'b0000000, 3'b001}: begin //SLL
                sll modsll(rs1, rs2[0+:5], rd);
            end
            {7'b0000000, 3'b101}: begin //SLR
                srl modsrl(rs1, rs2[0+:5], rd);
            end
            {7'b0010100, 3'b101}: begin //SRA
                sra modsra(rs1, rs2[0+:5], rd);
            end

            {7'b0000000, 3'b010}: begin // SLT
                slt modslt(rs1, rs2, rd);
            end
            {7'b0000000, 3'b011}: begin // SLTU
                rd = {63'b0, (rs1 < rs2)};
            end
            default: rd = 64'b0;
        endcase
    end
endmodule

