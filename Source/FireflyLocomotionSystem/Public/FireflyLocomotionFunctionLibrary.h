// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FireflyLocomotionFunctionLibrary.generated.h"

class UCharacterMovementComponent;
class UFireflyCharacterMovementComponent;

/** */
UCLASS()
class FIREFLYLOCOMOTIONSYSTEM_API UFireflyLocomotionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region CharacterMovement

public:
	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static UCharacterMovementComponent* GetCharacterMovement(APawn* InPawn);

	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static UFireflyCharacterMovementComponent* GetFireflyCharacterMovement(APawn* InPawn);

	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static FTransform ExtractBoneTransformFromAnimation(const UAnimSequence* Animation, FName BoneName, float Time, bool bComponentSpace);

#pragma endregion	
};
