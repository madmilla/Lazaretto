#include "OCR2_TicTacToeOCR.h"
#include <bitset>
#include <fstream>

using namespace OCR2;

TicTacToeOCR::TicTacToeOCR():
	left(0),
	right(0),
	up(0),
	down(0)
{}

TicTacToeOCR::TicTacToeOCR(int l, int r, int u, int d) :
	left(l),
	right(r),
	up(u),
	down(d)
{}

TicTacToeOCR::~TicTacToeOCR() { }

char TicTacToeOCR::Apply(const ImageLib::ImageGray & source, bool recheck){
	
	
	//width of picture 
	int breedte = source.width();
	//height of picture
	int hoogte = source.height();
	//width of char
	int charBreedte = breedte - left - right;
	//height of char
	int charHoogte = hoogte - up - down;
	//result of the check
	short value = check(source);
	if (charBreedte >= charHoogte){
		
		return '-';
	}
	
	
	//This for loop checks I there is written a character or a stripe by looking for black pixels under the place where the stripe should be
	bool stripe = true;
	for (int x = 0; x <= charBreedte; x++){
		if (*source.data(x + left, charHoogte - charHoogte / 8 + up) <= 122){
			stripe = false;
			break;
		}
	}
	if (value == value / 8 * 8 && recheck == false){
		int old = down;
		setDown(down + (charHoogte / 8));
		char c = Apply(source, true);
		setDown(old);
		char co = Apply(source, true);
		if (c != '/' || c==co){
			return c;
		}

		
	}
	if (stripe == true){
		return '-';
	}
	//this switch statement contains all the return statements of this function
	switch (value){
	case 170:
		
		if (*source.data((charBreedte / 4) + left, (charHoogte / 4) + up ) <= 122 && (*source.data((charBreedte-(charBreedte / 4)) +left, (charHoogte / 4) + up) <= 122)){
			return '0';

		}
		else if (*source.data((charBreedte - (charBreedte / 4)) - 2 + left, (charHoogte / 3) + up - 3) >= 122){
			return 'G';
		}
		else{
			return 'O';
		}
	

	case 234:
		return 'G';
		
	
	case  186:
		if (*source.data((charBreedte / 4) - 2 + left, charHoogte - (charHoogte / 6 * 2) + up - 2) <= 122 && *source.data(charBreedte-(charBreedte / 4) - 2 + left, (charHoogte / 6 * 2) + up - 2) <= 122){
			return '8';
		}

		if (*source.data((charBreedte / 4) - 2 + left, charHoogte-(charHoogte / 6 * 2) + up - 2) <= 122){
			return '6';		
		}
		
		return '9';
		
		
	
	case 227:
		if (*source.data(charBreedte - (charBreedte / 8) + left, charHoogte-(charHoogte / 4) + up) <= 122){
			return 'G';
		}
		else{
			return 'C';
		}
	
	
	case 162:
		return'C';
	

	case 381:
		if (*source.data(charBreedte - (charBreedte / 3) + left, charHoogte - (charHoogte / 4) + up) <= 122){
			return 'N';
		}
		else if (* source.data(charBreedte - (charBreedte / 3) + left, (charHoogte / 4) + up) <= 122 && *source.data(charBreedte - (charBreedte / 4) + left, (charHoogte / 2) + up) >= 122){
			return 'M';
		}
		else{
			return 'H';
		}
	
	case 133:
		return 'A';
	
	
	case 438:
		return 'B';
	
	

	case 430:
		return 'D';
	

	case 503:
		return 'E';
	
	case 508:
	case 500:
		return 'F';
	case 235:
		return'G';

	case 507:
	case 511:
		return 'I';
	

	case 78:
		return 'J';
	
	case 309:
	case 293:
		return 'K';
	

	case 295:
		return 'L';
	

	case 444:
		return 'P';
	
	case 436:
		return 'P';
	

	case 171:
		return 'Q';
	
	case 445:
	case 437 :
		return 'R';
	

	case 210:
	case 214:
	case 218:
	case 410:
	case 474:
		return 'S';
	

	case 466:
		if (*source.data(charBreedte / 2 + left, charHoogte / 4 + up) <= 122){
			return 'T';
		}
		return 'S';

	case 362:
		return 'U';
	

	case 322:
		return 'V';
	

	case 472:
		return 'W';
	

	case 341:
		return 'X';
	
	
	case 338:
		return 'Y';
	
	

	case 471:
		return 'Z';
	

	case 475:
	case 473:
	case 467:
		return '1';
	

	case 407:
		return '2';
	
	case 414:
	case 406:
		return '3';
	
	case 146:
		if (*source.data((charBreedte / 8) + left, (charHoogte / 4) + up) >= 122){
			return '3';
		}
		return '8';
	case 32:
	case 56:
	case 160:
	case 168:
	case 184:
		return '4';
	

	case 446:
		if (*source.data(charBreedte - (charBreedte / 8) + left, (charHoogte / 4) + up) <= 122){
			return 'B';
		}
		return '5';
	

	case 464:
		if (*source.data((charBreedte / 4) + left, (charHoogte / 8) + up) <= 122){
			return '7';
		}
		return 'W';
	

	case 147:
		return '8';
	case 442:
		if (*source.data(charBreedte / 8 + left, charHoogte-(charHoogte / 4) + up) <= 122){
			return '8';
		}
		return '9';
	case 402:
		return '9';
	default:
		return '/';
	}
	
}

