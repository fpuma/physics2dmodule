namespace Puma
{
    [Sharpmake.Generate]
    class UtilsLib : Puma.SharpmakeBase.IHeaderOnly
    {
        public UtilsLib()
            : base("Utils", @"submodules\utils\source\utils")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");

            conf.SolutionFolder = "Extern";
        }
    }
}