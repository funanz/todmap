## An example of the map generation algorithm for "The Tower of Druaga"<br>「ドルアーガの塔」マップ生成アルゴリズムの例

    $ make
    $ ./todmap --ac 1 --fc 1
    $ ./todmap --progress --ac 1 --fc 1
    $ ./todmap --ac `seq 1 60`
    $ ./todmap --fc `seq 1 60`

## Usage: todmap [options]... &lt;floor number&gt;...

|Option|Description|
|---|---|
|-a, --ac|Generated in the arcade version|
|-f, --fc|Generated in the FC (NES) version|
|-p, --progress|Show progress|
|-P, --no-progress|Don't show progress|
|&lt;floor number&gt;|Floor number (1-60)|

## Reference
- http://rdev.php.xdomain.jp/makimura/archive/family-basic/druaga-map-viewer
- http://cockatrice.blog111.fc2.com/blog-entry-482.html
