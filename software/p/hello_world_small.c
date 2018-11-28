#include "altera_up_avalon_character_lcd.h"
#include "system.h"
#include "sys/alt_stdio.h"
#include "io.h"
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_jtag_uart_regs.h"
#include <string.h>


void delay(int a){ //bounce
	volatile int i = 0;
	while(i<a*10000){
		i++;
	}
}

/*Write Console*/

void write(char * v) {
	int i = 0;
	while (v[i] != '\0') {
		IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_BASE, v[i]);
		i++;
	}
}

/************************************ESP**********************************/

/*Mensagens*/

/*Mensagem connect*/
char connectMessage[] = { 0x10 // Connect
		, 0x0C + 0x04 // Remaining Length
				, 0x00 // 0
		, 0x06 // 6
		, 0x4d // M
		, 0x51 // Q
		, 0x49 // I
		, 0x73 // S
		, 0x64 // D
		, 0x70 // P
		, 0x03 // Protocol version = 3
		, 0x02 // Clean session only
		, 0x00 // Keepalive MSB
		, 0x3c // Keepaliave LSB = 60
		, 0x00 // String length MSB
		, 0x02 // String length LSB = 2
		, 0x4d // M
		, 0x70 // P .. Let's say client ID = MP
		};
/*Mensagem disconnect*/
char disconnectMessage[] = {0xE0, 0x00};

char publishMessage []= { 0x30 // Publish with QOS 0
		, 0x05 + 0x05 // Remaining length
		, 0x00 // MSB
		, 0x03 // 3 bytes of topic
		, 0x61 // a
		, 0x2F ///
		, 0x62 // b (a/b) is the topic
		, 0x48, 0x45, 0x4c, 0x4c, 0x4f // HELLO is the message
};


char pb1 [] = { 0x30 // Publish with QOS 0
			, 0x05 + 0x0a // Remaining length
			, 0x00 // MSB
			, 0x03 // 3 bytes of topic
			, 0x61 // a
			, 0x2F ///
			, 0x62 // b (a/b) is the topic
			, 0x4d, 0x65, 0x6e, 0x73, 0x61, 0x67, 0x65, 0x6d, 0x20, 0x30 // Mensagem 1 is the message
	};

char pb2 [] = { 0x30 // Publish with QOS 0
			, 0x05 + 0x0a // Remaining length
			, 0x00 // MSB
			, 0x03 // 3 bytes of topic
			, 0x61 // a
			, 0x2F ///
			, 0x62 // b (a/b) is the topic
			, 0x4d, 0x65, 0x6e, 0x73, 0x61, 0x67, 0x65, 0x6d, 0x20, 0x30 // Mensagem 1 is the message
	};

char pb3 [] = { 0x30 // Publish with QOS 0
			, 0x05 + 0x0a // Remaining length
			, 0x00 // MSB
			, 0x03 // 3 bytes of topic
			, 0x61 // a
			, 0x2F ///
			, 0x62 // b (a/b) is the topic
			, 0x4d, 0x65, 0x6e, 0x73, 0x61, 0x67, 0x65, 0x6d, 0x20, 0x30 // Mensagem 1 is the message
	};

char pb4 [] = { 0x30 // Publish with QOS 0
			, 0x05 + 0x0a // Remaining length
			, 0x00 // MSB
			, 0x03 // 3 bytes of topic
			, 0x61 // a
			, 0x2F ///
			, 0x62 // b (a/b) is the topic
			, 0x4d, 0x65, 0x6e, 0x73, 0x61, 0x67, 0x65, 0x6d, 0x20, 0x30 // Mensagem 1 is the message
	};
char pb5 [] = { 0x30 // Publish with QOS 0
			, 0x05 + 0x0a // Remaining length
			, 0x00 // MSB
			, 0x03 // 3 bytes of topic
			, 0x61 // a
			, 0x2F ///
			, 0x62 // b (a/b) is the topic
			, 0x4d, 0x65, 0x6e, 0x73, 0x61, 0x67, 0x65, 0x6d, 0x20, 0x30 // Mensagem 1 is the message
	};

void sendCommand(char * cmd) {
	alt_putstr(cmd);
	char a;

	while (1) {
		if (IORD_ALTERA_AVALON_UART_STATUS(ESP_BASE) & (1 << 7)) {
			a = IORD_ALTERA_AVALON_UART_RXDATA(ESP_BASE);
			IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_BASE, a);
		}
		if(a=='K')
			break;
	}

}

void espTest() {
	sendCommand("AT\r\n");
}
void espMode() {
	sendCommand("AT+CWMODE=1\r\n");
}

void espConnect(char * ssid, char * pass) {
	char net[80] = "AT+CWJAP=\"";
	strcat(net, ssid);
	strcat(net, "\",\"");
	strcat(net, pass);
	strcat(net, "\"\r\n");
	sendCommand(net);
}

