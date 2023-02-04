<?php
$redis=new Redis();
$redis->connect('127.0.0.1');
//$redis->set('set_testkey', 1);
//var_dump ( $redis->get('set_testkey') );

$redis->delete('h');
$redis->hSet('h', 'key1', 'hello'); /* 1, 'key1' => 'hello' in the hash at "h" */
$redis->hSet('h', 'key2', 'world'); /* 1, 'key1' => 'hello' in the hash at "h" */
// 
// echo $redis->hSet('h', 'key1', 'plop'); /* 0, value was replaced. */
// 
// 
// var_dump($redis->hKeys('h'));
// echo $redis->hLen('h'); /* returns 2 */
// 
// var_dump($redis->hgetall('h'));

$redis->delete('myHashKey');
$redis->hSet('myHashKey', '1', 'val 1'); 
$redis->hSet('myHashKey', '2', 'val 2'); 
$redis->hSet('myHashKey', '3', 'val 3'); 


$redis->zAdd("myHashzSet", 1, "myHashKey:1");
$redis->zAdd("myHashzSet", 2, "myHashKey:2");
$redis->zAdd("myHashzSet", 3, "myHashKey:3");

$members = $redis->zRange("myHashzSet", 0, -1);
$redis->multi();
foreach($members as $hashKey) {
    $redis->hGetAll($hashKey);
}
$results = $redis->exec();
var_dump( $results );

