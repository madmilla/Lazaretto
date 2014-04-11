#pragma once
#include "ImageLib.h"

//
//! Team: OCR2
//! Author(s): Matthijs Veldhuizen
//! Version: 1.0

namespace OCR2 {

	struct CharacterMesh {
		std::array<int, 9> meshes;

		inline CharacterMesh(int m1, int m2, int m3, int m4, int m5, int m6, int m7, int m8, int m9) {
			meshes[0] = m1;
			meshes[1] = m2;
			meshes[2] = m3;
			meshes[3] = m4;
			meshes[4] = m5;
			meshes[5] = m6;
			meshes[6] = m7;
			meshes[7] = m8;
			meshes[8] = m9;
		}
	};

	class StaticOCR2 {
	public:
		StaticOCR2();
		~StaticOCR2();

		char Apply(const ImageLib::ImageGray & Img);
	};

}