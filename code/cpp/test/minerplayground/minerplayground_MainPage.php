    <?php


function MinerPlayGround_MainPage_match()			
{	
    return true;
	return contains_fn ( urlCurrent(), "minerplayground.html" );
}


// function append( $sval, $sappend )
// {
	// printf("php append( '$sval', '$sappend')\n");
	// outputdirectunit("output_value_unit_from_php_fun", "dddddddddddd",  "sek" );
	// return $sval . " " . $sappend . " " . $sappend;
// }

// function MyAction( $param1, $param2, $param3 )
// {
	// printf("ML_PHP: MyAction( '$param1', '$param2', '$param3')\n");
	// return nodeClick();
// }

// function MyModifier( $val )
// {
	// return " MyModifier $val ";
    // }

function navigatorTest()
{
    printf("navigatorTest()\n");
    navDropDownSelectCreate("genre_name");
    navOptionAdd(1, "Pop/Rock" );
    navOptionAdd(1, "Blues" );
    navOptionAdd(1, "Jazz" );
    navDropDownSelectCreate("media_format_name");
    navOptionAdd(1, "MP3" );
    navOptionAdd(1, "CD" );
    navOptionAdd(1, "WMA" );
    navAutoInputCreate("search_name", "a,b,c", 2, 4 );
 //   navBeginStateSet(" genre1, media2 , b c");
 //   navEndStateSet(" genre2, media2, b a " );

    navStart();
    $i = 0;
    while ( ! navNavigationDone() ) {
        printf( "L: %d, %s\n", $i, navStateString() );
        navNextState();

        if ( $i++ > 1000 ) {
            printf("Error\n");
            break;
        }
    }
    printf( "L: E, %s\n", navStateString() );

}

function clickLoadTest()
{
}

function MinerPlayGround_MainPage_mine()			
{
//    clickLoadTest();
    return;

     navigatorTest();
     //return;

//	domActionCreate			( 	"MyAction", "click", "false", "", NEAREST_BACKWARD );
	domActionCreate			( 	"MyAction", "click" );
	
	domFind 	( 1, 'INPUT_onClick', "contains" );			
	doAction	( 'MyAction', "false", "", NEAREST_AUTO );
//	doAction	( 'click', "false", "", NEAREST_AUTO );

//	domSeqCreate ( "doActionSeq", "TR, TD, INPUT, onclick, #con:INPUT_checkbox_onClick", "equals", -2 );
//	doActionFind( 1, "doActionSeq", "MyAction" ); 
//	doActionFind( 1, "doActionSeq", "click", "false", "", NEAREST_BACKWARD ); 

	
	printf("\n*** MinerPlayGround_MainPage_mine ***\n");
	//domDebugPrint("_MinerPlayGround_DBG.html");
	// outputDirectUnit ( "TEST_3_PARAMS_VERSION", "   outputDirectUnit 3 params   ", "unit" );		
	// outputDirectUnit ( "TEST_4_PARAMS_VERSION", "   outputDirectUnit 4 params   ", "unit", "raw" );		
	
  //  domSeqCreate ( "myseq", "TR, TD, INPUT, onclick, ?, #con:onClick", "equals", 4 );
//    domSeqCreate ( "myseq", "TR, TD, INPUT, onclick, #10, #con:onClick", "equals", 4 );
//	domFind( 1 , "myseq" );
//	outputValue ( "myseq"  );
	
	modifierCreate	( "MyModifier", "prepend", "GED " );
	outputDirect 	( "ModifierTesT", "  raw string  ", "append", " HEST" );
    outputDirect    ( "ModifierTesT", "  raw string  ", "MyModifier" );
    outputDirect    ( "raw", "  raw string  ", "raw" );
        
	domNewSearch();
	outputValueFindNext( 1, "myseq", "OUT_NAME", "MyModifier", "HEST ", "", "", "" ); 

	domFind( 1 , "find", "equals"	);
	assert ( nodeValue() == 'find' ); 	
	outputValueUnit("OUTPUT_VALUE_UNIT", "DKK", "append", ",-" );
	valueModify ( "append", "GED" );
	outputValue("OUTPUT_VALUE" , "prepend", "do " );

	outputValueFindNext( 1, "showMe", "OUT_NAME", "prepend", "HEST", "", "", "" ); 
	
 	
 	
/*	printf ( "2 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
 	for ( $i = 0; $i < 8; $i++ ) {
	 	printf ( "'%s' ", nodeValue() );
	 	domStep(1);
 	}
 	printf ( "\n3 POS: %d\n", domGetPos());*/
 	
	//MinerPlayGround_RegressionTest();	
	//MinerPlayGround_FindSequences(); 	

	
	/*
	domSetPos(1);
	printf ( "1 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
	domSetPos(2);
	printf ( "2 NODEVAL(%d): '%s'\n", domGetPos(), nodeValue() );
	
	printf ( "1 NODE(%d): '%s'\n", domGetPos(), nodeValue() );
	$iPos = domFindNextPos ( 1, "stop", equals ) ;
	printf ( "2 NODE(%d): '%s'   STOP(%d): '%s' \n", domGetPos(), nodeValue(), $iPos, nodeValue($iPos) );
	
	$iPos = domFind( 2 , "find", equals	);
	printf ( "3 NODEVAL(%d,%d): '%s'\n", domGetPos(), $iPos, nodeValue() );

*/	
	printf("\n");	
}

function MinerPlayGround_MainPage_navigate()			
{	
//    domFind ( "('A_onClick')", "contains" );
    domFind ( "('JS_onClick')", "contains" );
    printf("ML: BEFORE CLICK\n");
//    nodeClick(NEAREST_AUTO, true);
    nodeClick();
    printf("ML: AFTER CLICK\n");
	return true;
}


function MinerPlayGround_RegressionTest()			
{
	printf("\n*** MinerPlayGround_RegressionTest: BEGIN ***\n");

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
	// ----------------------------------------
	// --- domFindStopAt : Stop at position ---
	// ----------------------------------------
	domFind( 1, "stop", "equals" );
	$iPosStop = domGetPos();  	
	domStep ( 1 );
																assert ( nodeValue() == 'STOP1' ); 	
	
	
	// --------------------------------------------
	// --- domFindStopAt : Stop at string match ---
	// --------------------------------------------
	$iPosStop  = domFind ( 1, "stop", "equals" ) ;
	$iPosStop = domGetPos();  	
	

	return;

	
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
	
	
	printf("*** MinerPlayGround_RegressionTest: DONE  ***\n\n");
}

function MinerPlayGround_FindSequences()			
{
	printf("\n*** MinerPlayGround_FindSequences ***\n");
 	
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


