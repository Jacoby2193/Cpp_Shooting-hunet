// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "PlayerPawn.h"
#include <Components/BoxComponent.h>
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameOverWidget.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 충돌체 컴포넌트를 생성해서 루트에 배치하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	// 외관 컴포넌트를 생성해서 루트에 붙이고싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	// MeshComp는 충돌체를 Off시키고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BoxComp의 충돌설정을 하고싶다.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	//BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//BoxComp->SetCollisionObjectType(ECC_GameTraceChannel3);
	//BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	//BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	// 방향을 정하고
	int32 randValue = FMath::RandRange(0, 99);
	// 30%의 확률로 플레이어 방향으로
	if (randValue < 30) {
		//// 목적지를 찾고싶다.
		//AActor* target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//// 목적지 방향을 구하고싶다. target <- me
		//Direction = target->GetActorLocation() - this->GetActorLocation();
		//// 벡터를 정규화 하고싶다. (방향으로서 의미가있게 하기위해서 크기를 1로 만드는 것이다.)
		//Direction.Normalize();

		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
		//// 목적지 방향을 구하고싶다. target <- me
		//Direction = target->GetActorLocation() - this->GetActorLocation();
		//// 벡터를 정규화 하고싶다. (방향으로서 의미가있게 하기위해서 크기를 1로 만드는 것이다.)
		//Direction.Normalize();

		for (TActorIterator<APlayerPawn> it(GetWorld()); it; ++it)
		{
			APlayerPawn* target = *it;
			if (nullptr == target)
				continue;

			// 목적지 방향을 구하고싶다. target <- me
			Direction = target->GetActorLocation() - this->GetActorLocation();
			// 벡터를 정규화 하고싶다. (방향으로서 의미가있게 하기위해서 크기를 1로 만드는 것이다.)
			Direction.Normalize();
		}

	}
	// 나머지 확률로 앞방향으로 하고싶다.
	else {
		Direction = GetActorForwardVector();
	}

	// Direction 방향으로 회전하고싶다.
	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(Direction, GetActorUpVector());
	SetActorRotation(newRotation);


	// 박스컴포넌트에 충돌이 발생하면 나도 알려줘 라고 하고싶다.
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxCompBeginOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 그 방향으로 이동하고싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	SetActorLocation(P0 + Direction * Speed * DeltaTime);
}

void AEnemyActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("AEnemyActor::NotifyActorBeginOverlap"));
}

void AEnemyActor::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AEnemyActor::OnBoxCompBeginOverlap"));

	// 만약 OtherActor가 Player라면
	auto* player = Cast<APlayerPawn>(OtherActor);
	if (nullptr != player)
	{
		// 너죽고 
		player->Destroy();
		// 나죽고 
		Destroy();
		
		// 게임오버UI를 생성해서 화면에 보이게 하고싶다.
		auto ui = CreateWidget(GetWorld(), GameOverUIFactory);
		ui->AddToViewport();
		
		auto pc = GetWorld()->GetFirstPlayerController();
		// 정지
		pc->SetPause(true);
		// 마우스 포인터가 나오게 하고싶다.
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeUIOnly());
	}
}

