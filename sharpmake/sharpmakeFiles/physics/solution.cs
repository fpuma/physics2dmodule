using System.IO;

namespace Puma
{
    [Sharpmake.Generate]
    public class PhysicsSolution : Puma.Common.IMySolution
    {
        public PhysicsSolution()
            : base("Physics")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Puma.Physics>( target );
            conf.AddProject<Puma.PhysicsTests>( target );
        }
    }


    [Sharpmake.Generate]
    public class ExternSolution : Puma.Common.IMySolution
    {
        public ExternSolution()
            : base("ExternLibs")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Extern.Box2D>(target);
        }
    }

}