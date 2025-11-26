#pragma once

namespace Dogo
{
	class Renderer2D;

	class SpriteRenderSystem2D
	{
	public:
		SpriteRenderSystem2D() = default;
		~SpriteRenderSystem2D() = default;

		void Update(const std::shared_ptr<Renderer2D>& renderer);
	};

	class PhysicsSystem
	{
	public:
		PhysicsSystem() = default;
		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem& operator=(const PhysicsSystem&) = delete;
		void Update(double step);
	private:
		double m_Accumulator = 0.0;
		const double m_FixedStep = 1.0 / 60.0;
	};

	class AudioSystem2D
	{
	public:
		AudioSystem2D() = default;
		AudioSystem2D(const AudioSystem2D&) = delete;
		AudioSystem2D& operator=(const AudioSystem2D&) = delete;
		void Update();
	};
	class AudioSystem3D
	{
	public:
		AudioSystem3D() = default;
		AudioSystem3D(const AudioSystem3D&) = delete;
		AudioSystem3D& operator=(const AudioSystem3D&) = delete;
		void Update();
	};
	class MovementSystem2D
	{
	public:
		MovementSystem2D() = default;
		MovementSystem2D(const MovementSystem2D&) = delete;
		MovementSystem2D& operator=(const MovementSystem2D&) = delete;
		void Update(double step);
	};
	class MovementSystem3D
	{
	public:
		MovementSystem3D() = default;
		MovementSystem3D(const MovementSystem3D&) = delete;
		MovementSystem3D& operator=(const MovementSystem3D&) = delete;
		void Update(double step);
	};
}