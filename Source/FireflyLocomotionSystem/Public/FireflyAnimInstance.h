// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FireflyAnimInstance.generated.h"

class UCharacterMovementComponent;

/**  */
UCLASS()
class FIREFLYLOCOMOTIONSYSTEM_API UFireflyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

#pragma region AnimInstance

public:
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

#pragma endregion


#pragma region CharacterMovement

protected:
	/** ����ʵ����ӵ����Я���Ľ�ɫ�˶����ʵ�� */
	UPROPERTY(BlueprintReadOnly, Category = "FireflyLocomotionSystem")
	UCharacterMovementComponent* OwnerCharacterMovement;

#pragma endregion


#pragma region LocationData

protected:
	virtual void UpdateLocationData(float DeltaSeconds);

protected:
	/** ����ʵ����ӵ���ߵ�ǰ���ϴθ��µ�λ�ƾ���� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomotionSystem|LocationData")
	float DisplacementSinceLastUpdate = 0.f;

	/** ����ʵ����ӵ���ߵ�ǰ����������ϵ�е�λ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomotionSystem|LocationData")
	FVector WorldLocation = FVector::ZeroVector;

	/** ����ʵ����ӵ���ߵ�ǰ��λ���ٶ�ֵ */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomotionSystem|LocationData")
	float DisplacementSpeed = 0.f;	

#pragma endregion


#pragma region RotationData

protected:
	virtual void UpdateRotationData();

protected:
	/** ����ʵ����ӵ���ߵ�ǰ��������ϵ���ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|RotationData")
	FRotator WorldRotation = FRotator::ZeroRotator;

#pragma endregion


#pragma region VelocityData

protected:
	virtual void UpdateVelocityData();

protected:
	/** ����ʵ����ӵ���ߵ�ǰ�Ƿ�ӵ���ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	uint8 bHasVelocity : 1;

	/** ����ʵ����ӵ���ߵ�ǰ��������ϵ���ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FVector WorldVelocity = FVector::ZeroVector;

	/** ����ʵ����ӵ���ߵ�ǰ��������ϵ���ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	FVector LocalVelocity = FVector::ZeroVector;

	/** ����ʵ����ӵ���ߵ�ǰ�ٶ�ʸ���������������ϵ�ĽǶ� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|VelocityState")
	float LocalVelocityDirectionAngle = 0.f;

#pragma endregion


#pragma region AccelerationData

protected:
	virtual void UpdateAccelerationData();

protected:
	/** ����ʵ����ӵ���ߵ�ǰ�Ƿ�ӵ�м��ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	uint8 bHasAcceleration : 1;

	/** ����ʵ����ӵ���ߵ�ǰ��������ϵ���ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	FVector WorldAcceleration = FVector::ZeroVector;

	/** ����ʵ����ӵ���ߵ�ǰ��������ϵ���ٶ�ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	FVector LocalAcceleration = FVector::ZeroVector;

	/** ����ʵ����ӵ���ߵ�ǰ�Ļ�ת����ʸ�� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|AccelerationState")
	FVector PivotDirection = FVector::ZeroVector;

#pragma endregion


#pragma region CharacterState

protected:
	virtual void UpdateCharacterState();

protected:
	/** ����ʵ����ӵ�����Ƿ��ڶ׷��� */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsCrouching : 1;

	/** ����ʵ����ӵ�����Ƿ�����Ծ����״̬ */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsJumpingToApex : 1;

	/** ����ʵ����ӵ�����Ƿ��ڿ�������״̬ */
	UPROPERTY(BlueprintReadWrite, Category = "FireflyLocomoitionSystem|CharacterState")
	uint8 bIsFallingToGround : 1;

private:
	/** ��ǰ�����Ƿ��ǵ�һ�θ����Ƿ� */
	bool bIsFirstUpdate = true;

#pragma endregion
};
