// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:
	// 충돌체와 외관
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	// 태어날 때 방향을 정하고
	// 살아가면서 그 방향으로 계속 이동하고싶다.
	UPROPERTY(EditAnywhere)
	FVector Direction;

	UPROPERTY(EditAnywhere)
	float Speed = 500;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOverWidget> GameOverUIFactory;

};
