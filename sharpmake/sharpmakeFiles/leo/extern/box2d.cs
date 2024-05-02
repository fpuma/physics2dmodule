namespace Extern
{
    [Sharpmake.Generate]
    class Box2D : Puma.SharpmakeBase.IStaticLibrary
    {
        public Box2D()
            : base("Box2D", @"submodules\box2d")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.SourceFilesBuildExcludeRegex.Add("glad");
            conf.SourceFilesBuildExcludeRegex.Add("glfw");
            conf.SourceFilesBuildExcludeRegex.Add("imgui");
            conf.SourceFilesBuildExcludeRegex.Add("sajson");
            conf.SourceFilesBuildExcludeRegex.Add("testbed");
            conf.SourceFilesBuildExcludeRegex.Add("unit-test");

            conf.IncludePrivatePaths.Add(SourceRootPath + @"\src");
            conf.IncludePaths.Add(SourceRootPath + @"\include");

            conf.SolutionFolder = "Extern";
        }
    }
}