# Using Miner Templates



## standard\_project\_item\_template.tpl.php
This section describes how the standard_project_item_template.tpl.php is working.
We will use cycling as the general example.

To use the template you will "derive" from this and create you own like this:

### cycling_template.tpl.php
    <?php
    require_once "webminer.php";
    require_once "utils.php";
    require_once "standard_project_item_template.tpl.php";
    ...
    // Default settings
    settingSet( "project", "cycling");
    ...
    // Default modifiers
    modifierCreate  ( "model_year__ItemPage__MOD" , "trimYear" );
    ...

    //Default dom sequences 
    domSeqCreate("description_html__ItemPage__FIND#1", "META, name, description, content", "equals", 1);
    ...


    function TEMPLATE__ItemPage__outputNames()
    {
        return "
    item_title,
    item_name,
    brand_name_text,
    ...
    }

    ...

    

## Writing values to the output
The TEMPLATE\_\_ItemPage\_\_outputNames() is the function which specifies what values we try to find (and write
 to output) on each ItemPage (typically a product page in a webshop).
 
In the above example you can see a snippet of this function as it looks for the cycling project.
I basically list the names of the output values we want written for each item - if the item has this field - thas is!

In addition to the values you specify here the standard_project_item_template will also write these values:

item_invalid, item_url, item_type_text, item_subtype_text

The way this is done is effectively by looping all these values and calling the crawler built-in function called 
outputValueFind().

So in pseudo code the loop looks like this:

    $outputNames = some-function-that combines-TEMPLATE__ItemPage__outputNames-and-the-standard-ones();


    foreach ($outputNames as $outputName ) {
        outputValueFind ( "{$outputName}__SearchResults__FIND", $outputName, "{$outputName}__SearchResults__MOD");
    }

The above loop will make sure that all values that are found by a dom sequnce with the given name is written to the output.
The value is not written directly to the output but passed to a modifier function named ("{$outputName}__SearchResults__MOD"). 
If no such function is specified the output value is passed to the output via the built-in trimDefault function, which trimms 
"whitespace" from both ends.

### outputValueFind() function in details
In the following we present a pseudo code implementation of the outputValueFind function so it's more clear what it actually does.


    // Function that combines the domFind() and outputValue() functions for more handy coding of 
    // the most common use cases. 
    // By default this function will save the current dom position before doing any work and restore the dom position 
    // back when completely done. This effective means that the current dom position is NOT changed. There are other 
    // overloads of this function that allows you to change this behaviour it you really need - which you probably don't.
    //
    // @param $domSeq: Dom sequence which can be either a named one created from domSeqCreate() or if a PHP function 
    //                 exists with this name it will be used.
    // @param $outputName: This is simply the actual name under which the value found will be written to the output.
    //                     The "key" so to speak of the key-value pair written tro the json file.
    // @param $modifierFn: Function to postprocess the value found at the dom position pointed out by the $domSeq 
    //                     parameter. This function takes a string parameter (the value) and return a string - the 
    //                     modified value.
    // @return           : Thjis function returns the dom position found (and moved to)
    function outputValueFind(string $domSeq, string $outputName, $modifierFn, string $modifierParameters...) : int
    {
        $posSave = domPos();

        $value = "";
        $pos = 0;
        
        // First check if dom sequence is really a php function and if so call this function
        if (isPhpFunction($domSeq)) {
        // Normal case, where the PHP function return a new dom position (integer)
        $pos = $domSeq();
        
        // Special case where the custom dom sequence PHP function returns a non empty string
        // Which we want to use as a value instead of getting the value from the current dom position 
        // using valueGet()
        if (is_string($pos)) {
            $value = $pos;
            $pos = 0;
        }
        else {  
            $pos = domFind($domSeq);    // Normal case: Call domFind with the sequence!
        }
        
        if ($pos != 0) { 
            $value = valueGet();    // Get value from current dom position
        }
        else if ($value == "")
            $value = settingGet($outputName);   // Try to get the value from settings
        }
        // else value is either empty or the value returned from a user defined PHP function
        
        // See if we have a modifier function defined, and if not we use the trimDefault function
        if ($modifierFn == '') {
            $modifierFn = trimDefault;
        }
        
        // Call modifier function with our value as first parameter and forward any extra modifier modifier parameters
        // Extra modifier parameterts couild for example be a string to prepend the value in we use modifier "prepend"
        $modifiedValue = $modifierFn($value, $modifierParameters...); 
        
        // Write final value to json/output
        if ($modifiedValue != '') {
            outputDirect($sFieldName, $modifiedValue);
        }

        // Restore dom position
        domPosSet($posSave);
        return $pos; // Return the position found from the dom sequence or 0 (zero) if sequence did not find a position.
    }





 
