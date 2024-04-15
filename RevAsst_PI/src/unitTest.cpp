
#ifdef UnitTest
#include <gtest/gtest.h>
#include "MotorController.h"

class SetMotorDirectionTest : public ::testing::Test {
protected:
    MotorController motorController;
};

TEST_F(SetMotorDirectionTest, ForwardDirectionTest) {
    int input1Pin = 24;
    int input2Pin = 23;
    int speedAPin = 12;
    int direction = 1; // Forward direction
    int speed = 50;
    
    motorController.setMotorDirection(input1Pin, input2Pin, speedAPin, direction, speed);
    // Add assertions
}

TEST_F(SetMotorDirectionTest, BackwardDirectionTest) {
    int input1Pin = 24;
    int input2Pin = 23;
    int speedAPin = 12;
    int direction = 0; // Backward direction
    int speed =50;
    motorController.setMotorDirection(input1Pin, input2Pin, speedAPin, direction, speed);
    // Add assertions
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif 