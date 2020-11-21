namespace Puma
{
    [Sharpmake.Export]
    class Graphics : Puma.Common.IExternBinaries
    {
        public Graphics()
            : base("Utils", @"graphics")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\bin");
            
            if(target.Optimization == Sharpmake.Optimization.Debug)
            {
                conf.LibraryFiles.Add("graphics_d.lib"); 
                conf.LibraryFiles.Add("sdlgfx_d.lib");
                conf.LibraryFiles.Add("utils_d.lib");
            }
            else
            {
                conf.LibraryFiles.Add("graphics_r.lib");
                conf.LibraryFiles.Add("sdlgfx_r.lib");
                conf.LibraryFiles.Add("utils_r.lib");
            }

            conf.LibraryFiles.Add("SDL2.lib");
            conf.LibraryFiles.Add("SDL2_image.lib");
            conf.LibraryFiles.Add("SDL2_ttf.lib");
            conf.LibraryFiles.Add("SDL2main.lib");

            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\libfreetype-6.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\libjpeg-9.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\libpng16-16.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\libtiff-5.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\libwebp-7.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\SDL2.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\SDL2_image.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\SDL2_ttf.dll");
            conf.TargetCopyFiles.Add(SourceRootPath + @"\bin\zlib1.dll");
        }
    }
}