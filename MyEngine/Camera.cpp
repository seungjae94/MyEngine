#include "PreCompile.h"
#include "Camera.h"
#include "EngineCore.h"
#include "EngineDirectDevice.h"

Camera::Camera()
{
	// 뷰포트 초기화
	ViewPort.Width = 1280;
	ViewPort.Height = 720;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.MinDepth = 0;
	ViewPort.MaxDepth = 1;
}

Camera::~Camera()
{
}

void Camera::SetViewPortToPipeline() const
{
	EngineCore::DirectDevice.Context->RSSetViewports(1, &ViewPort);
}
