#pragma once

#include "Rendering.h"
#include "Singleton.h"
#include "Maths\Vector.h"

namespace Rendering
{
	class Renderer : public Singleton<Renderer>
	{
	public: // constructors and destructors
		RENDERING_API Renderer(int windowWidth, int windowHeight);
		RENDERING_API ~Renderer(void);

	protected:
		bool IsHardwareSupported();

	public:
		RENDERING_API void SetSize(int windowWidth, int windowHeight);
		RENDERING_API void LoadShaders();
		RENDERING_API virtual void Init();
		RENDERING_API virtual void ResizeWindow(int windowWidth, int windowHeight);
		//RENDERING_API void RenderGrid(const Maths::PointF& lower, const Maths::PointF& upper, float density, float level = 0.0f, float start = 0.0f, float end = 1.0f) const;
	protected:
		int m_windowWidth;
		int m_windowHeight;

		bool m_renderOrtographicEnabled;

		Maths::Vector2Df m_vecFullscreenTexCoords[6];
		Maths::Vector3Df m_vecFullscreenVertices[6];
		bool m_drawingBackgroundEnabled;

		bool m_MultisampleTexturesEnabled;
		int m_iScreenSamples;
	};
}

