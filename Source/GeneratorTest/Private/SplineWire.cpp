// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineWire.h"

#include "Powerable.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASplineWire::ASplineWire()
{
	SplineWireComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Wire"));
	SplineWireComponent->SetupAttachment(RootComponent);

	// Disabled since it's handled in the blueprint (purely visual since it sets up the spline mesh)
	/*
	for (int Point = 0; Point <= SplineWireComponent->GetNumberOfSplinePoints() - 2; ++Point)
	{
		USplineMeshComponent* WireSegment = CreateDefaultSubobject<USplineMeshComponent>(FName("WireSegment"));
		WireSegment->SetStaticMesh(WireMesh);
		WireSegment->SetMaterial(0, WireMaterialInstance);
		SplineMeshes.Add(WireSegment);
		WireSegment->SetForwardAxis(ESplineMeshAxis::Z);
		AttachToComponent(SplineWireComponent, FAttachmentTransformRules::KeepRelativeTransform);

		FVector StartPosition, StartTangent, EndPosition, EndTangent;
		SplineWireComponent->GetLocationAndTangentAtSplinePoint(Point, StartPosition, StartTangent, ESplineCoordinateSpace::Local);
		SplineWireComponent->GetLocationAndTangentAtSplinePoint(Point + 1, EndPosition, EndTangent, ESplineCoordinateSpace::Local);
		WireSegment->SetStartAndEnd(StartPosition, StartTangent, EndPosition, EndTangent);
	}
	*/
}

// Called when the game starts or when spawned
void ASplineWire::BeginPlay()
{
	Super::BeginPlay();

	ThisGuid = FGuid::NewGuid();

	// Disabled since we were having problems setting up dynamic materials on the spline
	/*
	for (USplineMeshComponent* Mesh : SplineMeshes)
	{
		DynamicMaterials.Add(UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this));
	}
	*/

	bIsSetupDone = true;

	//SetAppearance(bIsPowered);
	SetPowerNext(bIsPowered);
}

void ASplineWire::SetAppearance(bool Powered)
{
	if (bIsSetupDone)
	{
		if (bIsForward)
		{
			I = SplineMeshes.Num() - 1;

			if (I >= 0)
			{
				CurrentMaterial = DynamicMaterials[I];
				CurrentMaterial->SetScalarParameterValue(FName("On/Off"), bIsPowered);
				SplineMeshes[I]->SetMaterial(0, CurrentMaterial);
				--I;
				//Optional Delay...add here
			}
		}
		else
		{
			I = 0;

			if (I < SplineMeshes.Num())
			{
				CurrentMaterial = DynamicMaterials[I];
				CurrentMaterial->SetScalarParameterValue(FName("On/Off"), bIsPowered);
				SplineMeshes[I]->SetMaterial(0, CurrentMaterial);
				++I;
				//Optional Delay...add here
			}
		}
	}
}

void ASplineWire::SetPowerNext(const bool Powered)
{
	for (AActor* Actor : NextPowerable)
	{
		if (Cast<IPowerable>(Actor))
		{
			Cast<IPowerable>(Actor)->SetPowered(Powered, ThisGuid);
		}
	}
}

void ASplineWire::SetPowered(bool IsPowered, FGuid SetterID)
{
	bIsPowered = IsPowered;
	//SetAppearance(bIsPowered);
	//Optional Delay...add here
	SetPowerNext(bIsPowered);
}