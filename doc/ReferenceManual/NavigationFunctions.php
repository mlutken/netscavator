<?php

// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Navigation functions";


$f = array();
$f["name"] =
// **************************
       "Navigation functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for controlling the navigator. The navigator is a way to traverse all search input 
combination for a given site. An introductionary example is given here and it is highly recommended to 
read:
http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
and following examples.
TEXT;
$f["seealso"]   = "all-functions, all-function-groups";
$f["examples"][]    = <<<TEXT
// From: http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
function ExNavigator_beginMining()         
{
    ...
    domSeqCreate  ( "ClothesSelectSeq"  , "SELECT, name, clothes_type"  , "equals"  );
    domSeqCreate  ( "FabricSelectSeq"   , "SELECT, name, fabric_type"   , "equals"  );
    domSeqCreate  ( "DoSearchBtnSeq"    , "INPUT, value, Search"        , "equals"  );
    ...
    navDropDownSelectCreate("clothesSelect");
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( 1,  "dresses"            , ATTR, "Dress,  F"     );
    navOptionAdd ( 2,  "ties"               , ATTR, "Tie,    M"     );
    navOptionAdd ( 3,  "jackets"            , ATTR, "Jacket, MF"    );
    navDropDownSelectCreate("fabricSelect");
    navOptionAdd ( 1 );
    navOptionAdd ( 2 );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq", "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "FabricSelectSeq" , "fabricSelect"  ); // Select fabric drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq"  , "click"         ); // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$f["examples"][]    = <<<TEXT
// Simpler form of: http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
function ExNavigator_beginMining()         
{
    ...
    navInputOptionsCreate( "clothesSelect" );
    navAttributeNamesCreate ("sex");
    navOptionAdd ( "dress"        , ATTR, "F"  );
    navOptionAdd ( "tie"          , ATTR, "M"  );
    navOptionAdd ( "jacket"       , ATTR, "MF" );
    ...
}
...
TEXT;
$f["examples"][]    = <<<TEXT
// Simpler form of: http://www.netscavator.com/content/example-navigator-text-input-and-custom-trim
function ExNavigator_beginMining()         
{
    ...
    domSeqCreate  ( "DoSearchBtnSeq", "INPUT, value, Search", "equals" );
    ...
    navInputOptionsCreate( "clothesSelect" );
    navOptionAdd ( "dress"    );
    navOptionAdd ( "tie"      );
    navOptionAdd ( "jacket"   );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq",   "clothesSelect" ); // Input search string according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$f["examples"][]    = <<<TEXT
From: http://www.netscavator.com/content/example-navigator-url-load
function ExNavigator_beginMining()         
{
    ...
    navUrlLoadCreate("clothesPageLoader", "sleipnerexamples.com.localhost/sites/ExNavigatorUrlLoad/searchlisting.php");
    navAttributeNamesCreate ("product_name, sex, fabric");
    navOptionAdd    ( "url1" , "?clothes_type=dress&fabric_type=wool&page=0"     , ATTR, "Dress,     F,  Wool"    );  
    navOptionAdd    ( "url2" , "?clothes_type=dress&fabric_type=cotton&page=0"   , ATTR, "Dress,     F,  Cotton"  );  
    navOptionAdd    ( "url3" , "?clothes_type=tie&fabric_type=wool&page=0"       , ATTR, "Tie,       M,  Wool"    );  
    navOptionAdd    ( "url4" , "?clothes_type=tie&fabric_type=cotton&page=0"     , ATTR, "Tie,       M,  Cotton"  );  
    navOptionAdd    ( "url5" , "?clothes_type=jacket&fabric_type=wool&page=0"    , ATTR, "Jacket,    MF, Wool"    );  
    navOptionAdd    ( "url6" , "?clothes_type=jacket&fabric_type=cotton&page=0"  , ATTR, "Jacket,    MF, Cotton"  );  
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "HTML", "clothesPageLoader"   ); // 'Always find'. The HTML tag will allways be present
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navActiveNavigatorSet";
// ********************
$f["syntax"][]  = <<<TEXT
void navActiveNavigatorSet ( string sNavigatorName );
TEXT;
$f["params"][]    = array ( "string", "sNavigatorName", "Name of new active navigator." );

$f["desc"]      = <<<TEXT
Switch active navigator or create new. Switched the active navigator to be the one specified. If no navigator 
by that name exists a new one is created and set as active. 
Normally you will only need a single default navigator. This one is called "Navigator" and is by default set as the active. 
So unless you need multiple navigators, which you most likely don't you can safely ignore this function as well as its 
counterpart navActiveNavigatorGet.
TEXT;
$f["seealso"]       = "navActiveNavigatorGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navActiveNavigatorGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navActiveNavigatorGet ();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "Name of current active navigator." );

$f["desc"]      = <<<TEXT
Get name of the currently active navigator. By default a navigator is created for you, which is called 
"Navigator". Normally you will only need a single default navigator. 
So unless you need multiple navigators, which you most likely don't you can safely ignore this function as well as its 
counterpart navActiveNavigatorSet.
TEXT;
$f["seealso"]       = "navActiveNavigatorSet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navJavascriptExecuteCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void navJavascriptExecuteCreate ( string sNavActionName );
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of action \"wheel\". Refer to this name for example in doActionFind to actually fire the current action according to the current navigator state." );

