import urllib
import urllib2
import os
import re
import xbmc
import xbmcplugin
import xbmcgui
import cookielib
import xbmcvfs
import xbmcaddon
from BeautifulSoup import BeautifulSoup
import StorageServer
from webviewer import webviewer
cache = StorageServer.StorageServer("piratebay", 24)
addon = xbmcaddon.Addon('plugin.program.piratebay')
profile = xbmc.translatePath(addon.getAddonInfo('profile'))
home = addon.getAddonInfo('path')
icon = xbmc.translatePath( os.path.join( home, 'icon.png' ) )
sort = addon.getSetting('sort')
cache.dbg = True
UT_ADDRESS = addon.getSetting('ip')
UT_PORT = addon.getSetting('port')
UT_USER = addon.getSetting('usr')
UT_PASSWORD = addon.getSetting('pwd')

passman = urllib2.HTTPPasswordMgrWithDefaultRealm()
# this creates a password manager
passman.add_password(None, 'http://'+UT_ADDRESS+':'+str(UT_PORT)+'/gui/', UT_USER, UT_PASSWORD)

authhandler = urllib2.HTTPBasicAuthHandler(passman)
# create the AuthHandler

opener = urllib2.build_opener(authhandler)

cj = cookielib.CookieJar()
opener.add_handler(urllib2.HTTPCookieProcessor(cj))

urllib2.install_opener(opener)
# All calls to urllib2.urlopen will now use our handler

def cache_cats():
        req = urllib2.Request('http://thepirateboat.eu/browse')
        response = urllib2.urlopen(req)
        link=response.read()
        response.close()
        return(link, 200)


def Categories():
        BASE = 'http://thepirateboat.eu/browse/'
        addDir('Search','',icon,4, 0)
        result = cache.cacheFunction(cache_cats)
        soup = BeautifulSoup(result[0], convertEntities=BeautifulSoup.HTML_ENTITIES)
        cats = soup.select('optgroup')
        for i in cats:
            main_name = i['label']
            main_id = i.option['value'][0]+'00'
            if sort == "1":
                BASE = BASE.replace('browse', 'top')
            addDir(main_name, BASE+main_id, icon, 1, 0)
            for sub in i('option'):
                sub_name = sub.string
                sub_id = sub['value']
                if sort == "1":
                    BASE = BASE.replace('browse', 'top')
                addDir(main_name+' - '+sub_name, BASE+sub_id, icon, 1, 0)


def Search():
        searchStr = ''
        keyboard = xbmc.Keyboard(searchStr, "Search")
        keyboard.doModal()
        if (keyboard.isConfirmed() == False):
                return
        searchstring = keyboard.getText()
        if len(searchstring) == 0:
                return
        newStr = searchstring.replace(' ','%20')
        url = 'http://thepirateboat.eu/search/'+newStr
        getTorrents(url, '0')


def getTorrents(url, page):
        if not sort == "1":
            print 'Page: '+page
            print 'Sort: '+sort
            if sort == "0":
                url+= '/'+page+'/3'
            if sort == "2":
                url+= '/'+page+'/7'
            if sort == "3":
                url+= '/'+page+'/9'
            # if sort == "3":
                # url+= '/'+page+'/3'
            # if sort == "4":
                # url+= '/'+page+'/3'
        print '----URL: '+url
        req = urllib2.Request(url)
        response = urllib2.urlopen(req)
        link=response.read()
        response.close()
        soup = BeautifulSoup(link, convertEntities=BeautifulSoup.HTML_ENTITIES)
        torrents = soup('div', attrs={'id' : "main-content"})[0]('tr')
        print '-----list count: '+str(len(torrents))
        if not sort == "1":
            items = torrents[1:31]
        else: items = torrents[1:]
        for i in items:
            try:
                name = i('div')[0]('a')[0].string.encode('ascii', 'ignore')
                print '----name: ' + name
                info_url = 'http://thepirateboat.eu'+i('a')[2]['href']
                t_url = i('a')[3]['href']
                print '----magnet link: ' + t_url
                le = i('td')[-1].string
                se = i('td')[-2].string
                try:
                    size = i('font')[0].contents[2].split(', Size')[1].split(',')[0].encode('ascii', 'ignore')
                except:
                    try:
                        size = i('font')[0].contents[1].split('Size ')[1].split(',')[0].encode('ascii', 'ignore')
                    except:
                        try:
                            size = i('font')[0].contents[0].split('Size ')[1].split(',')[0].encode('ascii', 'ignore')
                        except:
                            size = '?'
                addDownload(name+' | S: '+se+' L: '+le+' | '+size, t_url, icon, 3, info_url)
            except:
                print '----parse failed----'
                pass
        if not sort == "1":
            try:
                if soup('table')[0]('a')[-1].img['alt'] == 'Next':
                    addDir('Next Page',url.split('/'+page)[0],icon,1,page=int(page)+1)
            except:
                try:
                    if soup('div', attrs={'align' : "center"})[0]('a')[-1].img['alt'] == 'Next':
                        addDir('Next Page',url.split('/'+page)[0],icon,1,page=int(page)+1)
                except:
                    pass


