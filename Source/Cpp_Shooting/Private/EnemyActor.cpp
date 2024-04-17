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
	// �浹ü ������Ʈ�� �����ؼ� ��Ʈ�� ��ġ�ϰ�ʹ�.
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	// �ܰ� ������Ʈ�� �����ؼ� ��Ʈ�� ���̰�ʹ�.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	// MeshComp�� �浹ü�� Off��Ű��ʹ�.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BoxComp�� �浹������ �ϰ�ʹ�.
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
	// ������ ���ϰ�
	int32 randValue = FMath::RandRange(0, 99);
	// 30%�� Ȯ���� �÷��̾� ��������
	if (randValue < 30) {
		//// �������� ã��ʹ�.
		//AActor* target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//// ������ ������ ���ϰ�ʹ�. target <- me
		//Direction = target->GetActorLocation() - this->GetActorLocation();
		//// ���͸� ����ȭ �ϰ�ʹ�. (�������μ� �ǹ̰��ְ� �ϱ����ؼ� ũ�⸦ 1�� ����� ���̴�.)
		//Direction.Normalize();

		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());
		//// ������ ������ ���ϰ�ʹ�. target <- me
		//Direction = target->GetActorLocation() - this->GetActorLocation();
		//// ���͸� ����ȭ �ϰ�ʹ�. (�������μ� �ǹ̰��ְ� �ϱ����ؼ� ũ�⸦ 1�� ����� ���̴�.)
		//Direction.Normalize();

		for (TActorIterator<APlayerPawn> it(GetWorld()); it; ++it)
		{
			APlayerPawn* target = *it;
			if (nullptr == target)
				continue;

			// ������ ������ ���ϰ�ʹ�. target <- me
			Direction = target->GetActorLocation() - this->GetActorLocation();
			// ���͸� ����ȭ �ϰ�ʹ�. (�������μ� �ǹ̰��ְ� �ϱ����ؼ� ũ�⸦ 1�� ����� ���̴�.)
			Direction.Normalize();
		}

	}
	// ������ Ȯ���� �չ������� �ϰ�ʹ�.
	else {
		Direction = GetActorForwardVector();
	}

	// Direction �������� ȸ���ϰ�ʹ�.
	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(Direction, GetActorUpVector());
	SetActorRotation(newRotation);


	// �ڽ�������Ʈ�� �浹�� �߻��ϸ� ���� �˷��� ��� �ϰ�ʹ�.
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxCompBeginOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �� �������� �̵��ϰ�ʹ�.
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

	// ���� OtherActor�� Player���
	auto* player = Cast<APlayerPawn>(OtherActor);
	if (nullptr != player)
	{
		// ���װ� 
		player->Destroy();
		// ���װ� 
		Destroy();
		
		// ���ӿ���UI�� �����ؼ� ȭ�鿡 ���̰� �ϰ�ʹ�.
		auto ui = CreateWidget(GetWorld(), GameOverUIFactory);
		ui->AddToViewport();
		
		auto pc = GetWorld()->GetFirstPlayerController();
		// ����
		pc->SetPause(true);
		// ���콺 �����Ͱ� ������ �ϰ�ʹ�.
		pc->SetShowMouseCursor(true);
		pc->SetInputMode(FInputModeUIOnly());
	}
}

