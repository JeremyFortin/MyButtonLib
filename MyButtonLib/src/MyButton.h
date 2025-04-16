#ifndef MYBUTTON_H
#define MYBUTTON_H

class MyButton
{
private:
    int buttonGPIO;
    int buttonDebounceDelay;
    int buttonLongPressDuration;
    int buttonDoubleClickMaxDelay;

    bool isPressed;
    bool lastRawState;
    unsigned long lastDebounceTime;
    unsigned long pressStart;
    unsigned long lastReleaseTime;
    bool waitingSecondClick;
    bool pendingSingleClick;

public:
    MyButton(int gpioNumber, int typebouton);
    void setButtonDebounceDelay(int delay);
    void setButtonLongPressDuration(int duration);
    void setButtonDoubleClickMaxDelay(int delay);
    int checkMyButton();
};

#endif
