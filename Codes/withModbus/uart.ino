//receive one byte data
unsigned char USART_Receive()
{
  while(!(UCSR0A & (1<<RXC0)));  //receive buffer empty
  return UDR0; //receive reg
}


//transmit one byte
void UART_Txchar(char ch)
{
  while(!(UCSR0A & (1<<UDRE0))); //WAIT UNTIL EMPTY TRANSMIT BUFFER
  UDR0 = ch; // after transmit buffer empty load data to the uart data register

}


//transmit string
void trans_string(char str[]){
  int lenght = strlen(str);
  char trans;
  for(int i=0;i<lenght;i++){
    trans = str[i];
    UART_Txchar(trans);
  }
}

//transmit number
void trans_num(uint16_t num){
  String number = String(num);
  int lenght = number.length();
  char trans;
  for(int i=0;i<lenght;i++){
    trans = number[i];
    UART_Txchar(trans);
  }
  // UART_Txchar('\n');
}

void init_uart(){
  //Enable transmitter and recirever bits - Use USART0

  UCSR0B |= (1<<RXEN0) | (1<<TXEN0); // ENABLE RX AND RX

  //SET THE DATA SIZE FOR COMMUNIATION
  UCSR0C &= (~(1<<UMSEL00)) & (~(1<<UMSEL01));   //ENABLE ASYNCHRONOUS USART COMMUNICATION
  UCSR0C &= (~(1<<UPM00)) & (~(1<<UPM01));   // DISABLE PARITY BIT
  UCSR0C &= (~(1<<USBS0)); //CHOOSE ONE STOP BIT

  //SET DATA LENGHT TO BE 8 BITS
  UCSR0B &= (~(1<<UCSZ02));
  UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);  //SET 8BITS 011 BITS IN UCSZ02,UCSZ00,UCSZ01

  //SET THE SPEED FOR TRANSMISSION

  UCSR0A |= (1<<U2X0); //SELSCT HIGH SPEED MODE
  // UCSR0A &= ~(1<<U2X0); // low speed

  //BAUDRATE
  UBRR0 = 207; //9600 BAUDRATE FROM DATASHEET DIRECT TABLE FOR U2X0=1 if u2x=0 , ubrr0 = 103
}






