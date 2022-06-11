#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "main.h"
TEST_CASE("закрытие окна1") {
   SetCursorPos(800, 550);
   mouse_event(MOUSEEVENTF_LEFTDOWN, 500, 500, 0, 0);
   CHECK(start() == false );
   mouse_event(MOUSEEVENTF_LEFTUP, 500, 500, 0, 0);
}
