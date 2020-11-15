namespace Puma
{
    [Sharpmake.Generate]
    class PhysicsTests : Puma.Common.IMyApplication
    {
        public PhysicsTests()
            : base("PhysicsTests", @"physicstests")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Puma.Physics>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

        }
    }
}