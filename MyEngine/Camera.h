#pragma once

class Level;

class Camera
{
	friend Level;
public:
	Camera();
	~Camera();

	Camera(const Camera& _Other) = delete;
	Camera(Camera&& _Other) noexcept = delete;
	Camera& operator=(const Camera& _Other) = delete;
	Camera& operator=(Camera&& _Other) noexcept = delete;

protected:


private:
	D3D11_VIEWPORT ViewPort = {};

	void SetViewPortToPipeline() const;
};

