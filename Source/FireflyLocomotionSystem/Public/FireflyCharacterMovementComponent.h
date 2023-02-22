// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FireflyCharacterMovementComponent.generated.h"

/** 移动的步态类型 */
UENUM(BlueprintType)
enum class EFireflyMovementGait : uint8
{
	Idle			UMETA(DisplayName="停步静止"),
	Walk			UMETA(DisplayName="静步慢走"),
	Jog				UMETA(DisplayName="轻步慢跑"),
	Run				UMETA(DisplayName="快步奔跑"),
	Sprint			UMETA(DisplayName="冲刺疾跑"),
};

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
		uint8 SavedRequestToRun : 1;
		uint8 SavedRequestToJog : 1;
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
	float PhysicalDesiredRotationAlphaValueOverridingRootMotionRotation = 300.f;

	/** 期望旋转在RootMotion过程中的影响速率 */
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = "0", UIMin = "0"))
	float ControlDesiredRotationAlphaValueOverridingRootMotionRotation = 15.f;

#pragma endregion


#pragma region MovementGait 移动步态

public:
	/** 根据移动输入和Character状态更新设置CharacterMovement各种状态的MaxSpeed */
	virtual float UpdateMaxSpeedFirefly() { return GetMaxSpeed(); }

	/** 更新角色的移动步态，项目中自定义 */
	virtual void UpdateMovementGait() {}

	/** 角色的移动步态更新时处理的逻辑，项目中自定义 */
	virtual void HandleMovementGaitChanged() {}

	/** 当前是否在冲刺疾跑 */
	UFUNCTION(BlueprintPure, Category = "Pawn|Components|CharacterMovement")
	virtual bool GetIsSprinting() const { return RequestToSprint; }

	/** 当前是否在快步奔跑 */
	UFUNCTION(BlueprintPure, Category = "Pawn|Components|CharacterMovement")
	virtual bool GetIsRunning() const { return RequestToRun; }

	/** 当前是否在轻步慢跑 */
	UFUNCTION(BlueprintPure, Category = "Pawn|Components|CharacterMovement")
	virtual bool GetIsJogging() const { return RequestToJog; }

	/** 当前是否在静步慢走 */
	UFUNCTION(BlueprintPure, Category = "Pawn|Components|CharacterMovement")
	virtual bool GetIsWalking() const { return RequestToWalk; }

	/** 申请开启或关闭冲刺疾跑 */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement")
	virtual void RequestShiftSprint(bool bWantToSprint);

	/** 申请开启或关闭快步奔跑 */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement")
	virtual void RequestShiftRun(bool bWantToRun);

	/** 申请开启或关闭轻步慢跑 */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement")
	virtual void RequestShiftJog(bool bWantToJog);

	/** 申请开启或关闭静步慢走 */
	UFUNCTION(BlueprintCallable, Category = "Pawn|Components|CharacterMovement")
	virtual void RequestShiftWalk(bool bWantToWalk);	

	EFireflyMovementGait GetCurrentMovementGait() const { return CurrentMovementGait; }

protected:
	/** 角色的当前移动速度模式，默认为Jog */
	UPROPERTY(BlueprintReadOnly, Category = "CharacterMovement")
	EFireflyMovementGait CurrentMovementGait = EFireflyMovementGait::Jog;

	/** 是否开启冲刺移动 */
	uint8 RequestToSprint : 1;

	/** 是否开启快步奔跑 */
	uint8 RequestToRun : 1;

	/** 是否开启轻步慢跑 */
	uint8 RequestToJog : 1;

	/** 是否开启轻步慢跑 */
	uint8 RequestToWalk : 1;

#pragma endregion
};
