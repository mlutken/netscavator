<?php


function Events_MainPage_match()			
{	
	return contains_fn ( urlCurrent(), "events.html" );
}

function Events_MainPage_mine()			
{
	printf("\n*** Events_MainPage_mine ***\n");
// 	domDebugPrint("./EVENTS.html");
	$aEvents = array (	'INPUT_onClick', 'INPUT_button_onClick', 'INPUT_checkbox_onClick', '',  
						'INPUT_hidden_onClick','INPUT_image_onClick','INPUT_password_onClick',
						'INPUT_radio_onClick','INPUT_reset_onClick','INPUT_submit_onClick',
						'INPUT_text_onClick',
						'INPUT_file_onClick',
						'BUTTON_onClick','TD_onClick', 'DIV_onClick', 'SPAN_onClick',
						'A_onClick');
	foreach ( $aEvents as $event ) {
		domFind ( 1, $event, 	"contains" );			
		if ( nodeClick () )	{	
 			printf ("CLICK: $event\n");
		}
	}

	domfind ( 1, 'DIV_MouseEvents', "equals" );
	//nodeClick();
	nodeMouseEvent('dblclick');
	printf ("NODE: %s\n", valueGet() );
	printf("\n*** Events_MainPage_mine DONE ***\n");
}

function Events_MainPage_navigate()			
{	
 	
 	
/*	domFind		( 1,	"map_search_input_small",	equals	);
 	inputSet	( 0	);	
	domFindNext	( 1,	"map_search_input_small",	equals	);
 	inputSet	( 100000000	);	
	domFind 	( 	 1, "javascript:doListSearch();"	, equals 	)	;
	nodeClick	()										;					*/
 	
 	return true;
}

// --- Events ---
//     * focus
//     * blur
//     * select
//     * change
//     * click
//     * dblclick
//     * mousedown
//     * mouseup
//     * mouseover
//     * mousemove
//     * mouseout
//     * keypress
//     * keydown
//     * keyup



?>


