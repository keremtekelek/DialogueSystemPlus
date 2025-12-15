#include "DialogueSystemPlusCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Subsystems/Subsystem_Dialogue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);



ADialogueSystemPlusCharacter::ADialogueSystemPlusCharacter()
{
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh()); 
	FollowCamera->bUsePawnControlRotation = true; 


	
	
}

// This function is needed as sockets are not present during construction
void ADialogueSystemPlusCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FollowCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("head"));
	FollowCamera->SetRelativeLocation(FVector(0, 12, 0));
}


void ADialogueSystemPlusCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UGameInstance* GI = GetGameInstance())
	{
		DialogueSubsystem = GI->GetSubsystem<USubsystem_Dialogue>();
	}

	if (DialogueSubsystem)
	{
		DialogueSubsystem->DSM_MainCharacter = DSM_MainCharacter;
		DialogueSubsystem->DataTable_MainCharacter = DataTable_MainCharacter;

		DialogueSubsystem->MainCharacter = this;
	}
}



// Input

void ADialogueSystemPlusCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADialogueSystemPlusCharacter::Move);

		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADialogueSystemPlusCharacter::Look);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ADialogueSystemPlusCharacter::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ADialogueSystemPlusCharacter::SprintEnd);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADialogueSystemPlusCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADialogueSystemPlusCharacter::Move(const FInputActionValue& Value)
{
	
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADialogueSystemPlusCharacter::Look(const FInputActionValue& Value)
{
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADialogueSystemPlusCharacter::SprintStart(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 420.f;
	IsCharacterSprinting = true;
}

void ADialogueSystemPlusCharacter::SprintEnd(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	IsCharacterSprinting = false;
}

void ADialogueSystemPlusCharacter::Interact(const FInputActionValue& Value)
{
	/*
	* if (UGameInstance* GI = GetGameInstance())
	{
		if (USubsystem_Dialogue* DialogueSubsystem = GI->GetSubsystem<USubsystem_Dialogue>())
		{
			DialogueSubsystem->Interacted();
		}
	}
	 */

	if (DialogueSubsystem)
	{
		DialogueSubsystem->Interacted();
	}
	
}


