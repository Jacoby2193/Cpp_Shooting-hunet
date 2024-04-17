// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include <Components/BoxComponent.h>
#include "EnemyActor.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(37.5f, 12.5f, 50));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1));

	// MeshComp는 충돌체를 Off시키고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BoxComp의 충돌설정을 하고싶다.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnBoxCompBeginOverlap);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 앞 방향으로 이동하고싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector dir = GetActorForwardVector();
	FVector v = dir * Speed;
	SetActorLocation(P0 + v * DeltaTime);
}

void ABulletActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약 상대가 Enemy라면 
	if (OtherActor->IsA<AEnemyActor>())
	{
		// 너죽고
		OtherActor->Destroy();
		// 나죽고
		this->Destroy();
	}
}