$f["desc"]      = <<<TEXT
Create javascript executer actions "wheel" for the navigator. Follow this by one or more calls to navOptionAdd specifying an option name 
and actual javascript to excute for each option. Optionally you can, like for the other actions, associate attributes with each option.
TEXT;
$f["seealso"]       = "navOptionAdd, navUrlLoadCreate, navInputOptionsCreate, navDropDownSelectCreate, navDomPosClickCreate, navAutoInputCreate";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navUrlLoadCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void navUrlLoadCreate ( string sNavActionName, string sBaseUrl );
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of action \"wheel\". Refer to this name for example in doActionFind to actually fire the current action according to the current navigator state." );
$f["params"][]    = array ( "string", "sBaseUrl", "Base URL that gets prepended to each \"leaf\" URL in the options." );

$f["desc"]      = <<<TEXT
Create URL loader actions "wheel" for the navigator. Follow this by one or more calls to navOptionAdd specifying an option name 
and actual "leaf" URL to load for each option. Note that the sBaseUrl gets prepended to each "leaf" URL from the options. 
Optionally you can, like for the other actions, associate attributes with each option.
TEXT;
$f["seealso"]       = "navOptionAdd, navJavascriptExecuteCreate, navInputOptionsCreate, navDropDownSelectCreate, navDomPosClickCreate, navAutoInputCreate";
$f["examples"][]    = <<<TEXT
From: http://www.netscavator.com/content/example-navigator-url-load
function ExNavigator_beginMining()         
{
    ...
    navUrlLoadCreate("clothesPageLoader", "sleipnerexamples.com.localhost/sites/ExNavigatorUrlLoad/searchlisting.php");
    navAttributeNamesCreate ("product_name, sex, fabric");
    navOptionAdd    ( "url1" , "?clothes_type=dress&fabric_type=wool&page=0"     , ATTR, "Dress,     F,  Wool"    );  
    navOptionAdd    ( "url2" , "?clothes_type=dress&fabric_type=cotton&page=0"   , ATTR, "Dress,     F,  Cotton"  );  
    navOptionAdd    ( "url3" , "?clothes_type=tie&fabric_type=wool&page=0"       , ATTR, "Tie,       M,  Wool"    );  
    navOptionAdd    ( "url4" , "?clothes_type=tie&fabric_type=cotton&page=0"     , ATTR, "Tie,       M,  Cotton"  );  
    navOptionAdd    ( "url5" , "?clothes_type=jacket&fabric_type=wool&page=0"    , ATTR, "Jacket,    MF, Wool"    );  
    navOptionAdd    ( "url6" , "?clothes_type=jacket&fabric_type=cotton&page=0"  , ATTR, "Jacket,    MF, Cotton"  );  
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "HTML", "clothesPageLoader"   ); // 'Always find'. The HTML tag will allways be present
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navInputOptionsCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void navInputOptionsCreate ( string sNavActionName );
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of action \"wheel\". Refer to this name for example in doActionFind to actually fire the current action according to the current navigator state." );

$f["desc"]      = <<<TEXT
Create input options "wheel" for the navigator. Follow this by one or more calls to navOptionAdd specifying the the string to 
"write" in the INPUT field for each option. 
Optionally you can, like for the other actions, associate attributes with each option.
TEXT;
$f["seealso"]       = "navOptionAdd, navUrlLoadCreate, navJavascriptExecuteCreate, navDropDownSelectCreate, navDomPosClickCreate, navAutoInputCreate";
$f["examples"][]    = <<<TEXT
// Simpler form of: http://www.netscavator.com/content/example-navigator-text-input-and-custom-trim
function ExNavigator_beginMining()         
{
    ...
    domSeqCreate  ( "DoSearchBtnSeq", "INPUT, value, Search", "equals" );
    ...
    navInputOptionsCreate( "clothesSelect" );
    navOptionAdd ( "dress"    );
    navOptionAdd ( "tie"      );
    navOptionAdd ( "jacket"   );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq",   "clothesSelect" ); // Input search string according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navDropDownSelectCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void navDropDownSelectCreate ( string sNavActionName );
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of action \"wheel\". Refer to this name for example in doActionFind to actually fire the current action according to the current navigator state." );

