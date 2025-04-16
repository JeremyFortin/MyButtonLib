#include "MyButton.h"
#include <Arduino.h>

MyButton::MyButton(int gpioNumber, int typebouton)
    : buttonGPIO(gpioNumber),
      buttonDebounceDelay(50),
      buttonLongPressDuration(1000),
      buttonDoubleClickMaxDelay(300),
      isPressed(false),
      lastRawState(false),
      lastDebounceTime(0),
      pressStart(0),
      lastReleaseTime(0),
      waitingSecondClick(false),
      pendingSingleClick(false)
{
    pinMode(buttonGPIO, typebouton);
}

void MyButton::setButtonDebounceDelay(int delay)
{
    buttonDebounceDelay = delay;
}

void MyButton::setButtonLongPressDuration(int duration)
{
    buttonLongPressDuration = duration;
}

void MyButton::setButtonDoubleClickMaxDelay(int delay)
{
    buttonDoubleClickMaxDelay = delay;
}

int MyButton::checkMyButton()
{
    bool currentState = digitalRead(buttonGPIO);
    unsigned long now = millis();

    if (currentState != lastRawState)
    {
        lastDebounceTime = now;
        lastRawState = currentState;
    }

    if ((now - lastDebounceTime) > buttonDebounceDelay)
    {
        if (currentState != isPressed)
        {
            isPressed = currentState;

            if (isPressed)
            {
                pressStart = now;
            }
            else
            {
                unsigned long pressDuration = now - pressStart;
                lastReleaseTime = now;

                if (pressDuration >= buttonLongPressDuration)
                {
                    waitingSecondClick = false;
                    pendingSingleClick = false;
                    return 3;
                }

                if (waitingSecondClick)
                {
                    if ((now - lastReleaseTime) <= buttonDoubleClickMaxDelay)
                    {
                        waitingSecondClick = false;
                        pendingSingleClick = false;
                        return 2;
                    }
                }
                else
                {
                    waitingSecondClick = true;
                    pendingSingleClick = true;
                }
            }
        }
    }

    if (waitingSecondClick && (now - lastReleaseTime > buttonDoubleClickMaxDelay))
    {
        waitingSecondClick = false;
        if (pendingSingleClick)
        {
            pendingSingleClick = false;
            return 1;
        }
    }

    return 0;
}
