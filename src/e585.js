var getstatus = function(){	
	var rooter = HTTPGET ( "http://192.168.1.1/en/conn_index.asp");
	
	//sig
	var getcellinfo = rooter.match(/var cellinfo  = \[(.*?)\]/i);
	var cellinfo = getcellinfo[1].split(",");
	var signal = cellinfo[4].match(/(\d)/);
	
	//ntype
	var getsysinfo = rooter.match(/var sysinfo = \[(.*?)\]/i);
	var sysinfo = getsysinfo[1].split(",");
	
	//connect
	var getpppstate = rooter.match(/var ppp_state = (.*)/i);
	var pppstatus = getpppstate[1].match(/(\d)/);
	
	//wifi
	var getwifinumber = rooter.match(/var wifi_number = (.*)/i);
	var wifinumber = getwifinumber[1].match(/(\d)/);
	
	//batt
	var getbatteryinfo = rooter.match(/var battery_info = \[(.*?)\]/i);
	
	//carrier
	var getoperator = rooter.match(/var operator_rat = \[(.*?)\]/i);
	var operator = getoperator[1].split(",");
	var carriername = operator[1].slice(2,-1).toLowerCase();
	
	//msd
	var getmicrosdstatus = rooter.match(/var sd_card_status = (.*)/i);
	var microsdstatus = getmicrosdstatus[1].slice(0,-1);
	
	//cspd
	var getflux = rooter.match(/top.flux= \[(.*?)\]/i);
	var flux = getflux[1].split(",");
	var currentspeed = flux[8].slice(1,-1);
	
	//trsf
	var getdataflow = rooter.match(/top.data_flow = \[(.*?)\]/i);
	var dataflow = getdataflow[1].split(",");
	var totaltransfar = dataflow[3].slice(1,-1);
	
	//ctime
	//console.log("\nunixtime: "+ dataflow[0]);
	var connecttime = new Date((dataflow[0])*1000);
	var hour = (connecttime.getUTCHours() < 10) ? "0" + connecttime.getUTCHours() : connecttime.getUTCHours();
	var min = (connecttime.getUTCMinutes() < 10) ? "0" + connecttime.getUTCMinutes() : connecttime.getUTCMinutes();
	var time = hour + ":" + min;
	
	//keymake
	var sig = signal[1];
	var ntype = sysinfo[6];
	var cnct = pppstatus[1];
	var wifi = wifinumber[1];
	var batt = getbatteryinfo[1];
	var crr = carriername;
	var msd = microsdstatus;
	var cspd = currentspeed;	
	var trsf = totaltransfar;	
	var ctime = time;	
	
	
	var dict = {
		"KEY_SIG"	: sig,
		"KEY_NTYPE"	: ntype,
		"KEY_CNCT"	: cnct,
		"KEY_WIFI"	: wifi,
		"KEY_BATT"	: batt,
		"KEY_CRR"	: crr,
		"KEY_MSD"	: msd,
		"KEY_CSPD"	: cspd,
		"KEY_TRSF"	: trsf,
		"KEY_CTIME"	: ctime,
	};
	Pebble.sendAppMessage(dict);
};

Pebble.addEventListener("ready",
	function(e) {
		getstatus();
	}
);

function HTTPGET (url) {
	var req = new XMLHttpRequest();
	req.open ("GET", url, false);
	req.send (null);
	return req.responseText;
}