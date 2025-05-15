module full_adder(
    input a,
    input b,
    input cin,
    output sum,
    output cout
);
    wire w1, w2, w3;
    xor x1(w1, a, b);
    xor x2(sum, w1, cin);
    and a1(w2, a, b);
    and a2(w3, w1, cin);
    or o1(cout, w2, w3);
endmodule
//ripply carry adder64
module adder64(
    input [63:0] a,
    input [63:0] b,
    input cin,
    output [63:0] sum,
    output cout
);
    wire [63:0] c;
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin : adder_loop
            if (i == 0) begin
                full_adder fa(a[i], b[i], cin, sum[i], c[i]);
            end else begin
                full_adder fa(a[i], b[i], c[i-1], sum[i], c[i]);
            end
        end
    endgenerate
    assign cout = c[63];
endmodule
//a-b 
module subtractor64(
    input [63:0] a,
    input [63:0] b,
    output [63:0] diff,
    output cout
);
    wire [63:0] not_b = ~b;
    adder64 add(a, not_b, 1'b1, diff, cout);
endmodule

module and64(
    input [63:0] a,
    input [63:0] b,
    output [63:0] result
);
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin : and_loop
            and g(result[i], a[i], b[i]);
        end
    endgenerate
endmodule

module or64(
    input [63:0] a,
    input [63:0] b,
    output [63:0] result
);
    genvar i;
    generate
        for (i = 0; i < 64; i = i + 1) begin : or_loop
            or g(result[i], a[i], b[i]);
        end
    endgenerate
endmodule

//beq
module beq64(
    input [63:0] a,
    input [63:0] b,
    output [63:0] result
);
    wire equal;
    assign equal = (a == b);
    assign result = {63'b0, equal};
endmodule
//alu
module ALU(
    input [3:0] control,
    input [63:0] a,
    input [63:0] b,
    output reg [63:0] result
);
    //controls
    parameter ADD  = 4'b0000;
    parameter SUB  = 4'b0001;
    parameter AND  = 4'b0100;
    parameter OR   = 4'b0101;
    parameter BEQ  = 4'b1010;

    wire [63:0] add_result, sub_result;
    wire [63:0] and_result, or_result;
    wire [63:0] beq_result;

    adder64 add_inst(a, b, 1'b0, add_result, );
    subtractor64 sub_inst(a, b, sub_result, );
    and64 and_inst(a, b, and_result);
    or64 or_inst(a, b, or_result);
    beq64 beq_inst(a, b, beq_result);
    always @(*) begin
        case(control)
            ADD:  result = add_result;
            SUB:  result = sub_result;
            AND:  result = and_result;
            OR:   result = or_result;
            BEQ:  result = beq_result;
            default: result = 64'b0;
        endcase
    end
endmodule
