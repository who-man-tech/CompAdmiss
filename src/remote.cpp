#include <remote.h>

Remote::Remote(uint8_t ir_pin)
    : ir_pin_(ir_pin)
    , remote_(ir_pin_)
    {
        pinMode(ir_pin_, INPUT);
        remote_.enableIRIn(); // Включаем получение данных от пульта
    }



void Remote::update() {
    // Получаем данные от пульта
    if (millis() - timer_ > 1000) {

        if (remote_.decode(&results_)) { // Если данные от пульта получены
            Serial.println(results_.value); 
            remote_.resume(); // Получаем следующее значение
        }

        // Задаем значения для кнопок пульта
        if (index_ < 17) {
            if (results_.decode_type) { // Если данные от пульта получены
                index_++;
                info_.info[index_] = results_.value;
            }
        }


        timer_ = millis();
    }
}



void Remote::setRemoteButtons(){ // Устанавливаем значения кнопкам пульта
    index_ = 0;
}



bool Remote::isButtOne(){
    if (results_.value == info_.butt.one) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtTwo(){
    if (results_.value == info_.butt.two) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtThree(){
    if (results_.value == info_.butt.three) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtFour(){
    if (results_.value == info_.butt.four) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtFive(){
    if (results_.value == info_.butt.five) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtSix(){
    if (results_.value == info_.butt.six) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtSeven(){
    if (results_.value == info_.butt.seven) {
        return true;
    }
    else {
        return false;
    }
}


bool Remote::isButtEight(){
    if (results_.value == info_.butt.eight) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtNine(){
    if (results_.value == info_.butt.nine) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtZero(){
    if (results_.value == info_.butt.zero) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtStar(){
    if (results_.value == info_.butt.star) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtGrid(){
    if (results_.value == info_.butt.grid) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtUp(){
    if (results_.value == info_.butt.up) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtLeft(){
    if (results_.value == info_.butt.left) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtOk(){
    if (results_.value == info_.butt.ok) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtRight(){
    if (results_.value == info_.butt.right) {
        return true;
    }
    else {
        return false;
    }
}



bool Remote::isButtDown(){
    if (results_.value == info_.butt.down) {
        return true;
    }
    else {
        return false;
    }
}