#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

const int windowY = 20;
const int windowX = 10;
auto size = 25;
/**Пустые массивы полей для игроков*/
int field[windowY][windowX] = {0};
int field2[windowY][windowX] = {0};

struct Point
{
   int x, y;
} a[4], b[4], c[4], d[4];
/**Массив где хранятся размеры фигур*/
int figures[7][4] = {
        1, 3, 5, 7, 2, 4, 5, 7, 3, 5, 4, 6, 3, 5, 4, 7, 2, 3, 5, 7, 3, 5, 7, 6, 2, 3, 4, 5,
};
/** Функция реализует остановку фигуры в конце  первого поля и создания новой фигуры.
 */
bool check()
{
   for (int i = 0; i < 4; i++)
      if (a[i].x < -3 || a[i].x >= 7 || a[i].y >= windowY)
         return false;
      else if (field[a[i].y][a[i].x])
         return false;
   return true;
}
/** Функция реализует остановку фигуры в конце  второго поля и создания новой фигуры.
 */
bool check2()
{
   for (int i = 0; i < 4; i++)
      if (c[i].x < -3 || c[i].x >= 7 || c[i].y >= windowY)
         return false;
      else if (field2[c[i].y][c[i].x])
         return false;
   return true;
}
/** Функция menu реализует начальный экран для игры с кнопками.
 */
void menu(RenderWindow &window)
{ /**Класс Image  подгружает изображение из файла в проект.
   */
   Image background_field, menu_field;
   menu_field.loadFromFile("ffww2.png");
   background_field.loadFromFile("ffww.png");
   /**Класс Texture преобразует  изображение из файла в текстуру.
    */
   Texture background_field_texture, menu_field_texture;
   menu_field_texture.loadFromImage(menu_field);
   background_field_texture.loadFromImage(background_field);
   /**Класс Sprite преобразует  текстуру в спрайт для вывода на экран.
    */
   Sprite background_menu(background_field_texture);
   background_menu.setPosition(0, 0);
   Sprite menu_field_sprite(menu_field_texture);
   menu_field_sprite.setPosition(0, 0);
   /**Класс Font подгружает сторонний шрифт в прорект.
    */
   Font font1;
   font1.loadFromFile("font1.otf");
   /**Класс Text подгружает сторонний шрифт в прорект.
    */
   Text text1("START", font1, 50), text2("ABOUT", font1, 50), text3("EXIT", font1, 50), text4("TETRIS", font1, 80), text5("", font1, 50);
   text1.setPosition(175, 205);
   text2.setPosition(175, 280);
   text3.setPosition(210, 355);
   text4.setPosition(72, 50);
   text4.setFillColor(Color::Green);
   /** Цикл запуска окна перед игрой с  активными кнопками "Start" "About" "Exit".
    *   "Start"-закрывает меню и запускает цикл с игрой.
    *   "About" - краткая инофрмация о проекте.
    *   "Exit"- закрывает полностью окно проекта.
    */
   bool isMenu = true;
   int menuNum = 0;
   while (isMenu)
   {
      text1.setFillColor(Color::Green);
      text2.setFillColor(Color::Green);
      text3.setFillColor(Color::Green);
      if (IntRect(175, 205, 240, 50).contains(Mouse::getPosition(window)))
      {
         text1.setFillColor(Color::Blue);
         menuNum = 1;
      }
      if (IntRect(175, 280, 240, 50).contains(Mouse::getPosition(window)))
      {
         text2.setFillColor(Color::Blue);
         menuNum = 2;
      }
      if (IntRect(210, 355, 170, 50).contains(Mouse::getPosition(window)))
      {
         text3.setFillColor(Color::Blue);
         menuNum = 3;
      }
      if (Mouse::isButtonPressed(Mouse::Left))
      {
         if (menuNum == 1)
            isMenu = false;

         if (menuNum == 2)
         {
            window.draw(menu_field_sprite);
            window.display();
            while (!Keyboard::isKeyPressed(Keyboard::Escape))
               ;
         }
         if (menuNum == 3)
         {
            window.close();
            isMenu = false;
         }
      }
      Event event;
      while (window.pollEvent(event))
      {
         if (event.type == Event::Closed)
            window.close();
      }
      /** Выводит текст и задний фон для меню на экран.*/
      window.draw(background_menu);
      window.draw(text1);
      window.draw(text2);
      window.draw(text3);
      window.draw(text4);
      window.display();
   }
}

