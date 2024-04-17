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
	// 충돌체 컴포넌트를 생성해서 Root로 배치하고싶다.
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	// 외형을 담당할 컴포넌트를 생성해서 Root에 배치하고싶다.
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* Arrow;

	// 가로축, 세로축 입력을 받을 함수를 구현하고싶다.
	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);

	float h;
	float v;

	UPROPERTY(EditAnywhere)
	float Speed = 500;

	// 마우스 왼쪽 버튼을 누르면 총알액터를 레벨에 Spawn하고 싶다.(Arrow 컴포넌트의 Transform을 이용해서)
	// 개선 : 마우스 왼쪽 버튼을 누르고있으면 총알이 발사되되 0.2초마다 발사되고싶다.
	// 떼면 그만 발사하고싶다.
	void OnActionFirePressed();
	void OnActionFireReleased();
	void MakeBullet();

	// 총쏘기 기능이 활성화 되면
	// 시간이 흐르다가 일정시간이 되면 총알 하나 만들고싶다.
	bool bAutoFire;
	float CurrentTime;
	float FireTime = 0.2f;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

};
