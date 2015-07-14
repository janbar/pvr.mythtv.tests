/*
 * File:   testsuite.h
 * Author: janbar
 *
 * Created on 27 juin 2015
 */

#ifndef TESTSUITE_H
#define	TESTSUITE_H

#include <cstdio>
#include <cstdarg>
#include <vector>

namespace pvrtest
{
  typedef enum
  {
    TEST_SUCCEEDED,
    TEST_FAILED,
    TEST_INCOMPLETE,
  } TestStatus;

  // Unit test interface
  class UnitTest
  {
  public:
    virtual ~UnitTest() {}
    virtual void RunTest() = 0;
    static void Out(TestStatus state, const char *format, ... )
    {
      char buffer[16384];
      va_list args;
      va_start (args, format);
      vsprintf (buffer, format, args);
      va_end (args);
      fprintf(stdout, "%-50.50s.... %s\n", buffer,
              (state == TEST_SUCCEEDED ? "\x1b[32msucceeded\x1b[0m" :
                state == TEST_FAILED ? "\x1b[31mFAILED\x1b[0m" : "\x1b[36mincomplete\x1b[0m"));
    }
  };

  // Test suite: run set of unit test
  class TestSuite
  {
  public:
    TestSuite() {}
    ~TestSuite()
    {
      ClearAll();
    }
    void AddUnitTest(UnitTest* ut) { if (ut) m_list.push_back(ut); }
    void ClearAll()
    {
      for (std::vector<UnitTest*>::const_iterator it = m_list.begin(); it != m_list.end(); ++it)
        delete (*it);
      m_list.clear();
    }
    void RunAll()
    {
      for (std::vector<UnitTest*>::const_iterator it = m_list.begin(); it != m_list.end(); ++it)
        (*it)->RunTest();
    }
  private:
    std::vector<UnitTest*> m_list;
  };
}

#endif	/* TESTSUITE_H */

