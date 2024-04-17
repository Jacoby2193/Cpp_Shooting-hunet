// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

//class UBoxComponent;

UCLASS()
class CPP_SHOOTING_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// �浹ü ������Ʈ�� �����ؼ� Root�� ��ġ�ϰ�ʹ�.
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	// ������ ����� ������Ʈ�� �����ؼ� Root�� ��ġ�ϰ�ʹ�.
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* Arrow;

	// ������, ������ �Է��� ���� �Լ��� �����ϰ�ʹ�.
	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);

	float h;
	float v;

	UPROPERTY(EditAnywhere)
	float Speed = 500;

	// ���콺 ���� ��ư�� ������ �Ѿ˾��͸� ������ Spawn�ϰ� �ʹ�.(Arrow ������Ʈ�� Transform�� �̿��ؼ�)
	// ���� : ���콺 ���� ��ư�� ������������ �Ѿ��� �߻�ǵ� 0.2�ʸ��� �߻�ǰ�ʹ�.
	// ���� �׸� �߻��ϰ�ʹ�.
	void OnActionFirePressed();
	void OnActionFireReleased();
	void MakeBullet();

	// �ѽ�� ����� Ȱ��ȭ �Ǹ�
	// �ð��� �帣�ٰ� �����ð��� �Ǹ� �Ѿ� �ϳ� �����ʹ�.
	bool bAutoFire;
	float CurrentTime;
	float FireTime = 0.2f;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

};
