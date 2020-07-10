/*
 
*/

#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

#include "gtest/gtest.h"

extern "C" {
  #include "./LinkedList.h"
  #include "./LinkedList_priv.h"
}

#include "./test_suite.h"

namespace hw1 {
  
  int comparator(LLPayload_t p1, LLPayload_t p2) {
    // A comparator used to test sort.
    if (p1 > p2)
      return 1;
    if (p1 < p2)
      return -1;
    return 0;
  }

  class Test_LinkedList : public ::testing::Test {
  protected:
    // Code here will be called before each test executes (ie, before
    // each TEST_F).
    virtual void SetUp() {
      freeInvocations_ = 0;
    }

    // Code here will be called after each test executes (ie, after
    // each TEST_F)
    virtual void TearDown() {
      // Verify that none of the tests modifies any of the
      // testing constants.
      ASSERT_EQ((LLPayload_t)1U, kOne);
      ASSERT_EQ((LLPayload_t)2U, kTwo);
      ASSERT_EQ((LLPayload_t)3U, kThree);
      ASSERT_EQ((LLPayload_t)4U, kFour);
      ASSERT_EQ((LLPayload_t)5U, kFive);
    }

    // These values are used as payloads for the LinkedList tests.
    // They cannot be const, as stored value pointers are non-const.
    static LLPayload_t kOne, kTwo, kThree, kFour, kFive;

    // A stubbed and instrumented version of free() which counts how many
    // times it's been invoked; this allows us to make assertions without
    // actually freeing the payload (which had never been allocated in the
    // first place).  Note that the counter is reset in SetUp().
    static int freeInvocations_;
    static void StubbedFree(LLPayload_t payload) {
      // Do nothing but verify the payload is non-NULL and
      // increment the free count.
      ASSERT_TRUE(payload != NULL);
      freeInvocations_++;
    }
  };  // class Test_LinkedList

  TEST_F(Test_LinkedList, TestLinkedListCoverage) {                                 //create a linkedlist
    LinkedList *llp = LinkedList_Allocate();
    LinkedList_Sort(llp, true, &comparator);
  }

} 
