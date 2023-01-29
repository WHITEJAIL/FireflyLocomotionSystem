// Fill out your copyright notice in the Description page of Project Settings.


#include "FireflyLocomotionFunctionLibrary.h"

#include "FireflyCharacterMovementComponent.h"

UCharacterMovementComponent* UFireflyLocomotionFunctionLibrary::GetCharacterMovement(APawn* InPawn)
{
	UActorComponent* Comp = InPawn->GetComponentByClass(UCharacterMovementComponent::StaticClass());
	if (IsValid(Comp))
	{
		return Cast<UCharacterMovementComponent>(Comp);
	}

	return nullptr;
}

UFireflyCharacterMovementComponent* UFireflyLocomotionFunctionLibrary::GetFireflyCharacterMovement(APawn* InPawn)
{
	UActorComponent* Comp = InPawn->GetComponentByClass(UFireflyCharacterMovementComponent::StaticClass());
	if (IsValid(Comp))
	{
		return Cast<UFireflyCharacterMovementComponent>(Comp);
	}

	return nullptr;
}
