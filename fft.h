#pragma once
#include "circbuffer.h"
#include <vector>
#include <numbers>
#include <complex>
using std::vector;
using std::complex;
#define V_PI 3.14159265358979311600

namespace vino {

	template <class T>
	vector<complex<double>> ditfft2(CircBuffer<T> input, int N, int startIndex, int stride = 1) {
		vector<complex<double>> X(N);

		if (N == 1) {
			X[0] = input.read(0);
		}
		else {
			vector<complex<double>> X_half =	ditfft2(input, N / 2, 0, 2 * stride);
			vector<complex<double>> X_half2 = ditfft2(input, N / 2, stride, 2 * stride);
			for (int k = 0; k < N / 2; k++) {
				auto p = X[k];
				auto q = std::exp(complex(-2*V_PI)) * X[k + N / 2];
				X[k] = p + q;
				X[k + N / 2] = p - q;
			}
		}

		return X;
	}

	template <class T>
	void fft(CircBuffer<T> input, T* output, int stride = 1) {
		const int N = input.getSize();

		auto res = ditfft2<T>(input, N, 0, 1);
	}
}