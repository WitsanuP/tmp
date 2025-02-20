`timescale 1ns / 1ps

module uart_tx #(parameter CLK_FREQ = 75000000, // System Clock Frequency (Hz)
                  parameter BAUD_RATE = 921600)  // UART Baud Rate
(
    input  wire       clk,
    input  wire       nRESET,
    input  wire [7:0] data_in,
    input  wire       enable,
    output reg        tx,
    output reg        busy
);

    localparam integer BAUD_CNT_MAX = CLK_FREQ / BAUD_RATE;
    
    reg [3:0] bit_count;
    reg [8:0] shift_reg;
    reg [15:0] baud_counter;
    reg sending;
    
    always @(posedge clk or negedge nRESET) begin
        if (!nRESET) begin
            baud_counter <= 0;
            bit_count    <= 0;
            shift_reg    <= 9'b111111111;
            sending      <= 0;
            tx           <= 1;
            busy         <= 0;
        end else begin
            if (enable && !sending) begin // Start transmission
                shift_reg <= {1'b1, data_in, 1'b0}; // Stop bit, data, start bit
                sending   <= 1;
                bit_count <= 0;
                baud_counter <= 0;
                busy      <= 1;
            end
            
            if (sending) begin
                if (baud_counter == BAUD_CNT_MAX - 1) begin
                    baud_counter <= 0;
                    tx           <= shift_reg[0];
                    shift_reg    <= {1'b1, shift_reg[8:1]};
                    bit_count    <= bit_count + 1;
                    
                    if (bit_count == 10) begin // Stop bit sent
                        sending <= 0;
                        busy    <= 0;
                    end
                end else begin
                    baud_counter <= baud_counter + 1;
                end
            end
        end
    end
endmodule
