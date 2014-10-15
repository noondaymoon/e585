var getstatus = function(){ //ページを取得してアレコレする
	
	//var rooter = HTTPGET ( "http://192.168.1.1/en/conn_index.asp");
	
	//動作テスト用
	var rooter = HTTPGET ( "https://dl.dropboxusercontent.com/u/4570910/conn_index.asp");
		
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
	console.log("\nflux: " + flux);
	var currentspeed = flux[8].slice(1,-1);
	console.log("\ncurrent: " + currentspeed);
	
	//trsf
	var getdataflow = rooter.match(/top.data_flow = \[(.*?)\]/i);
	var dataflow = getdataflow[1].split(",");
	var totaltransfar = dataflow[3].slice(1,-1);
	
	
	console.log("getdataflow: "+getdataflow[1]);
	//ctime
	console.log("\nunixtime: "+ dataflow[0]);
	var connecttime = new Date((dataflow[0])*1000);
	
	console.log("connecttime: "+connecttime);
	
	var hour = (connecttime.getUTCHours() < 10) ? "0" + connecttime.getUTCHours() : connecttime.getUTCHours();
	console.log("hour: "+hour);
	var min = (connecttime.getUTCMinutes() < 10) ? "0" + connecttime.getUTCMinutes() : connecttime.getUTCMinutes();
	console.log("min: "+min);
	var time = hour + ":" + min;
	console.log("time: "+time);
	
	//keymake
	var sig = signal[1];
	console.log ("signal level: " + sig);
	
	var ntype = sysinfo[6];
	console.log ("network type: " + ntype);
	
	var cnct = pppstatus[1];
	console.log ("cnct: " + cnct);
	
	var wifi = wifinumber[1];
	console.log ("connect wifi device: " + wifi);
	
	var batt = getbatteryinfo[1];
	console.log ("battery status: " + batt);
	
	var crr = carriername;
	console.log ("carrier name: " + crr);
	
	var msd = microsdstatus;
	console.log ("microSD status: " + msd);
	
	var cspd = currentspeed;
	console.log ("current trasfar speed: " + cspd);
	
	var trsf = totaltransfar;
	console.log ("total transfar volume: " + trsf);
	
	var ctime = time;
	console.log ("connect time: " + ctime);
	
	
		//c側へ送るための辞書を作成する

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
			
		}; //構造体
	
	//dictをc側へ送る
		Pebble.sendAppMessage(dict);
};

//pebble用アプリと連携するための最初の記述
Pebble.addEventListener("ready",
	function(e) {
		//pebbleから"ready"が送られてくるのを待って、以下のオシゴトをさせる
		getstatus();
	}
);

function HTTPGET (url) {
	var req = new XMLHttpRequest();
	req.open ("GET", url, false);
	req.send (null);
	return req.responseText;
}