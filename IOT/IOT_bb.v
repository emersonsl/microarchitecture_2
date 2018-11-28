
module IOT (
	clk_clk,
	esp_rxd,
	esp_txd,
	input_export,
	lcd_DATA,
	lcd_ON,
	lcd_BLON,
	lcd_EN,
	lcd_RS,
	lcd_RW,
	output_export);	

	input		clk_clk;
	input		esp_rxd;
	output		esp_txd;
	input	[3:0]	input_export;
	inout	[7:0]	lcd_DATA;
	output		lcd_ON;
	output		lcd_BLON;
	output		lcd_EN;
	output		lcd_RS;
	output		lcd_RW;
	output	[3:0]	output_export;
endmodule
