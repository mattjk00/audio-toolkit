#pragma once
#include "circbuffer.h"

namespace vino {
	template <class T>
	void fft(CircBuffer<T> input, T* output);
}