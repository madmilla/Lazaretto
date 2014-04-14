#pragma once
#include <functional>
#include "ImageLib.h"

namespace ImageLib {
	namespace Reduction {

		inline std::unique_ptr<ImageGray> reduce_to_gray(const ImageRGB & src,
			std::function<unsigned char(ImageRGB::const_pointer p)> f)
		{
			auto trg = std::make_unique<ImageGray>(src.width(), src.height());

			auto src_ptr = src.data();
			auto trg_ptr = trg->data();

			for (int i = 0; i < trg->size(); i++) {
				*trg_ptr = f(src_ptr);

				src_ptr.red++;
				src_ptr.green++;
				src_ptr.blue++;

				trg_ptr++;
			}

			return trg;
		}

	}
}