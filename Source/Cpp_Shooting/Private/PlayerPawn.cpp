// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include <Components/ArrowComponent.h>
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// �浹ü ������Ʈ�� �����ؼ� Root�� ��ġ�ϰ�ʹ�.
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	SetRootComponent(BoxComp);

	// ������ ����� ������Ʈ�� �����ؼ� Root�� ��ġ�ϰ�ʹ�.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	// �ѱ�
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	// MeshComp�� �浹ü�� Off��Ű��ʹ�.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BoxComp�� �浹������ �ϰ�ʹ�.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	auto pc = GetWorld()->GetFirstPlayerController();
	// ����
	pc->SetPause(false);
	// ���콺 �����Ͱ� ������ �ϰ�ʹ�.
	pc->SetShowMouseCursor(false);
	pc->SetInputMode(FInputModeGameOnly());

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �̵����� P = P0 + vt
	FVector velocity = FVector(0, h, v).GetSafeNormal() * Speed;
	FVector P0 = GetActorLocation();

	SetActorLocation(P0 + velocity * DeltaTime);



	// ���� �ѽ�� ����� Ȱ��ȭ �Ǹ�
	if (true == bAutoFire)
	{
		// 1. �ð��� �帣�ٰ�
		CurrentTime += DeltaTime;
		// 2. ���� ���� �ð��� �߻� �ð��� �Ǹ�
		if (CurrentTime > FireTime)
		{
			// 3. �Ѿ� �ϳ� �����ʹ�.
			MakeBullet();
			// 4. ����ð��� 0���� �ʱ�ȭ �ϰ�ʹ�.
			CurrentTime = 0;
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerPawn::OnActionFirePressed);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &APlayerPawn::OnActionFireReleased);
	
}

void APlayerPawn::OnAxisHorizontal(float value)
{
	h = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	v = value;
}

void APlayerPawn::OnActionFirePressed()
{
	// �ѽ�� ����� Ȱ��ȭ �ϰ�ʹ�.
	bAutoFire = true;
	CurrentTime = 0;
	MakeBullet();
}

void APlayerPawn::OnActionFireReleased()
{
	// �ѽ�� ����� ��Ȱ��ȭ �ϰ�ʹ�.
	bAutoFire = false;
}

void APlayerPawn::MakeBullet()
{
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, Arrow->GetComponentTransform());

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

