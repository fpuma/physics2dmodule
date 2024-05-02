namespace Puma
{
    [Sharpmake.Generate]
    class Box2DTest : Puma.SharpmakeBase.IApplication
    {
        public Box2DTest()
            : base("Box2DTest", @"tests\box2dtest")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPublicDependency<Extern.Box2D>(target);
            conf.AddPublicDependency<Puma.Graphics>(target);
            conf.AddPublicDependency<Puma.Utils>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

        }
    }
}