$f["desc"]      = <<<TEXT
Create drop-down options "wheel" for the navigator. Follow this by one or more calls to navOptionAdd specifying the the option index and optianlly 
a name for each option.  
Optionally you can, like for the other actions, associate attributes with each option.
TEXT;
$f["seealso"]       = "navOptionAdd, navUrlLoadCreate, navInputOptionsCreate, navJavascriptExecuteCreate, navDomPosClickCreate, navAutoInputCreate";
$f["examples"][]    = <<<TEXT
// From: http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
function ExNavigator_beginMining()         
{
    ...
    domSeqCreate  ( "ClothesSelectSeq"  , "SELECT, name, clothes_type"  , "equals"  );
    domSeqCreate  ( "FabricSelectSeq"   , "SELECT, name, fabric_type"   , "equals"  );
    domSeqCreate  ( "DoSearchBtnSeq"    , "INPUT, value, Search"        , "equals"  );
    ...
    navDropDownSelectCreate("clothesSelect");
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( 1,  "dresses"            , ATTR, "Dress,  F"     );
    navOptionAdd ( 2,  "ties"               , ATTR, "Tie,    M"     );
    navOptionAdd ( 3,  "jackets"            , ATTR, "Jacket, MF"    );
    navDropDownSelectCreate("fabricSelect");
    navOptionAdd ( 1 );
    navOptionAdd ( 2 );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq", "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "FabricSelectSeq" , "fabricSelect"  ); // Select fabric drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq"  , "click"         ); // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navDomPosClickCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void navDomPosClickCreate ( string sNavActionName, string sFindNextDomPosSequence );
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of action \"wheel\". Refer to this name for example in doActionFind to actually fire the current action according to the current navigator state." );
$f["params"][]    = array ( "string", "sFindNextDomPosSequence", "Must refer to a named dom sequence, created using domSeqCreate. The dom sequence must have parameter placeholder called '#1', which will be substituted each time the action is fired with the actual parameter from the option." );

$f["desc"]      = <<<TEXT
Create "click at dom positions" "wheel" for the navigator. Follow this by one or more calls to navOptionAdd specifying the 
a name for each option and the parameter to subsitute in the sFindNextDomPosSequence to locate each of the dom 
positions.  
See this example for a practical example of how this functionality is to be used.
http://www.netscavator.com/content/example-navigator-domposclick-radio-buttons
Optionally you can, like for the other actions, associate attributes with each option.
TEXT;
$f["seealso"]       = "navOptionAdd, navUrlLoadCreate, navInputOptionsCreate, navDropDownSelectCreate, navJavascriptExecuteCreate, navAutoInputCreate";
$f["examples"][]    = <<<TEXT
From: http://www.netscavator.com/content/example-navigator-domposclick-radio-buttons
function ExNavigator_beginMining()         
{
    ...
    // Define dom sequences for the positions we need
    domSeqCreate  ( "DoSearchBtnSeq"    , "INPUT, value, Search"    , "equals"          );

    // Dom sequences to find the start of each of the two readio groups
    domSeqCreate  ( "ClothesSelectSeq"  , "Select clothes type"  , "contains"   );
    domSeqCreate  ( "FabricSelectSeq"   , "Select fabric type"   , "contains"   );
    
    // Dom sub-sequences to find the each of the radio buttons within a group
    domSeqCreate  ( "clothesSelectSubSeq", "clothes_type, value, #1, type, radio", "contains" );
    domSeqCreate  ( "fabricSelectSubSeq" , "fabric_type, value, #1, type, radio", "contains" );
    
    ...  
    // Navigator
    navDomPosClickCreate("clothesSelect", "clothesSelectSubSeq" );
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( "Dresses",   "dress"     , ATTR, "Dress,  F"     );
    navOptionAdd ( "Ties",      "tie"       , ATTR, "Tie,    M"     );
    navOptionAdd ( "Jackets",   "jacket"    , ATTR, "Jacket, MF"    );
    navDomPosClickCreate("fabricSelect", "fabricSelectSubSeq" );
    navAttributeNamesCreate ("fabric");
    navOptionAdd ( "Wool"   ,   "wool"      , ATTR, "Wool"          );
    navOptionAdd ( "Cotton" ,   "cotton"    , ATTR, "Cotton"        );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq",   "clothesSelect" ); // Select clothes radio button according to current navigator state
    doActionFind ( 1, "FabricSelectSeq",    "fabricSelect"  ); // Select fabric radio button according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navAutoInputCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void  navAutoInputCreate ( string sNavActionName, string sCharsList, int iMinLength, int iMaxLength );
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of action \"wheel\". Refer to this name for example in doActionFind to actually fire the current action according to the current navigator state." );
$f["params"][]    = array ( "string", "sCharsList", "List of all the characters you want to create combinations of like for example \"abc\"" );
$f["params"][]    = array ( "string", "iMinLength", "Minimum number of characters in each combination/input string." );
$f["params"][]    = array ( "string", "iMaxLength", "Maximum number of characters in each combination/input string" );

$f["desc"]      = <<<TEXT
Create a special dom character combinations "wheel" for the navigator. The idea is a brute-force approach of running through 
all 3-letter combinations of the letter a-z. This "wheel" you assign a range of characters for example all 
the english letters "abcdefghijklmnopqrstuvwxyz" as well as a minmum ans a maximum lenght.
Let us first explain how it works if both min and max lenght are set to 2 and with the sCharsList being "abc". 
Each time this wheel "turns" so to speak, that is when you call navNextState you get to the next combination. For this 
example the combinations are as follows:
<code>
aa
ab
ac
ba
bb
bc
</code>
The current option/combination string is then "typed" in the INPUT field when you do for example a 
'doActionFind("SearchForInput_FIND", "AutoCharsAction" );' Ofcourse you need to make sure that the SearchForInput_FIND sequence 
actually locates the INPUT field you want to input each of the combinations into.

