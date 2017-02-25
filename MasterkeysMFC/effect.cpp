#include "stdafx.h"
#include "effect.h"

struct Keystroke {
	int x;
	int y;
	int cycle = 0;
	float angle = (rand() % 628) / 100.f;
	bool pressed = true;

	Keystroke(int x, int y) :x(x), y(y) {};
};

int rate = 10;
float cycling_speed = PI / 12;
float size = 1;
float speed = 2;
float start_distance = 1;
int color = 384;

std::vector<Keystroke*> keystrokes;
std::vector<Keystroke*> keystrokestmp;
std::map<std::pair<int, int>, Keystroke*> keymap;
std::mutex mut;


void setRate(int r) {
	rate = r;
}

void setSpread(float s) {
	speed = s;
}
void setCycle(float c) {
	cycling_speed = c;
}
void setSize(float s) {
	size = s;
}
void setStart(float s) {
	start_distance = s;
}

void setColor(int c) {
	color = c;
}

void switchDevice(int d) {
	EnableKeyInterrupt(false);
	keystrokes.clear();
	keystrokestmp.clear();
	keymap.clear();
	SetFullLedColor(0, 0, 0);
	EnableLedControl(false);

	SetControlDevice((DEVICE_INDEX)d);

	if (IsDevicePlug()) {
		EnableLedControl(true);
		EnableKeyInterrupt(true);
	}
}

void ColorCycleInit() {
	
	SetKeyCallBack(ColorCycleCallback);
	
	
	SetControlDevice(DEV_MKeys_L);
	if (IsDevicePlug()) {
		EnableLedControl(true);
		RefreshLed(true);
		EnableKeyInterrupt(true);
	}

	timer_start(update);
	srand(time(NULL));
};


void ColorCycleStop() {
	EnableLedControl(false);
};

void CALLBACK ColorCycleCallback(int iRow, int iColumn, bool bPressed)
{
	if (bPressed) {
		Keystroke* key = new Keystroke(iColumn, iRow);
		mut.lock();
		keystrokestmp.push_back(key);
		mut.unlock();
		keymap[std::make_pair(iColumn, iRow)] = key;
	}
	else if(keymap.count(std::make_pair(iColumn, iRow))) {
		keymap[std::make_pair(iColumn, iRow)]->pressed = false;
		keymap.erase(std::make_pair(iColumn, iRow));
	}
};

void timer_start(std::function<void(void)> func)
{
	std::thread([func]() {
		while (true)
		{
			func();
			std::this_thread::sleep_for(std::chrono::milliseconds(rate));
		}
	}).detach();
};


void update()
{
	if (!keystrokestmp.empty()) {
		mut.lock();
		keystrokes.insert(keystrokes.end(), keystrokestmp.begin(), keystrokestmp.end());
		keystrokestmp.clear();
		mut.unlock();
	}

	if (keystrokes.empty()) {
		return;
	}
		

	COLOR_MATRIX ColorCycleBuffer;
	memset(&ColorCycleBuffer, 0, sizeof(ColorCycleBuffer));

	for (Keystroke* key : keystrokes) {
		float xDirStart = cos(key->angle);
		float yDirStart = sin(key->angle);

		for (int y = 0; y < MAX_LED_ROW; y++) {
			for (int x = 0; x < MAX_LED_COLUMN; x++) {
				float xDir = xPosMap[y][x] - xPosMap[key->y][key->x];
				float yDir = yPosMap[y][x] - yPosMap[key->y][key->x];
				float angle = atan2(yDirStart, xDirStart) - atan2(yDir, xDir);
				float distance = sqrt(pow(xDir, 2) + pow(yDir, 2));
				float intensity = 1 - abs(distance - (key->cycle* speed + start_distance)) / size;
				intensity = intensity < 0 ? 0 : intensity;

				int anglenorm = angle * 384 / PI;

				int anglenormr = anglenorm > 384 ? anglenorm - 768 : anglenorm;
				anglenormr = anglenormr < -384 ? anglenormr + 768 : anglenormr;
				int red = color - abs(anglenormr);
				red = red < 0 ? 0 : red;
				red = red > 255 ? 255 : red;

				int anglenormg = anglenorm > 384 + 256 ? anglenorm - 768 : anglenorm;
				anglenormg = anglenormg < -384 + 256 ? anglenormg + 768 : anglenormg;
				int green = color - abs(anglenormg - 256);
				green = green < 0 ? 0 : green;
				green = green > 255 ? 255 : green;

				//baaaaaad :D
				int anglenormb = anglenorm > 384 + 512 ? anglenorm - 768 : anglenorm;
				anglenormb = anglenormb < -384 + 512 ? anglenormb + 768 : anglenormb;
				anglenormb = anglenormb > 384 + 512 ? anglenormb - 768 : anglenormb;
				anglenormb = anglenormb < -384 + 512 ? anglenormb + 768 : anglenormb;
				int blue = color - abs(anglenormb - 512);
				blue = blue < 0 ? 0 : blue;
				blue = blue > 255 ? 255 : blue;

				ColorCycleBuffer.KeyColor[y][x] = KEY_COLOR(red, green, blue) * intensity + ColorCycleBuffer.KeyColor[y][x] * (1 - intensity);
			}
		}
		key->angle += cycling_speed;

		if (key->pressed == false) {
			key->cycle++;
		}
	}
	SetAllLedColor(ColorCycleBuffer);

	int i = 0;
	while (i<keystrokes.size() && keystrokes.at(i)->cycle >(22 + size) / speed) {
		delete (keystrokes[i]);
		i++;
	}

	if (i) {
		keystrokes.erase(keystrokes.begin(), keystrokes.begin() + i);
	}
};
