#include <gtest/gtest.h>
#include "chroma/chroma.h"


// CIRCULAR BUFFER TESTS

TEST(CircularBufferTest, CreateBuffer) {
  chroma::circular_buffer<int> buf(10);
  EXPECT_EQ(buf.size(), 10);
  EXPECT_EQ(buf.count(), 0);
  EXPECT_FALSE(buf.full());
}

TEST(CircularBufferTest, PushSingleElement) {
  chroma::circular_buffer<int> buf(10);
  int data = 5;
  buf.push(&data, 1);
  EXPECT_EQ(buf.count(), 1);
}

TEST(CircularBufferTest, PushMultipleElements) {
  chroma::circular_buffer<int> buf(10);
  int data[] = {1, 2, 3, 4, 5};
  buf.push(data, 5);
  EXPECT_EQ(buf.count(), 5);
}

TEST(CircularBufferTest, PopSingleElement) {
  chroma::circular_buffer<int> buf(10);
  int data = 5;
  buf.push(&data, 1);
  
  int pop_data;
  buf.pop(&pop_data, 1);
  EXPECT_EQ(pop_data, 5);
  EXPECT_EQ(buf.count(), 0);
}

TEST(CircularBufferTest, PopMultipleElements) {
  chroma::circular_buffer<int> buf(10);
  int data[] = {1, 2, 3, 4, 5};
  buf.push(data, 5);

  int pop_data[5];
  buf.pop(pop_data, 5);
  for (int i = 0; i < 5; ++i)
    EXPECT_EQ(pop_data[i], data[i]);

  EXPECT_EQ(buf.count(), 0);
}

TEST(CircularBufferTest, WrapAround) {
  chroma::circular_buffer<int> buf(3);
  int data[] = {1, 2, 3, 4, 5, 6};
  buf.push(data, 3);
  EXPECT_EQ(buf.count(), 3);

  int data2[] = {7, 8, 9};
  buf.push(data2, 3);
  EXPECT_EQ(buf.count(), 3);  // Ensure the count remains correct after wrap-around

  int pop_data[3];
  buf.pop(pop_data, 3);
  // Expect the latter half of data due to wrap-around
  EXPECT_EQ(pop_data[0], 7);
  EXPECT_EQ(pop_data[1], 8);
  EXPECT_EQ(pop_data[2], 9);
}

TEST(CircularBufferTest, PopFromEmptyBuffer) {
  chroma::circular_buffer<int> buf(10);
  int pop_data;
  EXPECT_THROW(buf.pop(&pop_data, 1), std::out_of_range);
}

TEST(CircularBufferTest, PopTooManyElements) {
  chroma::circular_buffer<int> buf(10);
  int data = 5;
  buf.push(&data, 1);

  int pop_data[2];
  EXPECT_THROW(buf.pop(pop_data, 2), std::out_of_range);
}

