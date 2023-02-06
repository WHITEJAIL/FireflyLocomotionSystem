// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireflyLocomotionTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FireflyLocomotionFunctionLibrary.generated.h"

class UCharacterMovementComponent;
class UFireflyCharacterMovementComponent;

/** */
UCLASS()
class FIREFLYLOCOMOTIONSYSTEM_API UFireflyLocomotionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

#pragma region CharacterMovement

	/** 若指定的Pawn拥有角色运动组件，则返回组件实例 */
	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static UCharacterMovementComponent* GetCharacterMovement(APawn* InPawn);

	/** 若指定的Pawn拥有Firefly角色运动组件，则返回组件实例 */
	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static UFireflyCharacterMovementComponent* GetFireflyCharacterMovement(APawn* InPawn);

#pragma endregion


#pragma region Direction

	/** 根据指定的角度值确认一个方向，可以只考虑四向，也可以考虑八向 */
	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static EFireflyLocomotionDirectionType SelectLocomotionDirectionFromAngle(float Angle, 
		EFireflyLocomotionDirectionMethod DirectionMethod = EFireflyLocomotionDirectionMethod::FourDirection);

	/** 根据指定的方向值确认一个相反的方向 */
	UFUNCTION(BlueprintPure, Category = "FireflyLocomotionSystem")
	static EFireflyLocomotionDirectionType GetOppositeCardinalDirection(EFireflyLocomotionDirectionType InDirection);

#pragma endregion	
};
