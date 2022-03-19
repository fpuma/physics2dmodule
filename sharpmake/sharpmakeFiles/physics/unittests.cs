namespace Puma
{
    [Sharpmake.Generate]
    class UnitTests : Puma.Common.IMyApplication
    {
        public UnitTests()
            : base("UnitTests", @"unittests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Leo>(target);
            conf.AddPublicDependency<Puma.GoogleTest>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            if(target.Optimization != Sharpmake.Optimization.Debug)
            {
                conf.IsExcludedFromBuild = true;
            }
        }
    }
}