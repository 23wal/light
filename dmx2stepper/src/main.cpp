#include <Arduino.h>
#include <DMXSerial.h>
#include <Stepper.h>

// dmx
const int dipPins[10] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int dmxAddress = 0;

// motor
#define STEPS_PER_REV 2048
#define MIN_SPEED 1
#define MAX_SPEED 10

#define TYPE_DIRECT 1
#define TYPE_SPEED 2
unsigned long lastUpdate = 0; // Tracks last loop execution

int currentPosition = 0; // Stores the stepper's current position
int rotationSteps = 0;   // Tracks how many steps have been taken in rotation mode
bool rotate = false;

Stepper stepper(STEPS_PER_REV, A0, A2, A1, A3); // Define stepper pins

typedef struct {
    int type;
    int address;
    int value;
    int oldValue;
} dataNode;

dataNode functions[2] = {{TYPE_DIRECT, 0, 0, 0}, {TYPE_SPEED, 1, 0, 0}};

void setup() {
    DMXSerial.init(DMXReceiver);
    stepper.setSpeed(MAX_SPEED); // Default speed (RPM, not step delay)
    for (int i = 0; i < 10; i++) {
        pinMode(dipPins[i], INPUT_PULLUP); // Enable internal pull-up resistors
    }
    dmxAddress = 0;
    for (int i = 0; i < 10; i++) {
        if (digitalRead(dipPins[i]) == LOW) { // Switch ON means LOW due to pull-up
            dmxAddress |= (1 << i);           // Set corresponding bit
        }
    }
}

void loop() {
    for (dataNode &node : functions) {
        node.value = DMXSerial.read(dmxAddress + node.address);
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
                int targetPosition = map(node.value, 1, 255, 0, STEPS_PER_REV);
                // Calculate shortest distance
                int distance = targetPosition - (rotationSteps + currentPosition);

                // If the distance is more than half a revolution, take the shorter path
                if (abs(distance) > STEPS_PER_REV / 2) {
                    distance -= STEPS_PER_REV * ((distance > 0) ? 1 : -1);
                }
                stepper.step(distance);

                rotationSteps = 0;
                currentPosition = targetPosition;
            }
            break;
        case TYPE_SPEED:
            stepper.setSpeed(map(node.value, 0, 255, MIN_SPEED, MAX_SPEED));
            break;
        default:
            break;
        }
        node.oldValue = node.value;
    }

    // Continuous rotation mode
    if (rotate) {
        // Move continuously
        stepper.step(1);
        // Count how many steps have been taken
        rotationSteps += 1;

        // Reset rotationSteps after a full rotation
        if (rotationSteps >= STEPS_PER_REV) {
            rotationSteps = 0; // Reset after one full rotation
        }
    }
}
