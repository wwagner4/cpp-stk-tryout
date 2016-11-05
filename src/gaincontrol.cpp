// doctus example for gain control

#include "SineWave.h"
#include "RtWvOut.h"
#include "Envelope.h"
#include <cstdlib>
#include <cstdio>

using namespace stk;

int main() {
	double srate = 44100.0;

	Stk::setSampleRate(srate);
	Stk::showWarnings(true);

	double dur = 2; // seconds
	int nFrames = dur * srate;

	StkFrames frames = StkFrames(0.1, nFrames, 1);

	SineWave sine;
	sine.setFrequency(777.0);

	Envelope env = Envelope();
	env.setTime(dur / 2);

	env.keyOn();
	RtWvOut* dac = new RtWvOut(2);

	for (int t=0; t< nFrames; t++) {

		double time = t / srate;
		if (time >= dur / 2) {
			env.keyOff();
		}
		double sample = 0.0;
		sample += sine.tick();
		sample *= env.tick();
		sample *= 0.3;

		dac -> tick(sample);
	}

	delete dac;

	return 0;
}
