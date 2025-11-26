#include "dgpch.h"
#include "AudioEngine.h"
#include "Dogo/Utils/Logger.h"
namespace Dogo
{
    static ALuint effect = 0;
    static ALuint slot = 0;
    static ALCdevice* device;
    static ALCcontext* context;
	bool initOpenAL()
	{
        device = alcOpenDevice(nullptr);
        if (!device) return false;

        const ALCint attribs[] = {
            ALC_MAX_AUXILIARY_SENDS, 4,
            0
        };

        context = alcCreateContext(device, attribs);
        if (!context) return false;

        if (!alcMakeContextCurrent(context)) return false;

        ALfloat listenerPos[] = { 0.0f, 0.0f, 0.0f };
        ALfloat listenerVel[] = { 0.0f, 0.0f, 0.0f };
        ALfloat listenerOri[] = { 0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f };

        alListenerfv(AL_POSITION, listenerPos);
        alListenerfv(AL_VELOCITY, listenerVel);
        alListenerfv(AL_ORIENTATION, listenerOri);

        return true;
	}
	void shutdownOpenAL()
	{
        alcMakeContextCurrent(nullptr);
        if (context) alcDestroyContext(context);
        if (device) alcCloseDevice(device);
	}

    bool loadWav(const char* filename, AudioData& out)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            DG_ERROR("Failed to open WAV file: %s", filename);
            return false;
        }

        char riff[4];
        uint32_t chunkSize;
        char wave[4];

        file.read(riff, 4);
        file.read(reinterpret_cast<char*>(&chunkSize), 4);
        file.read(wave, 4);

        if (strncmp(riff, "RIFF", 4) != 0 || strncmp(wave, "WAVE", 4) != 0) {
            DG_ERROR("Not a valid WAV file: %s", filename);
            return false;
        }

        char chunkId[4];
        uint32_t chunkDataSize;

        uint16_t audioFormat = 0;
        uint16_t numChannels = 0;
        uint32_t sampleRate = 0;
        uint16_t bitsPerSample = 0;

        bool fmtRead = false;
        bool dataRead = false;

        while (file.read(chunkId, 4)) {
            file.read(reinterpret_cast<char*>(&chunkDataSize), 4);

            if (strncmp(chunkId, "fmt ", 4) == 0) {
                if (chunkDataSize < 16) {
                    DG_ERROR("Invalid fmt chunk size in WAV: %s", filename);
                    return false;
                }

                file.read(reinterpret_cast<char*>(&audioFormat), 2);
                file.read(reinterpret_cast<char*>(&numChannels), 2);
                file.read(reinterpret_cast<char*>(&sampleRate), 4);
                file.seekg(6, std::ios::cur);
                file.read(reinterpret_cast<char*>(&bitsPerSample), 2);

                if (chunkDataSize > 16)
                    file.seekg(chunkDataSize - 16, std::ios::cur);

                fmtRead = true;
            }
            else if (strncmp(chunkId, "data", 4) == 0) {
                if (!fmtRead) {
                    DG_ERROR("Data chunk before fmt chunk in WAV: %s", filename);
                    return false;
                }

                out.data.resize(chunkDataSize);
                file.read(out.data.data(), chunkDataSize);

                out.frequency = sampleRate;

                if (bitsPerSample == 8) {
                    out.format = (numChannels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
                }
                else if (bitsPerSample == 16) {
                    out.format = (numChannels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
                }
                else {
                    DG_ERROR("Unsupported bits per sample: %d", bitsPerSample);
                    return false;
                }

                dataRead = true;
                break;
            }
            else {
                // Skip unknown chunk
                file.seekg(chunkDataSize, std::ios::cur);
            }
        }

        if (!fmtRead || !dataRead) {
            DG_ERROR("Failed to read fmt or data chunk in WAV: %s", filename);
            return false;
        }

        return true;
    }


    ALuint PlayAudioData(ALuint source, const Dogo::AudioData& audio)
    {
        ALuint buffer;
        alGenBuffers(1, &buffer);

        alBufferData(buffer,
            audio.format,
            audio.data.data(),
            static_cast<ALsizei>(audio.data.size()),
            audio.frequency);

        alSourcei(source, AL_BUFFER, buffer);

        return buffer;
    }

}