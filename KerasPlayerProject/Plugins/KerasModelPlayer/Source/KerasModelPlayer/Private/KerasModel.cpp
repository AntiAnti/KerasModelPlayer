// Created by YuriNK. Contact: ykasczc@gmail.com
// Using keras2cpp library by gosha20777: https://github.com/gosha20777/keras2cpp
// MIT Lincese

#include "KerasModel.h"
#include "Misc/Paths.h"
#include "keras2cpp/model.h"
#include <string>
#include <vector>

using keras2cpp::Model;
using keras2cpp::Tensor;

void FKerasTensor::GetSize(TArray<int32>& Size) const
{
	Size.SetNumUninitialized(data.dims_.size());

	for (int i = 0; i < Size.Num(); i++)
	{
		Size[i] = data.dims_[i];
	}
	FMemory::Memcpy(Size.GetData(), data.dims_.data(), sizeof(size_t) * Size.Num());
}

void FKerasTensor::Resize(const TArray<int32>& Dims)
{
	switch (Dims.Num())
	{
		case 1: data.resize(Dims[0]); break;
		case 2: data.resize(Dims[0], Dims[1]); break;
		case 3: data.resize(Dims[0], Dims[1], Dims[2]); break;
		case 4: data.resize(Dims[0], Dims[1], Dims[2], Dims[3]); break;
	}
	InitAddressMultipliersCache();
}

void FKerasTensor::SetFromArray(const TArray<float>& InData)
{
	if (InData.Num() != data.size())
	{
		data.resize(InData.Num());
		InitAddressMultipliersCache();
	}
	FMemory::Memcpy(data.data_.data(), InData.GetData(), sizeof(float) * InData.Num());
}

void FKerasTensor::GetAsFlatArray(TArray<float>& OutData) const
{
	OutData.SetNumUninitialized(data.data_.size());
	FMemory::Memcpy(OutData.GetData(), data.data_.data(), sizeof(float) * data.data_.size());
}

void FKerasTensor::FromFile(FString FileName)
{
	std::string szFileName = TCHAR_TO_ANSI(*FileName);
	data = Tensor(keras2cpp::Stream(szFileName));
	InitAddressMultipliersCache();
}

void FKerasTensor::InitAddressMultipliersCache()
{
	int32 CurrVal = 1;
	int32 Last = data.dims_.size() - 1;
	if (Last < 0) return;

	AddressMultipliersCache.SetNumUninitialized(Last + 1);
	AddressMultipliersCache[Last] = 1;
	for (int32 Dim = Last - 1; Dim != INDEX_NONE; Dim--)
	{
		CurrVal *= data.dims_[Dim + 1];
		AddressMultipliersCache[Dim] = CurrVal;
	}
}

int32 FKerasTensor::GetAddress(TArray<int32> Address) const
{
	int32 Addr = 0;
	int32 DataSize = data.data_.size();

	for (int32 i = 0; i < AddressMultipliersCache.Num(); i++)
	{
		int32 n = Address.IsValidIndex(i) ? Address[i] : 0;
		Addr += AddressMultipliersCache[i] * n;

		if (Addr >= DataSize)
		{
			return INDEX_NONE;
		}
	}

	return Addr;
}

void FKerasTensor::SetValueByAddress(const TArray<int32>& Address, float NewValue)
{
	int32 addr = GetAddress(Address);
	if (addr != INDEX_NONE && addr < data.data_.size())
	{
		data.data_[addr] = NewValue;
	}
}

float FKerasTensor::GetValueByAddress(const TArray<int32>& Address) const
{
	int32 addr = GetAddress(Address);
	if (addr != INDEX_NONE && addr < data.data_.size())
	{
		return data.data_[addr];
	}

	return 0.f;
}

// **********************************************************************************************

UKerasModel::UKerasModel()
	: KerasModel(nullptr)
	, bLoaded(false)
	, EvaluateDuration(0.)
{}

void UKerasModel::BeginDestroy()
{
	Super::BeginDestroy();

	if (KerasModel)
	{
		delete KerasModel;
		bLoaded = false;
	}
}

bool UKerasModel::LoadFromFile(FString FileName)
{
	if (FPaths::FileExists(FileName))
	{
		std::string szFileName = TCHAR_TO_ANSI(*FileName);
		KerasModel = new keras2cpp::Model(Model::load(szFileName));
		bLoaded = true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't find keras model file %s"), *FileName);
		KerasModel = nullptr;
		bLoaded = false;
	}
	return bLoaded;
}

void UKerasModel::Evaluate(const FKerasTensor& InputData, FKerasTensor& OutputData)
{
	if (bLoaded)
	{
		double t_before = FPlatformTime::Seconds();
		OutputData = (*KerasModel)(InputData.data);
		double t_after = FPlatformTime::Seconds();

		EvaluateDuration = (t_after - t_before) * 1000.;
	}
	else
	{
		EvaluateDuration = -1.;
	}
}
