#include "SineWave.h"
#include "Adsr.h"
#include "RtAudio.h"
#include <cstdio>
using namespace stk;

class Piece {

	SineWave sine;
	ADSR adsr;

public:
	StkFloat tick(void);
	Piece(void);
	void keyOn(void);
	void keyOff(void);
};

Piece::Piece() {
	sine.setFrequency(555.0);
	adsr.setAttackTime(0.01);
	adsr.setDecayTime(0.5);
	adsr.setSustainLevel(0.3);
	adsr.setReleaseTime(1.0);
}

void Piece::keyOn() {
	adsr.keyOn();
}

void Piece::keyOff() {
	adsr.keyOff();
}

StkFloat Piece::tick() {
	return sine.tick() * adsr.tick();
}

class Ctx {

	RtAudio dac;
	Piece piece;

private:
	void setupRtAudioStream(RtAudio* dac, Piece* piece);

public:
	Ctx(void);
	void run(void);
	static int tick(void *outputBuffer, void *inputBuffer,
			unsigned int nBufferFrames, double streamTime,
			RtAudioStreamStatus status, void *dataPointer) {
		Piece *piece = (Piece *) dataPointer;
		register StkFloat *samples = (StkFloat *) outputBuffer;
		for (unsigned int i = 0; i < nBufferFrames; i++) {
			*samples++ = piece->tick();
		}
		return 0;
	}
	virtual ~Ctx(void);

};

Ctx::Ctx() {
	printf("Ctx constructed\n");
}
Ctx::~Ctx(void) {
	if (dac.isStreamOpen()) {
		dac.closeStream();
	}
	printf("Ctx deconstructed\n");
}

void Ctx::run() {
	printf("[run] START\n");
	try {
		Stk::setSampleRate(44100.0);
		setupRtAudioStream(&dac, &piece);
		dac.startStream();
		piece.keyOn();
		Stk::sleep(1500);
		piece.keyOff();
		Stk::sleep(2500);
		dac.closeStream();
	} catch (RtAudioError &error) {
		error.printMessage();
	}
	printf("[run] END\n");
}

void Ctx::setupRtAudioStream(RtAudio* dac, Piece* piece) {

	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac->getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format =
			(sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	dac->openStream(&parameters, NULL, format, (unsigned int) Stk::sampleRate(),
			&bufferFrames, &tick, (void *) piece);

}

int main() {
	Ctx ctx;
	ctx.run();
	return 0;
}
