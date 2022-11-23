#include "Ball.h"

class Ball
{
 public:
	 Vect pos;
	 RECT rect;
   
	 Ball(Vect pos) : pos(pos)
	 {
		 rect.left = wBall - 5;
		 rect.top = hBall - 5;
		 rect.right = wBall + 5;
		 rect.bottom = hBall + 5;
	 }

	 void Draw(HDC hdc)
	 {
		 Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	 }


};
