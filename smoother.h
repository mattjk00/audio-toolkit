#pragma once
#include <cmath>

namespace vino {
	class Smoother {
	public:
		Smoother(int sr); // sample rate
		void tick();
		float smooth_lerp(float a, float b);
		float lerp(float a, float b, float f) { return a * (1.0 - f) + (b * f); }
	private:
		int sample_timer;
		int sample_rate;
	};

	Smoother::Smoother(int sr) : sample_timer(0), sample_rate(sr) {
		// nothing here rn.
	}

	void Smoother::tick() {
		sample_timer += 1;
		if (sample_timer >= sample_rate) {
			sample_timer = 0;
		}
	}

	float Smoother::smooth_lerp(float a, float b) {
		float f = std::sinf((float)sample_timer / (float)sample_rate);
		return lerp(a, b, f);
	}
}