If you set iMinLength = 2 and iMaxLength = 3, you will get the same sequence as above unless you call navAutoInputIncreaseLength, which 
will add an extra letterto the current state so for example you would get:
<code>
aa
ab
ac  // Call navAutoInputIncreaseLength(true) here
aca
acb
acc
ba
bb
bc
</code>
The idea with this is that often a webpage might hit a maximum number of results returned if you search for a two letter combination 
and when that happens you could call 'navAutoInputIncreaseLength(true);' and search again with an extra letter to reduce the number 
of returned results, which hopefully then does not max out. This is to ensure you don't loose any results because of hard 
maximum limits set by the site you are crawling.
TEXT;
$f["seealso"]       = "navAutoInputIncreaseLength, navOptionAdd, navUrlLoadCreate, navInputOptionsCreate, navDropDownSelectCreate, navDomPosClickCreate, navJavascriptExecuteCreate";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navAttributeNamesCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void navAttributeNamesCreate ( string sAttrNames, string sDelimiter = "," );
TEXT;
$f["params"][]    = array ( "string", "sAttrNames", "List of attribute names." );
$f["params"][]    = array ( "string", "sDelimiter", "Delimiter to use. Default is comma \",\", so normally you do not specify this parameter." );

$f["desc"]      = <<<TEXT
Create attributes for an action "wheel". Applies to the last added action wheel and is normalle called right after 
like this: 
<code>
navUrlLoadCreate("genreNameSelect", "http://www.cdmarket.eu");
navAttributeNamesCreate ("genre_name, media_format_name");
</code>

See examples for more.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
navUrlLoadCreate("genreNameSelect", "http://www.cdmarket.eu");
navAttributeNamesCreate ("genre_name, media_format_name");
navOptionAdd    ( "Blues"           , "/cdaudio/Blues"   , ATTR, "Jazz/Blues   , CD"    );
navOptionAdd    ( "ClassicalVinyl"  , "/vinyl/Classical" , ATTR, "Classical    , Vinyl" );
...
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navCurrentStateIndicesSet";
// ********************
$f["syntax"][]  = <<<TEXT
void navCurrentStateIndicesSet ( string sState );
TEXT;
$f["params"][]    = array ( "string", "sState", "State indices string to set as current state. For example \"2,0\"" );

$f["desc"]      = <<<TEXT
Set the current navigator state using indices for each "wheel". 
Each option you add to an action "wheel" gets an index starting from zero. So for example if we have a navigator like the one 
used in the first navigator example http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects: 
<code>
navDropDownSelectCreate("clothesSelect");
navAttributeNamesCreate ("product_name, sex");
navOptionAdd ( 1,  "dresses"            , ATTR, "Dress,  F"     );
navOptionAdd ( 2,  "ties"               , ATTR, "Tie,    M"     );
navOptionAdd ( 3,  "jackets"            , ATTR, "Jacket, MF"    );
navDropDownSelectCreate("fabricSelect");
navAttributeNamesCreate ("fabric");
navOptionAdd ( 1,  "wool"               , ATTR, "Wool"          );
navOptionAdd ( 2,  "cotton"             , ATTR, "Cotton"        );
</code>

We have theese combinations of state names and corresponding indices

<table border=1>
<tr><th></th><th>clothesSelect, fabricSelect    </th><th> clothesWheelIndex , fabricWheelIndex </th></tr>  
<tr><td>1 </td><td>  Dresses, Wool              </td><td>                 0 , 0</td></tr>
<tr><td>2 </td><td> Dresses, Cotton             </td><td>                 0 , 1</td></tr>
<tr><td>3 </td><td> Ties, Wool                  </td><td>                 1 , 0</td></tr>
<tr><td>4 </td><td>  Ties, Cotton               </td><td>                 1 , 1</td></tr>
<tr><td>5 </td><td>  Jackets, Wool              </td><td>                 2 , 0</td></tr>
<tr><td>6 </td><td>  Jackets, Cotton            </td><td>                 2 , 1</td></tr>

Note that the indices we are talking about here is purely automatically assigned and has nothing to do 
with the drop-down index you want selected for each option.
TEXT;
$f["seealso"]       = "navCurrentStateIndicesGet, navCurrentStateSet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navCurrentStateIndicesGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navCurrentStateIndicesGet () const;
TEXT;
$f["params"][]    = array ( "string", "RETURN", "Current state indices string. For example \"2,0\"" );

$f["desc"]      = <<<TEXT
Get a comma separated string representing the current navigator state using the index for each "wheel". Each option 
you add to an action "wheel" gets an index starting from zero. So for example if we have a navigator like the one 
used in the first navigator example http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects:
<code>
navDropDownSelectCreate("clothesSelect");
navAttributeNamesCreate ("product_name, sex");
navOptionAdd ( 1,  "dresses"            , ATTR, "Dress,  F"     );
navOptionAdd ( 2,  "ties"               , ATTR, "Tie,    M"     );
navOptionAdd ( 3,  "jackets"            , ATTR, "Jacket, MF"    );
navDropDownSelectCreate("fabricSelect");
navAttributeNamesCreate ("fabric");
navOptionAdd ( 1,  "wool"               , ATTR, "Wool"          );
navOptionAdd ( 2,  "cotton"             , ATTR, "Cotton"        );
</code>

