// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireflyLocomotionTypes.generated.h"

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

/** 移动的阶段类型 */
UENUM(BlueprintType)
enum class EFireflyLocomotionStageType : uint8
{
	InPlace			UMETA(DisplayName="原地静止"),
	Start			UMETA(DisplayName="开始移动"),
	Loop			UMETA(DisplayName="持续移动"),
	Stop			UMETA(DisplayName="停止移动"),
	Pivot			UMETA(DisplayName="移动回转"),
};

/** 方向判定的方法 */
UENUM(BlueprintType)
enum class EFireflyLocomotionDirectionMethod : uint8
{
	TwoDirection,
	FourDirection,
	SixDirection,
	EightDirection
};

/** 八方向的枚举类型 */
UENUM(BlueprintType)
enum class EFireflyLocomotionDirectionType : uint8
{
	Forward,	
	Backward,
	Left,
	Right,
	FwdLeft,
	FwdRight,
	BwdLeft,
	BwdRight,
};

/** 动画系统选择的根骨骼航向角偏移更新的计算方式 */
UENUM(BlueprintType)
enum class EFireflyRootYawOffsetModeType : uint8
{
	BlendOut,
	Hold,
	Accumulate
};

/** 速度混合数据 */
USTRUCT(BlueprintType)
struct FFireflyVelocityBlendData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Forward = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Backward = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Left = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Right = 0.f;

	FFireflyVelocityBlendData() {}

	FFireflyVelocityBlendData(float InForward, float InBackward, float InLeft, float InRight)
		: Forward(InForward), Backward(InBackward), Left(InLeft), Right(InRight) {}
};

/** 倾斜幅度数据 */
USTRUCT(BlueprintType)
struct FFireflyLeanAmountData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ForwardDirection = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RightDirection = 0.f;

	FFireflyLeanAmountData() {}

	FFireflyLeanAmountData(float InForwardDirection, float InRightDirection)
		: ForwardDirection(InForwardDirection), RightDirection(InRightDirection){}
};

/** 八方向对应的动画序列 */
USTRUCT(BlueprintType)
struct FFireflyLocomotionDirectionalAnimationSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Forward = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Backward = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Left = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_Right = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_FwdLeft = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_FwdRight = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_BwdLeft = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequenceBase* Anim_BwdRight = nullptr;
};
