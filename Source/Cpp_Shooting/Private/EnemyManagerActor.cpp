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
	// 1. �ð��� �帣�ٰ�
	CurrentTime += DeltaTime;
	// 2. ���� ����ð��� �����ð��� �Ǹ�
	if (CurrentTime > MakeTime)
	{
		// 3. ���� Spawn�ϰ�ʹ�. Arrow�� Transform��...
		GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, ArrowComp->GetComponentTransform());
		// 4. ����ð��� 0���� �ʱ�ȭ �ϰ�ʹ�.
		CurrentTime = 0;
	}
}

