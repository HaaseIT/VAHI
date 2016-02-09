function BrowserCheck() {
	var b = navigator.userAgent.toLowerCase()

	// get browser version
	this.major = this.v = parseInt(navigator.appVersion)
	this.minor = parseFloat(navigator.appVersion)

	// check for Netscape detect masked browsers workaround for NN6 returning navigator.appVersion = 5
	this.ns = (this.major >= 4 && ((b.indexOf("mozilla") != -1) && (b.indexOf("spoofer") == -1) && (b.indexOf("compatible") == -1) && (b.indexOf("opera") == -1) && (b.indexOf("webtv") == -1)))
	this.ns4 = (this.ns && (this.major == 4))
	this.ns4up = (this.ns && (this.major >= 4))
	this.ns5 = (this.ns && (this.major == 5))
	this.ns5up = (this.ns && (this.major >= 5))
	this.ns6 = (this.ns && ((this.major == 6) || (b.indexOf("netscape6") != -1)))
	this.ns6up = (this.ns && ((this.major >= 6) || this.ns6))

	// check for Microsoft Internet Explorer detect masked browsers workaround for IE5 returning navigator.appVersion = 4
	this.ie = (this.major >= 4 && ((b.indexOf("msie") != -1) && (b.indexOf("spoofer") == -1) && (b.indexOf("opera") == -1) && (b.indexOf("webtv") == -1)))
	this.ie4 = (b.indexOf("msie 4") != -1)
	this.ie4up = (this.ie && (this.major >= 4))
	this.ie5 = (b.indexOf("msie 5") != -1)
	this.ie5up = (this.ie && (parseInt(b.substr(b.indexOf("msie")+5)) >= 5 || this.ie5))
	this.ie6 = (b.indexOf("msie 6") != -1)
	this.ie6up = (this.ie && (parseInt(b.substr(b.indexOf("msie")+5)) >= 6 || this.ie6))

	// Set new versions
	if (this.ie5up) {
		this.major = parseInt(b.substr(b.indexOf("msie")+5))
		this.minor = parseInt(b.substr(b.indexOf("msie")+6+this.major.toString().length))
		}
	
	// detect Opera
    this.opera = (b.indexOf("opera") != -1)
	this.opera3 = (b.indexOf("opera 3") != -1)
	this.opera4 = (b.indexOf("opera 4") != -1 || (this.opera && this.major == 4))
	this.opera5 = (b.indexOf("opera 5") != -1 || (this.opera && this.major == 5))
    this.opera6 = (b.indexOf("opera 6") != -1 || (this.opera && this.major == 6))
    this.opera6up = (this.opera6)
    this.opera5up = (this.opera5) || (this.opera6up)
    this.opera4up = (this.opera4) || (this.opera5up)
    this.opera3up = (this.opera3) || (this.opera4up)

	if (this.opera) {
		this.ns = this.ns4 = this.ns4up = this.ns5 = this.ns5up = this.ns6 = this.ns6up = this.ie = this.ie4 = this.ie4up = this.ie5 = this.ie5up = this.ie6 = this.ie6up = false
		}

	// check for Mozilla
	this.mozilla = (b.indexOf("mozilla") != -1)
	this.mozilla5 = this.mozilla // compatibility
	// Set versions
	if (this.mozilla && !this.ns4) {
		this.major = parseInt(b.substr(b.indexOf("rv:")+3))
		this.minor = parseFloat(b.substr(b.indexOf("rv:")+4+this.major.toString().length))
		}
	
	// check Konqueror
	this.konqueror = (b.indexOf("konqueror") != -1)
	if (this.konqueror) this.mozilla = this.mozilla5 = false
	// Set versions
	if (this.konqueror) {
		this.major = parseInt(b.substr(b.indexOf("konqueror/")+10))
		this.minor = parseFloat(b.substr(b.indexOf("konqueror/")+11+this.major.toString().length))
		this.ns = this.ns5 = this.konqueror
		}
	
	this.min = (this.ns || this.ie  || this.opera4up || this.konqueror)
	
	// platform detection without the use of document.platform
	this.win = this.pc = (b.indexOf("win") != -1 || b.indexOf("16bit") != -1)
	this.mac = (b.indexOf("mac") != -1)
	this.linux = (b.indexOf("linux") != -1)
	
	// object detection
	this.all = (document.all) ? true : false
	this.layers = (document.layers) ? true : false
	this.dom = (document.getElementById) ? true : false

	this.java = (navigator.javaEnabled())
	this.print = (window.print) ? true : false
	
	this.images = (document.images) ? true : false
	this.frames = (window.frames) ? true : false
	this.screen = (window.screen) ? true : false
	
	// JavaScript version detection (workaround for NS3 returning 1.2 instead of 1.1)
	if (this.opera3) this.js = 1.1
	else if ((this.ns4 && this.minor <= 4.05) || this.ie4) this.js = 1.2
	else if ((this.ns4 && this.minor > 4.05) || this.ie5up || this.opera4up) this.js = 1.3
	else if (this.ns5 && !this.ns6up) this.js = 1.4
	else if (this.ns6up || this.konqueror) this.js = 1.5
	}

// automatically create the "is" object
is = new BrowserCheck()

function WindowAttributes() {
	if (is.ie) {
		this.width = document.body.clientWidth
		this.height	= document.body.clientHeight
		}			
	if (is.ns || is.opera || is.konqueror) {
		this.width = window.innerWidth
		this.height = window.innerHeight
		}
	}
