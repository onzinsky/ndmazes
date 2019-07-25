// Source: http://www.cplusplus.com/articles/4z18T05o/#POSIX
// Altered by onz
#include "clear_screen.hpp"

// Paste one of the above ClearScreen code snippets here.
// For example, here's the POSIX stuff:
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif


// Not a good way to do this, but only one that worked for me.
// Didn't want to waste more time on this.
void ClearScreen()
  {
    system("clear");
  }