def Download(url):
        print '----magnet link: ' + url
        utorrent = 'http://'+UT_ADDRESS+':'+str(UT_PORT)+'/gui/token.html'
        req = urllib2.Request(utorrent)
        response = urllib2.urlopen(req)
        tokenfile=response.read()
        response.close()
        match = re.compile("<div id='token' style='display:none;'>(.+?)</div>").findall(tokenfile)
        token = match[0]
        print '----token: ' + tokenfile
        print '----token: ' + token
        utorrentadd = 'http://'+UT_ADDRESS+':'+str(UT_PORT)+'/gui/?token='+token+'&action=add-url&s='+urllib.quote(url)
        #utorrentadd = 'http://'+UT_ADDRESS+':'+str(UT_PORT)+'/gui/?token='+token+'&list=1'
        print '----url: ' + utorrentadd
        req = urllib2.Request(utorrentadd)
        response = urllib2.urlopen(req)
        success=response.read()
        response.close()
        message('Success', 'Your torrent is downloading!')
        print '----server response: ' + success


def message(title,text):
    dialog = xbmcgui.Dialog()
    dialog.ok(title, text)


def get_params():
        param=[]
        paramstring=sys.argv[2]
        if len(paramstring)>=2:
            params=sys.argv[2]
            cleanedparams=params.replace('?','')
            if (params[len(params)-1]=='/'):
                params=params[0:len(params)-2]
            pairsofparams=cleanedparams.split('&')
            param={}
            for i in range(len(pairsofparams)):
                splitparams={}
                splitparams=pairsofparams[i].split('=')
                if (len(splitparams))==2:
                    param[splitparams[0]]=splitparams[1]

        return param


def addDownload(name,url,iconimage,mode,info):
        u=sys.argv[0]+"?url="+urllib.quote_plus(url)+"&mode="+str(mode)+"&name="+urllib.quote_plus(name)
        ok=True
        liz=xbmcgui.ListItem(name, iconImage="DefaultFolder.png", thumbnailImage=iconimage)
        contextMenu = [('More Info',"XBMC.RunScript("+os.path.join( home, 'default.py' )+", info, "+info+")")]
        liz.addContextMenuItems(contextMenu, True)
        ok=xbmcplugin.addDirectoryItem(handle=int(sys.argv[1]),url=u,listitem=liz,isFolder=False)
        return ok


def addDir(name,url,iconimage,mode,page):
        u=sys.argv[0]+"?url="+urllib.quote_plus(url)+"&mode="+str(mode)+"&name="+urllib.quote_plus(name)+"&page="+str(page)
        ok=True
        liz=xbmcgui.ListItem(name, iconImage="DefaultFolder.png", thumbnailImage=iconimage)
        ok=xbmcplugin.addDirectoryItem(handle=int(sys.argv[1]),url=u,listitem=liz,isFolder=True)
        return ok


def run_plugin():
    params=get_params()
    url=None
    name=None
    mode=None

    try:
        url=urllib.unquote_plus(params["url"])
    except:
        pass
    try:
        name=urllib.unquote_plus(params["name"])
    except:
        pass
    try:
        mode=int(params["mode"])
    except:
        pass
    try:
        page=params["page"]
    except:
        pass

    print "Mode: "+str(mode)
    print "URL: "+str(url)
    print "Name: "+str(name)

    if mode==None:
        print ""
        Categories()

    elif mode==1:
        print""
        getTorrents(url, page)

    elif mode==2:
        print""

    elif mode==3:
        print""
        Download(url)

    elif mode==4:
        print""
        Search()

    xbmcplugin.endOfDirectory(int(sys.argv[1]))


if sys.argv[1] == 'info':
    webviewer.getWebResult(sys.argv[2])
    
else:
    run_plugin()
