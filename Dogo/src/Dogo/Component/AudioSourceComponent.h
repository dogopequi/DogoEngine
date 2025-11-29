#pragma once
#include "Components.h"
namespace Dogo
{
	namespace ECS
	{
        struct AudioSourceComponent : public DogoECS::DG_Component
        {
            ALuint source = 0;
            ALuint buffer = 0;
            AudioData audioData;
            std::string wavpath;
            float volume = 0.0f;
            std::string GetFilePath() const { return wavpath; }
            void SetFilePath(const std::string& filepath) { wavpath = filepath; LoadCommon(); }
            float GetVolume() const { return volume; }
            void SetVolume(float vol) { volume = vol; }
            void Play();
            ~AudioSourceComponent();
        protected:
            bool LoadCommon();
            AudioSourceComponent(const std::string& filepath, float vol);
            AudioSourceComponent();
        };

        struct AudioSourceComponent2D : public AudioSourceComponent
        {
            bool Load();
            AudioSourceComponent2D(const std::string& filepath, float vol);
            AudioSourceComponent2D() {}
            ~AudioSourceComponent2D() {}
        };
        struct AudioSourceComponent3D : public AudioSourceComponent
        {
            bool Load();
            AudioSourceComponent3D(const std::string& filepath, float vol);
            AudioSourceComponent3D() {}
            ~AudioSourceComponent3D() {}
        };

	}
}