<!--
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-04-07 16:00:11
 * @LastEditTime: 2025-06-05 13:33:59
-->
# 单目相机标定方法从理论到实践

> 帮助文档：
>
> 1. [单目相机成像原理.pdf](https://github.com/SHU-FLYMAN/CalibCamera/blob/master/docs/01%20%E7%90%86%E8%AE%BA%E9%83%A8%E5%88%86%EF%BC%9A%E5%8D%95%E7%9B%AE%E6%88%90%E5%83%8F%E8%BF%87%E7%A8%8B.pdf)
> 2. [程序帮助文档.pdf](https://github.com/SHU-FLYMAN/CalibCamera/blob/master/docs/02%20%E5%AE%9E%E8%B7%B5%E9%83%A8%E5%88%86%EF%BC%9A%E5%BC%A0%E6%AD%A3%E5%8F%8B%E6%A0%87%E5%AE%9A%E6%B3%95%20-%20OpenCV%E5%AE%9E%E7%8E%B0.pdf)
>


基于张正友标定发的单目相机标定具体步骤如下：

1. 准备标定图片（不同位置、角度、姿态下拍摄，至少需要3张，以10~20张为宜）
2. 对每一张标定图片，提取角点信息，并进行亚像素角点优化（绘制相应图像）
3. 调用张正友标定方法，对相机进标定，也就是计算内参和畸变系数
4. 对标定结果进行评价（重投影误差）
5. 利用标定结果（内参、畸变系数），对任何输入的图像进行矫正



## 使用方法


1. 修改相应的配置
   - `config.yaml`
2. 运行构建
   - `./build.sh`
3. 执行
   - `./CalibCamera ./config.yaml `


<img src="https://flyman-cjb.oss-cn-hangzhou.aliyuncs.com/picgos/20200806163018.png" width="宽度" height="高度" alt="图片名称" align=center>



## 基础知识（简要回顾）

简要的原理回顾如下：相机模型如下，主要包含四个坐标系：

<img src="https://img2018.cnblogs.com/blog/1516317/201902/1516317-20190219150222035-99963244.png" alt="img" style="zoom: 67%;" />

四个坐标系的转换关系如下：

<img src="https://flyman-cjb.oss-cn-hangzhou.aliyuncs.com/picgos/20200604162350.png" width="宽度" height="高度" alt="图片名称" align=center style="zoom:67%;" >

而我们主要关心的是从世界坐标系到像素坐标系的变换，它们的公式如下：

<img src="https://flyman-cjb.oss-cn-hangzhou.aliyuncs.com/picgos/20200806162243.png" width="宽度" height="高度" alt="图片名称" align=center>

而相机成像过程中存在着径向畸变和切向畸变，合并后：

<img src="https://flyman-cjb.oss-cn-hangzhou.aliyuncs.com/picgos/20200806162329.png" width="宽度" height="高度" alt="图片名称" align=center>

可以通过张正友标定法得到相机的**畸变系数**，除此之外还有它的**内参**。获得了这两个参数，我们就能对相机的整个成像过程建立较为准确的映射关系（至少是单向的）。

