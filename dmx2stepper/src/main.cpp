#include <Arduino.h>
#include <DMXSerial.h>
#include <Stepper.h>

#define DMX_ADDRESS 140

#define STEPS_PER_REV 2048
#define MIN_SPEED 1
#define MAX_SPEED 10

#define TYPE_DIRECT 1
#define TYPE_SPEED 2
unsigned long lastUpdate = 0; // Tracks last loop execution

int currentPosition = 0; // Stores the stepper's current position
int rotationSteps = 0;   // Tracks how many steps have been taken in rotation mode
bool rotate = false;

Stepper stepper(STEPS_PER_REV, 2, 4, 3, 5); // Define stepper pins

typedef struct {
    int type;
    int address;
    int value;
    int oldValue;
} dataNode;

dataNode functions[2] = {{TYPE_DIRECT, DMX_ADDRESS, 0, 0}, {TYPE_SPEED, DMX_ADDRESS + 1, 0, 0}};

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
