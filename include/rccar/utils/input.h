#pragma once

namespace rccar::utils::input {
    
class Digital {
   private:
    bool (*func)();
    bool value;
    bool prevValue;

   public:
    Digital(bool (*func)())
        : func(func),
        value(false),
        prevValue(false) {}

    void update(float delta);

    const bool getValue() const { return value; }

    const bool getPrevValue() const { return prevValue; }

    const bool isChanged() const { return value != prevValue; }

    const bool isDown() const { return value; }

    const bool isUp() const { return !value; }

    const bool isPressed() const { return value && !prevValue; }

    const bool isReleased() const { return !value && prevValue; }
};

class Analog {
   private:
    float (*func)();
    float value;
    float prevValue;

   public:
    Analog(float (*func)())
        : func(func),
        value(0.0F),
        prevValue(0.0F) {}

    void update(float delta);

    const float getValue() const { return value; }

    const float getPrevValue() const { return prevValue; }

    const bool isChanged() const { return value != prevValue; }
};

}
