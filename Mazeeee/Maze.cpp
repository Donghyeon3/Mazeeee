#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int block[18][32] =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,1},
{1,0,0,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,1,0,1},
{1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1},
{1,1,0,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
{1,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,1,0,1,1,1,1,1,0,1},
{1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,0,0,0,0,0,1},
{1,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,0,1,0,2,2,2,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,2,2,2,0,1},
{1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,1,0,0,1,0,0,0,0,0,1},
{1,0,0,0,0,0,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,1},
{1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
{1,1,0,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1},
{1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1},
{1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

SceneID scene1;
ObjectID p1, p2, p3, M, light, success;
int IX = 80, IY = 300;
int p1dx, p1dy;
int p2dx, p2dy;
int p3dx, p3dy;
int RN;
int speed = 2, lt = 1;
float bm = 2;
float t = 0;
float p1x = IX, p1y = IY, p2x = IX + 30, p2y = IY, p3x = IX + 60, p3y = IY;
float MX = 604, MY = 324;
TimerID timer1;

int direction(int dx, int dy) {
	if (dx > 0 && dy > 0) return 2;
	else if (dx > 0 && dy < 0) return 4;
	else if (dx < 0 && dy > 0) return 8;
	else if (dx < 0 && dy < 0) return 6;
	else if (dy > 0 && dx == 0) return 1;
	else if (dx > 0 && dy == 0) return 3;
	else if (dy < 0 && dx == 0) return 5;
	else if (dx < 0 && dy == 0) return 7;
}

void backmove(float* x, float* y, int dir) {
	if (dir == 1) {
		*y -= bm;
	}
	else if (dir == 2) {
		*x -= bm;
		*y -= bm;
	}
	else if (dir == 3) {
		*x -= bm;
	}
	else if (dir == 4) {
		*x -= bm;
		*y += bm;
	}
	else if (dir == 5) {
		*y += bm;
	}
	else if (dir == 6) {
		*x += bm;
		*y += bm;
	}
	else if (dir == 7) {
		*x += bm;
	}
	else if (dir == 8) {
		*x += bm;
		*y -= bm;
	}
}

void isBlocked(ObjectID object, int x, int y, int dir) {
	if (block[17 - (y / 40)][x / 40] == 1) {
		if (object == p1) {
			backmove(&p1x, &p1y, dir);
		}
		else if (object == p2) {
			backmove(&p2x, &p2y, dir);
		}
		else if (object == p3) {
			backmove(&p3x, &p3y, dir);
		}
		else if (object == M) {
			backmove(&MX, &MY, dir);
		}
	}
	else if (block[17 - (y / 40)][x / 40] == 2) {///////////Á¾·á
		locateObject(success, scene1, 200, 270);
		scaleObject(success, 1);
		showObject(success);
	}
}

void checkBlock(ObjectID object, int x, int y, int dir, int size) {
	isBlocked(object, x, y, dir);
	isBlocked(object, x + size, y, dir);
	isBlocked(object, x, y + size, dir);
	isBlocked(object, x + size, y + size, dir);
}

void setImageD(ObjectID object1, int id, int dir) {
	char pim[20];
	if (dir == 1) {
		sprintf_s(pim, 20, "images/%dU.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 2) {
		sprintf_s(pim, 20, "images/%dRU.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 3) {
		sprintf_s(pim, 20, "images/%dR.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 4) {
		sprintf_s(pim, 20, "images/%dRD.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 5) {
		sprintf_s(pim, 20, "images/%dD.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 6) {
		sprintf_s(pim, 20, "images/%dLD.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 7) {
		sprintf_s(pim, 20, "images/%dL.png", id);
		setObjectImage(object1, pim);
	}
	else if (dir == 8) {
		sprintf_s(pim, 20, "images/%dLU.png", id);
		setObjectImage(object1, pim);
	}
}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		p1x += p1dx;
		p1y += p1dy;
		p2x += p2dx;
		p2y += p2dy;
		p3x += p3dx;
		p3y += p3dy;
		t += 0.01;
		checkBlock(p2, p2x, p2y, direction(p2dx, p2dy), 24);
		checkBlock(p1, p1x, p1y, direction(p1dx, p1dy), 24);
		checkBlock(p3, p3x, p3y, direction(p3dx, p3dy), 24);
		setImageD(p2, 2, direction(p2dx, p2dy));
		setImageD(p1, 1, direction(p1dx, p1dy));
		setImageD(p3, 3, direction(p3dx, p3dy));
		if (lt == 1) {
			locateObject(light, scene1, p1x - 1910, p1y - 1070);
			lt++;
		}
		else if (lt == 2) {
			locateObject(light, scene1, p2x - 1910, p2y - 1070);
			lt++;
		}
		else if (lt == 3) {
			locateObject(light, scene1, p3x - 1910, p3y - 1070);
			lt = 1;
		}
		locateObject(M, scene1, MX, MY);
		if (((p1x >= MX && p1x <= MX + 32) && (p1y >= MY && p1y <= MY + 32)) || ((p1x + 24 >= MX && p1x + 24 <= MX + 32) && (p1y >= MY && p1y <= MY + 32)) || ((p1x >= MX && p1x <= MX + 32) && (p1y + 24 >= MY && p1y + 24 <= MY + 32)) || ((p1x + 24 >= MX && p1x + 24 <= MX + 32) && (p1y + 24 >= MY && p1y + 24 <= MY + 32))) {
			p1x = IX;
			p1y = IY;
		}
		if (((p2x >= MX && p2x <= MX + 32) && (p2y >= MY && p2y <= MY + 32)) || ((p2x + 24 >= MX && p2x + 24 <= MX + 32) && (p2y >= MY && p2y <= MY + 32)) || ((p2x >= MX && p2x <= MX + 32) && (p2y + 24 >= MY && p2y + 24 <= MY + 32)) || ((p2x + 24 >= MX && p2x + 24 <= MX + 32) && (p2y + 24 >= MY && p2y + 24 <= MY + 32))) {
			p2x = IX + 30;
			p2y = IY;
		}
		if (((p3x >= MX && p3x <= MX + 32) && (p3y >= MY && p3y <= MY + 32)) || ((p3x + 24 >= MX && p3x + 24 <= MX + 32) && (p3y >= MY && p3y <= MY + 32)) || ((p3x >= MX && p3x <= MX + 32) && (p3y + 24 >= MY && p3y + 24 <= MY + 32)) || ((p3x + 24 >= MX && p3x + 24 <= MX + 32) && (p3y + 24 >= MY && p3y + 24 <= MY + 32))) {
			p3x = IX + 60;
			p3y = IY;
		}
		if (t >= 0.2) {
			RN = rand() % 4;
			t = 0;
		}
		if (RN == 0) {
			MY += speed;
			checkBlock(M, MX, MY, 1, 32);
			setObjectImage(M, "images/4U.png");
		}
		else if (RN == 1) {
			MX += speed;
			checkBlock(M, MX, MY, 3, 32);
			setObjectImage(M, "images/4R.png");
		}
		else if (RN == 2) {
			MX -= speed;
			checkBlock(M, MX, MY, 7, 32);
			setObjectImage(M, "images/4L.png");
		}
		else if (RN == 3) {
			MY -= speed;
			checkBlock(M, MX, MY, 5, 32);
			setObjectImage(M, "images/4D.png");
		}
		locateObject(p1, scene1, p1x, p1y);
		locateObject(p2, scene1, p2x, p2y);
		locateObject(p3, scene1, p3x, p3y);
		setTimer(timer1, 0.01f);
		startTimer(timer1);
	}
}


void keyboardCallback(KeyCode code, KeyState state)
{
	if (code == KeyCode::KEY_D) {
		p1dx += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_A) {
		p1dx -= (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_W) {
		p1dy += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_S) {
		p1dy -= (state == KeyState::KEY_PRESSED ? speed : -speed);
	}

	if (code == KeyCode::KEY_L) {
		p2dx += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_J) {
		p2dx -= (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_I) {
		p2dy += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_K) {
		p2dy -= (state == KeyState::KEY_PRESSED ? speed : -speed);
	}

	if (code == KeyCode::KEY_RIGHT_ARROW) {
		p3dx += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_LEFT_ARROW) {
		p3dx -= (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_UP_ARROW) {
		p3dy += (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
	else if (code == KeyCode::KEY_DOWN_ARROW) {
		p3dy -= (state == KeyState::KEY_PRESSED ? speed : -speed);
	}
}

int main() {
	RN = rand() % 4;
	srand(time(NULL));
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);
	scene1 = createScene("Maze", "images/background.png");
	timer1 = createTimer(0.01f);
	startTimer(timer1);
	success = createObject("images/success.png");
	light = createObject("images/LIGHT.png");
	p1 = createObject("images/1D.png");
	p2 = createObject("images/2D.png");
	p3 = createObject("images/3D.png");
	M = createObject("images/4D.png");
	scaleObject(M, 0.08f);
	showObject(M);
	locateObject(M, scene1, MX, MY);
	locateObject(light, scene1, p1x - 1910, p1y - 1070);
	scaleObject(p2, 0.03f);
	scaleObject(p1, 0.03f);
	scaleObject(p3, 0.03f);
	//showObject(light);
	showObject(p1);
	showObject(p2);
	showObject(p3);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	startGame(scene1);
}