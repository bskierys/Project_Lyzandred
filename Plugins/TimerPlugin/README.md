# Timer Plugin — README

The plugin exposes a game-wide Timer Subsystem with:
- Stopwatch mode (counts up)
- Countdown mode (counts down from a given duration)
- Tick-driven updates via a multicast delegate
- A base UMG widget you can subclass for quick UI

## 1) Installation and setup
- Copy the content of this directory to `{YourProject}/Plugins/TimerPlugin`.
- In the Unreal Editor: Edit → Plugins → enable the Timer Plugin and restart the editor.
- For C++ projects, add the plugin’s runtime module to your module dependencies (in your .Build.cs). Example placeholders:
    - PublicDependencyModuleNames.AddRange(new string[] { " " }); 

## 2) Accessing the Timer Subsystem
- Blueprint:
    1. From any Blueprint with access to a World (e.g., Player Controller, HUD, Widget), call "Get Timer Subsystem"
    2. Store the returned reference for subsequent calls.

- C++:

``` c++
// Get the Timer Subsystem from any UObject with access to UWorld (e.g., AActor, UUserWidget)
#include "TimerSubsystem.h"

UTimerSubsystem* GetTimerSubsystem(UObject* WorldContextObject)
{
    UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
    if (!World) return nullptr;
    UGameInstance* GI = World->GetGameInstance();
    return GI ? GI->GetSubsystem<UTimerSubsystem>() : nullptr;
}
```

## 3) Stopwatch: start, stop, reset, query

- Start stopwatch:
    - Use node: Start Timer

- Stop stopwatch:
    - Use node: Stop Timer (returns the elapsed time as a float)

- Reset to initial state:
    - Use node: Reset Timer

- Query:
    - Get Current Time (elapsed seconds)
    - Is Running (bool)
    - On Timer Updated (multicast event that fires every tick with time)

Typical flow:
1. Get Timer Subsystem
2. Call Start Timer
3. Bind to On Timer Updated to refresh UI
4. Call Stop Timer when needed; use returned float to get elapsed time

## 4) Countdown: start, stop, remaining time, completion
You can use the countdown in two ways:
- Inline completion delegate parameter (passed at StartCountdown call)
- Multicast delegates (bind once and react when any countdown completes)

### 4.1 Countdown via inline completion delegate
#### Blueprint
- Use node: Start Countdown
    - Duration Seconds: the countdown duration
    - On Finished (optional pin): connect an event to be called when the countdown ends

- Optionally bind to On Timer Updated to receive remaining time each tick
- Get Remaining Time to poll current remaining seconds
- Notes:
    - If Duration Seconds is 0, it finishes immediately and On Finished executes

Typical Blueprint flow:
1. Get Timer Subsystem
2. Start Countdown (set “Duration Seconds”)
3. Optionally connect “On Finished” pin for a one-off callback
4. Bind to On Timer Updated to update UI

#### C++
``` c++
// Start a countdown with an inline completion delegate
void AMyActor::StartCountdownWithInlineCallback(float Duration)
{
    if (UTimerSubsystem* Timer = GetTimerSubsystem(this))
    {
        // Prepare the inline callback
        FOnCountdownFinished OnFinished;
        OnFinished.BindUObject(this, &AMyActor::HandleCountdownFinishedInline);

        // Start countdown (counts down from Duration to 0)
        Timer->StartCountdown(Duration, OnFinished);
    }
}

void AMyActor::HandleCountdownFinishedInline()
{
    // Called exactly once when this countdown reaches zero
}
```

### 4.2 Countdown via multicast delegates
#### Blueprint

Useful if you want to:
- Subscribe to end of timer in different actor on the scene.
- Subscribe with multiple actors to the same timer callback.

Process:
- Bind to: On Timer Finished: fires when the countdown reaches 0
- Start the countdown with Start Countdown (you can leave the On Finished pin unconnected if you only want multicast)

#### C++
``` c++
// Bind once to multicast delegates and then start countdown
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    if (UTimerSubsystem* Timer = GetTimerSubsystem(this))
    {
        Timer->StartCountdown(Duration);
        Timer->OnTimerFinished.AddUObject(this, &AMyActor::HandleCountdownFinishedMulticast);
    }
}

void AMyActor::HandleCountdownFinishedMulticast()
{
    // React to countdown completion
}
```

## 5) Displaying your own timer widget

### Default Widget

The Plugin comes with dwfault widget (`WBP_TimerDefault`) that you can use for
displaying the timer.
Simply add it to your Viewport when your game starts or just for the time you
need it. Directory `ExampleSetup` has screenshot of example Blueprints utilizing
the Widget.

### Custom Widget

TimerWidgetBase is a base UMG class intended to simplify building timer UI. The
typical workflow is:
- Subclass TimerWidgetBase for your project-specific look and behavior
- In that subclass, Override `UpdateDisplay` Event. This metod provides you with
Elapsed time in Stopwatch mode and Remaining time in Countdown mode.
- Add the widget to the viewport

The Plugin comes with BFL to simplify time formatting for timer.

``` c++
    FTimerFormat Format;
    Format.FormatTemplate = "{h}:{m}:{s}";
    const FString DisplayTime = UTimerFormatLibrary::FormatTime(Time, Format);
```

See the included in Plugin `WBP_TimerDefault` for the example.

## 6) Limitations and notes
- Single running timer:
    - The subsystem supports only one active run at a time (either stopwatch or countdown). Attempting to start a new one while running is ignored (with a log message). Stop and/or Reset first.

- Stopwatch vs. countdown:
    - They are mutually exclusive modes. Check Get Mode if you need to branch logic or formatting.

- StopTimer return value:
    - StopTimer returns elapsed time since the current run started (even if the current mode is countdown). For remaining time in countdown, use Get Remaining Time or the tick updates.

- Early stop of a countdown:
    - Manually stopping a countdown clears the inline completion delegate and does not broadcast the finished event. If you need a “cancelled” flow, handle it explicitly in your code/UI.

- Time source and pausing:
    - The subsystem uses a high-resolution time source that may continue advancing while the game is paused or time-dilated. If you require pause-aware behavior, gate Start/Stop/Reset with your pause state or add custom logic.
