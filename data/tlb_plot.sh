#!/usr/bin/env gnuplot
# set terminal postscript eps monochrome 'Helvetica' 20
set terminal postscript eps color solid linewidth 2 "Helvetica" 20
set style data linespoints
set ylabel 'Time per Access (ns)' font 'Helvetica,20'
set xlabel 'Number Of Pages' font 'Helvetica,20'
set pointsize 2
set key top left
set key width -2
# set ytic auto
set ytics 0,20,80
set yrange[0:*]
set xrange[1:4096]
set logscale x
# set xtics 1,16,228
# set xtics ("1" 1, "2" 2, "4" 4, "8" 8, "16" 16, "32" 32, "64" 64, "128" 128, "256" 256, "512" 512, "1024" 1024, "2048" 2048, "4096" 4096)
set xtics ("1" 1, "4" 4, "16" 16, "64" 64, "256" 256, "1024" 1024, "4096" 4096)
set title "TLB SIze Measurement"
# set xtics 4

# glyphs (the 'pt' parameter)
# 1 is plus
# 2 is x
# 3 is star
# 4 is empty square
# 5 is filled square
# 6 is empty circle
# 7 is filled circle
# 8 is empty up triangle
# 9 is filled up triangle
# 10 is empty down triangle
# 11 is full down triangle
# 12 is empty diamond
# 13 is full diamond
# 14 is empty pentagon
# 15 is full pentagon
# ofile=$alg."l$lock".csv
# locks=(1 16 256 4096 16384)
# algs=(ARRAY CLH MCS MUTEX TAS TICKET TTAS)
set output 'tlb.eps'
plot \
    'tlb_data.csv'                 u 1:($2) pt 7 lw 1.5 t ''