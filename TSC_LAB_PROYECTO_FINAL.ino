#include <OneWire.h>
#include <DallasTemperature.h>

//GPIO pin 0 is set as OneWire bus
OneWire ourWire1(0);
//GPIO pin 4 is set as OneWire bus
OneWire ourWire2(4);

//A variable or object is declared for our sensor 1
DallasTemperature sensors1(&ourWire1);
//A variable or object is declared for our sensor 2
DallasTemperature sensors2(&ourWire2);
int dutyCycle = 0;

//initial setting for data acquisition
int dutyCycleInitial = 255;
int dutyCycleFinish = 0;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;

//Status of transistors
int t1 = 0;
int t2 = 0;
int minutos = 10;

//set parameters
int period=10; //medium period
//int freq=1000;  // sampling time
int motor1Pin1 = 33;
int motor1Pin2 = 25;
//int enable1Pin = 32;
int conteo = 0;
float tempProm = 0;

void motor( void *pvParameters );
//void enviar( void *pvParameters );

void setup() {
  delay(1000);
  Serial.begin(115200);
  sensors1.begin();   //Sensor 1 starts
  sensors2.begin();   //Sensor 2 starts
 // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  //pinMode(enable1Pin, OUTPUT);

   // configure LED PWM functionalitites
  ledcSetup(pwmChannel, 30000, resolution);

  // attach the channel to the GPIO to be controlled
  //ledcAttachPin(enable1Pin, pwmChannel);
  
  //transistor 1
  pinMode(16, OUTPUT);
  //transitor 2
  pinMode(17, OUTPUT);
  //Serial.println("Choose any case: ");

   xTaskCreate(
    motor
    ,  "MotorDC"         // Descriptive name of the function (MAX 8 characters)
    ,  2048              // Size required in STACK memory
    ,  NULL              // INITIAL parameter to receive (void *)
    ,  0                // Priority, priority = 3 (configMAX_PRIORITIES - 1) is the highest, priority = 0 is the lowest.
    ,  NULL              // Variable that points to the task (optional)
   
);
}

void loop() {
  while (1){  
         digitalWrite(16, HIGH);
         //for (int i = 1; i <= minutos*60; i++) { // minute=10
          sensors1.requestTemperatures();
          //Obtain the temperature in ºC of sensor 1
         int temp1  = sensors1.getTempCByIndex(0);
          //print to display the temperature change
          tempProm =  tempProm +  temp1;
          if (conteo == 60){
            conteo = 0;
            tempProm =  tempProm/60;
            Serial.write(temp1);
            tempProm = 0;
           // Serial.print(",");
            //Serial.println(t1);
          }
        vTaskDelay(999);
        conteo++;
        }
    }
    
void motor( void *pvParameters ) {
  while (1) {
    delay(900000);
    // Move the DC motor forward at maximum speed
    //Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    vTaskDelay(10000);
    
      // Move the DC motor forward at maximum speed
      //digitalWrite(motor1Pin1, LOW);
      //digitalWrite(motor1Pin2, HIGH);
     //if (Serial.available())
     //{
      //String string = Serial.readStringUntil('\n');
      //dutyCycle = string.toInt();
      //ledcWrite(pwmChannel, dutyCycle);
    //}
      //vTaskDelay(period);
  }
}
    
