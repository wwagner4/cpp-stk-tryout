// rtsine.cpp STK tutorial program

#include "SineWave.h"
#include "RtWvOut.h"
#include <cstdlib>
#include <cstdio>

using namespace stk;

int main() {

	double srate = 44100.0;
	double dur = 2; // seconds
	int nChannel = 2;

	Stk::setSampleRate(srate);
	Stk::showWarnings(true);

	int nFrames = dur * srate;
	SineWave sine;
	RtWvOut *dac = 0;

	dac = new RtWvOut(nChannel);
	sine.setFrequency(441.0);

	StkFrames frames = StkFrames(0.1, nFrames, nChannel);
	for (int c = 0; c < nChannel; c++ ) {
		frames = sine.tick(frames, c);
	}
	dac->tick(frames);
	delete dac;

	return 0;
}
