// Granola - Granola - WindowsInput.h
// Created: 2023.05.29-11:10 AM
// Modified: 2023.05.29-11:10 AM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Input.h"

namespace Granola
{
	class WindowsInput : public Input
	{
	public:
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
