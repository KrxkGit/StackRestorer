# StackRestorer 堆栈还原器

## 简介

`addr2line` 是一个用于将程序中的地址转换为源代码中的文件名和行号的工具。它通常与调试信息一起使用，帮助开发者在调试时快速定位代码中的问题。利用 `addr2line` 可以实现堆栈的还原（如果符号表存在），但当面对分析大量的堆栈日志场景时，直接使用 `addr2line` 效率比较低，需要手动提取堆栈地址和可执行文件路径，比较麻烦。

本工具将地址提取、可执行文件文件名提取功能进行封装，简化操作。

## 覆盖场景

目前已覆盖的场景是 *Android Studio* 中输出的堆栈日志，其他场景的堆栈日志格式尚未经过测试，可能存在格式提取不兼容问题。

## 构建

### 前置条件

- 本项目采用 Visual Studio 2022 IDE 完成构建。
- 构建环境为 Windows，依赖于 [win_flex_bison](https://sourceforge.net/projects/winflexbison/) 。使用 Visual Studio 构建前请根据 [win_flex_bison](https://sourceforge.net/projects/winflexbison/) 文档在 Visual Studio 项目中添加 **生成自定义** 选项。（本项目已附带）
- 添加 **生成自定义** 选项完成后可利用 Visual Studio IDE 完成一键构建。（本项目已配置）

### 构建方法

完成前置条件后利用 Visual Studio 进行一键构建即可。

## 使用用法

### 前置依赖

- 需要安装 `addr2line` 工具并添加到 `PATH` 环境变量中。
- 准备好堆栈日志。格式示例如下：

```
2024-11-28 12:10:43.673 22710-22710 DEBUG            crash_dump64                          A        #04 pc 000000000002ff98  /data/app/~~RK1DGEzRXCGlUg6qlHb6pA==/com.krxk.test-nCIE4O1daFONAFgwBv_fpQ==/base.apk!libcares.so (offset 0xc000) (BuildId: 63f7662ff83c7c78eda3ac8d69a534de7aba74c0)
2024-11-28 12:10:43.673 22710-22710 DEBUG            crash_dump64                          A        #05 pc 000000000002e0bc  /data/app/~~RK1DGEzRXCGlUg6qlHb6pA==/com.krxk.test-nCIE4O1daFONAFgwBv_fpQ==/base.apk!libcares.so (offset 0xc000) (BuildId: 63f7662ff83c7c78eda3ac8d69a534de7aba74c0)
```

### 核心命令

```bat
用法: StackRestorer.exe [-h|-v] [-i 输入文件] [-I 可执行文件包含目录]
选项:
  -h, --help    显示帮助信息
  -v, --version 显示版本信息
  -i, --input   指定输入文件
  -I, --include 指定可执行文件包含目录

```

> - 注意：在当前版本 （v1.0）中，需要手动将可执行文件(如示例中的 `libcares.so` )手动复制到程序当前所在路径。
> - v1.1 已新增指定单个可执行文件包含目录的选项。

> 另外，程序也可以从标准命令输入接收日志，可结合 `<`、`>` 重定向符使用。