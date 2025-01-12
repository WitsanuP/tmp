
`timescale 1ps/1ps
module tb_top();
wire hdmi_scl;
wire hdmi_sda;
wire  hdmi_nreset;
wire  hdmi_clk;
wire  hdmi_hs;
wire  hdmi_vs;
wire  hdmi_de;
wire [23:0]  hdmi_d;


//	input rst_key,
wire led;

reg clk_125m;
reg clk_150m;
reg clk_27m;

    // reg RstB     = 0;
    // reg Clk      = 0;
    // reg [7:0]data_in  = 0;
    // reg en_in =0;

    // wire [31:0] data_out;
    // wire en_out;
    // // Task Definition

    always #(8000/2) clk_125m = ~clk_125m; // ????? clock ????? period 10ns
    always #(6667/2) clk_150m = ~clk_150m; 
    always #(37037/2) clk_27m = ~clk_27m; 
    // DUT Instantiation
    top dut  (

        .hdmi_scl(hdmi_scl),
        .hdmi_sda(hdmi_sda),
        .hdmi_nreset(hdmi_nreset),
        .hdmi_clk(hdmi_clk),
        .hdmi_hs(hdmi_hs),
        .hdmi_vs(hdmi_vs),
        .hdmi_de(hdmi_de),
        .hdmi_d(hdmi_d),
        
        
    //	input rst_key,
        .led(led),
    
        .clk_125m(clk_125m),
        .clk_150m(clk_150m),
        .clk_27m(clk_27m)
        
    );

    // Test Sequence
    initial begin
        $display("Starting test");
        // Reset phase
        
        // repeat(10)@(posedge Clk);
        // RstB = 1;
        // repeat(100)@(posedge Clk);
        // repeat(54)@(posedge Clk)
        // begin
        //     repeat(2)@(posedge Clk);
        //     en_in <= 1;
        //     data_in<= 8'hff;
        //     repeat(1)@(posedge Clk);
        //     en_in <= 0;

        // end
        // repeat(100)@(posedge Clk)
        // begin
        //     repeat(2)@(posedge Clk);
        //     en_in <= 1;
        //     data_in<= $random( );//8'hab;
        //     repeat(1)@(posedge Clk);
        //     en_in <= 0;

        // end

        

	
    	  
        repeat(50000)@(posedge clk_125m);
          
	$stop;
    end

        // ----------- dumping wave -----------
    initial begin
        $dumpfile("tb_top.vcd");
        $dumpvars(0,tb_top);
    end

    // // Monitor Outputs
    // initial begin
    //     $monitor("Time=%0t | RstB=%b | HdDataIn=%b | HdDataInValid=%b | HdDataOut=%b | HdDataOutValid=%b",
    //              $time, RstB, HdDataIn, HdDataInValid, HdDataOut, HdDataOutValid);
    // end

endmodule