void TicTacToeOCR::Learn(const ImageLib::ImageGray & source, char c) {
	short value = check(source);
	std::bitset<9> y(value);

	std::ofstream out;

	out.open("Value.txt", std::ios::app);

	out << c
		<< "= "
		<< y
		<< " "
		<< value
		<< "\n";
}

inline short TicTacToeOCR::check(const ImageLib::ImageGray & source){
	int breedte = source.width();
	int hoogte = source.height();
	int charBreedte = breedte - left - right;
	int charHoogte = hoogte - up - down;
	short value = 0;
	//left up
	//std::cout << *source.data((charBreedte / 8) + left, charHoogte / 12 + up);
	if (*source.data((charBreedte / 8) + left, charHoogte / 12 + up) <= 122){
		value += 1;
	}
	value = value * 2;
	//middle up
	if (*source.data(charBreedte / 2 + left, charHoogte / 12 + up) <= 122){
		value += 1;
	}
	value = value * 2;
	//right up
	if (*source.data((charBreedte - (charBreedte / 8)) + left, charHoogte / 12 + up) <= 122){
		value += 1;
	}
	value = value * 2;

	//left middle
	if (*source.data((charBreedte / 4) / 2 + left, (charHoogte / 2 + up)) <= 122){
		value += 1;
	}
	value = value * 2;
	//middle middle
	bool calc = false;
	for (int y = charHoogte / 2 - 1 + up; y >= (charHoogte * 43 / 100) + up; y--){

		if ((*source.data(charBreedte / 2 + left, y) <= 122) && (*source.data(charBreedte / 2 + left, y + 1) <= 122)){
			calc = true;
			//std::cout << "boven is waar";
			break;
		}
	}

	for (int y = charHoogte / 2 + 1 + up; y <= (charHoogte * 57 / 100) + up && calc != true; y++){
		if ((*source.data(charBreedte / 2 + left, y) <= 122) && (*source.data(charBreedte / 2 + left, y - 1) <= 122)){
			calc = true;
			//std::cout << "onder is waar";
			break;
		}
	}

	if (calc == true) {
		value += 1;
		calc = false;
	}

	value = value * 2;

	//right middle
	for (int y = charHoogte / 2 - 1 + up; y >= (charHoogte * 43 / 100) + up; y--){

		if ((*source.data((charBreedte - (charBreedte / 8)) + left, y) <= 122) && (*source.data((charBreedte - (charBreedte / 8)) + left, y + 1) <= 122)){
			calc = true;
			//std::cout << "boven is waar";
			break;
		}
	}

	for (int y = charHoogte / 2 + 1 + up; y <= (charHoogte * 57 / 100) + up && calc != true; y++){
		if ((*source.data((charBreedte - (charBreedte / 8)) + left, y) <= 122) && (*source.data((charBreedte - (charBreedte / 8)) + left, y - 1) <= 122)){
			calc = true;
			//std::cout << "onder is waar";
			break;
		}
	}
	if (calc == true) {
		value += 1;
		calc = false;
	}


	value = value * 2;


	//left down
	if (*source.data((charBreedte / 8) + left, (charHoogte - charHoogte / 12) + up) <= 122
		|| *source.data((charBreedte / 8) - 1 + left, (charHoogte - charHoogte / 12) + up) <= 122
		&& *source.data((charBreedte / 8) - 2 + left, (charHoogte - charHoogte / 12) + up) <= 122){
		value += 1;
	}
	value = value * 2;
	//middle down
	if (*source.data(charBreedte / 2 + left, (charHoogte - charHoogte / 12) + up) <= 122
		|| *source.data(charBreedte / 2 - 1 + left, (charHoogte - charHoogte / 12) + up) <= 122
		&& * source.data(charBreedte / 2 - 2 + left, (charHoogte - charHoogte / 12) + up) <= 122){
		value += 1;
	}
	value = value * 2;
	//right down
	if (*source.data(charBreedte - (charBreedte / 8) + left, (charHoogte - charHoogte / 12) + up) <= 122
		|| *source.data(charBreedte - (charBreedte / 8) - 2 + left, (charHoogte - charHoogte / 12) + up) <= 122
		&& *source.data(charBreedte - (charBreedte / 8) - 1 + left, (charHoogte - charHoogte / 12) + up) <= 122){
		value += 1;
	}

	return value;
}