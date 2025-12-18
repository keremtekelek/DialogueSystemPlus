#include "Subsystems/Subsystem_EventManager.h"
//#include "Subsystems/Subsystem_Dialogue.h"

void USubsystem_EventManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TriggeredEvents.Empty();
	
	//AddEventName("Demo Started");
}

void USubsystem_EventManager::Deinitialize()
{
	Super::Deinitialize();
}


void USubsystem_EventManager::Tick(float DeltaTime)
{
	TimeSinceLastTick += DeltaTime;

	if (TimeSinceLastTick >= TickInterval)
	{
		//***WRITE CODES ABOUT TICK IN HERE!***
		
		DebuggningEvents();
		 
		TimeSinceLastTick -= TickInterval; 
	}
}

ETickableTickType USubsystem_EventManager::GetTickableTickType() const
{
	return (IsTemplate() ? ETickableTickType::Never : ETickableTickType::Always);
}

TStatId USubsystem_EventManager::GetStatId() const
{
	
	RETURN_QUICK_DECLARE_CYCLE_STAT(USubsystem_EventManager, STATGROUP_Tickables);
}

void USubsystem_EventManager::TriggerEvent(TArray<FName> EventNameToTrigger)
{
	for (const FName& IncomingEvent : EventNameToTrigger)
	{
		if (IncomingEvent != NAME_None)
		{
			FName NormalizedIncomingEvent = NormalizeEventName(IncomingEvent);
			
			if (AllEvents.Contains(IncomingEvent))
			{
				TriggeredEvents.AddUnique(NormalizedIncomingEvent);
			}
			else
			{
				AddEventName(IncomingEvent);
				TriggeredEvents.AddUnique(NormalizedIncomingEvent);
			}

			//*** Make Triggered Event Happen ***

			if ("demostarted" == NormalizedIncomingEvent)
			{
				PrintString(" demostarted is triggered ",10.f,FColor::Blue);
			}
			else if ("potatosellerangry" == NormalizedIncomingEvent)
			{
				PrintString("Potato Seller Angy is triggered", 7.f,FColor::Red);
			}
			
		}
	}
}

void USubsystem_EventManager::AddEventName(FName EventName)
{
	AllEvents.AddUnique(NormalizeEventName(EventName));
}

FName USubsystem_EventManager::NormalizeEventName(FName EventNameToNormalize)
{
	FString LoweredString = EventNameToNormalize.ToString().ToLower();
	LoweredString  = LoweredString .Replace(TEXT(" "), TEXT(""));
	FName FinalEventName = FName(*LoweredString);

	return FinalEventName;
}



TArray<FName> USubsystem_EventManager::GetUnProcessedEvents()
{
	TArray<FName> UnProcessedEvents;
	TSet<FName> TriggeredEventsSet(TriggeredEvents);

	
	for (const FName& Event : AllEvents)
	{
		
		if (!TriggeredEvents.Contains(Event))
		{
			RemainingEvents.Add(Event);
		}
	}

	return UnProcessedEvents;
}


void USubsystem_EventManager::PrintString(const FString& Message, float Time, FColor Color)
{
	if (!GEngine)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1,Time, Color, Message);
}

void USubsystem_EventManager::DebuggningEvents()
{
	TArray<FName>& ArrayEvents = AllEvents; 
	FString Str_Events = TEXT("{ ");
	for (int32 i = 0; i < ArrayEvents.Num(); ++i)
	{
		Str_Events += ArrayEvents[i].ToString();
		if (i < ArrayEvents.Num() - 1) Str_Events += TEXT(", ");
	}
	Str_Events += TEXT(" }");

	FString FinalText = FString::Printf(TEXT(
	"---All Global Events---\n "
	"= %s\n"
	"------------------------"

	), *Str_Events);

	PrintString(Str_Events, 0.1f,FColor::White);
		
}
