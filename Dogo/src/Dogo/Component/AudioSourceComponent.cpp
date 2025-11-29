#include "dgpch.h"
#include "AudioSourceComponent.h"

namespace Dogo
{
	namespace ECS
	{
		bool AudioSourceComponent::LoadCommon()
		{
			if (!wavpath.empty() && Dogo::loadWav(wavpath.c_str(), audioData)) {
				if (buffer != 0)
					alDeleteBuffers(1, &buffer);

				buffer = Dogo::PlayAudioData(source, audioData);

				alSourcef(source, AL_GAIN, volume);
				alSourcei(source, AL_LOOPING, AL_FALSE);
				return true;
			}
			else
				DG_ERROR("Audio component could load file: %s\n", wavpath);
			return false;
		}

		AudioSourceComponent::AudioSourceComponent(const std::string& filepath, float vol) : DogoECS::DG_Component(), wavpath(filepath), volume(vol)
		{
			std::ifstream f(wavpath);
			if (!f) {
				DG_ERROR("Audio file not found: %s\n", wavpath);
			}
			alGenSources(1, &source);
		}
		AudioSourceComponent::AudioSourceComponent() : DogoECS::DG_Component()
		{
		}
		AudioSourceComponent::~AudioSourceComponent()
		{
			if (buffer != 0)
				alDeleteBuffers(1, &buffer);
			if (source != 0)
				alDeleteSources(1, &source);
		}

		void AudioSourceComponent::Play()
		{
			ALint state;
			alGetSourcei(source, AL_SOURCE_STATE, &state);
			if (state != AL_PLAYING) {
				alSourcePlay(source);
			}
		}

		AudioSourceComponent2D::AudioSourceComponent2D(const std::string& filepath, float vol) : AudioSourceComponent(filepath, vol)
		{
		}


		bool AudioSourceComponent2D::Load()
		{
			if (!LoadCommon())
				return false;
			alSourcei(source, AL_SOURCE_RELATIVE, AL_FALSE);
			alSourcef(source, AL_ROLLOFF_FACTOR, 0.0f);

			return true;
		}
		bool AudioSourceComponent3D::Load()
		{
			if (!LoadCommon())
				return false;
			alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
			alSourcef(source, AL_ROLLOFF_FACTOR, 1.0f);

			return true;
		}
		AudioSourceComponent3D::AudioSourceComponent3D(const std::string& filepath, float vol) : AudioSourceComponent(filepath, vol)
		{
		}
	}
}