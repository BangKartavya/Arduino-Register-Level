#include <Arduino.h>

int A = PD7;
int B = PB0;
int C = PB1;
int D = PB2;
int E = PB3;
int F = PB4;
int G = PB5;

void setup() {
    DDRB = 0x3f;
    DDRD = 0x80;
    Serial.begin(115200);
}

void clear() {
    PORTB = 0x0;
    PORTD = 0x0;
    PORTC = 0x0;
}

void print0() {
    // turn on every segment except G

    PORTB |= (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << F);
    PORTD |= (1 << A);
}

void print1() {
    // turn on only B and C

    PORTB |= (1 << B) | (1 << C);
}

void print2() {
    // turn on only A B G E D

    PORTB |= (1 << B) | (1 << G) | (1 << E) | (1 << D);
    PORTD |= (1 << A);
}

void print3() {
    // turn on everthing except F and E

    PORTB |= (1 << B) | (1 << G) | (1 << C) | (1 << D);
    PORTD |= (1 << A);
}

void print4() {
    // turn on only F G B C

    PORTB |= (1 << F) | (1 << G) | (1 << B) | (1 << C);
}

void print5() {
    // turn on only A F G C D

    PORTB |= (1 << F) | (1 << G) | (1 << C) | (1 << D);
    PORTD |= (1 << A);
}

void print6() {
    // only B is off
    PORTB |= (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);
    PORTD |= (1 << A);
}

void print7() {
    // turn on only A B C

    PORTB |= (1 << B) | (1 << C);
    PORTD |= (1 << A);
}

void print8() {
    // turn on everything

    PORTB |= (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);
    PORTD |= (1 << A);
}

void print9() {
    // only E is off
    PORTB |= (1 << B) | (1 << C) | (1 << D) | (1 << F) | (1 << G);
    PORTD |= (1 << A);
}

void printA() {
    // only D is off
    PORTB |= (1 << B) | (1 << C) | (1 << E) | (1 << F) | (1 << G);
    PORTD |= (1 << A);
}

void printB() {
    // A and B are off

    PORTB |= (1 << C) | (1 << D) | (1 << E) | (1 << F) | (1 << G);
}

void printC() {
    // turn on A F E D

    PORTB |= (1 << D) | (1 << E) | (1 << F);
    PORTD |= (1 << A);
}

void printD() {
    // A and F are off

    PORTB |= (1 << B) | (1 << C) | (1 << D) | (1 << E) | (1 << G);
}

void printE() {
    // B and C are off

    PORTB |= (1 << D) | (1 << E) | (1 << F) | (1 << G);
    PORTD |= (1 << A);
}

void printF() {
    // B C D are off

    PORTB |= (1 << E) | (1 << F) | (1 << G);
    PORTD |= (1 << A);
}

void loop() {
    print0();
    Serial.println(PINB);
    delay(1000);
    clear();
    delay(1000);
    print1();
    delay(1000);
    clear();
    delay(1000);
    print2();
    delay(1000);
    clear();
    delay(1000);
    print3();
    delay(1000);
    clear();
    delay(1000);
    print4();
    delay(1000);
    clear();
    delay(1000);
    print5();
    delay(1000);
    clear();
    delay(1000);
    print6();
    delay(1000);
    clear();
    delay(1000);
    print7();
    delay(1000);
    clear();
    delay(1000);
    print8();
    delay(1000);
    clear();
    delay(1000);
    print9();
    delay(1000);
    clear();
    delay(1000);
    printA();
    delay(1000);
    clear();
    delay(1000);
    printB();
    delay(1000);
    clear();
    delay(1000);
    printC();
    delay(1000);
    clear();
    delay(1000);
    printD();
    delay(1000);
    clear();
    delay(1000);
    printE();
    delay(1000);
    clear();
    delay(1000);
    printF();
    delay(1000);
    clear();
    delay(1000);
}