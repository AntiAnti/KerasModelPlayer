// Copyright Epic Games, In// Created by YuriNK. Contact: ykasczc@gmail.com
// Using keras2cpp library by gosha20777: https://github.com/gosha20777/keras2cpp
// MIT Lincese

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "keras2cpp/model.h"
#include "KerasModel.generated.h"

using keras2cpp::Model;
using keras2cpp::Tensor;

/** Wrapper for keras2cpp::Tensor */
USTRUCT(BlueprintType, meta=(DisplayName="Tensor"))
struct FKerasTensor
{
	GENERATED_USTRUCT_BODY()

	// Main data is stored here
	Tensor data;

	FKerasTensor operator=(const Tensor& in)
	{
		this->data = in;
		InitAddressMultipliersCache();
		return *this;
	}

	void Resize(const TArray<int32>& Dims);
	void GetSize(TArray<int32>& Size) const;
	void SetFromArray(const TArray<float>& InData);
	void GetAsFlatArray(TArray<float>& OutData) const;
	void FromFile(FString FileName);
	int32 GetAddress(TArray<int32> Address) const;
	void SetValueByAddress(const TArray<int32>& Address, float NewValue);
	float GetValueByAddress(const TArray<int32>& Address) const;

private:
	TArray<int32> AddressMultipliersCache;
	void InitAddressMultipliersCache();
};

/**
 * 
 */
UCLASS(BlueprintType)
class KERASMODELPLAYER_API UKerasModel : public UObject
{
	GENERATED_BODY()
	
public:
	UKerasModel();
	virtual void BeginDestroy() override;

	// Load model from file, see https://github.com/gosha20777/keras2cpp for details
	UFUNCTION(BlueprintCallable, Category = "Keras Model")
	bool LoadFromFile(FString FileName);

	// Evaluate data from model
	UFUNCTION(BlueprintCallable, Category = "Keras Model")
	void Evaluate(const FKerasTensor& InputData, FKerasTensor& OutputData);

	// Is model loaded? Unsafe. Returns true even for invalid model.
	UFUNCTION(BlueprintPure, Category = "Keras Model")
	bool IsLoaded() const { return bLoaded; }

	// Get time consumption for the last Evaluate call
	UFUNCTION(BlueprintPure, Category = "Keras Model")
	float GetLastExecuteTime() const { return (float)EvaluateDuration; }

private:
	// Pointer to the model loaded from file
	keras2cpp::Model* KerasModel;
	// Is model loaded to use?
	bool bLoaded;
	// Time to perform last Evaluate call
	double EvaluateDuration;
};