We have theese combinations of state names and corresponding indices:

<table border=1>
<tr><th></th><th>clothesSelect, fabricSelect    </th><th> clothesWheelIndex , fabricWheelIndex </th></tr>  
<tr><td>1 </td><td>  Dresses, Wool              </td><td>                 0 , 0</td></tr>
<tr><td>2 </td><td> Dresses, Cotton             </td><td>                 0 , 1</td></tr>
<tr><td>3 </td><td> Ties, Wool                  </td><td>                 1 , 0</td></tr>
<tr><td>4 </td><td>  Ties, Cotton               </td><td>                 1 , 1</td></tr>
<tr><td>5 </td><td>  Jackets, Wool              </td><td>                 2 , 0</td></tr>
<tr><td>6 </td><td>  Jackets, Cotton            </td><td>                 2 , 1</td></tr>
</table>

Note that the indices we are talking about here is purely automatically assigned and has nothing to do 
with the drop-down index you want selected for each option.
TEXT;

$f["note"]          = "These indices are sed to represent the current state of the navigator in the Crawler.status file. So if your crawler crashes or you need to force close it for some reason this state string is used by the continue flag to pick up scanning where we left. Command line option '--continue'. ";
$f["seealso"]       = "navCurrentStateIndicesSet, navCurrentStateSet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navCurrentStateSet";
// ********************
$f["syntax"][]  = <<<TEXT
void navCurrentStateSet ( string sState, string sDelimiter );
void navCurrentStateSet ( string sState );
TEXT;
$f["params"][]    = array ( "string", "sState", "Comma (or delimiter) separated string of option names." );
$f["params"][]    = array ( "string", "sDelimiter", "Delimiter to use in case you do not use comma \",\"." );

$f["desc"]      = <<<TEXT
Set the current navigator state using option names for each "wheel". 
TEXT;
$f["seealso"]       = "navBeginStateSet, navEndStateSet, navCurrentStateIndicesSet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navBeginStateSet";
// ********************
$f["syntax"][]  = <<<TEXT
void navBeginStateSet ( string sState, string sDelimiter );
void navBeginStateSet ( string sState );
TEXT;
$f["params"][]    = array ( "string", "sState", "Comma (or delimiter) separated string of option names." );
$f["params"][]    = array ( "string", "sDelimiter", "Delimiter to use in case you do not use comma \",\"." );

$f["desc"]      = <<<TEXT
Set the navigator begin state using option names for each "wheel". This function a supplied for convenience 
only. It does the same as navCurrentStateSet.

TEXT;
$f["seealso"]       = "navCurrentStateSet, navEndStateSet, navCurrentStateIndicesSet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navEndStateSet";
// ********************
$f["syntax"][]  = <<<TEXT
void navEndStateSet ( string sState, string sDelimiter );
void navEndStateSet ( string sState );
TEXT;
$f["params"][]    = array ( "string", "sState", "Comma (or delimiter) separated string of option names." );
$f["params"][]    = array ( "string", "sDelimiter", "Delimiter to use in case you do not use comma \",\"." );

$f["desc"]      = <<<TEXT
Set the navigator end state using option names for each "wheel". Set this state if you need the navigator 
to terminate navigation at a specific state.
TEXT;
$f["seealso"]       = "navCurrentStateSet, navBeginStateSet, navCurrentStateIndicesSet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navOptionResourceAdd";
// ********************
$f["syntax"][]  = <<<TEXT
void navOptionResourceAdd ( string sResourcePath, string sScriptFilterFunction,  bool bForceDownload  );
TEXT;
$f["params"][]    = array ( "string", "sResourcePath", "Path to resource file. Use http:// for files on a server. For local files th path is assumed to be relative to the script directory and if not found then we try relative to current directory (startup dir)." );
$f["params"][]    = array ( "string", "sScriptFilterFunction", "An optional PHP fuction to call for each line. Return the strings you want to add as input options and do not return anything for those lines in the resource file that you want filtered out." );
$f["params"][]    = array ( "string", "bForceDownload", "Set to true to force downloading a new resource file from the server (only applies to http:// resources). Otherwise the file only gets downloaded if it is not found locally." );

$f["desc"]      = <<<TEXT
Add a resource file to an action "wheel". Currently only really used with navInputOptionsCreate to supply 
a large number of strings to use as search strings. Like for example:
<code>
navInputOptionsCreate( "clothesSelect" );
navOptionResourceAdd( "http://examples.netscavator.com/sites/ExNavigatorFileInput/clothes_types.txt", "", true );
</code>
See example: http://examples.netscavator.com/content/example-navigator-external-file-input
This navigators clothesSelect "wheel", which refers to a simple text INPUT field, will now for each state get the 
next line from the resource file "typed in". The resource file is a simple text file with one line per input string.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
// Given a resource file like this:
// dress ; F
// tie ; M
// jacket ; MF

// We create a navigator like this
navInputOptionsCreate   ( "clothesSelect" );
navOptionResourceAdd    ( "http://sleipnerexamples.com.localhost/sites/ExNavigatorFileInputFilter/clothes_types.txt", "filterClothesTypesOnly_F", true );


