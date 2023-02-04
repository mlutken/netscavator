<?php

// Standard word delimiters for use with strtok function
define('WORD_DELIMETERS', "\\ \n\t,");

/**
Same as standard php function explode, but also trims spaces from begin and end of each 
part added to the array returned.*/
function explodeTrim($delimiter, $string)
{
    $aTmp = explode($delimiter, $string);
    $a = array();
    foreach ($aTmp as $s) {
        $a[] = trim($s);
    }
    return $a;
}

/// Removes all occurences of the elements in the \a $aLookFor array 
/// \return String with all occurences of the elements in the \a $aLookFor array removed.
function remove_all( $str, $aLookFor )
{
	foreach ( $aLookFor as $sLookFor ) {
		$str = str_replace  ( $sLookFor , "" , $str );		
	}
	return $str;
}

/// Makes all chars in string lower case 
/// \return String with all chars in lower case.
function str_to_lower( $str )
{
	if ( PHP_OS == "Linux" ) {
		return mb_strtolower( $str, 'UTF-8' );
	}
	else {
		return mb_strtolower( $str, 'UTF-8' );
        // // return strtolower ( $str );
		// //return $str;
	}
}


/// Makes all chars in string lower case 
/// \return String with all chars in lower case.
function toLower( $str )
{
	if ( PHP_OS == "Linux" ) {
		return mb_strtolower( $str, 'UTF-8' );
	}
	else {
		return mb_strtolower( $str, 'UTF-8' );
        // // return strtolower ( $str );
		// //return $str;
	}
}


/// Makes all chars in string upper case 
/// \return String with all chars in upper case.
function str_to_upper( $str )
{
	if ( PHP_OS == "Linux" ) {
		return mb_strtoupper( $str, 'UTF-8' );
	}
	else {
		return mb_strtoupper( $str, 'UTF-8' );
        // // return strtoupper ( $str );
        // //return $str;
	}
}

/// Capitalizes (upper case) first letter of first word in string.  
/// \return String with first letter of first word in in upper case.
function capitalize_first( $str )
{
    if ( $str == "" ) return $str;
	$str[0]=str_to_upper( $str[0] );
	return $str;
}

/// Capitalizes (upper case) first letter of all words in string.  
/// \return String with first letter of all words in in upper case.
function capitalize_all_words( $str )
{
	$a = explode( ' ', $str );
	$str = "";
	$iWordCount = count( $a );
	for ( $i = 0; $i < $iWordCount; $i++ ) {
		$str .= capitalize_first ( $a[$i] );
		if ( $i < $iWordCount -1 ) $str .= ' ';
	}
	return $str;
}

/** Fixes casing from eiher all-lowercase or all-uppercase to more normal 
casing with lowercase and each word staring with uppercase letter. 
Use if album/song/artist names are in either all lowercase or all uppercase 
on the site in question. */
function fixWrongCasingInName( $nameToFix )
{
    return capitalize_all_words ( str_to_lower( $nameToFix ) );
}

/** Removes all chars between pairs of chars given as arrays. 
  \code
  // Remove all in brackes {}, [], ().
  \$string = removeBetween(array('(', '{', '['), array(')', '}', ']'), \$string);
  \endcode
 */
function removeBetween($startChars_a, $endChars_a, $string)
{
    $s = '';
    $n = 0;
    $skip = false;
    $endSkipChar = '';
    $len = strlen($string);
    while ($n < $len) {
        $c = $string[$n];


        if (!$skip) {
            $skipCharIndex = array_search($c, $startChars_a, true);
            if ($skipCharIndex !== false) {
                $skip = true;
                $endSkipChar = $endChars_a[$skipCharIndex];
            }
        }

        if (!$skip)
            $s .= $c;

        if ($skip) {
            if ($c == $endSkipChar)
                $skip = false;
        }

        $n++;
    }

    return $s;
}

/** Remove all in brackes {}, [], (). 
  \return String with all inside brackes: {}, [], () including the brackets removed. */
function removeAllInBrackets($string)
{
    return removeBetween(array('(', '{', '['), array(')', '}', ']'), $string);
}


// -------------------------------------------------
// --- Filter navigator resource files functions ---
// -------------------------------------------------

function filterOnStartingLetter( $line, $letterFrom, $letterTo )
{
    $line = trimDefault_fn($line);
//	printf("filterOnStartingLetter( $line, $letterFrom, $letterTo )\n");
    
    if ( $letterTo == "#" ) $letterFrom = "#";    // Ensure that allNonAZ is first in our alphabetic/logical order
    $bAllNonAZ      = $letterFrom == "#";
    $bAZWanted      = $letterTo   != "#";    // If ($letterTo == #) we don't match any lines beginning with letters A-Za-z
   
    if ( $letterFrom == "#" ) $letterFrom  = "a";
    
    $upper  = str_to_upper($letterFrom) . "-" . str_to_upper($letterTo);
    $lower  = str_to_lower($letterFrom) . "-" . str_to_lower($letterTo);
    $expr = "^([${upper}${lower}])" ;

    $exprAllAZ = "^([A-Za-z])" ;
    
    if ( ( $bAZWanted and  regexSearch_fn($line, "${expr}" ) )       or
         ( $bAllNonAZ and !regexSearch_fn($line, "${exprAllAZ}" ) )   
        ) 
    {
 //       printf("PHP: filterOnStartingLetter INCLUDING ($line)\n");
        return $line;
    }
    else {
//        printf("PHP: searchStringSelect_FILTER SKIPPING  ($line)\n");
        return "";
    }
}


function navStartingLetter_FILTER( $line )
{
    $letterFrom  = cmdValStrGet("start");
    $letterTo    = cmdValStrGet("end"); 
    return filterOnStartingLetter( $line, $letterFrom, $letterTo );
}


function navStartingLetterAddQuotes_FILTER( $line )
{
    $line = navStartingLetter_FILTER( $line );
	
	$line = "\"${line}\"";
	return $line;
 
 }
