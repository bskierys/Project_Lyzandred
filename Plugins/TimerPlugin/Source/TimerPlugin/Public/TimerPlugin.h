// Created by Bartłomiej Kierys

#pragma once

#include "Modules/ModuleManager.h"

class FTimerPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
