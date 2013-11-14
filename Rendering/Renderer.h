#pragma once

#include "Rendering.h"
#include "Singleton.h"
#include "Maths\Vector.h"

namespace Rendering
{
	class RENDERING_API Renderer
	{
	public: // constructors and destructors
		Renderer(int windowWidth, int windowHeight);
		~Renderer(void);

	protected:
		bool IsHardwareSupported();

	public:
		Renderer* GetRenderer();
		void SetSize(int windowWidth, int windowHeight);
		void LoadShaders();
		virtual void Init();
		virtual void ResizeWindow(int windowWidth, int windowHeight);
		void RenderTriangle(const Maths::Point3Df& A, const Maths::Point3Df& B, const Maths::Point3Df& C) const;
		void RenderGrid(const Maths::Point3Df& lower, const Maths::Point3Df& upper, float density, float level = 0.0f, float start = 0.0f, float end = 1.0f) const;
	protected:
		int m_windowWidth;
		int m_windowHeight;

		bool m_renderOrtographicEnabled;

		Maths::Vector2Df m_vecFullscreenTexCoords[6];
		Maths::Vector3Df m_vecFullscreenVertices[6];
		bool m_drawingBackgroundEnabled;

		bool m_MultisampleTexturesEnabled;
		int m_iScreenSamples;

		static Renderer* s_renderer;
	};
}

