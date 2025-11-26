#include "dgpch.h"
#include "Components.h"
#include "Dogo/Renderer/2D/Sprite.h"
namespace Dogo
{
	namespace ECS
	{
		SpriteRendererComponent::SpriteRendererComponent() : DG_Component()
		{

		}

		void SpriteRendererComponent::Draw(std::weak_ptr<Dogo::Renderer2D> renderer, float actorX, float actorY)
		{
			if (!renderer.expired()) {
				if (sprite.GetTexture().has_value())
				{
					//renderer.lock()->Submit(glm::vec2(actorX, actorY), glm::vec2(sprite.GetWidth(), sprite.GetHeight()), sprite.GetTexture().value());
					renderer.lock()->Submit(CreateQuad(actorX, actorY, sprite.GetWidth(), sprite.GetHeight(), sprite.GetPivotX(), sprite.GetPivotY(), sprite.GetUV()), sprite.GetTexture().value());
				}
			}
			else
				DG_ERROR("Renderer pointer in Sprite: %s has expired.", sprite.GetName());
		}
		RigidBodyComponent::~RigidBodyComponent()
		{
			rigidBody = nullptr;
			shape = nullptr;
		}
		void RigidBodyComponent::Init(const glm::vec3& pos, const glm::vec3& shape, bool kinematic)
		{
			rigidBody = DG_Physics::GetRigidDynamic(PxTransform(PxVec3(pos.x, pos.y, pos.z)));
			this->shape = DG_Physics::GetShape(shape.x, shape.y, shape.z);
			rigidBody->attachShape(*this->shape);
			PxRigidBodyExt::updateMassAndInertia(*rigidBody, mass);
			this->kinematic = kinematic;
			rigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, kinematic);
			this->shape->setSimulationFilterData(filterData);
			rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
			DG_Physics::AddActor(rigidBody);
		}
		void RigidBodyComponent::ApplyKinematic()
		{
			rigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC,kinematic);
		}


		AudioSourceComponent::AudioSourceComponent(const std::string& filepath, float vol) : DogoECS::DG_Component(), wavpath(filepath), volume(vol)
		{
			std::ifstream f(wavpath);
			if (!f) {
				std::cerr << "Audio file not found: " << wavpath << std::endl;
			}
			alGenSources(1, &source);
			LoadCommon();
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
			return false;
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