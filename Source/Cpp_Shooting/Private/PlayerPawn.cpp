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
	// 충돌체 컴포넌트를 생성해서 Root로 배치하고싶다.
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	SetRootComponent(BoxComp);

	// 외형을 담당할 컴포넌트를 생성해서 Root에 배치하고싶다.
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	// 총구
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	// MeshComp는 충돌체를 Off시키고싶다.
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BoxComp의 충돌설정을 하고싶다.
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	auto pc = GetWorld()->GetFirstPlayerController();
	// 정지
	pc->SetPause(false);
	// 마우스 포인터가 나오게 하고싶다.
	pc->SetShowMouseCursor(false);
	pc->SetInputMode(FInputModeGameOnly());

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 이동공식 P = P0 + vt
	FVector velocity = FVector(0, h, v).GetSafeNormal() * Speed;
	FVector P0 = GetActorLocation();

	SetActorLocation(P0 + velocity * DeltaTime);



	// 만약 총쏘기 기능이 활성화 되면
	if (true == bAutoFire)
	{
		// 1. 시간이 흐르다가
		CurrentTime += DeltaTime;
		// 2. 만약 현재 시간이 발사 시간이 되면
		if (CurrentTime > FireTime)
		{
			// 3. 총알 하나 만들고싶다.
			MakeBullet();
			// 4. 현재시간을 0으로 초기화 하고싶다.
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
	// 총쏘기 기능을 활성화 하고싶다.
	bAutoFire = true;
	CurrentTime = 0;
	MakeBullet();
}

void APlayerPawn::OnActionFireReleased()
{
	// 총쏘기 기능을 비활성화 하고싶다.
	bAutoFire = false;
}

void APlayerPawn::MakeBullet()
{
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, Arrow->GetComponentTransform());

	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

