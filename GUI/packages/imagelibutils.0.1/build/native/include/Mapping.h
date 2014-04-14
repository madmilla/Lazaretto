#pragma once
#include <functional>
#include "ImageLib.h"

namespace ImageLib {
	namespace Mapping {

		template<typename T>
		inline std::unique_ptr<T> map(const T & src,
			std::function<unsigned char(const unsigned char & p)> f)
		{
			auto trg = std::make_unique<T>(src.width(), src.height());

			auto src_iter = src.cbegin();
			auto trg_iter = trg->begin();

			for (int i = 0; i < src.size(); i++) {
				*trg_iter = f(*src_iter);

				src_iter++;
				trg_iter++;
			}

			return trg;
		}

		inline std::unique_ptr<ImageRGB> map_rgb(const ImageRGB & src,
			std::function<void(ImageRGB::const_pointer src_p, ImageRGB::pointer trg_p)> f)
		{
			auto trg = std::make_unique<ImageRGB>(src.width(), src.height());

			auto src_ptr = src.data();
			auto trg_ptr = trg->data();

			for (int i = 0; i < src.size(); i++) {
				f(src_ptr, trg_ptr);

				src_ptr.red++;
				src_ptr.green++;
				src_ptr.blue++;

				trg_ptr.red++;
				trg_ptr.green++;
				trg_ptr.blue++;
			}

			return trg;
		}
	}
}