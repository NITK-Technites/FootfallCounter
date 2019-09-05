#include<EEPROM.h>

uint8_t button_pin[4] = {2, 3, 4, 5};//digital pins to which the four legs of PUSH button are connected
uint8_t led_pin[4] = {6, 7, 8, 9};//digital pins to which the four LED's are connected
uint16_t footfall = 0;//initalizing the footfall counter

void setup() {
  init_pins();//function for initializing the pins 
  init_EEPROM();//function using EEPROM to put the track of previous counter value though arduino is bound to reset
 // clear_footfall(); //to intialize counter value in EEPROM to zero
  Serial.begin(9600);//setting the baud rate
}
void loop() {
  uint8_t curr_step = 0;//curr_step is the current step which we are in ....initialzing it to zero
  digitalWrite(led_pin[curr_step], HIGH);//the 1st LED will remain glowing until some one steps on it
  while (digitalRead(button_pin[curr_step]))
  {
    ;
  }
  digitalWrite(led_pin[curr_step], LOW);//once some one steps LED should go LOW
  curr_step++;//moving forward to next step
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(led_pin[curr_step + i], HIGH);//making both LED 2&3 HIGH giving an indication to user to show the next places where he has to step
  }
  boolean stat[2] = {0, 0};//variables for that should become 1 once the user stamps on step 2&3
  while (1)
  {
    for (int i = 0; i < 2; i++)//loop for steps 2&3
    {
      if (!digitalRead(button_pin[curr_step + i]))
    {
      stat[i] = 1;//whenever he steps the button pin goes low and stat increments to 1
      }
    }
    if ((stat[0] == 1) && (stat[1] == 1))//if both elements in stat goes high it means he has stepped on both steps2&3
    {
      break;//now it should come out of the while loop that will run until he stamps on both steps2&3
    }
  }
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(led_pin[curr_step + i], LOW);//both the LED'S 2&3 should go LOW once he stamps on steps 2&3
  }
  curr_step += 2;//incrementing the current step to 3
  digitalWrite(led_pin[curr_step], HIGH);//now we are making 4th LED high to give an indication to user to now stamp on 4th board
  while (digitalRead(button_pin[curr_step]))
  {
    ;// loop that will run until user stamps on 4th step 
  }
  digitalWrite(led_pin[curr_step], LOW);//LED 4 goes low once the user steps on 4th board
  footfall++;//once he steps on on all the boards in order we increment the footfall counter 
  EEPROM.put(0,footfall);//asking EEPROM to put that footfall counter value in the memory
  Serial.println(footfall);//for printing on serial monitor
}



void init_pins()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(button_pin[i], INPUT_PULLUP);//initializing button pins as inputs and to be HIGH
    pinMode(led_pin[i], OUTPUT);//intializing LED pins as outputs

  }
}

void init_EEPROM()
{
  EEPROM.get(0,footfall);//function to get the footfall counter value from EEPROM memory
  
}

void clear_footfall()
{
  uint16_t clr=0;
 EEPROM.put(0,clr);//initializing the footfall counter value in EEPROM memory
}

