// progrm sensor robot

#include <Robot.h> //library untuk robot

const int PIN_L = 10;
const int PIN_C = 11;
const int PIN_R = 12;

Robot bot (3, 5, 6, 9); //pembentukan objrk untuk mengakses robot

void setup() { 
  //menentukan kecepatan komunikasi dengan port serial
  Serial.begin (9600);

  //pendefinisian pin-pin pada arduino yang dihubungkan ke pin-pin modul pendeteksi garis 
  pinMode (PIN_L, INPUT);
  pinMode (PIN_C, INPUT);
  pinMode (PIN_R, INPUT);

  // kecepatan motor diatur sebesar 60%
  bot.aturkecepatan (60);

}

void loop() {
  //pembacaan ketiga sensor
  int nilaiPinL = digitalRead(PIN_L); //PIN_L untuk sensor left (kiri)
  int nilaiPinC = digitalRead(PIN_C); //PIN_C untuk sensor center (tengah)
  int nilaiPinR = digitalRead(PIN_R); //PIN_R untuk sensor right (kanan)

  if (nilaiPinL == 1 && nilaiPinR == 0){
    //sensor kiri di luar garis hitam
    bot.belokKanan (2); //dibelokkan selama 2 milidetik
  }
  else if (nilaiPinR == 1 && nilaiPinL == 0){
    //sensor kanan diluar garis hitam
    bot.belokKiri (2); //dibelokkan selama 2 milidetik
  }
  else if (nilaiPinL + nilaiPinC + nilaiPinR ==0){
    //ketiga sensor didalam garis hitam
    bot.maju (6); //dimajukan selama 6 milidetik
  }
  else if (nilaiPinL + nilaiPinC + nilaiPinR == 3){
    //ketiga sensor diluar garis hitam
    bot.mundur (2); //dimundurkan selama 2 milidetik 
  }
  delay(1000) ; //pembacaan data sensor dilakukan per satu detik 

}
