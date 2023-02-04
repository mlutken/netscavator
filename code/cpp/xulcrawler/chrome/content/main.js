var g_specialThing = undefined;

function onMainXulWinLoaded()
{
    //alert("onMainXulWinLoaded");
    initCrawler();
}

function initCrawler()
{
    if ( g_specialThing == undefined ) {
        try {
            const cid = "@starkravingfinkle.org/specialthing;1";
            var obj = Components.classes[cid].createInstance();
            g_specialThing = obj.QueryInterface(Components.interfaces.ISpecialThing);
            g_specialThing.init("chrome://xulcrawler/content/main.xul","mybrowser1");
        }
        catch (err) {
            alert(err);
            return;
        }
    }
}

/*
cbmake.py && cp ./build_cbs/libs/shared/Release/libCSpecialThing.so ./xulcrawler/components/ && /home/ml/code/crawler/code/cpp/3rdparty/xulrunner-4.0/linux_64_release/xulrunner/xulrunner ./xulcrawler/application.ini
*/

function jsdump(str)
{
  Components.classes['@mozilla.org/consoleservice;1']
            .getService(Components.interfaces.nsIConsoleService)
            .logStringMessage(str);
}


function showMore() {
  document.getElementById("more-text").hidden = false;
  doXPCOM();
}

function doFileNew() {
  alert('doFileNew');
}

function doFileOpen() {
  alert('doFileOpen');
}

function doFileExit() {
  alert('doFileExit');
}

//      <browser id="mybrowser1"  src="http://www.google.dk" flex="1" type="content-primary" />



function onPageLoaded()
{
    alert("onPageLoaded");
}

function doXPCOM() {
//     document.getElementById("mywindow").title="blar";
// 
     var browser = document.getElementById("mybrowser1");
//     browser.contentWindow.location.href = "http://www.mozilla.org";

     initCrawler();
     
    //browser.addEventListener("DOMContentLoaded", onPageLoaded, false);     
     
     //     var win = browser.contentWindow
 //    alert("docElement: " + browser);
 //    alert("sss: " + browser.contentWindow.location.href);
//     alert("sss: " + browser.contentWindow.location.href);
//     alert("sss: " + win.location );
    // browser.contentWindow.location.href = "http://www.dr.dk";
     
//    jsdump("dsfsdfdsgds");
    
    
    g_specialThing.dbgPrint("hej\n");
//    Console.log("sdfsdf"); 
//     try {
//         const cid = "@starkravingfinkle.org/specialthing;1";
//         var obj = Components.classes[cid].createInstance();
//         obj = obj.QueryInterface(Components.interfaces.ISpecialThing);
//     }
//     catch (err) {
//         alert(err);
//         return;
//     }

    var res = g_specialThing.add(5, 4);
    g_specialThing.dbgPrint( '5+4 = ' + res + "\n" );

    var name = g_specialThing.name;
 // alert('Name = ' + name);

    g_specialThing.name = 'New Name';
    name = g_specialThing.name;
 // alert('Name = ' + name);
  
//    alert("docElement: " + docElement);
}


function doXPCOM1() {
    var winEnum = Components
            .classes["@mozilla.org/appshell/window-mediator;1"]
            .getService(Components.interfaces.nsIWindowMediator)
            .getXULWindowEnumerator(null);
    var win = null;
    while(winEnum.hasMoreElements())
    try {
        win = winEnum.getNext()
                .QueryInterface(Components.interfaces.nsIXULWindow).docShell
                .QueryInterface(Components.interfaces.nsIInterfaceRequestor)
                .getInterface(Components.interfaces.nsIDOMWindow)
                ;
        //here do checks... I check for mase XUL file name
        alert(win.location);        
        if(win.location == 'chrome://xulcrawler/content/main.xul') {
        //here return from function or do something
        break;
        }
    } 
    catch(e){ 
        alert(e); 
    }
    
}

