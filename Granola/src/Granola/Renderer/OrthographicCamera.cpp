﻿#include "grlpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Granola
{
	OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
		  m_ViewMatrix(1.0f),
		  m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
	{
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		const glm::mat4 transform = translate(glm::mat4(1.0f), m_Position) *
			rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
