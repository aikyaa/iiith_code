
module WriteBack (
    input [63:0] ALU_result ,
    input [63:0] Data ,
    input MemtoReg ,
    output  [63:0] Write_data
);
    
    MUX U1(.B(ALU_result), .C(Data), .Sel(MemtoReg), .Y(Write_data)) ;
    
endmodule

