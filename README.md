# GalvoScannerCorrect

Galvo scanner correct.
校正振镜算法。

## 补偿原理

振镜由于计算上的问题存在二次曲线的误差，又根据实际安装误差，可能存在平行四边形和梯形的误差。根据相关振镜论文，及参考jcz的相关标定方法，得到此算法。

## 编译执行

### 所需环境

- [visual studio](https://visualstudio.microsoft.com/)
- [gnuplot](http://www.gnuplot.info/)

### 执行

打开工程后编译执行，执行完成后，打开`output`下的`*.plt`文件即可看到各种补偿执行后的结果。

## LICENSE

MIT.