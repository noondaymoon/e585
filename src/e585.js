var getstatus = function(){ //ページを取得してアレコレする
	
	//var rooter = HTTPGET ( "192.168.1.1/en/conn_index.asp");
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
	
	//cspd (確認中)
	var getflux = rooter.match(/top.flux= \[(.*?)\]/i);
	var flux = getflux[1].split(",");
	console.log("\nflux: " + flux);
	var currentspeed = flux[6].slice(1,-1);
	console.log("\ncurrent: " + currentspeed);
	
	//trsf
	var getdataflow = rooter.match(/top.data_flow = \[(.*?)\]/i);
	var dataflow = getdataflow[1].split(",");
	var totaltransfar = dataflow[3].slice(1,-1);
	
	//ctime
	var connecttime = new Date((dataflow[0])*1000);
	var hour = (connecttime.getHours() < 10) ? "0" + connecttime.getHours() : connecttime.getHours();
	var min = (connecttime.getMinutes() < 10) ? "0" + connecttime.getMinutes() : connecttime.getMinutes();
	var time = hour + ":" + min;
	
	//keymake
	var sig = signal[1];
	console.log ("\nsignal level: " + sig);
	
	var ntype = sysinfo[6];
	console.log ("\nnetwork type: " + ntype);
	
	var cnct = pppstatus[1];
	console.log ("\ncnct: " + cnct);
	
	var wifi = wifinumber[1];
	console.log ("\nconnect wifi device: " + wifi);
	
	var batt = getbatteryinfo[1];
	console.log ("\nbattery status: " + batt);
	
	var crr = carriername;
	console.log ("\ncarrier name: " + crr);
	
	var msd = microsdstatus;
	console.log ("\nmicroSD status: " + msd);
	
	var cspd = currentspeed;
	console.log ("\ncurrent trasfar speed: " + cspd);
	
	var trsf = totaltransfar;
	console.log ("\ntotal transfar volume: " + trsf);
	
	var ctime = time;
	console.log ("\nconnect time: " + ctime);
	
	
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

