#pragma once

/// <summary>
/// A class to handle time change when doing simulation
/// </summary>
class Timer {
	//private attributes
	unsigned int prevTicks;
	unsigned int currTicks;

public:
	/// <summary>
	/// Constructor. Assign attributes' values.
	/// </summary>
	Timer();

	/// Destructor.
	~Timer();

	/// <summary>
	/// Start the timer
	/// </summary>
	void Start();

	/// <summary>
	/// Update the tick
	/// </summary>
	void UpdateFrameTicks();

	/// <returns>The time different between the previous tick and
	/// the current tick</returns>
	float GetDeltaTime() const;

	/// <param name="fps">the current frame per second</param>
	/// <returns>the sleep time</returns>
	unsigned int GetSleepTime(const unsigned int fps) const;
};
