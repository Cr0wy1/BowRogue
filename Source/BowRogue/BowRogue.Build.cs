// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BowRogue : ModuleRules
{
	public BowRogue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ApexDestruction", "Niagara" });

        PublicIncludePaths.AddRange(new string[] {
            "D:/Programs/Unreal Engine/UE_4.23/Engine/Plugins/FX/Niagara/Source/Niagara/Public"
            //Path.Combine(ModuleDirectory, "Niagara")
        });
    }
}
