// Created by YuriNK. Contact: ykasczc@gmail.com
// Using keras2cpp library by gosha20777: https://github.com/gosha20777/keras2cpp
// MIT Lincese

#include "KerasFunctionLibrary.h"
#include "KerasModel.h"

void UKerasFunctionLibrary::TensorResize(FKerasTensor& Tensor, const TArray<int32>& Dimensions)
{
	Tensor.Resize(Dimensions);
}

void UKerasFunctionLibrary::TensorGetSize(FKerasTensor& Tensor, TArray<int32>& Dimensions)
{
	Tensor.GetSize(Dimensions);
}

FKerasTensor UKerasFunctionLibrary::CreateTensorFromArray(const TArray<float>& InData)
{
	FKerasTensor t;
	t.SetFromArray(InData);
	return t;
}

void UKerasFunctionLibrary::UpdateTensorFromArray(FKerasTensor& Tensor, const TArray<float>& InData)
{
	Tensor.SetFromArray(InData);
}

FKerasTensor UKerasFunctionLibrary::CreateTensorFromFile(FString FileName)
{
	FKerasTensor t;
	t.FromFile(FileName);
	return t;
}

void UKerasFunctionLibrary::TensorAsFlatArray(const FKerasTensor& Tensor, TArray<float>& OutData)
{
	Tensor.GetAsFlatArray(OutData);
}

void UKerasFunctionLibrary::TensorSetValue(FKerasTensor& Tensor, const TArray<int32>& Address, float NewValue)
{
	Tensor.SetValueByAddress(Address, NewValue);
}

float UKerasFunctionLibrary::TensorGetValue(const FKerasTensor& Tensor, const TArray<int32>& Address)
{
	return Tensor.GetValueByAddress(Address);
}

bool UKerasFunctionLibrary::CreateKerasModelFromFile(UObject* Context, FString FileName, UKerasModel*& LoadedModel)
{
	if (!IsValid(Context))
	{
		LoadedModel = NewObject<UKerasModel>(UKerasModel::StaticClass());
	}
	else
	{
		LoadedModel = NewObject<UKerasModel>(Context, UKerasModel::StaticClass());
	}

	if (IsValid(LoadedModel))
	{
		return LoadedModel->LoadFromFile(FileName);
	}

	return false;
}