// And a filter function like this, which only adds the dress as an 
// option since it is (F)emale clothing.
function filterClothesTypesOnly_F(\$line)
{
    \$parts_a = explode(";", \$line);
    \$clothes_type       = trimDefault_fn( \$parts_a[0] );
    \$sex                = trimDefault_fn( \$parts_a[1] );
    if ( \$sex == "F" ) return \$clothes_type;
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navOptionAdd";
// ********************
$f["syntax"][]  = <<<TEXT
void  navOptionAdd ( int iCount, string sValue, string sSearchFor  );
void  navOptionAdd ( int iCount, string sValue );
void  navOptionAdd ( string sValue, string sSearchFor );
void  navOptionAdd ( string sValue );
void  navOptionAdd ( int iCount );
void  navOptionAdd ( int iCount, string sValue, string sSearchFor,
                     int attrStart, string sAttributes, string sDelimiter = "," );
void  navOptionAdd ( int iCount, string sValue,
                     int attrStart, string sAttributes, string sDelimiter = "," );
void  navOptionAdd ( string sValue, string sSearchFor,
                     int attrStart, string sAttributes, string sDelimiter = "," );
void  navOptionAdd ( string sValue,
                     int attrStart, string sAttributes, string sDelimiter = "," );
void  navOptionAdd ( int iCount, int attrStart, string sAttributes, string sDelimiter = "," );
TEXT;
$f["params"][]    = array ( "string", "iCount", "Drop-down option to select. First option has number 0 (zero)" );
$f["params"][]    = array ( "string", "sValue", "Value to use when refering to the option. For example when setting the option state with navCurrentStateSet. If you have not specified the sSearchFor, the sValue will be used as the sSearchFor also." );
$f["params"][]    = array ( "string", "sSearchFor", "Actual input string used by the action (\"wheel\"). For example the actual search/input string in InputOptions (navInputOptionsCreate).  " );
$f["params"][]    = array ( "string", "attrStart", "[optional] The contant ATTR (no quotes) to signal that the following parameter are an attributes string." );
$f["params"][]    = array ( "string", "sAttributes", "[optional] A string (comma separated by default) with attributes. One per attribute name created using navAttributeNamesCreate." );
$f["params"][]    = array ( "string", "sDelimiter", "[optional] In case you need comma in your attrubute names (not likely) you can specify an alternate delimiter character, say ';'." );

$f["desc"]      = <<<TEXT
Add option to action "wheel", optionally specifying attributes. Which overload you need depends on which action 
"wheel" you created before calling navOptionAdd. For example if you created a drop-down action "wheel" 
(navDropDownSelectCreate) you would need to specify the index to select in the drop-down for each option you 
add, which means using a form of navOptionAdd that has the iCount (=index-to-select) parameter. 

If on the other hand you created an input options "wheel" you need to specify the sSearchFor. The sValue is most 
often only used to refer the the option, for example when setting the option state with navCurrentStateSet. So if 
you use an overload of this function that only takes the sValue parameter, but not the sSearchFor, the sValue will 
be used as the sSearchFor also. See the examples.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
// From: http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
function ExNavigator_beginMining()         
{
    ...
    domSeqCreate  ( "ClothesSelectSeq"  , "SELECT, name, clothes_type"  , "equals"  );
    domSeqCreate  ( "FabricSelectSeq"   , "SELECT, name, fabric_type"   , "equals"  );
    domSeqCreate  ( "DoSearchBtnSeq"    , "INPUT, value, Search"        , "equals"  );
    ...
    navDropDownSelectCreate("clothesSelect");
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( 1,  "dresses"            , ATTR, "Dress,  F"     );
    navOptionAdd ( 2,  "ties"               , ATTR, "Tie,    M"     );
    navOptionAdd ( 3,  "jackets"            , ATTR, "Jacket, MF"    );
    navDropDownSelectCreate("fabricSelect");
    navOptionAdd ( 1 );
    navOptionAdd ( 2 );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq", "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "FabricSelectSeq" , "fabricSelect"  ); // Select fabric drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq"  , "click"         ); // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$f["examples"][]    = <<<TEXT
// Simpler form of: http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
function ExNavigator_beginMining()         
{
    ...
    navInputOptionsCreate( "clothesSelect" );
    navAttributeNamesCreate ("sex");
    navOptionAdd ( "dress"        , ATTR, "F"  );
    navOptionAdd ( "tie"          , ATTR, "M"  );
    navOptionAdd ( "jacket"       , ATTR, "MF" );
    ...
}
...
TEXT;
$f["examples"][]    = <<<TEXT
// Simpler form of: http://www.netscavator.com/content/example-navigator-text-input-and-custom-trim
function ExNavigator_beginMining()         
{
    ...
    domSeqCreate  ( "DoSearchBtnSeq", "INPUT, value, Search", "equals" );
    ...
    navInputOptionsCreate( "clothesSelect" );
    navOptionAdd ( "dress"    );
    navOptionAdd ( "tie"      );
    navOptionAdd ( "jacket"   );
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "ClothesSelectSeq",   "clothesSelect" ); // Input search string according to current navigator state
    doActionFind ( 1, "DoSearchBtnSeq",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;
$f["examples"][]    = <<<TEXT
From: http://www.netscavator.com/content/example-navigator-url-load
function ExNavigator_beginMining()         
{
    ...
    navUrlLoadCreate("clothesPageLoader", "sleipnerexamples.com.localhost/sites/ExNavigatorUrlLoad/searchlisting.php");
    navAttributeNamesCreate ("product_name, sex, fabric");
    navOptionAdd    ( "url1" , "?clothes_type=dress&fabric_type=wool&page=0"     , ATTR, "Dress,     F,  Wool"    );  
    navOptionAdd    ( "url2" , "?clothes_type=dress&fabric_type=cotton&page=0"   , ATTR, "Dress,     F,  Cotton"  );  
    navOptionAdd    ( "url3" , "?clothes_type=tie&fabric_type=wool&page=0"       , ATTR, "Tie,       M,  Wool"    );  
    navOptionAdd    ( "url4" , "?clothes_type=tie&fabric_type=cotton&page=0"     , ATTR, "Tie,       M,  Cotton"  );  
    navOptionAdd    ( "url5" , "?clothes_type=jacket&fabric_type=wool&page=0"    , ATTR, "Jacket,    MF, Wool"    );  
    navOptionAdd    ( "url6" , "?clothes_type=jacket&fabric_type=cotton&page=0"  , ATTR, "Jacket,    MF, Cotton"  );  
    ...
}
...
function ExNavigator_DoSearch_navigate()           
{   
    doActionFind ( 1, "HTML", "clothesPageLoader"   ); // 'Always find'. The HTML tag will allways be present
    return true;  // Return 'true' since the navigation results in loading of a new page.
}
TEXT;

$a[] = $f;


// $f = $f_common;
// $f["name"] =
// // ********************
//        "navOptionAttributesAdd";
// // ********************
// $f["syntax"][]  = <<<TEXT
// void        navOptionAttributesAdd  ( string sAttrValue1, string sAttrValue2,
//                                       string sAttrValue3, string sAttrValue4  );
// void        navOptionAttributesAdd  ( string sAttrValue1, string sAttrValue2,
//                                       string sAttrValue3 );
// void        navOptionAttributesAdd  ( string sAttrValue1, string sAttrValue2 );
// void        navOptionAttributesAdd  ( string sAttrValue1 );
// TEXT;
// $f["params"][]    = array ( "string", "sAttrValue1", "" );
// $f["params"][]    = array ( "string", "sAttrValue2", "" );
// $f["params"][]    = array ( "string", "sAttrValue3", "" );
// $f["params"][]    = array ( "string", "sAttrValue4", "" );
// 
// $f["desc"]      = <<<TEXT
// TEXT;
// $f["seealso"]       = "";
// $f["examples"][]    = <<<TEXT
// TEXT;
// $a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navDomTextValueGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navDomTextValueGet ( string sNavActionName ) const;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action name of InputOption to get the dom HTML 'text' attribute for." );
$f["params"][]    = array ( "string", "RETURN", "The actual dom HTML 'text' attribute." );

$f["desc"]      = <<<TEXT
Get the "text" attribute of the actual dom HTML element for the current option. Currenly only applies to INPUT options meaning 
action "wheels" created with navInputOptionsCreate.
TEXT;
$f["seealso"]       = "navDomValueGet, navValueGet, navSearchForGet, navCountGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navDomValueGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navDomValueGet ( string sNavActionName ) const;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action name of InputOption to get the dom HTML 'value' attribute for." );
$f["params"][]    = array ( "string", "RETURN", "The actual dom HTML 'value' attribute." );

$f["desc"]      = <<<TEXT
Get the "value" attribute of the actual dom HTML element for the current option. Currenly only applies to INPUT options meaning 
action "wheels" created with navInputOptionsCreate.
TEXT;
$f["seealso"]       = "navDomTextValueGet, navValueGet, navSearchForGet, navCountGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navValueGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navValueGet ( string sNavActionName ) ;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action name to get the current value (sValue) from." );
$f["params"][]    = array ( "string", "RETURN", "Value (sValue) of the current option in the action \"wheel\"." );

