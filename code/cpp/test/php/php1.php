#!/usr/bin/php -q

The world of Belgian dressing

<?php

$interact = fopen("php://stdin","r");
for ($k=1; $k<11; $k++) {
print "$k dollops of mayonnaise\n";
$line = fgets($interact,1024);
}

?>

and there's a chip in there somewhere
