// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 시간이 흐르다가 생성시간이 되면 적을 하나 생성해서 Arrow위치에 배치하고싶다.
	UPROPERTY(EditAnywhere)
	class USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* ArrowComp;

	float CurrentTime;
	float MakeTime = 2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyActor> EnemyFactory;

};
