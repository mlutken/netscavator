<?php


function frames_MainPage_match()			
{	
	return contains ( urlCurrent(), "frames.html" );
}

function frames_MainPage_mine()			
{
	printf("\n*** frames_MainPage_mine ***\n");
	domDebugPrint("./frames_DBG.html");
 	
 	domFind ( 1 , "INPUT_checkbox_onClick", contains );
 	nodeClick();
	
 	domFind ( 1 , "INPUT_radio_onClick", contains );
 	nodeClick();
	
	printf("\n");	
}

function frames_MainPage_navigate()			
{	
	return true;
}


function frames_RegressionTest()			
{
	printf("\n*** frames_RegressionTest: BEGIN ***\n");
}



?>


