namespace Puma
{
    [Sharpmake.Generate]
    class Leo : Puma.SharpmakeBase.IStaticLibrary
    {
        public Leo()
            : base("Leo", @"leo")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Extern.Box2D>(target);
            conf.AddPublicDependency<Puma.UtilsLib>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");
            conf.IncludePaths.Add(@"\shared");

            conf.PrecompHeader = @"precompiledphysics.h";
            conf.PrecompSource = @"precompiledphysics.cpp";

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}