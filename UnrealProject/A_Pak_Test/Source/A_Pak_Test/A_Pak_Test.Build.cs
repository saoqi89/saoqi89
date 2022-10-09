// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class A_Pak_Test : ModuleRules
{
	public A_Pak_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "PakFile", "UMG" });
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"ImageWrapper",
				// ... add private dependencies that you statically link with here ...	
			}
		);

	}
}
