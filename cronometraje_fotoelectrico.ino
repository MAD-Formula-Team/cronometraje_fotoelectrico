/*
 * Sistema de medicion de tiempo por vuelta con una celula fotoelectrica
 * Lap time meter with an optical detector
 * Omron Aprimatic E3JM-R4M4-G
 * Author: Javier Gallego Carracedo
 * Date: 04/04/2021
 * MAD Formula Team
 */

const int filter_value = 20;

int sensor = 12;
int value;
int value_prev = 0;
int filter = filter_value;
boolean passing = false;
boolean passing_prev = false;
long lap_time, ellapsed_time;
int velo_time;

void setup()
{
  // put your setup code here, to run once:
  pinMode(sensor, INPUT);
  Serial.begin(9600);

}

void loop()
{
  // put your main code here, to run repeatedly:
  read_sensor();
  lap_timer();
  passing_time();
  send_bluetooth();
  passing_prev = passing;
}

void read_sensor()
{
  value = digitalRead(sensor);

  if(value == value_prev && filter > 0){
    filter --;
    if(filter == 0){
      passing = value;
    }
  }
  else if (value != value_prev){
    value_prev = value;
    filter = filter_value;
  }
}

void lap_timer(){
  if(passing && passing != passing_prev){
      ellapsed_time = millis()-lap_time;
      //print_time(ellapsed_time);
      lap_time = millis();
  }
}

void passing_time(){
  if(passing && !passing_prev){
      velo_time = millis();
  }
  if(!passing && passing_prev){
    velo_time = millis()-velo_time;
    //print_time(velo_time);
  }
}

void print_time(long t){
  int msecs = t%1000;
  int secs = t/1000;
  int mins = secs/60;
  secs = secs%60;

  Serial.print(mins);
  Serial.print(":");
  Serial.print(secs);
  Serial.print(".");
  Serial.println(msecs);
}

void send_bluetooth(){
  if(!passing && passing_prev){
    Serial.println(ellapsed_time);
    Serial.println(velo_time);
  }
}
