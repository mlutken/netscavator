<?php


function options_MainPage_match()			
{	
	return contains ( urlCurrent(), "options.html" );
}

function options_MainPage_mine()			
{
	printf("\n*** options_MainPage_mine ***\n");
	domDebugPrint("./options_DBG.html");
 	
 	domFind ( 1 , "displayOption(this)", contains );
 	printf( "select::Length: %d\n", selectLength() ) ;
 	printf( "select::SelectedIndex: %d\n", selectSelectedIndex() ) ;
	selectSelect(1);
 	printf( "select::SelectedIndex: %d\n", selectSelectedIndex() ) ;
	
 	domSetPos(selectSelectedDomPos());
 	printf( "Selected option Node value: %s\n", nodeValueDebug(0, 3) ) ;
	

 	
	domFind ( 1, "ZEALAND_SOUTH", contains );
	printf("ZEALAND_SOUTH 1\n");
	selectOption();
	printf("ZEALAND_SOUTH 2\n");
 	printf( "select::SelectedIndex: %d\n", selectSelectedIndex() ) ;
 	
 	domSetPos(selectSelectedDomPos());
 	printf( "Selected option Node value: %s\n", nodeValueDebug(0, 3) ) ;
	printf("\n");	
}

function options_MainPage_navigate()			
{	
	return true;
}


function options_RegressionTest()			
{
	printf("\n*** options_RegressionTest: BEGIN ***\n");
}



?>


