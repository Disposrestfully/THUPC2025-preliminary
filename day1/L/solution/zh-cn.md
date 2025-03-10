题目很明显是一个最小割问题。对于题目描述中的“通知一个分部，在其所有下辖的铁路上设立检查站”操作，我们需要对如下问题进行网络流建模：给定网络流图以及对其边的划分，一次可以以 $1$ 的代价割掉一个划分集合中的所有边。特别地，在同一个划分集合中的所有边都与某个点相邻。

考虑某个形如 $A_i \to x_i \to B_i$ 的划分集合，其中 $A_i$ 和 $B_i$ 为任意点集。考虑如下建模：

- 建立虚点 $p_i, q_i$；
- 有边 $(p_i,q_i,1)$、$(A_i, p_i, 1)$、$(x_i, p_i, 1)$、$(q_i,x_i,1)$、$(q_i,B_i,1)$。

注意到在这个建模中，若所有边都不被割掉，其连通关系恰好为 $A_i \to x \to B_i$，而割掉 $p_i \to q_i$ 之后这个连通关系就消失了，符合我们的需求。

再注意到网络流图上的所有边边权均为 1，直接运行 dinic 算法求解最大流的复杂度为 $O(n \sqrt{m})$，足以通过本题。
