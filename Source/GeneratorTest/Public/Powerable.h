// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Powerable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPowerable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENERATORTEST_API IPowerable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetPowered(bool bIsPowered, FGuid SetterID);
	virtual FGuid SetGUID();
};
