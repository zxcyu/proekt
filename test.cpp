#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "main.h"

TEST_CASE("1")
{
   /**
    * Метод ставит курсор в точку на экране,после чего зажимается левая кнопка мыши.
    * Когда окно закрывается, кнопка отжимается.
    **/
   SetCursorPos(800, 550);
   mouse_event(MOUSEEVENTF_LEFTDOWN, 500, 500, 0, 0);
   CHECK(start() == false);
   mouse_event(MOUSEEVENTF_LEFTUP, 500, 500, 0, 0);
}
TEST_CASE("2")
{
   CHECK(check() == true);
   CHECK(check2() == true);
}