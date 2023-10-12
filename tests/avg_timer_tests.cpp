#include <gtest/gtest.h>
#include "chroma/chroma.h"


// AVERAGE TIMER TEST

class AvgTimerTest : public ::testing::Test {
protected:
    chroma::avg_timer timer{"Test Timer"};

    void SetUp() override {
        timer.reset();
    }
};

TEST_F(AvgTimerTest, InitialCountIsZero) {
    EXPECT_EQ(timer.count(), 0);
}

TEST_F(AvgTimerTest, ComputesAverageTime) {
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Sleep for 100ms
    timer.stop();

    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Sleep for 200ms
    timer.stop();

    // The average should be close to 150ms, but allow some small variation due to scheduling
    EXPECT_NEAR(timer.get_current().count(), 150, 10);  // Expect average to be within 10ms of 150ms
}

TEST_F(AvgTimerTest, CountIncrements) {
    timer.start();
    timer.stop();
    EXPECT_EQ(timer.count(), 1);

    timer.start();
    timer.stop();
    EXPECT_EQ(timer.count(), 2);
}

TEST_F(AvgTimerTest, ResetFunctionWorks) {
    timer.start();
    timer.stop();
    timer.reset();
    EXPECT_EQ(timer.count(), 0);
    EXPECT_NEAR(timer.get_current().count(), 0, 1e-5);  // Expect average to be very close to 0
}

TEST_F(AvgTimerTest, LongerDurationAverage) {
    for (int i = 0; i < 10; ++i) {
        timer.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Sleep for 50ms
        timer.stop();
    }

    // The average should be close to 50ms
    EXPECT_NEAR(timer.get_current().count(), 50, 5);  // Expect average to be within 5ms of 50ms
}
