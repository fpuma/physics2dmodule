using System.IO;

namespace Puma
{
    [Sharpmake.Generate]
    public class LeoSolution : Puma.SharpmakeBase.ISolution
    {
        public LeoSolution()
            : base("leo")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Puma.PhysicsTests>( target );
            conf.AddProject<Puma.Leo>( target );
            conf.AddProject<Puma.Box2DTest>(target);
            conf.AddProject<Puma.UnitTests>(target);
            conf.AddProject<Extern.Box2D>(target);
        }
    }
}