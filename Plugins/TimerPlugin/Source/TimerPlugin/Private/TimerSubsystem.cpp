// Created by Bartłomiej Kierys


#include "TimerSubsystem.h"

DEFINE_LOG_CATEGORY(LogTimer)

void UTimerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTimer, Log, TEXT("Timer Subsystem initialized"));
}

void UTimerSubsystem::Deinitialize()
{
	OnTimerStarted.Clear();
	OnTimerUpdated.Clear();
	OnTimerFinished.Clear();
	
	if (PendingCountdownFinished.IsBound())
	{
		PendingCountdownFinished.Clear();
	}
	
	UE_LOG(LogTimer, Log, TEXT("Timer Subsystem deinitialized"));
	Super::Deinitialize();
}

void UTimerSubsystem::StartTimer()
{
	if (bRunning)
	{
		UE_LOG(LogTimer, Log, TEXT("Timer already running. Stop and Reset Timer first"));
		return;
	}
	
	Mode = ETimerMode::Stopwatch;
	bFinishedNotified = false;
	bRunning = true;
	StartTime = NowSeconds();

	OnTimerStarted.Broadcast(ETimerMode::Stopwatch);
	UE_LOG(LogTimer, Log, TEXT("Stopwatch started"));
}

float UTimerSubsystem::StopTimer()
{
	if (!bRunning)
	{
		return CurrentTime;
	}

	bRunning = false;
	CurrentTime = FPlatformTime::Seconds() - StartTime;
	PendingCountdownFinished = FOnCountdownFinished();

	UE_LOG(LogTimer, Log, TEXT("Timer ended. Time: %f"), CurrentTime);
	
	return CurrentTime;
}

void UTimerSubsystem::StartCountdown(float DurationSeconds, FOnCountdownFinished OnFinished)
{
	if (bRunning)
	{
		UE_LOG(LogTimer, Log, TEXT("Timer already running. Stop and Reset Timer first"));
		return;
	}
	
	Mode = ETimerMode::Countdown;
	CountdownDuration = FMath::Max(0.0f, DurationSeconds);
	StartTime = NowSeconds();
	CurrentTime = CountdownDuration;
	bRunning = true;
	bFinishedNotified = false;

	PendingCountdownFinished = OnFinished;

	OnTimerStarted.Broadcast(ETimerMode::Countdown);
	OnTimerUpdated.Broadcast(CurrentTime);
	UE_LOG(LogTimer, Log, TEXT("Countdown started for %f seconds"), CountdownDuration);

	if (CountdownDuration <= 0.0f)
	{
		bRunning = false;
		bFinishedNotified = true;

		OnTimerFinished.Broadcast();
		PendingCountdownFinished.ExecuteIfBound();
		PendingCountdownFinished = FOnCountdownFinished();
		UE_LOG(LogTimer, Log, TEXT("Countdown finished immediately (zero duration)"));
	}
}

void UTimerSubsystem::ResetTimer()
{
	bRunning = false;
	bFinishedNotified = false;
	CurrentTime = 0.0;
	StartTime = 0.0;
	Mode = ETimerMode::Stopwatch;
	CountdownDuration = 0.0f;
}

float UTimerSubsystem::GetCurrentTime() const
{
	if (bRunning)
	{
		return static_cast<float>(NowSeconds() - StartTime);
	}
	return static_cast<float>(CurrentTime);
}

float UTimerSubsystem::GetRemainingTime() const
{
	if (Mode != ETimerMode::Countdown)
	{
		return 0.0f;
	}

	const double Elapsed = bRunning ? (NowSeconds() - StartTime) : CurrentTime;
	const float Remaining = FMath::Max(CountdownDuration - static_cast<float>(Elapsed), 0.0f);
	return Remaining;
}

bool UTimerSubsystem::IsRunning() const
{
	return bRunning;
}

void UTimerSubsystem::Tick(float DeltaTime)
{
	if (!bRunning)
	{
		return;
	}

	const float Elapsed = static_cast<float>(NowSeconds() - StartTime);

	if (Mode == ETimerMode::Stopwatch)
	{
		CurrentTime = Elapsed;
		OnTimerUpdated.Broadcast(Elapsed);
	}
	else if (Mode == ETimerMode::Countdown)
	{
		CurrentTime = Elapsed;
		const float Remaining = FMath::Max(CountdownDuration - Elapsed, 0.0f);

		OnTimerUpdated.Broadcast(Remaining);

		if (Remaining <= 0.0f)
		{
			CurrentTime = CountdownDuration;
			bRunning = false;

			if (!bFinishedNotified)
			{
				bFinishedNotified = true;
				OnTimerFinished.Broadcast();

				PendingCountdownFinished.ExecuteIfBound();
				PendingCountdownFinished = FOnCountdownFinished();
			}

			UE_LOG(LogTimer, Log, TEXT("Countdown finished"));
		}
	}
}

TStatId UTimerSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UTimerSubsystem, STATGROUP_Tickables);
}