$f["desc"]      = <<<TEXT
Get the value of the action "wheels" current state. This the sValue parameter from navOptionAdd.
TEXT;
$f["seealso"]       = "navSearchForGet, navCountGet, navDomValueGet, navDomTextValueGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navSearchForGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navSearchForGet ( string sNavActionName ) ;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action name to get the current search-for string (sSearchFor) from." );
$f["params"][]    = array ( "string", "RETURN", "Search-for string (sSearchFor) of the current option in the action \"wheel\"." );

$f["desc"]      = <<<TEXT
Get the search-for string of the action "wheels" current state. This the sSearchFor parameter from navOptionAdd.
TEXT;
$f["seealso"]       = "navValueGet, navCountGet, navDomValueGet, navDomTextValueGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navCountGet";
// ********************
$f["syntax"][]  = <<<TEXT
int navCountGet ( string sNavActionName ) ;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action name to get the current count (iCount) from." );
$f["params"][]    = array ( "int", "RETURN", "Count (iCount) of the current option in the action \"wheel\"." );

$f["desc"]      = <<<TEXT
Get the count value of the action "wheels" current state. This the iCount parameter from navOptionAdd.
TEXT;
$f["seealso"]       = "navValueGet, navSearchForGet, navDomValueGet, navDomTextValueGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navOptionIndexGet";
// ********************
$f["syntax"][]  = <<<TEXT
int navOptionIndexGet ( string sNavActionName ) ;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action name to get the current index of." );
$f["params"][]    = array ( "int", "RETURN", "Index of the action \"wheel\".");

