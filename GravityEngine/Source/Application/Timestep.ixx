export module Timestep;
import stdlib;

export class Timestep
{
private:
	float DeltaTime;
	std::chrono::steady_clock::time_point LastTime;

public:
	Timestep(float time = 0.f)
		: DeltaTime(time), LastTime(std::chrono::steady_clock::now()) {}

	operator float() const { return DeltaTime; }

	void operator++(int)
	{
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		DeltaTime = std::chrono::duration<float>(now - LastTime).count();
		LastTime = now;
	}

	float GetSeconds() const { return DeltaTime; }
	float GetMilliseconds() const { return DeltaTime * 1000.f; }
	float GetMicroseconds() const { return DeltaTime * 1000000.f; }
};