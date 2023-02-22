// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireflyLocomotionTypes.h"
#include "Engine/DataAsset.h"
#include "FireflyLocomotionAnimSet.generated.h"

/** 自使用高级运动系统的动画集配置资产 */
UCLASS(BlueprintType)
class FIREFLYLOCOMOTIONSYSTEM_API UFireflyLocomotionAnimSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region PrimaryDataAsset

public:
	UFireflyLocomotionAnimSet(const FObjectInitializer& ObjectInitializer);

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

#pragma endregion


#pragma region InPlace

public:
	/** 动画：站立状态的原地静止 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Idle;

	/** 动画：站立状态的原地向左转90° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Turn_90_L;

	/** 动画：站立状态的原地向右转90° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Turn_90_R;

	/** 动画：站立状态的原地向左转180° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Turn_180_L;

	/** 动画：站立状态的原地向右转180° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Turn_180_R;

	/** 动画：站立状态的原地静止 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Crouch_Idle;

	/** 动画：站立状态的原地向左转90° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Crouch_Turn_90_L;

	/** 动画：站立状态的原地向右转90° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Crouch_Turn_90_R;

	/** 动画：站立状态的原地向左转180° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Crouch_Turn_180_L;

	/** 动画：站立状态的原地向右转180° */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "In Place")
	UAnimSequenceBase* Anim_InPlace_Crouch_Turn_180_R;

#pragma endregion


#pragma region Walk

public:
	/** 动画集：站立状态静步慢走的开始移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Walk")
	FFireflyLocomotionDirectionalAnimationSet AnimSet_Walk_Start;

	/** 动画集：站立状态静步慢走的移动循环 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Walk")
	FFireflyLocomotionDirectionalAnimationSet AnimSet_Walk_Loop;

	/** 动画集：站立状态快步奔跑的停止移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Walk")
	FFireflyLocomotionDirectionalAnimationSet AnimSet_Walk_Stop;

	/** 动画集：站立状态冲刺疾跑的移动回转 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Walk")
	FFireflyLocomotionDirectionalAnimationSet AnimSet_Walk_Pivot;

#pragma endregion


#pragma region Jog

public:
	/** 动画集：站立状态静步慢走的开始移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jog")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Jog_Start;

	/** 动画集：站立状态静步慢走的移动循环 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jog")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Jog_Loop;

	/** 动画集：站立状态快步奔跑的停止移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jog")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Jog_Stop;

	/** 动画集：站立状态冲刺疾跑的移动回转 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jog")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Jog_Pivot;

#pragma endregion


#pragma region Run

public:
	/** 动画集：站立状态静步慢走的开始移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Run")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Run_Start;

	/** 动画集：站立状态静步慢走的移动循环 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Run")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Run_Loop;

	/** 动画集：站立状态快步奔跑的停止移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Run")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Run_Stop;

	/** 动画集：站立状态冲刺疾跑的移动回转 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Run")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Run_Pivot;

#pragma endregion


#pragma region Sprint

public:
	/** 动画集：站立状态静步慢走的开始移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sprint")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Sprint_Start;

	/** 动画集：站立状态静步慢走的移动循环 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sprint")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Sprint_Loop;

	/** 动画集：站立状态快步奔跑的停止移动 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sprint")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Sprint_Stop;

	/** 动画集：站立状态冲刺疾跑的移动回转 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sprint")
		FFireflyLocomotionDirectionalAnimationSet AnimSet_Sprint_Pivot;

#pragma endregion
};
