
#include "NuiApi.h"

class CGestures
{

public: 
	CGestures(bool follow, bool isMiddle);

	~CGestures();

void gestureControl(Vector4 righthand, Vector4 lefthand, Vector4 head, Vector4 waist);

private:
	bool follow;
	bool isMiddle;
	Vector4 rHand;
	Vector4 lHand;
	Vector4 head;
	Vector4 waist;

void getPastPosition (Vector4 one, Vector4 two, Vector4 three, Vector4 four);
void checkMiddle(Vector4 mid);
void isFollow(Vector4 hand);

};
/* End of File */
