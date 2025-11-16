// Created by Bartłomiej Kierys

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimerSubsystem.generated.h"

UENUM(BlueprintType)
enum class ETimerMode : uint8
{
	Stopwatch UMETA(DisplayName = "Stopwatch"),
	Countdown UMETA(DisplayName = "Countdown")
};

DECLARE_LOG_CATEGORY_EXTERN(LogTimer, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerUpdatedSignature, float, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerStartedSignature, ETimerMode, Mode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimerFinishedSignature);
DECLARE_DYNAMIC_DELEGATE(FOnCountdownFinished);

/**
 * A subsystem class that provides timer functionality within a game instance.
 * Supports both Stopwatch (elapsed time) and Countdown (remaining time) modes.
 * Only a single timer is allowed to run simultaneously. No lap or pause functionality.
 */
UCLASS(Blueprintable)
class TIMERPLUGIN_API UTimerSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	/**
	 * Fires once any timer is started.
	 */
	UPROPERTY(BlueprintAssignable)
	FTimerStartedSignature OnTimerStarted;
	
	/**
	* Fires every tick with the "current" value:
	* - Stopwatch mode: elapsed time
	* - Countdown mode: remaining time
	*/
	UPROPERTY(BlueprintAssignable)
	FTimerUpdatedSignature OnTimerUpdated;

	/**
	 * Fires once when the countdown reaches zero.
	 */
	UPROPERTY(BlueprintAssignable)
	FTimerFinishedSignature OnTimerFinished;

#pragma region API
	/**
	 * Start timer. The timer will not start if it is already running. Use Stop and Reset before Starting again.
	 */
	UFUNCTION(BlueprintCallable)
	void StartTimer();

	/**
	 * Stops the timer but does not reset the time. Use `Reset` to clear elapsed time.
	 * 
	 * @return Time elapsed from the start when this method was called.
	 * In countdown mode this returns elapsed time since start (not remaining).
	 */
	UFUNCTION(BlueprintCallable)
	float StopTimer();

	/**
	* Start countdown mode for the given duration (in seconds).
	* When the countdown reaches zero, OnTimerFinished is broadcast.
	* The timer will not start if it is already running.
	*/
	// In UTimerSubsystem class public section, replace the existing StartCountdown declaration with:
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "OnFinished", AdvancedDisplay = "OnFinished"))
	void StartCountdown(float DurationSeconds, FOnCountdownFinished OnFinished);

	// Optionally keep a lightweight C++ wrapper (not exposed to Blueprints) for internal calls:
	void StartCountdown(float DurationSeconds)
	{
		StartCountdown(DurationSeconds, FOnCountdownFinished());
	}
	
	/**
	 * Stops the timer immediately and clears the elapsed time.
	 * Resets mode to Stopwatch by default.
	 */
	UFUNCTION(BlueprintCallable)
	void ResetTimer();

	/**
	 * @return Current Time Elapsed since the start of the timer.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentTime() const;

	/**
	 * @return Remaining time (seconds) for countdown mode. Returns 0 if not in countdown.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRemainingTime() const;
	
	/**
	 * @return Whether the timer is currently running.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsRunning() const;

	/**
	* @return Current mode (Stopwatch or Countdown).
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ETimerMode GetMode() const { return Mode; }

	/**
	* @return Countdown duration in seconds (0 if not in countdown).
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCountdownDuration() const { return CountdownDuration; }


#pragma endregion

#pragma region Tick
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
#pragma endregion

private:
	// State
	bool bRunning = false;
	bool bFinishedNotified = false;

	// Time bookkeeping
	double StartTime = 0.0;    // Start timestamp
	double CurrentTime = 0.0;  // Elapsed time at stop (for both modes)

	// Mode
	UPROPERTY()
	ETimerMode Mode = ETimerMode::Stopwatch;

	// Countdown configuration
	UPROPERTY()
	float CountdownDuration = 0.0f; // Duration set for countdown (seconds)

	// Helpers
	static double NowSeconds() { return FPlatformTime::Seconds(); }

	UPROPERTY()
	FOnCountdownFinished PendingCountdownFinished;
};
