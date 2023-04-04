//Pendefinisian nomor pin untuk dihibungkan dengan pin OUT pada IR sensor
#define IR_Sensor1 /*No Pin*/  
#define IR_Sensor2 /*No Pin*/  
#define IR_Sensor3 /*NO Pin*/  

//Deklarasi variabel untuk menyimpan kondisi sensor
int IR1; 
int IR2;
int IR3;


void setup() {
  // put your setup code here, to run once:
  pinMode(IR_Sensor1, INPUT); //Pin didefinisikan sebagai input dari sensor 1
  pinMode(IR_Sensor2, INPUT); 
  pinMode(IR_Sensor3, INPUT)
  

}

void loop() {
  // put your main code here, to run repeatedly:
  IR1=digitalRead(IR_Sensor1)                           //Memasukkan kondisi sensor1 ke variabel IR1
  IR2=digitalRead(IR_Sensor2)
  IR3=digitalRead(IR_Sensor3)
  if(IR1==HIGH && IR2==LOW && IR3==HIGH){                //Seandainya hanya sensor tengah yang mendeteksi garis
    //Buat program untuk mengatur robot agar bergerak maju
  }   
  else if (IR1==HIGH && IR2==HIGH && IR3==LOW){          //Seandainya hanya sensor kanan yang mendeteksi garis
    //Buat program untuk mengatur robot agar bergerak ke kanan
  }
  else if (IR1==LOW && IR2==HIGH && IR3==HIGH){         //Seandainya hanya sensor kiri yang mendeteksi garis  
    //Buat program untuk mengatur robot agar bergerak ke kiri
  }
  else if (IR1==HIGH && IR2==HIGH && IR3==HIGH){        //Seandainya gak ada sensor yang mendeteksi garis
    //Buat program motor biar berhenti gerak
        
  }

}
