module hdmi(Fg_CLK,RESETn,ExtBTN,IntBTN); //! edit
// -------------------- Port ---------------------
    input           hdmi_clk; //74.25M Hz 
    input [23:0]    hdmi_data;
    input           hdmi_enable;  //1?use data_in: black ;
    input           hdmi_nReset;

    //hdmi
    output          vout_clk
    output          vout_hsyn;
    output          vout_vsyn;
    output          vout_de; //data enable
    output [23:0]   vout_data;
    output          vout_nReset;

    //fifo
    output          fifo_en;


// ------------------- Variable ------------------
parameter H_ACTIVE = 16'd1920;
parameter H_FP = 16'd88;
parameter H_SYNC = 16'd44;
parameter H_BP = 16'd148; 
parameter V_ACTIVE = 16'd1080;
parameter V_FP 	= 16'd4;
parameter V_SYNC  = 16'd5;
parameter V_BP	= 16'd36;

parameter   H_TOTAL = H_ACTIVE + H_FP + H_SYNC + H_BP;//行总长度
parameter   V_TOTAL = V_ACTIVE + V_FP + V_SYNC + V_BP;//场总长度

reg [11:0] counter_vsyn; //begin 0 end 2200, 280 + 1920
reg stage;
// -----------------------------------------------
always @(posedge hdmi_clk or negedge nReset) begin : vout_hsyn
    if(~nReset)begin
        stage       <= stage0;
        vout_hsyn   <= 0;
        vout_de     <= 0;
        vout_data   <= 0;
    end
    else begin
        case(state)
            idle begin
                vout_hsyn <= 1;
                if(counter_vsyn == 12'd88) begin //! edit number
                    stage <= stage1;
                    vout_hsyn <= 0;
                end
            end

            state0: begin
                vout_hsyn <= 1;
                if(counter_vsyn ==  12'd132) begin //! edit number
                    stage <= stage1;
                    vout_hsyn <= 0;
                end
            end
            state1: begin
                if(counter_vsyn ==  12'd280)begin //! edit number
                    stage <= state2;
                end
            end
            state2: begin
                vout_de <= 1;
                vout_data <= hdmi_data;
                if(counter_vsyn ==  12'd2200) begin //! edit number 
                    stage <= state3;
                    vout_de <= 0;
                    vout_data <= 24'h0;
                end
            end
            state3: begin
                if(counter_vsyn == something) begin //! edit number 
                    stage <= state0;
                end
            end
            default: stage <= idle;
        endcase
    end
    
end

always @(posedge hdmi_clk or negedge nReset) begin :vout_
    if(~nReset)begin

    end
    else begin
       
    end
end


always @(posedge hdmi_clk or negedge nReset) begin :vout_
    if(~nReset)begin

    end
    else begin
       
    end
end

// always @(posedge hdmi_clk or negedge nReset) begin :vout_
//     if(~nReset)begin

//     end
//     else begin
       
//     end
// end
///////////////////////////////////////////////////////////////////////////
    // input Fg_CLK;
    // input RESETn;
    // input  ExtBTN;
    // output reg IntBTN;

    // reg D1;
    // reg D2;
    // reg D3;
    // reg [25:0] counter;
    // reg enable_counter;


    
// always @(posedge Fg_CLK or negedge RESETn) begin
//     if(~RESETn)begin
//             D1 <= 0;
//             D2 <= 0;
//             D3 <= 0;
//     end
//     else begin
//         D1 <= ExtBTN;
//         D2 <= D1;
//         D3 <= D2;
//         if(~enable_counter) IntBTN <= (~D2 & D3 &(counter == 0));
//     end
// end



endmodule
