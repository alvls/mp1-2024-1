#include <iostream>
#include "exception.h"

using std::cout;

//using namespace file_fuction_line_exception;

void foo(size_t size)
{
  if (size > 10)
    throw FFLE_EXCEPTION_OBJ("size over 10");
}

int main()
{
  try
  {
    foo(12);
  }
  catch (const TFFLE_EXCEPTION& e)
  {
    cout << "Exception in \n  file: " << e.GetFile() << "\n  func: " << e.GetFunction() <<
      "\n  line: " << e.GetLine() << "\n  description: " << e.GetDescription();
  }
}
