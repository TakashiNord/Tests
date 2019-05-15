// test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <math.h>

using namespace std;

class Point {
public:
 int x ;
 int y ;
 Point::Point( int xx, int yy) { x=xx; y=yy; } ;
};

std::vector <Point> Points;


/*
Функция разбивает число на разряды и суммирует их
*/
int FVes1( int v )
{
  double tmp ;
  int whole , fractional ;
  int sum = 0;

  //#include <cmath>    float modf(float num, float *i)
  // Функция modf() раскладывает число num на целую и дробную части.
  // Функция возвращает дробную часть, а целая часть сохраняется в переменной-указатель i.
  // основная идея =>   int i = (int)d; double fract = d - i;
  tmp = fabs(v) ;
  do {
    tmp=tmp/10.0;
    whole = floor(tmp);
    fractional = floor( tmp*10. - whole * 10. );
    sum+=fractional;
    tmp=whole;
  } while(whole>0) ;
  return (sum) ;
}

/*
Функция суммирует вес 2-х чисел
*/
int FVes2( int v1 , int v2)
{
  int res=0;
  res=FVes1(v1) + FVes1(v2);
  return (res) ;
}

/*
Функция - основная
*/
long int F1()
{
  int x, y; // текущие целочисленные координаты
  int dx, dy ;
  int px, py ;
  int a, b; // координаты центра начала
  long int count = 0;
  int count_curr = 0;
  int Rprev, Rcur ;
  long int D1 , D2 ;
  long int w ;
  int WeightConst ;

  WeightConst = 25 ; // вес точки - ограничение
  dx = 1; dy = 1 ;
  a = 1000;
  b = 1000;

  Point P0(a,b);
  Points.push_back(P0);

  count = 1 ; // точка (a,b) - общее число точек
  count_curr=0; // число точек только для этого Радиуса
  Rprev=0;
  Rcur=1;
  while (1) {
    count_curr=0;
    // вариант с тупым перебором всех точек
    for (y=-Rcur+b; y<=(Rcur+b); ++y)
      for (x=-Rcur+a; x<=(Rcur+a); ++x)
      {
        D1=(x-a)*(x-a) + (y-b)*(y-b);
        if (D1<=(Rprev*Rprev)) {
         ;
        } else {
         if (D1<=(Rcur*Rcur)) {
           // calc Weight
           w=FVes2(x,y);
           //printf("\nP(%d ,%d) => W=%d",x,y,w);
           if (w<WeightConst) {
             // новая точка с подходящим весом, должна отсоять от уже выбранных на s=1
             // то-есть должен существовать маршрут
             for (unsigned i=0; i<Points.size(); i++)
             {
               px=Points[i].x;
               py=Points[i].y;
               D2=(x-px)*(x-px)+(y-py)*(y-py);
               if (D2==1) {
                  Point Pxy(x,y);
                  Points.push_back(Pxy);
                  count = count + 1 ;
                  count_curr += 1 ;
                  //printf("\nP(%d ,%d) => W=%d",x,y,w);
                  break ;
               }
              }
           } // if (w<WeightConst)
         } // if (D1<=(Rcur*Rcur))
        }
      } // for

    // отладка - контроль точек, помещаемых в список
    /*
    for (unsigned i=0; i<Points.size(); i++)
    {
       px=Points[i].x;
       py=Points[i].y;
       printf("  Pxy(%d ,%d)",px,py);
    } */

    printf("\nR=%d => N(points)=%d",Rcur,count_curr);
    if (count_curr==0) break ; // если не найдено Ни одной точки
    //if (Rcur==10) break ; // отладка
    Rprev=Rcur;
    Rcur=Rcur+1;
 } // while

 printf ("Count=%d  (Points.size=%d)", count, Points.size() ) ;

 return (count);
}


int main(int argc, char* argv[])
{

  F1() ;

  printf("\n\nHello World!\n");
  return 0;
}

