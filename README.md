## An example of the map generation algorithm for "The Tower of Druaga"<br>「ドルアーガの塔」マップ生成アルゴリズムの例

    $ make
    $ ./todmap --ac 1 --fc 1
    $ ./todmap --ac `seq 1 60`
    $ ./todmap --fc `seq 1 60`

## Usage: todmap [--ac | --fc] &lt;floor number&gt;...

|Option|Description|
|---|---|
|--ac|Generated in the arcade version|
|--fc|Generated in the FC (NES) version|
|&lt;floor number&gt;|Floor number (1-60)|
