	component IOT is
		port (
			clk_clk       : in    std_logic                    := 'X';             -- clk
			esp_rxd       : in    std_logic                    := 'X';             -- rxd
			esp_txd       : out   std_logic;                                       -- txd
			input_export  : in    std_logic_vector(3 downto 0) := (others => 'X'); -- export
			lcd_DATA      : inout std_logic_vector(7 downto 0) := (others => 'X'); -- DATA
			lcd_ON        : out   std_logic;                                       -- ON
			lcd_BLON      : out   std_logic;                                       -- BLON
			lcd_EN        : out   std_logic;                                       -- EN
			lcd_RS        : out   std_logic;                                       -- RS
			lcd_RW        : out   std_logic;                                       -- RW
			output_export : out   std_logic_vector(3 downto 0)                     -- export
		);
	end component IOT;

	u0 : component IOT
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --    clk.clk
			esp_rxd       => CONNECTED_TO_esp_rxd,       --    esp.rxd
			esp_txd       => CONNECTED_TO_esp_txd,       --       .txd
			input_export  => CONNECTED_TO_input_export,  --  input.export
			lcd_DATA      => CONNECTED_TO_lcd_DATA,      --    lcd.DATA
			lcd_ON        => CONNECTED_TO_lcd_ON,        --       .ON
			lcd_BLON      => CONNECTED_TO_lcd_BLON,      --       .BLON
			lcd_EN        => CONNECTED_TO_lcd_EN,        --       .EN
			lcd_RS        => CONNECTED_TO_lcd_RS,        --       .RS
			lcd_RW        => CONNECTED_TO_lcd_RW,        --       .RW
			output_export => CONNECTED_TO_output_export  -- output.export
		);

