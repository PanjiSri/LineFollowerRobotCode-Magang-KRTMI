#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>

class Robot{
    public :
    Robot (byte pinPwmA1, byte pinPwmA1, byte pinPwmB1, bytepinPwmb2);
    void maju(unsigned long lama);
    void mundur(unsigned long lama);
    void stop(unsigned long lama);
    void belokKiri(unsigned long lama);
    void belokKanan(unsigned long lama);
    void putarKiri(unsigned long lama);
    void putarKanan(unsigned long lama);
    void aturKecepatan(byte kecepatan);
    byte perolehKecepatan();

    private :
    byte pinIN1, pinIN2, pinIN3, pinIN4;
    byte kecepatan;
};

#endif 
