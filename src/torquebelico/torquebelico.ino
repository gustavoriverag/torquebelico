#define CH1 3
#define CH2 5

int pin_mot_1 = 6;
int pin_mot_1_r = 7;

int pin_mot_2 = 8;
int pin_mot_2_r = 9;

int pin_pwm_1 = 10;
int pin_pwm_2 = 11;

int empuje = 0;
int direccion = 0;

int M1 = 0;
int M2 = 0;

int M1_d = 0;
int M2_d = 0;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1100, 1900, minLimit, maxLimit);
}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(pin_mot_1, OUTPUT);
  pinMode(pin_mot_1_r, OUTPUT);
  pinMode(pin_mot_2, OUTPUT);
  pinMode(pin_mot_2_r, OUTPUT);
  pinMode(pin_pwm_1, OUTPUT);
  pinMode(pin_pwm_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  empuje = readChannel(CH1, -255, 255, 0);
  direccion = readChannel(CH2, -255, 255, 0);


  // calcular empuje para cada motor
  if (abs(empuje) > 50){
  // caso 1: empuje alto => manda empuje
    M1_d = 255 + direccion/10;
    M2_d = 255 - direccion/10;
    M1 = min(255, M1_d)/255*empuje;
    M2 = min(255, M2_d)/255*empuje;
  }
  
  else {
    
  // caso 2: empuje bajo => manda direccion
    M1 = direccion/2 + empuje;
    M2 = -direccion/2 + empuje;
  }

  //mandar señal correspondiente
  digitalWrite(pin_mot_1, (M1>=0));
  digitalWrite(pin_mot_1_r, (M1<0));
  digitalWrite(pin_mot_2, (M2>=0));
  digitalWrite(pin_mot_2_r, (M2<0));
  
  analogWrite(pin_pwm_1, min(abs(M1), 255));
  analogWrite(pin_pwm_2, min(abs(M2), 255));

  //

  
  Serial.print("m1: ");
  Serial.println(M1);
  
  Serial.print("m2: ");
  Serial.println(M2);

 // Serial.print("dir: ");
  //Serial.println(direccion);
  
  //Serial.print("em: ");
  //Serial.println(empuje);
}
