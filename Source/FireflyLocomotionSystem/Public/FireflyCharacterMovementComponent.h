// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FireflyCharacterMovementComponent.generated.h"

/** 加入了自定义功能的角色运动组件 */
UCLASS()
class FIREFLYLOCOMOTIONSYSTEM_API UFireflyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

#pragma region SavedMove // 移动数据包

	class FFireflySavedMove : public FSavedMove_Character
	{
	public:

		typedef FSavedMove_Character Super;

		///@brief Resets all saved variables.
		virtual void Clear() override;

		///@brief Store input commands in the compressed flags.
		virtual uint8 GetCompressedFlags() const override;

		///@brief This is used to check whether or not two moves can be combined into one.
		///Basically you just check to make sure that the saved variables are the same.
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;

		///@brief Sets up the move before sending it to the server. 
		virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
		///@brief Sets variables on character movement component before making a predictive correction.
		virtual void PrepMoveFor(class ACharacter* Character) override;

		uint8 SavedRequestToSprint : 1;

		uint8 SavedRequestToWalk : 1;
	};

	class FFireflyNetworkPredictionData_Client : public FNetworkPredictionData_Client_Character
	{
	public:
		FFireflyNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		///@brief Allocates a new copy of our custom saved move
		virtual FSavedMovePtr AllocateNewMove() override;
	};

#pragma endregion


#pragma region Override // 基类覆盖

protected:
	virtual void BeginPlay() override;

	virtual void PerformMovement(float DeltaTime) override;

public:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;

#pragma endregion


#pragma region RotationControl // 定制化

protected:
	/** 获取物理运动期望的旋转值 */
	FRotator GetPhysicsDesiredRotation(float DeltaTime) const;

protected:
	/** 期望旋转在RootMotion过程中的影响速率 */
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "0", UIMin = "0"))
	float PhysicalDesiredRotationAlphaValueOverridingRootMotionRotation = 30.f;

	/** 期望旋转在RootMotion过程中的影响速率 */
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "0", UIMin = "0"))
	float ControlDesiredRotationAlphaValueOverridingRootMotionRotation = 3.f;

#pragma endregion


#pragma region VelocityMode // 移动速度模式

public:
	/** 根据移动输入和Character状态更新设置CharacterMovement各种状态的MaxSpeed */
	UFUNCTION(BlueprintNativeEvent, Category = "Pawn|Components|CharacterMovement")
	float UpdateMaxSpeedFirefly();
	virtual float UpdateMaxSpeedFirefly_Implementation();

	/** 当前是否在冲刺移动 */
	UFUNCTION(BlueprintPure, Category = "Pawn|Components|CharacterMovement")
	bool GetIsSprinting() const;

	/** 当前是否在散步走 */
	UFUNCTION(BlueprintPure, Category = "Pawn|Components|CharacterMovement")
	bool GetIsWalking() const;	

	/** 申请开启或关闭散步走 */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement")
	virtual void RequestShiftWalk(bool bWantToWalk);

	/** 申请开启或关闭冲刺移动 */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement")
	virtual void RequestShiftSprint(bool bWantToSprint);

protected:
	/** 是否开启冲刺移动 */
	uint8 RequestToSprint : 1;

	/** 是否开启散步走 */
	uint8 RequestToWalk : 1;

#pragma endregion
};
