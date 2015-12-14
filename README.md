在我的一体机上运行数据（画的图的数据都是一体机上的运行数据）
====
hexin@hexin-Vostro-23-3340:~/workspace/tlb_measure$ ./tlb_bench -r100000 -n8000
# running on CPU 3; pinning to that CPU
# page size is 4096
1	average nanoseconds per access:16
2	average nanoseconds per access:17
4	average nanoseconds per access:16
8	average nanoseconds per access:16
16	average nanoseconds per access:18
32	average nanoseconds per access:18
64	average nanoseconds per access:21
128	average nanoseconds per access:24
256	average nanoseconds per access:24
512	average nanoseconds per access:24
1024	average nanoseconds per access:47
2048	average nanoseconds per access:67
4096	average nanoseconds per access:77
8192	average nanoseconds per access:82

在至强处理器上
----------------------------
[root@aimlab-phi ~]# ./tlb -r100000 -n4096
# running on CPU 2; pinning to that CPU
# page size is 4096
1	average nanoseconds per access:42
2	average nanoseconds per access:42
4	average nanoseconds per access:42
8	average nanoseconds per access:42
16	average nanoseconds per access:45
32	average nanoseconds per access:45
64	average nanoseconds per access:53
128	average nanoseconds per access:63
256	average nanoseconds per access:63
512	average nanoseconds per access:63
1024	average nanoseconds per access:63
2048	average nanoseconds per access:63
4096	average nanoseconds per access:102

在Xeon Phi上
---------------------------
[root@mic0 ~]# ./tlb_bench.mic -r100000 -n2048
# running on CPU 22; pinning to that CPU
# page size is 4096
1	average nanoseconds per access:213
2	average nanoseconds per access:213
4	average nanoseconds per access:213
8	average nanoseconds per access:213
16	average nanoseconds per access:232
32	average nanoseconds per access:232
64	average nanoseconds per access:232
128	average nanoseconds per access:374
256	average nanoseconds per access:560
512	average nanoseconds per access:564
1024	average nanoseconds per access:565
2048	average nanoseconds per access:567

