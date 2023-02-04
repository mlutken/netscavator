<?php


function DomFind_MainPage_match()			
{	
	return contains_fn ( urlCurrent(), "domFind.html" );
}

function DomFind_MainPage_mine()			
{
	printf("\n*** DomFind_MainPage_mine ***\n");
	domDebugPrint("./DomFind_DBG.html");
 	
 	
/*	printf ( "2 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
 	for ( $i = 0; $i < 8; $i++ ) {
	 	printf ( "'%s' ", nodeValue() );
	 	domStep(1);
 	}
 	printf ( "\n3 POS: %d\n", domGetPos());*/
 	
	DomFind_RegressionTest();	
	//DomFind_FindSequences(); 	

	domSetPos(1);
	printf ( "1 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
	domSetPos(2);
	printf ( "2 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
	
	printf ( "1 NODE(%d): '%s'\n", domGetPos(), nodeValue() );
	$iPos = domFindNextPos ( 1, "stop", equals ) ;
	printf ( "2 NODE(%d): '%s'   STOP(%d): '%s' \n", domGetPos(), nodeValue(), $iPos, nodeValue($iPos) );
	
	$iPos = domFind( 2 , "find", equals	);
	printf ( "3 NODEVAL(%d,%d): '%s'\n", domGetPos(), $iPos, nodeValue() );
	
	printf("\n");	
}

function DomFind_MainPage_navigate()			
{	
	return false;
}


function DomFind_RegressionTest()			
{
	printf("\n*** DomFind_RegressionTest: BEGIN ***\n");

	// ----------------------------
	// --- domFind, domFindNext ---
	// ----------------------------
	domFind( 2 , "find", "equals"	);
																assert ( nodeValue() == 'find' ); 	
	domFindNext( 1 , "id", "equals"	);
	domStep ( 1 );
																assert ( nodeValue() == 'INPUT_text_onClick' ); 	
	domFindNext( 1 , "not_there", "equals"	);
																assert ( nodeValue() == 'INPUT_text_onClick' ); 	
	domFindNext( -1 , "not_there", "equals"	);
																assert ( nodeValue() == 'INPUT_text_onClick' ); 	
	domPointerPush();
	domFindNext( -1 , "find", "equals"	);
																assert ( nodeValue() == 'find' ); 	
	domStep ( 1 );
																assert ( nodeValue() == 'FIND2' ); 	
	domPointerPop();
																assert ( nodeValue() == 'INPUT_text_onClick' ); 	
	domFindNext( -3 , "find", "equals"	);
																assert ( nodeValue() == 'INPUT_text_onClick' ); 	
	domFindNext( -1 , "not_there", "equals"	);
																assert ( nodeValue() == 'INPUT_text_onClick' ); 	
	domFindNext( -2 , "find", "equals"	);
																assert ( nodeValue() == 'find' ); 	
	domStep ( 1 );
																assert ( nodeValue() == 'FIND1' ); 	

	return;																
	// ----------------------------------------
	// --- domFindStopAt : Stop at position ---
	// ----------------------------------------
	domFind( 1, "stop", equals );
	$iPosStop = domGetPos();  	
	domStep ( 1 );
																assert ( nodeValue() == 'STOP1' ); 	
	domFindStopAt( 2 , "find", equals, $iPosStop  );
																assert ( nodeValue() == '#document' ); 	
	domFindStopAt( 1 , "find", equals, $iPosStop  );
																assert ( nodeValue() == 'find' ); 	
	domFind ( 1 , "SEARCH_BACK", equals	);
																assert ( nodeValue() == 'SEARCH_BACK' ); 	
	domFindNextStopAt( -2 , "find", equals, $iPosStop  );
																assert ( nodeValue() == 'SEARCH_BACK' ); 	
	domFindNextStopAt( -1 , "not_there", equals, $iPosStop   );
																assert ( nodeValue() == 'SEARCH_BACK' ); 	
	domFindNextStopAt( -1 , "find", equals, $iPosStop  );
																assert ( nodeValue() == 'find' ); 	
	
	
	// --------------------------------------------
	// --- domFindStopAt : Stop at string match ---
	// --------------------------------------------
	$iPosStop  = domFind ( 1, "stop", equals ) ;
	$iPosStop = domGetPos();  	
	


//	domFindStopAt( 2 , "find", equals, 1, "stop", equals   );
	
	domFindStopAt( 2 , "find", equals, domFind ( 1, "stop", equals )   );
																assert ( nodeValue() == '#document' ); 	
	domFindStopAt( 1 , "find", equals, domFind ( 1, "stop", equals )   );
																assert ( nodeValue() == 'find' ); 	
	domFind ( 1 , "SEARCH_BACK", equals	);
																assert ( nodeValue() == 'SEARCH_BACK' ); 	
	domFindNextStopAt( -2 , "find", equals, domFindNextPos ( -1, "stop", equals )   );
																assert ( nodeValue() == 'SEARCH_BACK' ); 	
	domFindNextStopAt( -1 , "not_there", equals, domFindNextPos ( -1, "stop", equals)   );
																assert ( nodeValue() == 'SEARCH_BACK' ); 	
	domFindNextStopAt( -1 , "find", equals, domFindNextPos ( -1, "stop", equals)   );
																assert ( nodeValue() == 'find' ); 	

	
	// --------------------------------------
	// --- SEQUENCE: domFind, domFindNext ---
	// --------------------------------------
	// Single node sequences
	domFind( 1 , new DomSeq("b", equals	) );
																assert ( nodeValue() == 'b' ); 	
	domStep ( 3 );
																assert ( nodeValue() == 'seq1' ); 	
	
	domFind( 2 , new DomSeq("b", equals	) );
																assert ( nodeValue() == 'b' ); 	
	domStep ( 3 );
																assert ( nodeValue() == 'seq2' ); 	
	domFind( 3 , new DomSeq("b", equals	) );
																assert ( nodeValue() == '#document' ); 	
	
	domFind ( 1, "SEARCH_BACK_SEQ", equals );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -3 , new DomSeq("b", equals	) );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -1 , new DomSeq("not_there", equals	) );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( 1 , new DomSeq("not_there", equals	) );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -1 , new DomSeq("b", equals	) );
																assert ( nodeValue() == 'b' ); 	
	domStep ( 3 );
																assert ( nodeValue() == 'seq2' ); 	
	domFind ( 1, "SEARCH_BACK_SEQ", equals );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -2 , new DomSeq("b", equals	) );
																assert ( nodeValue() == 'b' ); 	
	domStep ( 3 );
																assert ( nodeValue() == 'seq1' ); 	
	
	// Longer sequences
	domFind( 1 , new DomSeq("a","b","c","d", equals	) );
																assert ( nodeValue() == 'd' ); 	
	domStep ( 1 );
																assert ( nodeValue() == 'seq1' ); 	
	domFind( 2 , new DomSeq("a","b","c","d", equals	) );
																assert ( nodeValue() == 'd' ); 	
	domStep ( 1 );
																assert ( nodeValue() == 'seq2' ); 	
	domFind( 3 , new DomSeq("a","b","c","d", equals	) );		// Not in doc 3 times
																assert ( nodeValue() == '#document' ); 	
	domFind( 1 , new DomSeq("a","b","c","not_there", equals	) );		// Not in document 
																assert ( nodeValue() == '#document' ); 	
	
	domFind ( 1, "SEARCH_BACK_SEQ", equals );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -3 , new DomSeq("a","b","c","d", equals ) );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -1 , new DomSeq("a","b","c","not_there", equals ) );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -1 , new DomSeq("a","b","c","d", equals ) );
																assert ( nodeValue() == 'a' ); 	
	domStep ( 4 );
																assert ( nodeValue() == 'seq2' ); 	
	domFind ( 1, "SEARCH_BACK_SEQ", equals );
																assert ( nodeValue() == 'SEARCH_BACK_SEQ' ); 	
	domFindNext( -2 , new DomSeq("a","b","c","d", equals ) );
																assert ( nodeValue() == 'a' ); 	
	domStep ( 4 );
																assert ( nodeValue() == 'seq1' ); 	
	
	
	printf("*** DomFind_RegressionTest: DONE  ***\n\n");
}

function DomFind_FindSequences()			
{
	printf("\n*** DomFind_FindSequences ***\n");
 	
	domNewSearch();
	printf ( "1 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
	domFindNext( 13, new DomSeq ( "TD", "id", equals ) );
	domPointerPush();
 	printf ( "2 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
 	for ( $i = 0; $i < 8; $i++ ) {
	 	printf ( "'%s' ", nodeValue() );
	 	domStep(1);
 	}
	domPointerPop();
 	printf ( "\n2 POS: %d\n", domGetPos());
 	domFindNext( -10, new DomSeq ( "TR", "TD" , equals ) );
// 	domFindNext( -100, "TR", equals );
 	printf ( "3 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
 	for ( $i = 0; $i < 8; $i++ ) {
	 	printf ( "'%s' ", nodeValue() );
	 	domStep(1);
 	}
 	printf ( "\n3 POS: %d\n", domGetPos());
 	
}


?>


