<?php 
	foreach ( $_GET as $key => $val ) {
		//$val = urldecode($val);
		echo "ML: " . $key ." => " . $val . "<br>\n";
	}

?>
