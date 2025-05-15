module ALU_test ;

// Inputs
reg [63:0] A;
reg [63:0] B;
reg [3:0] ALUcontrol;
reg [6:0] funct7;

wire [63:0] result;
wire zero ;
    ALU uut (
        .result(result),
        .zero(zero),
        .A(A),
        .B(B),
        .ALUcontrol(ALUcontrol)
    );
    
    // Test stimulus
    initial begin
        // Initialize with some delay
        #10;
        
        // Test 1: ADD
        A = 64'b0000000000000000000000000000000000000000000000000000000000000101; // 5
        B = 64'b0000000000000000000000000000000000000000000000000000000000000011; // 3
        ALUcontrol = 4'b0010;
        #10;
        $display("ADD Test: \nA=%b\nB=%b\nResult=%b\n", A, B, result);
        $display("-------------------------------------------------------------------------------\n");
        // Test 2: SUB
        A = 64'b0000000000000000000000000000000000000000000000000000000000000101; // 5
        B = 64'b0000000000000000000000000000000000000000000000000000000000000011; // 3
        ALUcontrol = 4'b0110;
        #10;
        $display("SUB Test: \nA=%b\nB=%b\nResult=%b\n", A, B, result);
        $display("-------------------------------------------------------------------------------\n");
        // Test 3: AND
        A = 64'b0000000000000000000000000000000000000000000000000000000000001111;
        B = 64'b0000000000000000000000000000000000000000000000000000000000000011;
        ALUcontrol = 4'b0000;
        #10;
        $display("AND Test:\nA=%b\nB=%b\nResult=%b\n", A, B, result);
        $display("-------------------------------------------------------------------------------\n");
        // Test 4: OR
        A = 64'b0000000000000000000000000000000000000000000000000000000000001100;
        B = 64'b0000000000000000000000000000000000000000000000000000000000000011;
        ALUcontrol = 4'b0001;
        #10;
        $display("OR Test:\nA=%b\nB=%b\nResult=%b\n", A, B, result);
        $display("-------------------------------------------------------------------------------\n");
        
        $finish;
    end
    
    // Optional: Generate VCD file for waveform viewing
    initial begin
        $dumpfile("ALU_test.vcd");
        $dumpvars(0, ALU_test);
    end
    

    
endmodule