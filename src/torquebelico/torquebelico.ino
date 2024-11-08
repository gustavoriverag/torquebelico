#define CH1 3
#define CH2 5

int pin_mot_1 = 5;
int pin_mot_1_r = 6;

int pin_mot_2 = 8;
int pin_mot_2_r = 9;

int pin_pwm_1 = 10;
int pin_pwm_2 = 11;

int empuje = 0;
int direccion = 0;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
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
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  empuje = readChannel(CH1, -255, 255, 0);
  direccion = readChannel(CH2, -1, 1, 0);
  Serial.print("CH2: ");
  Serial.println(pulseIn(CH3, HIGH));
  delay(500);
}
