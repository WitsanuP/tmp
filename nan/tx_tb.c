
`timescale 1ns / 1ps

module uart_tx_tb;
    parameter CLK_FREQ = 75000000;
    parameter BAUD_RATE = 921600;
    localparam integer CLK_PERIOD = 1000000000 / CLK_FREQ;
    localparam integer BIT_PERIOD = 1000000000 / BAUD_RATE;
    
    reg clk;
    reg nRESET;
    reg [7:0] data_in;
    reg enable;
    wire tx;
    wire busy;
    
    uart_tx #(.CLK_FREQ(CLK_FREQ), .BAUD_RATE(BAUD_RATE)) dut (
        .clk(clk),
        .nRESET(nRESET),
        .data_in(data_in),
        .enable(enable),
        .tx(tx),
        .busy(busy)
    );
    
    always #(CLK_PERIOD/2) clk = ~clk;
    
    initial begin
        clk = 0;
        nRESET = 0;
        enable = 0;
        data_in = 8'h00;
        #(10 * CLK_PERIOD);
        nRESET = 1;
        
        // Test sending data 8'hA5
        #(10 * CLK_PERIOD);
        enable = 1;
        data_in = 8'hA5;
        #(CLK_PERIOD);
        enable = 0;
        while (busy) #(CLK_PERIOD); // Wait until TX is ready
        #(BIT_PERIOD * 10); // Wait for transmission
        
        // Test sending another byte 8'h3C
        #(10 * CLK_PERIOD);
        enable = 1;
        data_in = 8'h3C;
        #(CLK_PERIOD);
        enable = 0;
        while (busy) #(CLK_PERIOD); // Wait until TX is ready
        #(BIT_PERIOD * 10);
        
        $stop;
    end
endmodule