$f["desc"]      = <<<TEXT
Get the option index of the action "wheels" current state. Each option added using navOptionAdd are assigned an running 
index starting from 0 (zero).
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navStateIndexGet";
// ********************
$f["syntax"][]  = <<<TEXT
int navStateIndexGet ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "State index." );

$f["desc"]      = <<<TEXT
A single integer number representing the current state.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navNumStatesGet";
// ********************
$f["syntax"][]  = <<<TEXT
int navNumStatesGet () const;
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Total number of states." );

$f["desc"]      = <<<TEXT
Total number of states in the current navigator.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navLastStateIndexGet";
// ********************
$f["syntax"][]  = <<<TEXT
int navLastStateIndexGet () const;
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Index of last state." );

$f["desc"]      = <<<TEXT
Get index of current navigators last state.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navAttributeGet";
// ********************
$f["syntax"][]  = <<<TEXT
string navAttributeGet ( string sNavActionName, string sAttrName ) ;
string navAttributeGet ( string sAttrName ) const;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Action \"wheel\" name to get current attribute from." );
$f["params"][]    = array ( "string", "sAttrName", "Attribute name ( from navAttributeNamesCreate) to get current value of." );
$f["params"][]    = array ( "string", "RETURN", "The value of the attribute." );

$f["desc"]      = <<<TEXT
Get specific attribute value of a given action "wheel".
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navNextState";
// ********************
$f["syntax"][]  = <<<TEXT
bool navNextState ();
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "" );

$f["desc"]      = <<<TEXT
Advance navigator to next state. Very important to call this somewhere to actually get all states traversed. Often 
you would call this in 'MyCrawler_SearchListing_navigate()' or 'MyCrawler__ProductPage_navigate()'. See navigator 
examples:
http://www.netscavator.com/content/example-navigator-introduction-and-drop-down-selects
and following examples.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navDoActionClickAll";
// ********************
$f["syntax"][]  = <<<TEXT
bool navDoActionClickAll ( string sNavActionName ) ;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "Name of DomClickPos action" );
$f["params"][]    = array ( "bool", "RETURN", "Tru if dom positions could be found and clicked." );

$f["desc"]      = <<<TEXT
Click on all dom positions found by the specified DomClickPos action "wheel". Sometimes needed to set all checkboxes to un-selected 
in case the page selects them all by default. Then when the normal action for this "wheel" fires you get just one checkbox selected. 
TEXT;
$f["seealso"]       = "navDoAction, doActionFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navDoAction";
// ********************
$f["syntax"][]  = <<<TEXT
bool navDoAction ( string sNavActionName ) ;
TEXT;
$f["params"][]    = array ( "string", "sNavActionName", "" );
$f["params"][]    = array ( "bool", "RETURN", "True if action was fired." );

$f["desc"]      = <<<TEXT
Do action according to "wheels" current state. You must be at the correct dom position before calling this - i.e. from 
a domFind. Normally you would not use this function but instead use doActionFind.
TEXT;
$f["seealso"]       = "doActionFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navStateString";
// ********************
$f["syntax"][]  = <<<TEXT
string navStateString () const;
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The navigators state." );

$f["desc"]      = <<<TEXT
Get navigators state as a comma separated string of the individual actions "wheels" current option. Mostly 
used for info/debug by for example writing this navigator state to the output like this:
'outputDirect ( "navigator_state", navStateString() );'
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


// $f = $f_common;
// $f["name"] =
// // ********************
//        "navStart";
// // ********************
// $f["syntax"][]  = <<<TEXT
// void navStart ();
// TEXT;
// $f["params"][]    = array ( "string", "", "" );
// 
// $f["desc"]      = <<<TEXT
// 
// TEXT;
// $f["seealso"]       = "";
// $f["examples"][]    = <<<TEXT
// TEXT;
// $a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navReset";
// ********************
$f["syntax"][]  = <<<TEXT
void navReset ();
TEXT;

$f["desc"]      = <<<TEXT
Reset navigator. Most likely you would never need to call this function. Can be used to restart navigation.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navNavigationDone";
// ********************
$f["syntax"][]  = <<<TEXT
bool navNavigationDone () const;
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if navigator is at last state/done." );

$f["desc"]      = <<<TEXT
Test for navigation at last state/done.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "navAutoInputIncreaseLength";
// ********************
$f["syntax"][]  = <<<TEXT
void navAutoInputIncreaseLength ( bool bDoIncreaseLength );
TEXT;
$f["params"][]    = array ( "bool", "bDoIncreaseLength", "True if we should increase by one character." );

$f["desc"]      = <<<TEXT
Used only with navAutoInputCreate. 
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;



?>
