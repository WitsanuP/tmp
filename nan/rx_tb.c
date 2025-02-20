
`timescale 1ns / 1ps

module uart_rx_tb;
    
    parameter CLK_FREQ  = 75_000_000;
    // parameter BAUD_RATE = 9_216_00;
    parameter BAUD_RATE = 3_216_000; // for test
    localparam integer CLK_PERIOD = 13333;//1000_000_000 / CLK_FREQ;
    localparam integer BIT_PERIOD = 310945;//1000000000 / BAUD_RATE;
    
    reg clk;
    reg nRESET;
    reg rx;
    wire [7:0] data_out;
    wire data_valid;
    
    uart_rx #(.CLK_FREQ(CLK_FREQ), .BAUD_RATE(BAUD_RATE)) dut (
        .clk(clk),
        .nRESET(nRESET),
        .rx(rx),
        .data_out(data_out),
        .data_valid(data_valid)
    );
    
    always #(CLK_PERIOD/2) clk = ~clk;
    
    initial begin
        clk = 0;
        nRESET = 0;
        rx = 1;
        #(10 * CLK_PERIOD);
        nRESET = 1;
        
        // Send Start Bit
        #(BIT_PERIOD);
        rx = 0;
        
        // Send Data Bits (Example: 8'hA5 -> 10100101)
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 1;
        
        // Send Stop Bit
        #(BIT_PERIOD); rx = 1;
        
        // Wait for Data Valid
        #(10 * BIT_PERIOD);
        

        ///////////
        #(BIT_PERIOD);
        rx = 0;
        
        // Send Data Bits (Example: 8'hA5 -> 10100111)
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 0;
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 1;
        #(BIT_PERIOD); rx = 1;
        
        // Send Stop Bit
        #(BIT_PERIOD); rx = 1;
        
        // Wait for Data Valid
        #(10 * BIT_PERIOD);
        $stop;
    end

    initial begin
        $dumpfile("uart_rx_tb.vcd");
        $dumpvars(0,uart_rx_tb);
        
    end
endmodule
