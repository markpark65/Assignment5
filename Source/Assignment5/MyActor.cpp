// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CurrentLocation = FVector(0.0f, 50.0f, 0.0f);
	TotalDistance = 0.0f;
	EventCount = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	// 시작 위치 로그 출력
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("C++ BeginPlay Start!!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
		FString::Printf(TEXT("시작 좌표: %s"), *CurrentLocation.ToString()));

	// 10회 랜덤 이동 및 회전 반복
	for (int32 i = 1; i <= 10; i++)
	{
		Move();
		Rotate();
		TriggerEvent();

		// 현재 스텝 및 좌표 출력 (도전 기능 포함)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White,
			FString::Printf(TEXT("[%d단계] 현재 위치: %s"), i, *CurrentLocation.ToString()));
	}

	// 최종 리포트 출력 (도전 기능)
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,
		FString::Printf(TEXT("=== 최종 리포트 ===\n총 이동 거리: %.2f\n총 이벤트 발생: %d회"), TotalDistance, EventCount));
}

void AMyActor::Move()
{
	FVector PreviousLocation = CurrentLocation;

	// X, Y 좌표에 랜덤한 스텝(0~2) 더하기
	CurrentLocation.X += CreateStep();
	CurrentLocation.Y += CreateStep();

	// 두 지점 사이의 거리 계산 및 누적 (도전)
	float StepDistance = FVector::Dist(PreviousLocation, CurrentLocation);
	TotalDistance += StepDistance;
}

void AMyActor::Rotate()
{

}

void AMyActor::TriggerEvent()
{
	if (FMath::RandRange(0, 1) == 1)
	{
		EventCount++;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT(" 이벤트 발생!"));
	}
}

int32 AMyActor::CreateStep()
{
	return FMath::RandRange(0, 2);
}
