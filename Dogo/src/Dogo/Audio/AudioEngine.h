#pragma once
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/efx.h"

namespace Dogo 
{
	struct AudioData {
		ALenum format;
		ALsizei frequency;
		std::vector<char> data;
	};
	bool initOpenAL();
	bool loadWav(const char* filename, AudioData& out);
	void shutdownOpenAL();
	ALuint PlayAudioData(ALuint source, const Dogo::AudioData& audio);
}

