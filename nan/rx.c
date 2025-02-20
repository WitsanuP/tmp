
module uart_rx #(parameter CLK_FREQ   = 75_000_000, // System Clock Frequency (Hz)
                  parameter BAUD_RATE = 9_216_000)  // UART Baud Rate
(
    input  wire       clk,
    input  wire       nRESET,
    input  wire       rx,
    output reg  [7:0] data_out,
    output reg        data_valid
);

    localparam integer BAUD_CNT_MAX = CLK_FREQ / BAUD_RATE;
    localparam integer HALF_BAUD_CNT = BAUD_CNT_MAX / 2;
    
    reg [3:0]  bit_count;
    reg        reg_bit_count, reg_bit_count2;

    reg [7:0]  shift_reg;
    reg [15:0] baud_counter;
    reg        receiving;
    
    always @(posedge clk or negedge nRESET) begin
        if (~nRESET) begin
            baud_counter <= 0;
            bit_count    <= 0;
            shift_reg    <= 0;
            receiving    <= 0;
     
        end else begin
            if (!receiving) begin
                if (!rx) begin  // Start bit detected
                    receiving    <= 1;
                    baud_counter <= HALF_BAUD_CNT;
                    bit_count    <= 0;
                end
            end 
            else begin
                if (baud_counter == BAUD_CNT_MAX - 1) begin
                    baud_counter <= 0;
                    shift_reg    <= {rx, shift_reg[7:1]};
                    bit_count    <= bit_count + 1;
                    
                    if (bit_count == 8) begin // Stop bit
                     
                        receiving   <= 0;
                    end 
                end else begin
                    baud_counter <= baud_counter + 1;
               
                end
            end
        end
    end
    always @(posedge clk or negedge nRESET) begin
        if (~nRESET) begin
            data_out    <= 0;
        end else begin
            data_out    <= shift_reg;
        end
    end

    always @(posedge clk or negedge nRESET) begin
        if (~nRESET) begin
            data_valid   <= 0;
        end else begin
                data_valid   <= reg_bit_count & ~reg_bit_count2;
        end
    end

    always @(posedge clk or negedge nRESET) begin
        if (~nRESET) begin
            reg_bit_count   <= 0;
        end else begin
           if ( bit_count == 9)  reg_bit_count <= 1;
           else reg_bit_count <= 0;
        end
    end

    always @(posedge clk or negedge nRESET) begin
        if (~nRESET) begin
            reg_bit_count2 <= 0;
        end else begin
            reg_bit_count2<= reg_bit_count;
        end
    end
    
endmodule
