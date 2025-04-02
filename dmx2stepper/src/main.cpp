#include <Arduino.h>
#include <DMXSerial.h>
#include <Stepper.h>

const int STEPS_PER_REV = 2048; // Adjust based on your motor
const int MIN_POS = -1000;      // Minimum mapped stepper position
const int MAX_POS = 1000;       // Maximum mapped stepper position
const int MIN_SPEED = 1;        // Min step delay in ms (higher is slower)
const int MAX_SPEED = 10;       // Max step delay in ms (lower is faster)
#define TYPE_DIRECT 1
#define TYPE_SPEED 2

int currentPosition = 0; // Stores the stepper's current position

Stepper stepper(STEPS_PER_REV, 2, 4, 3, 5); // Define stepper pins

typedef struct {
    int type;
    int address;
    int value;
    int oldValue;
} dataNode;

dataNode functions[2] = {{TYPE_DIRECT, 0, 0, 0}, {TYPE_SPEED, 1, 0, 0}};

bool rotate = false;

void setup() {
    DMXSerial.init(DMXReceiver);
    stepper.setSpeed(MAX_SPEED); // Default speed (RPM, not step delay)
}

void loop() {
    for (dataNode &node : functions) {
        node.value = DMXSerial.read(node.address);
        if (node.value == node.oldValue) {
            continue;
        }
        switch (node.type) {
        case TYPE_DIRECT:
            if (node.value == 0) {
                // Enable continuous rotation
                rotate = true;
            } else {
                rotate = false;
                int targetPosition = map(node.value, 1, 255, MIN_POS, MAX_POS);
                stepper.step(targetPosition - currentPosition);
                currentPosition = targetPosition; // Update position
            }
            break;
        case TYPE_SPEED:
            stepper.setSpeed(map(node.value, 0, 255, MIN_SPEED, MAX_SPEED));
            break;
        default:
            break;
        }

        node.oldValue = node.value;
        // Continuous rotation mode
        if (rotate) {        // If "direct" channel is 0
            stepper.step(1); // Move continuously
        }
    }
