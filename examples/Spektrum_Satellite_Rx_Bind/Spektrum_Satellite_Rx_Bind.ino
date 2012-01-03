// Spektrum Satellite Rx binding
// Based on sketch by Sam Kelly, sam@3drobotics.com
// with info from rcgroups, mikrokopter, etc.
// Confirmed works with Arduino Pro Mini 3.3V/5V 8MHz/16MHz
// Should work with any other Arduino
// Now works with Orange Receivers

int Bind_pin = 3;
int Rx_PowerPin = 1;
unsigned long time;

void setup()
{
  pinMode(Rx_Powerpin, OUTPUT);
  pinMode(Bind_pin, INPUT);
  digitalWrite(Bind_pin, HIGH);
  if (digitalRead(Bind_pin) == LOW){
    SpektrumBind(); // Place Sat into bind mode to interface with the Spektrum sat
  }
  digitalWrite(Rx_PowerPin, HIGH);
  Serial.begin(115200);
}

void loop()
{
}

void SpektrumBind(void)
{
  unsigned char connected = 0;

  // Connect the power for the Rx to RX_powerpin this is brought
  // high to turn on the Rx.
  delay(5);  // Delay added to work with Orange Receivers
  digitalWrite(Rx_PowerPin, HIGH);

  UCSR0B &= ~(1 << RXCIE0); // disable Rx interrupt
  UCSR0B &= ~(1 << RXEN0); // disable USART1 Rx
  PORTD &= ~(1 << PORTD0); // disable pull-up

  while(time <= 10000) // Wait 10 seconds for spektrum sat connection
  {
    time = millis();
    if(PIND & (1 << PORTD0))
    {
      connected = 1;
      break;
    }
  }

  if(connected)
  {
    DDRD |= (1 << DDD0); // Rx as output

    delay(90); // Delay after Rx startup

    // === Update 2011-08-18 ===
    // Bind mode data gathered from Spektrum DX8
    // 2 low pulses: DSM2 1024/22ms (this works with Doug Weibel's PPM Encoder firmware)
    // 3 low pulses: no result
    // 4 low pulses: DSM2 2048/11ms
    // 5 low pulses: no result
    // 6 low pulses: DSMX 22ms
    // 7 low pulses: no result
    // 8 low pulses: DSMX 11ms

    PORTD &= ~(1 << PORTD0);        delayMicroseconds(116);  // 1 LOW
    PORTD |= (1 << PORTD0);         delayMicroseconds(116);
    PORTD &= ~(1 << PORTD0);        delayMicroseconds(116);  // 2 LOW
    PORTD |= (1 << PORTD0);         delayMicroseconds(116);
    //    PORTD &= ~(1 << PORTD0);        delayMicroseconds(116);  // 3 LOW
    //    PORTD |= (1 << PORTD0);         delayMicroseconds(116);
    //    PORTD &= ~(1 << PORTD0);        delayMicroseconds(116);  // 4 LOW
    //    PORTD |= (1 << PORTD0);         delayMicroseconds(116);
    //    PORTD &= ~(1 << PORTD0);        delayMicroseconds(116);  // 5 LOW
    //    PORTD |= (1 << PORTD0);         delayMicroseconds(116);
    //    PORTD &= ~(1 << PORTD0);        delayMicroseconds(116);  // 6 LOW
    //    PORTD |= (1 << PORTD0);         delayMicroseconds(116);
    //    PORTD &= ~(1 << PORTD0); 		  delayMicroseconds(116);   // 7 LOW
    //    PORTD |= (1 << PORTD0);	  	  delayMicroseconds(116);    
    //    PORTD &= ~(1 << PORTD0); 		  delayMicroseconds(116);   // 8 LOW
    //    PORTD |= (1 << PORTD0); 		  delayMicroseconds(116);   

  }
  else
    DDRD &= ~(1 << DDD0); // Rx as input
  PORTD &= ~(1 << PORTD0);
}



