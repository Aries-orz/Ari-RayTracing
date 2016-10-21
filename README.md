
This is a global illumination renderer via unbiased Monte Carlo ray tracing, and was written based on the program smallpt. It can read and process .obj format file.

## Introduction
这是一个基于无偏差蒙特卡洛光线追踪的全局光照渲染器，部分代码参考smallpt实现。它能直接读取并处理.obj后缀格式的标准模型文件，并进行渲染。

## Features

* BRDF模型，以及蒙特卡洛Path tacing
* 能渲染标准模型，如平面，球体，长方体
* 能读入标准obj模型文件，并进行处理和渲染
* 使用包围盒，以及OpenMP技术来进行加速
* 良好的扩展性

## Usage
直接修改Demo.cpp或自己编写对应的代码文件，往Scene对象中加入各个模型，即可自定义构建场景，并进行全局光照渲染。

* Linux环境下，在Makefile所在目录直接make即可；
* Mac OS环境下，修改Makefile文件，注释掉与OpenMP相关的命令（Apple Clang暂不支持OpenMP），再make即可；
* Windows环境下，即可通过Makefile来编译链接，也可通过将源代码导入IDE然后自己配制编译链接参数（主要是加入OpenMP相关库和命令）来完成。

test_data文件夹中有一些从网上下载的obj模型文件。程序执行方式为：

    $ ./AriesRT [spp]

其中spp（samples per pixel）指每个像素点的取样数，缺省值为4。

## Demo
下图为Demo.cpp运行得到的结果（注：最终生成结果为ppm格式图片，在Linux中可直接查看，Windows下可用PS打开或用在线转换工具转成jpg格式）。其中该Demo所使用的运行环境为：

* CPU：i7-4770K，主频3.5GHz，四核八线程
* 参数：5000 （每次采样取5000/4=1250条样本光线）
* 运行时间：14小时左右
![pic](http://aries-orz.com/blog/wp-content/uploads/2016/07/result.jpg)

