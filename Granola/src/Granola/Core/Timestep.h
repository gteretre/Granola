// Granola - Granola - Timestep.h
// Created: 2023.06.18-3:40 PM
// Modified: 2023.06.18-3:40 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
namespace Granola
{
	class Timestep
	{
	public:
		Timestep(const float time = 0.0f) : m_Time(time)
		{
		}

		operator float() const { return m_Time; }

		[[nodiscard]] float GetTime() const { return m_Time; }
		[[nodiscard]] float GetSeconds() const { return m_Time; }
		[[nodiscard]] float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}
