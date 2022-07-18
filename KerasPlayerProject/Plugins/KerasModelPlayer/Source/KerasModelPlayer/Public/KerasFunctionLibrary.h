// Created by YuriNK. Contact: ykasczc@gmail.com
// Using keras2cpp library by gosha20777: https://github.com/gosha20777/keras2cpp
// MIT Lincese

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KerasModel.h"
#include "KerasFunctionLibrary.generated.h"

/**
 * Internal helper class to expose FKerasTensor functions to blueprints
 */
UCLASS()
class KERASMODELPLAYER_API UKerasFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Resize tensor (up to 4 dimensions)
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Resize"), Category = "Tensor")
	static void TensorResize(UPARAM(Ref)FKerasTensor& Tensor, const TArray<int32>& Dimensions);

	// Get tensor dimensions
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Size"), Category = "Tensor")
	static void TensorGetSize(UPARAM(Ref)FKerasTensor& Tensor, TArray<int32>& Dimensions);

	// Create new tensor from flat float array
	UFUNCTION(BlueprintCallable, Category = "Tensor")
	static FKerasTensor CreateTensorFromArray(const TArray<float>& InData);

	// Create new tensor from flat float array
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Update Data"), Category = "Tensor")
	static void UpdateTensorFromArray(UPARAM(Ref)FKerasTensor& Tensor, const TArray<float>& InData);

	// Create new tensor from binary file
	UFUNCTION(BlueprintCallable, Category = "Tensor")
	static FKerasTensor CreateTensorFromFile(FString FileName);

	// Read tensor data as flat float array
	UFUNCTION(BlueprintPure, meta = (DisplayName = "As Array"), Category = "Tensor")
	static void TensorAsFlatArray(const FKerasTensor& Tensor, TArray<float>& OutData);

	// Set single value by address
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Value"), Category = "Tensor")
	static void TensorSetValue(UPARAM(Ref)FKerasTensor& Tensor, const TArray<int32>& Address, float NewValue);

	// Get a value by address
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Value"), Category = "Tensor")
	static float TensorGetValue(const FKerasTensor& Tensor, const TArray<int32>& Address);

	// Create new model object and initialize model from file
	UFUNCTION(BlueprintCallable, Category = "Keras Model")
	static bool CreateKerasModelFromFile(UObject* Context, FString FileName, UKerasModel*& LoadedModel);
};
