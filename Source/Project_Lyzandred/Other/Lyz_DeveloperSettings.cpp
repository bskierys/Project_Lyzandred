#include "Lyz_DeveloperSettings.h"

#include "SubsystemConfig.h"

USubsystemConfig* ULyz_DeveloperSettings::GetSubsystemConfigByClass(TSubclassOf<USubsystemConfig> ParamClass) const
{
	if (!ParamClass)
	{ 
		return nullptr;
	}

	for (const TSoftObjectPtr<USubsystemConfig>& ConfigRef : SubsystemConfig)
	{
		if (ConfigRef.IsNull()) 
			continue;

		if (USubsystemConfig* LoadedConfig = ConfigRef.LoadSynchronous())
		{
			if (LoadedConfig->IsA(ParamClass)) 
			{
				return LoadedConfig;
			}
		}
	}
	return nullptr;
}
