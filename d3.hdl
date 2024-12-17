    library IEEE;
    use IEEE.STD_LOGIC_1164.all;
    use IEEE.STD_LOGIC_ARITH.all;
    use IEEE.STD_LOGIC_UNSIGNED.all;

    Entity TxSerial Is
    Port(
        RstB        : in    std_logic;
        Clk         : in    std_logic;
        
        TxFfEmpty   : in    std_logic;                          --! if(FIFO have data)? <br> Empty : Have data;
        TxFfRdData  : in    std_logic_vector(7 downto 0);       --! FIFO --Data-> This 

        TxFfRdEn    : out   std_logic;                          --! FIFO <- This
        
        SerDataOut  : out	std_logic
    );
    End Entity TxSerial;    

    Architecture rtl Of TxSerial Is
    -- constant
    constant cbuadCnt   : INTEGER := 434;

    -- sinal
    signal rBuadCnt     : std_logic_vector (9 downto 0);
    signal rBuadEnd     : std_logic;
    signal rSerData     : std_logic_vector (9 downto 0);
    signal rTxFfRdEn    : std_logic_vector (1 downto 0);
    signal rDataCnt     : std_logic_vector (3 downto 0);


        type SerStateType is
            (
                stIdle  ,
                stRdReq , 
                stWtData,
                stWtEnd

            );
    signal rState : SerStateType;

    -- signal rTxFfRdEn : std_logic;

    Begin
        -- output assignment
        SerDataOut <= rSerData(0);
        TxFfRdEn   <= rTxFfRdEn(0);
        

    ------------------------------------------------------------------------
        u_rBuadCnt : Process (Clk) Is -- counter down : from constant cbuadBnt to 1
        Begin
            if ( rising_edge(Clk) ) then
                if ( RstB = '0' ) then
                    rBuadCnt <=  conv_std_logic_vector(cbuadCnt, 10); -- funtion(int, bit) return binary(std_logic_vertor)
                else
                    if rState = stWtEnd then
                        if ( rBuadCnt = 1 )then
                            rBuadCnt <= conv_std_logic_vector(cbuadCnt, 10);
                        else
                            rBuadCnt <= rBuadCnt - 1;
                        end if;
                    end if;
                end if;
            end if;
        End Process u_rBuadCnt;
    ------------------------------------------------------------------------
        u_rBuadEnd : Process (Clk) Is -- make pulse when rBuadEnd == 1
        Begin
            if ( rising_edge(CLK) ) then
                if ( RstB = '0' ) then
                    rBuadEnd <= '0';
                else
                    if ( rBuadCnt = 1 ) then
                        rBuadEnd <= '1';
                    else
                        rBuadEnd <= '0';
                    end if;
                end if;
            end if;
        End Process u_rBuadEnd;
    ------------------------------------------------------------------------

    ------------------------------------------------------------------------
        u_rSerData : Process(Clk) Is
        Begin
            if (rising_edge(Clk)) then
                if(RstB = '0') then
                    rSerData <= (others => '1');
                else
                    if (rTxFfRdEn(1) = '1') then 
                        rSerData(9)          <= '1';
                        rSerData(8 downto 1) <= TxFfRdData;
                        rSerData(0)          <= '0';
                    else
                        if (rBuadEnd = '1') then
                            rSerData <= '1' & rSerData(9 downto 1);
                        else
                            rSerData <= rSerData ;
                        end if;
                    end if;
                end if;
            end if;
        End Process u_rSerData;
    ------------------------------------------------------------------------
        u_rTxFfRdEn : Process (Clk) Is 
        begin
            if rising_edge(Clk) then
                if RstB='0' then
                    rTxFfRdEn <= "00";
                else
                    rTxFfRdEn(1)    <=  rTxFfRdEn(0);
                    if(rState=stRdReq) then
                        rTxFfRdEn(0) <= '1';
                    else
                        rTxFfRdEn(0) <= '0';
                    end if;
                end if;
            end if;
        End Process u_rTxFfRdEn;
    ------------------------------------------------------------------------
        u_rState : process (Clk) is
        begin
            if rising_edge(Clk) then
                if RstB = '0' then
                    rState <= stIdle;
                else
                    case (rState) is
                    when stIdle => 
                        if TxFfEmpty = '0' then
                            rState <= stRdReq;
                        else
                            rState <= stIdle;
                        end if;
                    when stRdReq =>
                        rState <= stWtData;
                        
                    when stWtData =>
                        if rTxFfRdEn(1) = '1' then
                            rState <= stWtEnd;
                        else
                            rState <= stWtData;
                        end if;
                    when stWtEnd =>
                        --if SerEnd = '1' then
                        if rDataCnt = x"a" then
                            rState <= stIdle;
                        else
                            rState <= stWtEnd;
                        end if;
                    end case;
                end if;
            end if;
        end process u_rState;
        ------------------------------------------------------------------------
        u_rDataCnt: process(Clk) is 
        begin
            if rising_edge(Clk) then
                if (RstB = '0') then 
                    rDataCnt <= (others => '0'); 
                else    
                    
                        if (rState = stWtEnd ) then
                            if (rBuadEnd = '1') then
                                rDataCnt <= rDataCnt + 1;
                            else 
                                rDataCnt <= rDataCnt;
                            end if;
                        else 
                            rDataCnt <= (others => '0');
                        end if;
                    
                end if;
            end if;
        end process u_rDataCnt;


        End Architecture rtl;


