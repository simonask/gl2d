log("HEJSA VERDEN FRA JS!");

function A() {
	this.a = "hejsa";
}

function B() {
	this.b = "davs";
}
B.prototype = new A;

var b = new B();
log(b.a);

function initialize() {
	
}
