#include "OCR2_StaticOCR2.h"

using namespace OCR2;

CharacterMesh charset[] = {
	CharacterMesh(4, 40, 69, 92, 63, 36, 9, 46, 68),			// A
	CharacterMesh(92, 93, 92, 52, 58, 51, 64, 76, 73),			// B
	CharacterMesh(62, 87, 52, 57, 0, 57, 46, 0, 50),			// C
	CharacterMesh(89, 80, 89, 55, 0, 55, 51, 72, 52),			// D
	CharacterMesh(100, 100, 100, 50, 50, 50, 46, 25, 50),		// E
	CharacterMesh(100, 100, 100, 50, 50, 0, 50, 32, 0),			// F
	CharacterMesh(54, 80, 55, 56, 13, 57, 38, 40, 81),			// G
	CharacterMesh(80, 89, 80, 0, 50, 0, 80, 89, 80),			// H
	CharacterMesh(100, 100, 100, 100, 100, 100, 100, 100, 100),	// I
	CharacterMesh(0, 0, 52, 9, 9, 60, 100, 100, 73),			// J
	CharacterMesh(81, 96, 80, 56, 72, 39, 28, 0, 55),			// K
	CharacterMesh(100, 100, 100, 0, 0, 50, 0, 0, 50),			// L
	CharacterMesh(94, 81, 63, 17, 92, 22, 94, 81, 63),			// M
	CharacterMesh(96, 86, 80, 18, 74, 21, 80, 85, 97),			// N
	CharacterMesh(25, 80, 54, 57, 0, 58, 56, 71, 56),			// O
	CharacterMesh(92, 85, 85, 52, 37, 0, 70, 58, 0),			// P
	CharacterMesh(60, 76, 60, 56, 11, 80, 53, 72, 74),			// Q
	CharacterMesh(80, 92, 80, 45, 71, 42, 52, 40, 52),			// R
	CharacterMesh(69, 38, 53, 52, 61, 52, 44, 45, 70),			// S
	CharacterMesh(49, 0, 0, 92, 85, 85, 50, 0, 0),				// T
	CharacterMesh(80, 80, 66, 0, 0, 54, 80, 80, 66),			// U
	CharacterMesh(75, 44, 7, 4, 64, 96, 75, 47, 10),			// V
	CharacterMesh(70, 58, 28, 67, 98, 80, 63, 64, 40),			// W
	CharacterMesh(57, 10, 64, 41, 97, 34, 58, 10, 64),			// X
	CharacterMesh(66, 9, 0, 26, 90, 80, 66, 11, 0),				// Y
	CharacterMesh(39, 12, 87, 60, 76, 64, 88, 15, 50),			// Z

	CharacterMesh(59, 81, 59, 56, 0, 56, 60, 71, 60),			// 0
	CharacterMesh(54, 0, 0, 92, 83, 83, 100, 100, 100),			// 1
	CharacterMesh(45, 0, 70, 52, 48, 83, 69, 49, 50),			// 2
	CharacterMesh(42, 0, 54, 52, 47, 50, 70, 69, 68),			// 3
	CharacterMesh(3, 75, 18, 71, 68, 40, 50, 65, 59),			// 4
	CharacterMesh(96, 56, 51, 50, 43, 53, 26, 61, 67),			// 5
	CharacterMesh(15, 81, 68, 65, 57, 53, 9, 63, 66),			// 6
	CharacterMesh(50, 0, 35, 59, 65, 56, 84, 24, 0),			// 7
	CharacterMesh(63, 74, 69, 53, 60, 46, 64, 76, 68),			// 8
	CharacterMesh(66, 66, 6, 54, 54, 61, 66, 82, 18),			// 9

	CharacterMesh(0, 37, 0, 0, 37, 0, 0, 37, 0),				// -
};

StaticOCR2::StaticOCR2() { }
StaticOCR2::~StaticOCR2() { }

struct kader
{
	int x;
	int y;
	int bp = 0;
	int s = 0;
};

char StaticOCR2::Apply(const ImageLib::ImageGray & Img) {
	int x3 = Img.width();
	int x1 = x3 / 3;
	int x2 = x1 + ceil(x3 / 3);

	int y3 = Img.height();
	int y1 = y3 / 3;
	int y2 = y1 + ceil(y3 / 3);

	kader * ptr = new kader[9];

	ptr[0].x = x1;
	ptr[0].y = y1;
	ptr[0].s = x1 * y1;

	ptr[1].x = x1;
	ptr[1].y = y2;
	ptr[1].s = x1 * (y2 - y1);

	ptr[2].x = x1;
	ptr[2].y = y3;
	ptr[2].s = x1 * (y3 - y2);

	ptr[3].x = x2;
	ptr[3].y = y1;
	ptr[3].s = (x2 - x1) * y1;

	ptr[4].x = x2;
	ptr[4].y = y2;
	ptr[4].s = (x2 - x1) * (y2 - y1);

	ptr[5].x = x2;
	ptr[5].y = y3;
	ptr[5].s = (x2 - x1) * (y3 - y2);

	ptr[6].x = x3;
	ptr[6].y = y1;
	ptr[6].s = (x3 - x2) * y1;

	ptr[7].x = x3;
	ptr[7].y = y2;
	ptr[7].s = (x3 - x2) * (y2 - y1);

	ptr[8].x = x3;
	ptr[8].y = y3;
	ptr[8].s = (x3 - x2) * (y3 - y2);

	int x = 0, y = 0;
	for (int k = 0; k < 9; k++) {
		//std::cout << "Kader #" << k << ": startX " << x << " stopX " << ptr[k].x << " startY " << y << " stopY " << ptr[k].y << "\n\n";
		if (k < 3)
			x = 0;
		else if (k < 6)
			x = x1;
		else
			x = x2;
		for (; x < ptr[k].x; x++) {
			if (k == 0 || k == 3 || k == 6)
				y = 0;
			else if (k == 1 || k == 4 || k == 7)
				y = y1;
			else
				y = y2;
			for (; y < ptr[k].y; y++) {
				//std::cout << "(" << x << ", " << y << ") = " << (int)(Img.at(x, y));
				//std::cin.get();
				if ((int)(Img.at(x, y)) < 127) {
					ptr[k].bp++;
				}
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		ptr[i].bp = ((float)ptr[i].bp / (float)ptr[i].s) * 100.0;
		//std::cout << "Kader #" << (i + 1) << ": " << ptr[i].bp << "\n";
	}
	//std::cout << "\n";

	int array[37];
	std::memset(array, 0, sizeof(array));
	int tmp;
	for (int i = 0; i < 37; i++) {
		for (int x = 0; x < 9; x++) {
			tmp = charset[i].meshes[x] - ptr[x].bp;
			if (tmp < 0)
				tmp *= -1;
			array[i] += tmp;
		}
	}

	int smallest = 9999;
	int index;
	for (int i = 0; i < 37; i++) {
		if (array[i] < smallest) {
			smallest = array[i];
			index = i;
		}
		//std::cout << "array[" << i << "]: " << array[i] << "\n";
	}

	char alph[] = {
		'A', 'B', 'C', 'D', 'E',
		'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O',
		'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y',
		'Z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8',
		'9', '-'
	};

	//std::cout << "Het is letter: " << alph[index];
	//std::cin.get();

	delete[] ptr;

	return alph[index];
}

