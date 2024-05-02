using System.IO;

[module: Sharpmake.Include(@"..\..\sharpmakeutils\utils\*")]

[module: Sharpmake.Include(@"..\leo\physics\*")]
[module: Sharpmake.Include(@"..\leo\extern\*")]

public static class SharpmakeMainClass
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments sharpmakeArgs)
    {
        sharpmakeArgs.Generate<Puma.LeoSolution>();
    }
}

