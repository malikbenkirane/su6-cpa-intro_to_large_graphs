# files cleaned locally

*total size 2.1G without the friendster graph that is about 31G*

```
for (f in `{ls assets/*txt}) {
	echo $f
	time ./clean.sh <$f >assets/clean/`{basename $f}
}
```

```
assets/com-amazon.ungraph.txt
        4.04 real         5.29 user         0.12 sys
assets/email-Eu-core.txt
        0.23 real         0.25 user         0.01 sys
assets/com-lj.ungraph.txt
      309.42 real       320.66 user        34.70 sys
assets/test_clean.txt
        0.01 real         0.00 user         0.01 sys
assets/com-orkut.ungraph.txt
     1055.24 real      1123.98 user        93.73 sys
```


# special quantity (file read twice)

|graph code name|time  |file size|quantity       |#nodes  |#links    |
|---------------|-----:|--------:|--------------:|-------:|---------:|
|EMAIL          |0.02s |118.4K   |88109182       |986     |16064     |
|AMAZON         |0.33s |12M      |103415531      |334863  |925872    |
|LJ             |26.42s|478.32M  |789000450609   |3997962 |34681189  |
|ORKUT          |36s   |1.647G   |22292678512329 |3072441 |117185083 |
|FRIENDSTER     |14m48s|30.142G  |379856554324947|65608366|1806067135|
