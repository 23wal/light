#include <AccelStepper.h>
#include <Arduino.h>
#include <DMXSerial.h>

#define MAX_SPEED 200
#define TYPE_DIRECT 1
#define TYPE_SPEED 2
const int address = 0;
int dmx_value = 0;
bool rotate = true;

AccelStepper stepper;

typedef struct {
    int type;
    int address;
    int value;
    int oldValue;
} dataNode; //  creates a struct type dataNode

dataNode functions[2] = {{TYPE_DIRECT, 0, 0, -1}, {TYPE_SPEED, 1, 0, -1}};

// direct: 0: rotate nonstop; 1-255: move to position
// speed: 0-255: speed
void setup() {
    DMXSerial.init(DMXReceiver);
    stepper.setMaxSpeed(MAX_SPEED);
    stepper.setAcceleration(100);
    stepper.setSpeed(0);
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
                rotate = true;
            } else {
                rotate = false;
                stepper.moveTo(map(node.value, 1, 255, -500, 500));
            }
            break;
        case TYPE_SPEED:
            stepper.setSpeed(map(node.value, 0, 255, 0, MAX_SPEED));
            break;
        default:
            break;
        }
        node.oldValue = node.value;
    }

    // Ensure movement continues:
    if (rotate) {
        stepper.runSpeed(); // Non-blocking continuous rotation
    } else {
        stepper.run(); // If speed is 0, return to position mode
    }
}
