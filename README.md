Figure 1:Discovering TLB SIzes and Miss Costs
====
![Aaron Swartz](https://github.com/sayounara/tlb_measure/raw/master/data/tlb_bench.png)<br>
###从图中可以看出，当访问比较少的页数（低于64），平均访问时间大约是17纳秒。但访问64个页或者更多的时候，平均访问时间上升到大约26纳秒。当访问的页超出512或者更多，最终上升到大约80纳秒(这个时候已经要从内存访问页表啦）。从这些数据中，我们可以推断出这个处理器有一个二级TLB结构；第一级相对比较少（大约能容纳64到128个条目）；第二级TLB相对更大些但访问速度更慢些（能够容纳大约512个条目）。总得来看，在第一级TLB命中和TLB缺失之间的性能差距是相当大的。<br>

在我的一体机上运行数据（画的图的数据都是一体机上的运行数据）
====
hexin@hexin-Vostro-23-3340:~/workspace/tlb_measure$ ./tlb_bench -r100000 -n8000<br>
 running on CPU 3; pinning to that CPU<br>
page size is 4096<br>
1	average nanoseconds per access:16<br>
2	average nanoseconds per access:17<br>
4	average nanoseconds per access:16<br>
8	average nanoseconds per access:16<br>
16	average nanoseconds per access:18<br>
32	average nanoseconds per access:18<br>
64	average nanoseconds per access:21<br>
128	average nanoseconds per access:24<br>
256	average nanoseconds per access:24<br>
512	average nanoseconds per access:24<br>
1024	average nanoseconds per access:47<br>
2048	average nanoseconds per access:67<br>
4096	average nanoseconds per access:77<br>
8192	average nanoseconds per access:82<br>

一体机上的TLB信息
====
hexin@hexin-Vostro-23-3340:~/lock_bench/scripts$ x86info -c<br>
x86info v1.30.  Dave Jones 2001-2011<br>
Feedback to <davej@redhat.com>.<br>
<br>
Found 4 identical CPUs<br>
Extended Family: 0 Extended Model: 3 Family: 6 Model: 60 Stepping: 3<br>
Type: 0 (Original OEM)<br>
CPU Model (x86info's best guess): Unknown model. <br>
Processor name string (BIOS programmed): Intel(R) Core(TM) i3-4160 CPU @ 3.60GHz<br>

Cache info<br>
TLB info<br>
 Data TLB: 4KB pages, 4-way associative, 64 entries<br>
 Data TLB: 4KB pages, 4-way associative, 64 entries<br>
 64 byte prefetching.<br>
Found unknown cache descriptors: 63 76 b5 c1 ff <br>
Total processor threads: 4<br>
This system has 1 dual-core processor with hyper-threading (2 threads per core) running at an estimated 3.60GHz<br>

在至强处理器上
----------------------------
[root@aimlab-phi ~]# ./tlb -r100000 -n4096<br>
running on CPU 2; pinning to that CPU<br>
page size is 4096<br>
1	average nanoseconds per access:42<br>
2	average nanoseconds per access:42<br>
4	average nanoseconds per access:42<br>
8	average nanoseconds per access:42<br>
16	average nanoseconds per access:45<br>
32	average nanoseconds per access:45<br>
64	average nanoseconds per access:53<br>
128	average nanoseconds per access:63<br>
256	average nanoseconds per access:63<br>
512	average nanoseconds per access:63<br>
1024	average nanoseconds per access:63<br>
2048	average nanoseconds per access:63<br>
4096	average nanoseconds per access:102<br>

在Xeon Phi上
---------------------------
[root@mic0 ~]# ./tlb_bench.mic -r100000 -n2048<br>
running on CPU 22; pinning to that CPU<br>
page size is 4096<br>
1	average nanoseconds per access:213<br>
2	average nanoseconds per access:213<br>
4	average nanoseconds per access:213<br>
8	average nanoseconds per access:213<br>
16	average nanoseconds per access:232<br>
32	average nanoseconds per access:232<br>
64	average nanoseconds per access:232<br>
128	average nanoseconds per access:374<br>
256	average nanoseconds per access:560<br>
512	average nanoseconds per access:564<br>
1024	average nanoseconds per access:565<br>
2048	average nanoseconds per access:567<br>