bool start()
{
   srand(time(0));
   /**Класс RenderWindow создает окно для проекта.
    */
   RenderWindow window(VideoMode(windowX * size + windowX * size + 3 * size, windowY * size + size * 2), "Tetris!");
   menu(window);
   /**Класс Font подгружает в проект сторонний шрифт.
    */
   Font font1;
   font1.loadFromFile("font1.otf");
   /**Класс Image  подгружает изображение из файла в проект.
    */
   Image background_field, background_game1;
   background_field.loadFromFile("fon.png");
   background_game1.loadFromFile("ffww.png");
   /**Класс Text -.
    */
   Text text5("wasted", font1, 30), text6("wasted", font1, 30), text7(" ", font1, 20), text8(" ", font1, 20);
   /**Класс Texture преобразует  изображение из файла в текстуру.
    */
   Texture background_field_texture, background_game,texture;
   background_field_texture.loadFromImage(background_field);
   background_game.loadFromImage(background_game1);
   texture.loadFromFile("tiles.png");
   /**Класс Sprite преобразует  текстуру в спрайт для вывода на экран.
    */
   Sprite background[2], background_game_sprite(background_game);
   background_game_sprite.setPosition(0, 0);

   for (int i = 0; i < 2; i++)
   {
      background[i].setTexture(background_field_texture);
      background[i].setPosition(size + (windowX * size + size) * i, size);
   }

   Sprite tiles[2];
   for (int i = 0; i < 2; i++)
      tiles[i].setTexture(texture);
   int dx[2], colorNum[2];
   bool rotate[2];
   float timer[2], delay[2];
   Clock clock[2];
   for (int i = 0; i < 2; i++)
   {
      dx[i] = 0;
      colorNum[i] = 1;
      rotate[i] = false;
      timer[i] = 0;
      delay[i] = 0.3;
   }
   bool ad = true;
   bool good1 = true;
   bool good2 = true;
   while (window.isOpen())
   {
      float time[2];
      for (int i = 0; i < 2; i++)
      {
         time[i] = clock[i].getElapsedTime().asSeconds();
         clock[i].restart();
         timer[i] += time[i];
      }
      Event event;
      while (window.pollEvent(event))
      {
         if (event.type == Event::Closed)
            window.close();
         /** Забинжены клавиши для управления фигурами игроков.
          */
         if ((event.type == Event::KeyPressed))
            if (event.key.code == Keyboard::W)
               rotate[0] = true;
            else
            {
               if (event.key.code == Keyboard::D)
                  dx[0] = 1;
            }
         else if (event.key.code == Keyboard::A)
            dx[0] = -1;
         else if (event.key.code == Keyboard::Up)
            rotate[1] = true;
         else if (event.key.code == Keyboard::Right)
            dx[1] = 1;
         else if (event.key.code == Keyboard::Left)
            dx[1] = -1;
      }
      if (Keyboard::isKeyPressed(Keyboard::S))
         delay[0] = 0.05;
      if (Keyboard::isKeyPressed(Keyboard::Down))
         delay[1] = 0.05;
      if (Keyboard::isKeyPressed(Keyboard::Space))
         menu(window);

      for (int i = 0; i < 4; i++)
      {
         b[i] = a[i];
         d[i] = c[i];
         a[i].x += dx[0];
         c[i].x += dx[1];
      }
      if (!check())
      {
         for (int i = 0; i < 4; i++)
            a[i] = b[i];
      }
      if (!check2())
      {
         for (int i = 0; i < 4; i++)
            c[i] = d[i];
      }
      if (rotate[0])
      {
         Point p = a[1];
         for (int i = 0; i < 4; i++)
         {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
         }
         if (!check())
         {
            for (int i = 0; i < 4; i++)
               a[i] = b[i];
         }
      }
      if (rotate[1])
      {
         Point p = c[1];
         for (int i = 0; i < 4; i++)
         {
            int x = c[i].y - p.y;
            int y = c[i].x - p.x;
            c[i].x = p.x - x;
            c[i].y = p.y + y;
         }
         if (!check2())
         {
            for (int i = 0; i < 4; i++)
               c[i] = d[i];
         }
      }
      /**Метод падения фигур для первого игрока.
       */
      if (timer[0] > delay[0])
      {
         for (int i = 0; i < 4; i++)
         {
            b[i] = a[i];
            a[i].y += 1;
         }
         if (!check())
         {
            for (int i = 0; i < 4; i++)
               field[b[i].y][b[i].x] = colorNum[0];
            colorNum[0] = 1 + rand() % 7;
            int n = rand() % 7;

            for (int i = 0; i < 4; i++)
            {
               a[i].x = figures[n][i] % 2;
               a[i].y = figures[n][i] / 2;
            }
         }

         timer[0] = 0;
      }
      /**Метод падения фигур для второго игрока.
       */
      if (timer[1] > delay[1])
      {
         for (int i = 0; i < 4; i++)
         {
            d[i] = c[i];
            c[i].y += 1;
         }
         if (!check2())
         {
            for (int i = 0; i < 4; i++)
               field2[d[i].y][d[i].x] = colorNum[1];
            colorNum[1] = 1 + rand() % 7;
            int n = rand() % 7;
            for (int i = 0; i < 4; i++)
            {
               c[i].x = figures[n][i] % 2;
               c[i].y = figures[n][i] / 2;
            }
         }

         timer[1] = 0;
      }
      if (ad)
      {
         int n[2];
         for (int i = 0; i < 2; i++)
            n[i] = rand() % 7;
         if (a[0].x == 0 && c[0].x == 0)
            for (int i = 0; i < 4; i++)
            {
               a[i].x = figures[n[0]][i] % 2;
               a[i].y = figures[n[0]][i] / 2;
               c[i].x = figures[n[1]][i] % 2;
               c[i].y = figures[n[1]][i] / 2;
            }
         ad = false;
      }
      int sc1re;
      int k = windowY - 1;
      for (int i = windowY - 1; i > 0; i--)
      {
         int count = 0;
         for (int j = -3; j < 7; j++)
         {
            if (field[i][j])
               count++;
            field[k][j] = field[i][j];
         }
         if (count < windowX)
            k--;
      }

      if (k--)
      {
         sc1re += 10;
      }


      int k2 = windowY - 1;
      for (int i = windowY - 1; i > 0; i--)
      {
         int count = 0;
         for (int j = -3; j < 7; j++)
         {
            if (field2[i][j])
               count++;
            field2[k2][j] = field2[i][j];
         }
         if (count < windowX)
            k2--;
      }
      int sc2re;
      if (k2--)
      {
         sc2re += 10;
      }

      for (int i = 0; i < 2; i++)
      {
         dx[i] = 0;
         rotate[i] = false;
         delay[i] = 0.3;
      }
      window.clear(Color::White);
      window.draw(background_game_sprite);
      for (int i = 0; i < 2; i++)
         window.draw(background[i]);
      if (good1)
      {
         for (int i = 0; i < windowY; i++)
            for (int j = -3; j < 7; j++)
            {
               if (field[i][j] == 0)
                  continue;
               tiles[0].setTextureRect(IntRect(field[i][j] * size, 0, size, size));
               tiles[0].setPosition(j * size, i * size);
               tiles[0].move(4 * size, size);
               window.draw(tiles[0]);
               if (i <= 1)
               {
                  good1 = false;
               }
            }
      }
      else
      {
         window.draw(text6);
         text6.setPosition(55, 250);
      }
      if (good2)
      {
         for (int i = 0; i < windowY; i++)
            for (int j = -3; j < 7; j++)
            {
               if (field2[i][j] == 0)
                  continue;
               tiles[1].setTextureRect(IntRect(field2[i][j] * size, 0, size, size));
               tiles[1].setPosition((j * size), (i * size));
               tiles[1].move(5 * size + (size * windowX), size);
               window.draw(tiles[1]);
               if (i <= 1)
               {
                  good2 = false;
               }
            }
      }
      else
      {
         window.draw(text5);
         text5.setPosition(330, 250);
      }
      for (int i = 0; i < 4; i++)
      {
         tiles[0].setTextureRect(IntRect(colorNum[0] * size, 0, size, size));
         tiles[1].setTextureRect(IntRect(colorNum[1] * size, 0, size, size));
         tiles[0].setPosition(a[i].x * size, a[i].y * size);
         tiles[1].setPosition(c[i].x * size, c[i].y * size);

         for (int j = 0; j < 2; j++)
         {
            tiles[j].move(4 * size + (size * windowX + size) * j, size);
            window.draw(tiles[j]);
         }
      }
      /** Ниже строчки преобразуют численное значение в строку и выводят на экран рекод.
       */
      ostringstream sc1re_string, sc2re_string;
      sc1re_string << sc1re;
      sc2re_string << sc2re;
      text7.setString("score " + sc1re_string.str());
      text7.setPosition(25, 15);
      text8.setString("score " + sc2re_string.str());
      text8.setPosition(300, 15);
      window.draw(text7);
      window.draw(text8);
      window.display();
   }
   return 0;
}
