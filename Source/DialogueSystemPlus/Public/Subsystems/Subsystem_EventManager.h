#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "Subsystem_EventManager.generated.h"

//class USubsystem_Dialogue;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalEventTriggered, FName, EventName);

UCLASS()
class DIALOGUESYSTEMPLUS_API USubsystem_EventManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void Tick(float DeltaTime) override; 
	virtual ETickableTickType GetTickableTickType() const override;
	virtual TStatId GetStatId() const override;
	
public:

	UPROPERTY(BlueprintAssignable, Category = "Event System")
	FOnGlobalEventTriggered OnGlobalEventTriggered;
	
	// Variables about events
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName>RemainingEvents;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName> TriggeredEvents;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FName> AllEvents;

	// Tick Variables
	UPROPERTY()
	float TickInterval = 1.f; 

	UPROPERTY()
	float TimeSinceLastTick = 0.0f;
public:

	UFUNCTION(BlueprintCallable)
	void TriggerEvent(TArray<FName> EventNameToTrigger);

	UFUNCTION(BlueprintCallable)
	void AddEventName(FName EventName);

	UFUNCTION()
	FName NormalizeEventName(FName EventNameToNormalize);

	UFUNCTION()
	TArray<FName> GetUnProcessedEvents();

	UFUNCTION()
	static void PrintString(const FString& Message, float time, FColor Color);

	UFUNCTION()
	void DebuggningEvents();

	
	
};
