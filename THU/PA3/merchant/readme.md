# SPOC2020 3-1-2 Merchant

## Solution

拓扑排序+拓扑序上DP求一个有向无环图(DAG)的关键路径(最长的路径).

由于对输出路径序列的字典序有要求，所以采用反向拓扑(反向建图)来保证字典序。(用正向的只能保证找到关键路径，但保证不了字典序最小)

## 说明

两道题的代码文件放在一起写了。`merchant1.cpp`为第一道题，`merchant2.cpp`为第二道题。文件名末尾带有`_wa`标记的为错误的中间版本。

`test2-1.in`为本人构造的一些特殊情况的测试数据，调试时需手动粘贴进控制台。(之前正向建图拓扑一直WA，为了搞清楚原因构造了好多组可能卡掉的情况)