void espOpenTCPConnect(char * ip, char * port) {
	char net[80] = "AT+CIPSTART=\"TCP\",\"";
	strcat(net, ip);
	strcat(net, "\",");
	strcat(net, port);
	strcat(net, "\r\n");
	sendCommand(net);
}

void espTCPSend(char * message, int size) {
	char a;
	char net[] = "";
	sprintf(net, "AT+CIPSEND=%d\r\n", size);
	alt_putstr(net);

	while (1) {
		if (IORD_ALTERA_AVALON_UART_STATUS(ESP_BASE) & (1 << 7)) {
			a = IORD_ALTERA_AVALON_UART_RXDATA(ESP_BASE);
			IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_BASE, a);
		}
		if(a=='>')
			break;
	}

	//enviando messagem
	int i;
	for (i = 0; i < size; i++) {
		alt_putchar(message[i]);
		delay(3);
	}
}

void espSendMessage(int i){
	delay(100);
	switch (i){
		case 1: espTCPSend(pb1, sizeof(pb1)); break;
		case 2: espTCPSend(pb2, sizeof(pb2)); break;
		case 3: espTCPSend(pb3, sizeof(pb3)); break;
		case 4: espTCPSend(pb4, sizeof(pb4)); break;
		case 5: espTCPSend(pb5, sizeof(pb5)); break;
	}

	write("aqui");
}

/************************************LCD**********************************/

void writeLCD(alt_up_character_lcd_dev * char_lcd_dev, char word []){

	//limpando
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
	int j;
	for(j=0; j<16; j++){
		alt_up_character_lcd_string(char_lcd_dev, " ");
	}

	//escrevendo
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
	alt_up_character_lcd_string(char_lcd_dev, word);
}

void initConf(){
	espTest();
	espMode();
	espConnect("lima", "@senha363");
	espOpenTCPConnect("192.168.16.102", "1883");
	espTCPSend(connectMessage, sizeof(connectMessage));
	delay(10);
}

int main(void)
{
	initConf();

	unsigned int entrada;
	int i=1; //option
	int c=1; //control 0 - up/down, 1 - op, 2 - select, 3 - return
	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	if ( char_lcd_dev == NULL)
		write ("Error: could not open character LCD device\n");
	else
		write ("Opened character LCD device\n");
	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);

	IOWR(OUTPUT_BASE,0,15); //leds off
	while (1){
		entrada = IORD(INPUT_BASE, 0);

		switch(entrada){
			case 14: //up
				delay(30);
				if(c==0){
					i--;
					c=1;
				}
				break;
			case 13: //down
				delay(30);
				if(c==0){
					i++;
					c=1;
				}
				break;
			case 11: //select
				delay(30);
				if(c==0){
					c=2;
				}
				break;
			case 7: //return
				delay(30);
				if(c==3){
					write("aqui ret");
					IOWR(OUTPUT_BASE,0,15); //leds off
					c=1;
				}
				break;
		}


		if(i==0 && c==1){ //end up
			i=5;
		}else if(i==6 && c==1){ //end down
			i=1;
		}

		if(c==2){
			espTCPSend(publishMessage, sizeof(publishMessage));
		}

		if(i==1){ //op 1
			if(c==1){ //op
				writeLCD(char_lcd_dev, "OPCAO 1");
				c=0;
			}else if(c==2){ //msg
				writeLCD(char_lcd_dev, "MENSAGEM 1");
				IOWR(OUTPUT_BASE,0,14);
				c=3;
			}
		}else if(i==2){
			if(c==1){
				writeLCD(char_lcd_dev, "OPCAO 2");
				c=0;
			}else if(c==2){ //msg
				writeLCD(char_lcd_dev, "MENSAGEM 2");

				IOWR(OUTPUT_BASE,0,13);
				c=3;
			}
		}else if(i==3){
			if(c==1){
				writeLCD(char_lcd_dev, "OPCAO 3");
				c=0;
			}else if(c==2){ //msg
				writeLCD(char_lcd_dev, "MENSAGEM 3");

				IOWR(OUTPUT_BASE,0,12);
				c=3;
			}
		}else if(i== 4){
			if(c==1){
				writeLCD(char_lcd_dev, "OPCAO 4");
				c=0;
			}else if(c==2){ //msg
				writeLCD(char_lcd_dev, "MENSAGEM 4");

				IOWR(OUTPUT_BASE,0,11);
				c=3;
			}
		}else if(i==5){
			if(c==1){
				writeLCD(char_lcd_dev, "OPCAO 5");
				c=0;
			}else if(c==2){ //msg
				writeLCD(char_lcd_dev, "MENSAGEM 5");

				IOWR(OUTPUT_BASE,0,10);
				c=3;
			}
		}
	}
	return 0;
}
