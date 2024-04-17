// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include <Components/ArrowComponent.h>
#include "EnemyActor.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
	SetRootComponent(RootSceneComp);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 1. 시간이 흐르다가
	CurrentTime += DeltaTime;
	// 2. 만약 현재시간이 생성시간이 되면
	if (CurrentTime > MakeTime)
	{
		// 3. 적을 Spawn하고싶다. Arrow의 Transform에...
		GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, ArrowComp->GetComponentTransform());
		// 4. 현재시간을 0으로 초기화 하고싶다.
		CurrentTime = 0;
	}
}

