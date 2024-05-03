namespace Puma
{
    [Sharpmake.Generate]
    class UnitTests : Puma.SharpmakeBase.IApplication
    {
        public UnitTests()
            : base("UnitTests", @"tests\unittests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Leo>(target);
            conf.AddPublicDependency<Puma.GoogleTest>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Tests";
        }
    }
}