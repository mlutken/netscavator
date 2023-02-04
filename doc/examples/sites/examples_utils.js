
function showId( sID ) 
{
    var e = document.getElementById(sID);
    e.style.display = '';
}

function hideId( sID ) 
{
    var e = document.getElementById(sID);
    e.style.display = 'none';
}


function prepForSyntaxHtml ( sCode, sBrushName, sOpts, sTitle )
{
    // Note on the replace '_XXX_' with 'script':
    // If we create the string directly as we want it the js interpreter
    // complains about unterminated string. Seems only to happen if
    // we use </script>
    var s = "<_XXX_ type=\"syntaxhighlighter\" class=\"brush: ";
    s = s + sBrushName + "; " + sOpts + "\" >";
    s = s + "<![CDATA[" + sCode + "]]></_XXX_>";
    var s1 = s.replace(/_XXX_/g, "script"); 
    return s1;
}


function loadCode( sUrl, sID, sBrushName, sOpts )
{
    $.ajax({
        url : sUrl,
        dataType: 'text',
        success : function (data) {
        var prep = prepForSyntaxHtml( data, sBrushName, sOpts, "" );
        $("#" + sID).html(prep);
        SyntaxHighlighter.highlight();
        //console.log("prepForSyntaxHtml:\n" + prep );
        console.log("DBG: Loaded: " + sUrl );
        console.log(data);
        }
    });
}


function loadSourceAndToggle( sID )
{
    var e = document.getElementById(sID);
    $(e).toggle('fast');
}
