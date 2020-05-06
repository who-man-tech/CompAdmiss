#include <lights.h>



Lights::Lights(uint8_t data_pin, uint8_t num_leds)
    : data_pin_(data_pin)
    , num_leds_(num_leds)
    , is_on_(false)
    , speed_(20)
    , thishue(0)
    , mode_(emOneColor)
    , leds_(Adafruit_NeoPixel(num_leds_, data_pin_, NEO_GRB + NEO_KHZ800))
    {

    }


void Lights::begin() {
    leds_.begin();
    leds_.setBrightness(200);
    leds_.clear();
    leds_.show();
}



void Lights::update(uint8_t cpu_temp, uint8_t gpu_temp) {
    cpu_temp_ = cpu_temp;
    gpu_temp_ = gpu_temp;
    // Оповещение о высокой температуре
    if (cpu_temp_ >= 90 || gpu_temp_ >= 85){ // Если температура больше максимальной
        static unsigned long am_timer;
        static bool is_alarm_timer;
        if (millis() - am_timer > 500){ // Моргаем красным цветом.
            is_alarm_timer = !is_alarm_timer;
            am_timer = millis();
            oneColor(is_alarm_timer ? leds_.Color(255, 0, 0) : leds_.Color(0, 0, 0));
        }

        return;
    }

    if (is_on_) { // Если подсветка включена
        switch (mode_) {

        }
    }
    else {
        leds_.clear();
        leds_.show();
    }
}

bool Lights::safeDelay(int del_time) {
    if (millis() - timer < del_time)
        return true;

    timer = millis();
    return false;

}

int Lights::antipodal_index(int i) {
    int iN = i + num_leds_ / 2;
    if (i >= num_leds_ / 2) {
        iN = (i + num_leds_ / 2) % num_leds_;
    }
    return iN;
}



void Lights::PulseOneColor() {              //-m10-PULSE BRIGHTNESS ON ALL LEDS TO ONE COLOR
    static bool bouncedirection;
    static int ibright;

    if (safeDelay(speed_)) 
        return;

    if (bouncedirection == 0) {
            ibright++;
        if (ibright >= 255) {
            bouncedirection = 1;
        }
    }
    if (bouncedirection == 1) {
        ibright = ibright - 1;
        if (ibright <= 1) {
            bouncedirection = 0;
        }
    }
    for (int idex = 0 ; idex < num_leds_; idex++ ) {
        leds_.setPixelColor(idex, leds_.ColorHSV(thishue, 255, ibright));
    }
    leds_.show();
}

void Lights::rgbProp() { //-m27-RGB PROPELLER
    static int idex;

    if (safeDelay(speed_))
        return;

    idex++;
    int ghue = (thishue + 80) % 255;
    int bhue = (thishue + 160) % 255;
    int N3  = int(num_leds_ / 3);
    int N6  = int(num_leds_ / 6);
    int N12 = int(num_leds_ / 12);
    for (int i = 0; i < N3; i++ ) {
        int j0 = (idex + i + num_leds_ - N12) % num_leds_;
        int j1 = (j0 + N3) % num_leds_;
        int j2 = (j1 + N6) % num_leds_;
        leds_.setPixelColor(j0, leds_.ColorHSV(thishue, 255, 255));
        leds_.setPixelColor(j1, leds_.ColorHSV(ghue, 255, 255));
        leds_.setPixelColor(j2, leds_.ColorHSV(bhue, 255, 255));
    }
    leds_.show();
}

void Lights::rainbow() {
    static uint16_t ihue = 0;

    if (safeDelay(speed_))
        return;
    
    ihue += 500;
    if (ihue > 65536) {
        ihue = 0;
    }
    for (int idex_ = 0 ; idex_ < num_leds_; idex_++ ) {
        leds_.setPixelColor(idex_, leds_.ColorHSV(ihue, 255, 100));
    }
    leds_.show();
}

void Lights::randomColor() { //-m25-RANDOM COLOR POP
    static int idex;
    static int ihue;

    if (safeDelay(speed_))
        return;

    idex = random(0, num_leds_);
    ihue = random(0, 255);
    for (uint8_t i = 0; i < num_leds_; i++)
        leds_.setPixelColor(i, 0, 0, 0);
    leds_.setPixelColor(idex, leds_.ColorHSV(ihue, 255, 255));
    leds_.show();
}

void Lights::oneColor(uint32_t color) {
    for (int i = 0; i < num_leds_; i++)
        leds_.setPixelColor(i, color);
}

void Lights::adaptTemp() {
    
}

