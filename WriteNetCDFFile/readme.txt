1、我们需要用的是config.h文件和cxx文件夹中的ncvalues.h，ncvalues.cpp，netcdf.cpp和netcdfcpp.h这五个文件；
2、将这五个文件添加到你的工程目录下即可，分别添加到工程头文件和源文件中，在VS项目属性——VC++目录——包含目录,添加config.h,netcdfcpp.h和ncvalues.h头文件所在的位置即可。
3、将netcdf的c语言的头文件netcdf.h,动态链接库netcdf.dll和库文件netcdf.lib添加到VS2010中。
如何添加动态链接库：
a.将netcdf的c语言版本的include，lib和bin文件添加到工程目录下；
b.VS中项目属性——链接器——常规——附加库目录，这里添加你的bin文件中的netcdf.dll路径；
c.VS中项目属性——链接器——输入——附加依赖项，这里添加netcdf.lib库文件；
d.VS中项目属性——VC++目录——包含目录，添加netcdf.h头文件的位置；
e.VS中项目属性——VC++目录——库目录，添加netcdf.lib库文件的位置。

