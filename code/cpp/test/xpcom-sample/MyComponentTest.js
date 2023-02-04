function MyComponentTestGo() {
	try {
		netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
		const cid = "@mydomain.com/XPCOMSample/MyComponent;1";
		obj = Components.classes[cid].createInstance();
		obj = obj.QueryInterface(Components.interfaces.IMyComponent);
	} catch (err) {
		alert(err);
		return;
	}
	var res = obj.Add(3, 4);
	alert('Performing 3+4. Returned ' + res + '.');
}
