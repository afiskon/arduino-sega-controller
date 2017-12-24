#include <OLED_I2C.h>

OLED oled(SDA, SCL);
extern uint8_t SmallFont[];

#define UP_OR_Z 1
#define DOWN_OR_Y 2
#define LEFT_OR_X 3
#define RIGHT_OR_MODE 4
#define B_OR_A 6
#define SEL 7
#define C_OR_START 9

bool sega_up = false;
bool sega_down = false;
bool sega_left = false;
bool sega_right = false;

bool sega_start = false;
bool sega_mode = false;

bool sega_a = false;
bool sega_b = false;
bool sega_c = false;

bool sega_x = false;
bool sega_y = false;
bool sega_z = false;

void segaRead() {
    digitalWrite(SEL, HIGH);
    delayMicroseconds(20);

    sega_up = (digitalRead(UP_OR_Z) == LOW);
    sega_left = (digitalRead(LEFT_OR_X) == LOW);
    sega_right = (digitalRead(RIGHT_OR_MODE) == LOW);
    sega_down = (digitalRead(DOWN_OR_Y) == LOW);

    sega_c = (digitalRead(C_OR_START) == LOW);
    sega_b = (digitalRead(B_OR_A) == LOW);

    digitalWrite(SEL, LOW);
    delayMicroseconds(20);

    sega_a = (digitalRead(B_OR_A) == LOW);
    sega_start = (digitalRead(C_OR_START) == LOW);

    digitalWrite(SEL, HIGH);
    delayMicroseconds(20);
    digitalWrite(SEL, LOW);
    delayMicroseconds(20);
    digitalWrite(SEL, HIGH);
    delayMicroseconds(20);
    digitalWrite(SEL, LOW);
    delayMicroseconds(20);
    digitalWrite(SEL, HIGH);
    delayMicroseconds(20);

    sega_x = (digitalRead(LEFT_OR_X) == LOW);
    sega_y = (digitalRead(DOWN_OR_Y) == LOW);
    sega_z = (digitalRead(UP_OR_Z) == LOW);
    sega_mode = (digitalRead(RIGHT_OR_MODE) == LOW);

    digitalWrite(SEL, LOW);
    delayMicroseconds(20);

    digitalWrite(SEL, HIGH);
    delayMicroseconds(20);
}

void setup() {
    oled.begin();
    oled.setFont(SmallFont);

    pinMode(SEL, OUTPUT);
    digitalWrite(SEL, HIGH);

    pinMode(UP_OR_Z, INPUT);
    pinMode(DOWN_OR_Y, INPUT);
    pinMode(LEFT_OR_X, INPUT);
    pinMode(RIGHT_OR_MODE, INPUT);
    pinMode(B_OR_A, INPUT);
    pinMode(C_OR_START, INPUT);
}

void loop() {
    char temp[16];

    segaRead();
    oled.clrScr();

    sprintf(temp, " %s   %s  %s%s%s",
        sega_up ? "U" : "u",
        sega_mode ? "M" : "m",
        sega_x ? "X" : "x",
        sega_y ? "Y" : "y",
        sega_z ? "Z" : "z");
    oled.print(temp, CENTER, 8*4);

    sprintf(temp, "%s%s%s  %s  %s%s%s",
        sega_left ? "L": "l",
        sega_down ? "D": "d",
        sega_right ? "R" : "r",
        sega_start ? "S" : "s",
        sega_a ? "A" : "a",
        sega_b ? "B" : "b",
        sega_c ? "C" : "c");
    oled.print(temp, CENTER, 8*5);

    oled.update();
    delay(1);
}
