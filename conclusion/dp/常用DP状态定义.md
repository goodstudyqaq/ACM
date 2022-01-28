# 常用 DP 状态定义
- 注：本文译自：[https://apps.topcoder.com/forums/?module=Thread&threadID=697369&start=0](https://apps.topcoder.com/forums/?module=Thread&threadID=697369&start=0)

# 问题

解决 DP 问题时最具有创造力的部分就是在定义循环关系，循环关系包括两部分：状态域和转移方程。在 DP 中，状态域是指状态的集合。对于所有状态它们的结果都会被计算。转移方程是指不同状态之间的关系，即通过这个关系可以根据前继状态计算出当前状态的结果。

下面会介绍几类常用的 DP 状态定义，一些通用的实现和例子也会给出，当然针对部分特殊类型的状态的优化也会被提及。

# 方案

DP 的结果通常是用数组去存储的，[背包问题](https://en.wikipedia.org/wiki/Knapsack_problem#0-1_knapsack_problem)的解决方案就是如此：

```cpp

  int maxcost[items+1][space+1];
  memset(maxcost, -63, sizeof(maxcost));   //用负无穷大作为初始值来填充数组
  maxcost[0][0] = 0;                       //DP 的初始值
  for (int i = 0; i<items; i++)            //以正确的顺序迭代状态
    for (int j = 0; j<=space; j++) {
      int mc = maxcost[i][j];              //我们将处理两种类型的转换
      int ni, nj, nmc;                     //从状态 (i,j)->mc 到状态 (ni,nj)->nmc
 
      ni = i + 1;                          //刷表法转移: 不加当前第 i 项
      nj = j;
      nmc = mc;      
      if (maxcost[ni][nj] < nmc)           //松弛新状态的结果
        maxcost[ni][nj] = nmc;
 
      ni = i + 1;                          //刷表法转移: 加当前第 i 项
      nj = j + size[i];
      nmc = mc + cost[i];
      if (nj <= space && maxcost[ni][nj] < nmc)
        maxcost[ni][nj] = nmc;
    }
  int answer = -1000000000;                //得到结果
  for (j = 0; j<=space; j++)
    if (maxcost[items][j] > answer)
      answer = maxcost[items][j];
  return answer;
```

这里 (i, j) 的结果等于 maxcost[i][j]，结果的含义为考虑前 i 个物品时，使用的 size 大小为 j 时能得到的最大的价值。所以这里 (i, j) 的集合以及 maxcost 的概念组成了状态域。而转移则是加不加当前第 i 个物品。

遍历 DP 状态的顺序十分重要。上面的代码是根据递增的顺序去遍历(i, j)，因为所有的状态都是从 (i, *) 到 (i + 1, *)，所以只要 i 递增即可，对于填表法来说，所有状态 (i, j) 都依赖 (i - 1, *)。

要确定遍历状态的顺序，我们必须要在状态域上定义顺序。如果状态 (i1, j1) 直接或者间接(即通过其他几个状态) 依赖于状态 (i2, j2)，那么可以说状态 (i1, j1) 大于状态 (i2, j2)。这是状态域上的顺序定义。在所有 DP 中，任何状态一定要在比它小的状态之后考虑，否则就会有问题。

## 多维数组

上面说的背包问题就是多维数组状态域的一个例子(2维)。有许多问题都有着相似的状态域。一般来说，在这个类别中，状态由 k 个参数表示: (i1, i2, i3, ..., ik)，那么代码中的状态就要用多维数组去表示：$Result[N1][N2][N3]...[Nk]$。当然状态之间有一些转移关系，这些转移关系可能很复杂，但是状态的顺序通常很简单。

大多数情况下遍历状态的顺序都是字典序递增的，你要保证如果有状态 l = (i1, i2, i3, ..., ik) 直接依赖于状态 J =(j1, j2, j3, ..., jk) 那么有 l 的字典序大于 J。这个可以通过置换参数(比如用 (j, i) 而不是 (i, j))来实现，但是更换遍历的顺序通常更容易，下面是按照字典序遍历的一般代码。

```cpp
for (int i1 = 0; i1<N1; i1++)
    for (int i2 = 0; i2<N1; i2++)
      ...
        for (int ik = 0; ik<Nk; ik++) {
          //get some states (j1, j2, j3, ..., jk) -> jres by performing transitions
          //and handle them
        }
```

注意：由于 CPU 的缓存行为，更改数组中 DP 参数的顺序和嵌套循环会显著影响现代计算机的性能。

这种类型的状态很好理解也很好实现，这也是为什么教程的问题都是这种类型的状态。但这不是 SRM 中最常用的状态域类型，subset 更加流行。

## 集合的子集【状压DP】

这个问题的类型是有一个集合 X，这个集合的个数很小，不超过 20 个，这类 DP 常用 X 的子集作为状态域。通常来说它还有其他的额外参数，所以它的状态域可以被描述为 (s, a) ，s 是 X 的子集，a 是其他的参数。

考虑 [TSP](https://en.wikipedia.org/wiki/Travelling_salesman_problem) 问题，这里有城市集合 X = {0, 1, 2, ..., N - 1}。状态域有两个参数 s 和 a。(s, a) → R 表示从 0 到城市 a，图中经过的城市集合为 s 的最短路是 R。这个转移很简单，就是加一个额外的城市到最后，即 (s, a) → R 变成 (s + {v}, v) → R + M[a, v]。M[i, j] 表示从 i 到 j 的距离。任何哈密顿环就是经过每个点恰好一次再加上最后点到初始点的边形成一个环。所以 TSP 问题的解就等于 min(R[X, a] + M[a, 0])。

用二进制数很容易表示子集。可以看这篇文章了解更多的解释：[Representing sets with bitfields](https://apps.topcoder.com/forums/?module=Thread&threadID=671561&start=0)

这种 DP 通常按照集合包含来进行排序，使用刷表法的话，就是向当前子集中添加一些不在子集里的元素，所以当且仅当 t 是 s 的子集时，(s, a) 才会依赖 (t, b)。如果状态域的顺序是这样的话，那么我们就可以按照字典序去进行遍历，因为子集通常表示成一个二进制数，我们可以通过遍历 0 到 2^N - 1来遍历所有的子集，比如 TSP 问题的代码就长这样：

```cpp
  int res[1<<N][N];
  memset(res, 63, sizeof(res));       //用无穷大来填充 res
  res[1<<0][0] = 0;                   //初始化初始状态
 
  for (int s = 0; s < (1<<N); s++)    //以字典序遍历所有子集
    for (int a = 0; a < N; a++) {
      int r = res[s][a];
      for (int v = 0; v < N; v++) {   //遍历所有的城市,找到还没有访问的城市
        if (s & (1<<v)) continue;     
        int ns = s | (1<<v);          //进行转移
        int na = v;
        int nr = r + matr[a][v];      //转移后的结果
        if (res[ns][na] > nr)         //松弛
          res[ns][na] = nr;
      }
    }
  int answer = 1000000000;            //得到结果
  for (int a = 0; a < N; a++)
    answer = min(answer, res[(1<<N)-1][a] + matr[a][0]);
```

对于集合 s 来说，通常我们需要遍历 s 的所有子集，暴力实现的时间复杂度为 O(4^N) ，但它很容易优化成 O(3^N)。请阅读 [Iterating Over All Subsets of a Set](https://apps.topcoder.com/forums/?module=Thread&threadID=671150&start=0)

## 给定字符串的子串【区间DP】

有一个固定的字符串或者固定的线段，根据题目的定义，它可以被拆成两部分，每一部分又可以被拆成两部分，直到我们得到单位长度的字符串，通过这种做法，我们可以实现一些东西。

在它的状态中，通常有两个特别的参数 L 和 R，表示子串的左右下标，还有其他的额外参数，我们将它表示为 a。所以它的状态可以定义为 (L, R, a)。为了计算每个状态的解，通常方法是将子串分成两部分去考虑。所以遍历状态的顺序是根据子串长度去遍历，下面是一个子串 DP 的例子：

```cpp
  res[N+1][N+1];                          //[L, R] -> res
  for (int s = 0; s<=N; s++)              //遍历子串的长度
    for (int L = 0; L+s<=N; L++) {        //遍历左下标
      int R = L + s;                      //得到右下标
      if (s <= 1) {                       
        res[L][R] = DPBase(L, R);         //DP 的初始值
        continue;
      }
      tres = ???;                          
      for (int M = L+1; M<=R-1; M++)      //遍历所有的中间位置
        tres = DPInduction(tres, res[L][M], res[M][R]);
      res[L][R] = tres;
    }
  answer = DPAnswer(res[0][N]);
```

## 有根树的子树【树形DP】

问题涉及一个有根树，一般情况下图和边的方向已经给出，对于所有的子树一些结果可以被计算。因为每个子树都是独一无二的，所以我们可以通过顶点下标来表示子树，每个非叶子节点的结果都是由它的直接子节点的结果推导而来。

DP 的状态通常由 (v, a) 来表示，v 表示这个子树的根，a 是其他的参数。状态顺序是根据节点在树上的顺序有关，因此最简单的办法就是通过从根节点开始 dfs 去遍历整棵树。当 DFS 到达一个点时，它的结果就会被计算，并且存到一个全局变量当中。代码类似于：

```cpp
  bool vis[N];                                  //是否访问过的标记数组
  res[N];                                       //DP 的结果
 
  void DFS(int v) {                             //递归访问 v 的子树
    vis[v] = true;                              //标记当前节点已经访问
    res[v] = ???;                               //初始化结果
    for (int i = 0; i<nbr[v].size(); i++) {     //遍历所有的孩子
      int s = nbr[v][i];                        
      if (!vis[s]) {                            //如果这个点没有遍历，那么它是这个树的子节点
        DFS(s);                                 //递归遍历它的孩子
        res[v] = DPInduction(res[v], res[s]);   //重新计算这个顶点的结果
      }
    }
  }
  ...
  memset(vis, false, sizeof(vis));              //初始化所有结点都没有访问
  DFS(0);                                       //从根节点 0 开始
  answer = DPAnswer(res[0]);                    //得到根 0 的结果
```

有时候这个图不是联通的(比如一个森林)，这种情况下我们可以对每个图都跑一次 DFS，然后再把所有图的根节点的结果根据某种方式进行结合一下，通常简单的就是求和或者求最值，但有时候这个合并问题可能变成另一个 DP 问题。

这个代码十分的简单，因为它没有其他的参数，但通常来说状态域都包括其他的参数，并且转移会变复杂。DPInduction 可能会变成另一种 DP。它的状态域为 (k, a) k 是目前已经考虑过的节点个数，a 是其他额外的参数。

请注意里面的 DP 的存储，如果你解决的是最优解问题并且需要恢复方案，那么你就必须存 DP 的结果，这个时候你就需要一个全局变量 globalres[v, a] 以及一个局部变量 internalres[v, k, a]。

Topcoder 的题目很少需要方案，所以没必要存储局部结果，在下面的代码中局部结果在递归遍历所有的子节点后被初始化，并在 DFS 退出顶点后被丢弃。

```cpp
  bool vis[N];
  gres[N][A];
  intres[N+1][A];
  
  void DFS(int v) {
    vis[v] = true;
 
    vector<int> sons;
    for (int i = 0; i<nbr[v].size(); i++) {    //遍历所有的儿子，并存储他们的下标
      int s = nbr[v][i];
      if (!vis[s]) {
        DFS(s);
        sons.push_back(s);
      }
    }
 
    int SK = sons.size();                      //清空内部结果数组
    for (int k = 0; k<=SK; k++)
      memset(intres[k], ?, sizeof(intres[k]));
 
    for (int a = 0; a<A; a++)                  //对于所有的儿子跑内部 DP
      intres[0][a] = InternalDPBase(v, a);
    for (int k = 0; k<SK; k++)                 //k = 儿子的个数
      for (int a = 0; a<A; a++)                //a = 额外的参数
        for (int b = 0; b<A; b++) {            //b = 儿子正在用的参数
          int na = DPTransition(v, a, b);
          int nres = DPInduction(intres[k][a], gres[sons[k]][b]);
          intres[k+1][na] = DPMerge(intres[k+1][na], nres);
        }
    for (int a = 0; a<A; a++)                  //将内部 DP 的答案复制到顶点的结果
      gres[v][a] = intres[SK][a];
  }
  ...
  memset(vis, false, sizeof(vis));              
  for (int v = 0; v<N; v++) if (!vis[v]) {
    DFS(v);
    ???                                         //处理结果
  }
  ???                                           //得到答案
```

计算树形 DP 的时间复杂度十分重要，举个例子，上面的代码的时间复杂度为 O(N * A ^ 2)，但有些愚蠢的分析说时间复杂度为 O(N^2*A^2)。

令 Ki 表示 i 节点儿子的个数，尽管每个 Ki 可能会大到 N - 1，但它的总和总是等于 N - 1的。这是进行下一步分析的关键点。假设对于第 i 个节点来说，它跑的次数不超过 Ki * t 次，因为每个点只会被 dfs 一次，那么总时间应该为 TC(N) = sum(Ki * t) ≤ N * t。在上述 case 中 t = A ^ 2，所以你会得到 O(N * A ^ 2) 的时间复杂度。

不要在 DFS 的过程中遍历整个图的节点。比如上面那个case，用 memset 来初始化整个 intres 数组会使得复杂度上升，时间复杂度会变成 O(N * A + Ki * A ^ 2) 而不是 O(Ki * A ^ 2)。整体复杂度会变成 O(N^2*A + N*A^2)。

如果要恢复路径的话，你可以用相同的办法去做，但额外需要 O(N*A) 的空间。如果要恢复路径的话，你需要在全局去存储 internalres[v, k, a]。如果你动态开空间的话，那么你可以忽略 k > Ki 的状态，因为 Ki 的和等于 N，所以你会使用 O(N*A) 的空间。

## 分层 DP

这是最难的 DP 类型，它常用于在特殊图中的平铺问题或覆盖问题。比如：计算用多米诺骨牌来平铺一个矩形的方案数(有些格子不能用)，或者放尽可能多的棋子，并保证棋子之间不会相互攻击。

通常来说，这些问题都可以使用状压 DP 来做，并使用一些特殊性质来优化整个 DP。我们必须覆盖/平铺的东西可以分层考虑，即我们尝试逐层考虑并存储每一层的部分解结果。简单的矩形就是只有一行的平板，它的配置为每个格子是否被占用的状态。

状态可以定义为 (k, p)，k 是已经考虑过的层数，p 是每一层的配置。p 是当前尚未处理的层的必要信息。转移方程为从 (k, p) 到 (k + 1, q)，q 是新的配置。每一层的状态转移通常很大，因此他们都通过递归进行迭代，有时候还进行一些剪枝。search 必须找到将部分解决方案增加到下一层的所有方法。

下面的例子是计算用多米诺骨牌完全覆盖给定瓷砖上的空单元的方案。

```cpp
int res[M+1][1<<N];                     
                                        //k = 当前的行数
int k, p, q;                            //p = 第 k 行的状态
bool get(int i) {                       //q = 下一行的状态
  return matr[k][i] == '#'              
      || (p & (1<<i));                  //检查当前行的第 i 个单元格是否被覆盖
}
void Search(int i) {                    //i = 当前行已经处理的单元格数
  if (i == N) {
    add(res[k+1][q], res[k][p]);        //当前行已经处理完，进行转换
    return;
  }
 
  if (get(i)) {                         //如果当前单元格被覆盖，则跳过它
    Search(i+1);
    return;
  }
 
  if (i+1<N && !get(i+1))               //尝试放 (k, i)-(k, i + 1)
    Search(i+2);
 
  if (k+1<M && matr[k+1][i] != '#') {   //尝试放 (k, i)-(k + 1, i)
    q ^= (1<<i);                        //更新下一层的状态
    Search(i+1);
    q ^= (1<<i);
  }
}
...
res[0][0] = 1;                          //DP 的初始值
for (k = 0; k<M; k++)                   //从上到下遍历层
  for (p = 0; p<(1<<N); p++) {          //遍历当前层的状态
    q = 0;                              //初始化下一层的状态
    Search(0);                          //从 0 开始计算
  }
int answer = res[M][0];                 //答案等于最后一层状态为 0 的结果
```

这个时间复杂度不好被计算，因为每个点 i 可能到 i + 1 和 i + 2。单次搜索的复杂度不超过第 N 个斐波那契数列 fib(N)。此外，如果状态 p 只有 F 个空格，那么它就需要 O(fib(F)) 的时间复杂度。如果我们加上所有的 C(N,F)fib(F)，我们能够得到一个近似值 (1 + phi) ^ N ，phi 是黄金比率，整个时间复杂度大约为 O(M * (1 + phi) ^ N)，根据经验，它可能更小。

这个代码不是最优的，大多数分层 DP 都可以只存 2 层状态，此外，状态可以在加一些。可以定义 (k, p, i) 为状态，i 是已经考虑了多少个单元格，由于变成了 DP，所以不需要递归去搜索，那么复杂度就变得更低。

分层 DP 的难点有：

1. 状态可能不止一层，比如用长度为 3 的瓷砖覆盖网格，那么就需要存两层状态。
2. 状态可能很复杂，比如要在网格中找到某种意义上的最佳哈密顿回路，你必须使用匹配括号字符串来作为装填。
3. 状态结构可能不一样，比如每一层的状态都不同，你可以用 map 来存状态。