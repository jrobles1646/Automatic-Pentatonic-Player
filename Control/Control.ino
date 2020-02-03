

const int bPin1 = 3;  //Pin for push button 1
const int bPin2 = 2;  //Pin for push button 2
const int tempoPin = A1;
const int syncPin1 = 4;
const int syncPin2 = 5;

int tempo = 500;

bool bPin1State = true;
bool bPin2State = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  //pinMode(bPin1, INPUT);
  //pinMode(bPin2, INPUT);
  pinMode(syncPin1, OUTPUT);
  pinMode(syncPin2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(bPin1,INPUT_PULLUP);
  pinMode(bPin2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(bPin1), button1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bPin2), button2, CHANGE);
  delay(2000);
}

void loop()
{
  
  while(true)
  {
  tempo = (analogRead(tempoPin) + 60)/2;

  
  
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(syncPin1, HIGH);
  digitalWrite(syncPin2, HIGH);
  delay(tempo);
  
  digitalWrite(syncPin1, LOW);
  digitalWrite(syncPin2, LOW);
  delay(tempo);

  tempo = (analogRead(tempoPin) + 60)/2;

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(syncPin1, HIGH);
  digitalWrite(syncPin2, HIGH);
  delay(tempo);

  digitalWrite(syncPin1, LOW);
  digitalWrite(syncPin2, LOW);
  delay(tempo);
  }

  
}
void button1()
{
  if (bPin1State == false && bPin2State == true)
  {
    bPin1State = true;
    bPin2State = false;
    Serial.write(1);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}

void button2()
{
  if (bPin1State == true && bPin2State == false)
  {
    bPin1State = false;
    bPin2State = true;
    Serial.write(2);
  }
  digitalWrite(LED_BUILTIN, LOW);
}
