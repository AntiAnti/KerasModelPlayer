// Created by YuriNK. Contact: ykasczc@gmail.com
// Using keras2cpp library by gosha20777: https://github.com/gosha20777/keras2cpp
// MIT Lincese

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FKerasModelPlayerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
