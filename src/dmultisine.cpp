// rtsine.cpp STK tutorial program

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>

using namespace stk;

int main() {
	// Set the global sample rate before creating class instances.
	Stk::setSampleRate(44100.0);
	Stk::showWarnings(true);

	RtWvOut *dac = 0;

	try {
		// Define and open the default realtime output device for one-channel playback
		dac = new RtWvOut();
	} catch (StkError &) {
		exit(1);
	}

	int nFrames = 500000;
	const int nSines = 10;
	SineWave sines[nSines];
	double baseFreq = 400.0;

	double freq = baseFreq;
	double diffs[] = {0.3, 0.3, 0.3, 0.3, 34, 0.2, 0.2, 120, 0.1, 0.1, 0.1};
	double gains[] = {0.03, 0.02, 0.01, 0.005, 0.003, 0.003, 0.003, 0.002, 0.002, 0.001, 0.001};
	for (int i = 0; i < nSines; i++) {
		sines[i].setFrequency(freq);
		freq += diffs[i];
	}

	// Single-sample computations
	for (int i = 0; i < nFrames; i++) {
		try {
			double tickValue = 0.0;
			for (int i = 0; i < nSines; i++) {
				tickValue += sines[i].tick() * gains[i];
			}
			dac->tick(tickValue);
		} catch (StkError &) {
			goto cleanup;
		}
	}

	cleanup: delete dac;

	return 0;
}
