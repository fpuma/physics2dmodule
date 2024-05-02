namespace Puma
{
    [Sharpmake.Generate]
    class PhysicsTests : Puma.SharpmakeBase.IApplication
    {
        public PhysicsTests()
            : base("PhysicsTests", @"tests\physicstests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Leo>(target);
            conf.AddPublicDependency<Puma.Graphics>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

        }
    }
}