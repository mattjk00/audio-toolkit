#pragma once
using std::vector;

namespace vino {

	// A simple implementation of a circular buffer.
	template <class T>
	class CircBuffer {
	public:
		CircBuffer(size_t size);
		~CircBuffer();
		// Reads a sample at the given index.
		T read(int index);
		// Writes a sample to the end of the buffer. Returns the index written to.
		int write(T x);
	private:
		size_t size;
		vector<T> buffer;
		int rptr;
		int wptr;
		// Set to true after the buffer has been filled once. The read pointer will then start moving.
		bool wrapped_once;
	};

	template <class T>
	CircBuffer<T>::CircBuffer(size_t size)
		: rptr(0), wptr(0), wrapped_once(false)
	{
		this->size = size;
		buffer = vector<T>(size, 0);
	}

	template <class T>
	CircBuffer<T>::~CircBuffer() { }

	template <class T>
	T CircBuffer<T>::read(int index) {
		int i = index + rptr;
		if (i >= size) {
			i = i - size;
		}
		else if (i < 0) {
			i = size + i;
		}
		return buffer[i];
	}

	template <class T>
	int CircBuffer<T>::write(T x) {
		buffer[wptr] = x;
		wptr++;
		if (wptr == size) {
			wptr = 0;
			if (!wrapped_once) {
				wrapped_once = true;
				rptr = 0;
			}
		}

		if (wrapped_once) {
			rptr++;
			if (rptr == size) {
				rptr = 0;
			}
		}

		return wptr;
	}
}