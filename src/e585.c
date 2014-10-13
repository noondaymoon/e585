#include <pebble.h>

static Window *window;
static TextLayer *ntype_layer, *crr_layer, *cspd_layer, *trsf_layer, *ctime_layer;
static BitmapLayer *sig_layer, *cnct_layer, *wifi_layer, *batt_layer, *msd_layer;
static BitmapLayer *bg_layer, *ant_layer, *spdm_layer, *arw_layer, *clk_layer;

//appmessageのラベルを定義(参考：http://wisdom.sakura.ne.jp/programming/c/c51.html)
enum {
	KEY_SIG		= 0,
	KEY_NTYPE	= 1,
	KEY_CNCT	= 2,
	KEY_WIFI	= 3,
	KEY_BATT	= 4,
	KEY_CRR		= 5,
	KEY_MSD		= 6,
	KEY_CSPD	= 7,
	KEY_TRSF	= 8,
	KEY_CTIME	= 9,
	
};

//テキスト表示に使う変数の文字数も含めた定義
char 	sig_buffer		[4],
		ntype_buffer	[4],
		cnct_buffer		[4],
		wifi_buffer		[4],
		batt_buffer		[4],
		crr_buffer		[16],
		msd_buffer		[4],
		cspd_buffer		[16],
		trsf_buffer		[16],
		ctime_buffer	[8];

//appmessageよりtに収納された情報の処理
void process_tuple(Tuple *t)
	{
	int key = t->key; //keyを取得
	//int value = t->value->int32; //数値の場合は数値として取得(このコードでは未使用)
	char string_value[16];
	strcpy (string_value, t->value->cstring); //文字列の場合は文字列として取得
	//"strcpy"はstringをコピーする記述
	
	//ここからdictより取得した値に対応する動作
	switch (key) {
		
		//signal level
		case KEY_SIG:
		snprintf (sig_buffer, sizeof("x"), "%s", string_value);
		if (strcmp (sig_buffer, "1") == 0){
			bitmap_layer_set_bitmap (sig_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_SIG1));}
		else if (strcmp (sig_buffer, "2") == 0){
			bitmap_layer_set_bitmap (sig_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_SIG2));}
		else if (strcmp (sig_buffer, "3") == 0){
			bitmap_layer_set_bitmap (sig_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_SIG3));}
		else if (strcmp (sig_buffer, "4") == 0){
			bitmap_layer_set_bitmap (sig_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_SIG4));}
		else if (strcmp (sig_buffer, "5") == 0){
			bitmap_layer_set_bitmap (sig_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_SIG5));}
		else {layer_set_hidden (bitmap_layer_get_layer (sig_layer), true);}
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_sig: %s", sig_buffer);
		break;
		
		//network type
		case KEY_NTYPE:
		snprintf (ntype_buffer, sizeof("x"), "%s", string_value);
		if (strcmp (ntype_buffer, "1") == 0){
			text_layer_set_text (ntype_layer, "GSM");}
		else if (strcmp (ntype_buffer, "2") == 0){
			text_layer_set_text (ntype_layer, "GPRS");}
		else if (strcmp (ntype_buffer, "3") == 0){
			text_layer_set_text (ntype_layer, "EDGE");}
		else if (strcmp (ntype_buffer, "4") == 0){
			text_layer_set_text (ntype_layer, "3G");}
		else if (strcmp (ntype_buffer, "5") == 0){
			text_layer_set_text (ntype_layer, "H");}
		else if (strcmp (ntype_buffer, "6") == 0){
			text_layer_set_text (ntype_layer, "H");}
		else if (strcmp (ntype_buffer, "7") == 0){
			text_layer_set_text (ntype_layer, "H");}
		else {text_layer_set_text (ntype_layer, "");}
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_ntype: %s", ntype_buffer);
		break;
		
		//connect
		case KEY_CNCT:
		snprintf (cnct_buffer, sizeof("x"), "%s", string_value);
		if (strcmp (cnct_buffer, "1") == 0){
			bitmap_layer_set_bitmap(cnct_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_CNCT));}
		else {layer_set_hidden(bitmap_layer_get_layer(cnct_layer), true);}
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_cnct: %s", cnct_buffer);
		break;
		
		//wifi
		case KEY_WIFI:
		snprintf (wifi_buffer, sizeof("x"), "%s", string_value);
		if (strcmp (wifi_buffer, "0") == 0){
			bitmap_layer_set_bitmap (wifi_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_WIFI0));}
		else if (strcmp (wifi_buffer, "1") == 0){
			bitmap_layer_set_bitmap (wifi_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_WIFI1));}
		else if (strcmp (wifi_buffer, "2") == 0){
			bitmap_layer_set_bitmap (wifi_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_WIFI2));}
		else if (strcmp (wifi_buffer, "3") == 0){
			bitmap_layer_set_bitmap (wifi_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_WIFI3));}
		else if (strcmp (wifi_buffer, "4") == 0){
			bitmap_layer_set_bitmap (wifi_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_WIFI4));}
		else if (strcmp (wifi_buffer, "5") == 0){
			bitmap_layer_set_bitmap (wifi_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_WIFI5));}
		else {layer_set_hidden (bitmap_layer_get_layer (wifi_layer), true);}
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_wifi: %s", wifi_buffer);
		break;
		
		//battery_status
		case KEY_BATT:
		snprintf (batt_buffer, sizeof("x,x"), "%s", string_value);
		if (strcmp (batt_buffer, "0,0") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT0));}
		else if (strcmp (batt_buffer, "0,1") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT1));}
		else if (strcmp (batt_buffer, "0,2") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT2));}
		else if (strcmp (batt_buffer, "0,3") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT3));}
		else if (strcmp (batt_buffer, "0,4") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT4));}
		else if (strcmp (batt_buffer, "0,5") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT5));}
		else if (strcmp (batt_buffer, "0,6") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT6));}
		else if (strcmp (batt_buffer, "0,7") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT7));}
		else if (strcmp (batt_buffer, "0,8") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT8));}
		else if (strcmp (batt_buffer, "0,9") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT9));}
		else if (strcmp (batt_buffer, "1,0") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT10));}
		else if (strcmp (batt_buffer, "1,1") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT11));}
		else if (strcmp (batt_buffer, "1,2") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT12));}
		else if (strcmp (batt_buffer, "1,3") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT13));}
		else if (strcmp (batt_buffer, "1,4") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT14));}
		else if (strcmp (batt_buffer, "1,5") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT15));}
		else if (strcmp (batt_buffer, "1,6") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT16));}
		else if (strcmp (batt_buffer, "1,7") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT17));}
		else if (strcmp (batt_buffer, "1,8") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT18));}
		else if (strcmp (batt_buffer, "1,9") == 0){
			bitmap_layer_set_bitmap (batt_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_BATT19));}
		else {layer_set_hidden (bitmap_layer_get_layer (batt_layer), true);}
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_batt: %s", batt_buffer);
		break;
		
		//carrier name
		case KEY_CRR:
		snprintf (crr_buffer, sizeof("xxxxxxxxxx"), "%s", string_value);
		text_layer_set_text(crr_layer, (char*) &crr_buffer);
		bitmap_layer_set_bitmap(ant_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_ANT));
		bitmap_layer_set_bitmap(spdm_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_SPDM));
		bitmap_layer_set_bitmap(arw_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_TRSF));
		bitmap_layer_set_bitmap(clk_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_CLK));
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_crr: %s", crr_buffer);
		break;
		
		//microSD
		case KEY_MSD:
		snprintf (msd_buffer, sizeof("x"), "%s", string_value);
		if (strcmp (msd_buffer, "0") == 0){
			bitmap_layer_set_bitmap(msd_layer, gbitmap_create_with_resource(RESOURCE_ID_ICON_MSDS));}
		else {layer_set_hidden(bitmap_layer_get_layer(msd_layer), true);}
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_msd: %s", msd_buffer);
		break;
		
		//current speed
		case KEY_CSPD:
		snprintf (cspd_buffer, sizeof("xxxxxxxxxx"), "%s", string_value);
		text_layer_set_text(cspd_layer, (char*) &cspd_buffer);
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_cspd: %s", cspd_buffer);
		break;
		
		//transfar volume
		case KEY_TRSF:
		snprintf (trsf_buffer, sizeof("xxxxxxxxxx"), "%s", string_value);
		text_layer_set_text(trsf_layer, (char*) &trsf_buffer);
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_trsf: %s", trsf_buffer);
		break;
		
		//connect time
		case KEY_CTIME:
		snprintf (ctime_buffer, sizeof("xx:xx"), "%s", string_value);
		text_layer_set_text(ctime_layer, (char*) &ctime_buffer);
		APP_LOG(APP_LOG_LEVEL_INFO, "incoming_ctime: %s", ctime_buffer);
		break;
			
	}
}

//appmessageの取り出し
static void in_received_handler (DictionaryIterator *iter, void *context)
	{
	(void) context;

	//データを取得し"t"に構造体として収納する
	Tuple *t = dict_read_first(iter);
	while (t!= NULL) //以下のオシゴトをmessageからnullが返ってくるまで繰り返す
		{
		process_tuple(t);
		t = dict_read_next(iter);
	}
}


//windowに素材を配置
void window_load (Window *window)
	{
	
	//background layer
	bg_layer = bitmap_layer_create (GRect (0, 40, 144, 80));
	bitmap_layer_set_background_color(bg_layer, GColorWhite);
	layer_add_child(window_get_root_layer(window), (Layer *) bg_layer);
	
	//sig_layer (bitmap)
	sig_layer = bitmap_layer_create(GRect(0, 0, 36, 36));
	bitmap_layer_set_alignment(sig_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) sig_layer);
	
	//ntype_layer (text)
	ntype_layer = text_layer_create (GRect(32, 4, 36, 12));
	text_layer_set_background_color(ntype_layer, GColorClear);
	text_layer_set_text_color(ntype_layer, GColorWhite);
	text_layer_set_text_alignment(ntype_layer, GTextAlignmentCenter);
	text_layer_set_font(ntype_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROIDB_11)));
	layer_add_child(window_get_root_layer(window), (Layer *)ntype_layer);
	
	//cnct_layer (bitmap)
	cnct_layer = bitmap_layer_create(GRect(32, 20, 36, 8));
	bitmap_layer_set_alignment(cnct_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) cnct_layer);
	
	//wifi_layer (bitmap)
	wifi_layer = bitmap_layer_create(GRect(72, 0, 36, 36));
	bitmap_layer_set_alignment(wifi_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) wifi_layer);
	
	//batt_layer (bitmap)
	batt_layer = bitmap_layer_create(GRect(108, 0, 36, 36));
	bitmap_layer_set_alignment(batt_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) batt_layer);
	
	//ロードが終わるまで表示させない都合により、ant_layer,spdm_layer,arw_layer,clk_layerはcase crrと連動
	
	//ant_layer (bitmap)
	ant_layer = bitmap_layer_create(GRect(0, 44, 36, 36));
	bitmap_layer_set_alignment(ant_layer, GAlignCenter);
	bitmap_layer_set_compositing_mode(ant_layer, GCompOpAssignInverted);
	layer_add_child(window_get_root_layer(window), (Layer *) ant_layer);
	
	//spdm_layer (bitmap)
	spdm_layer = bitmap_layer_create(GRect(0, 81, 36, 36));
	bitmap_layer_set_alignment(spdm_layer, GAlignCenter);
	bitmap_layer_set_compositing_mode(spdm_layer, GCompOpAssignInverted);
	layer_add_child(window_get_root_layer(window), (Layer *) spdm_layer);
	
	//arw_layer (bitmap)
	arw_layer = bitmap_layer_create(GRect(2, 127, 12, 12));
	bitmap_layer_set_alignment(arw_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) arw_layer);
		
	//crr_layer (text)
	crr_layer = text_layer_create (GRect(36, 50, 108, 20));
	text_layer_set_background_color(crr_layer, GColorClear);
	text_layer_set_text_color(crr_layer, GColorBlack);
	text_layer_set_text_alignment(crr_layer, GTextAlignmentCenter);
	text_layer_set_font(crr_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROIDB_18)));
	layer_add_child(window_get_root_layer(window), (Layer *)crr_layer);
	
	//cspd_layer (text)
	cspd_layer = text_layer_create (GRect(36, 87, 108, 42));
	text_layer_set_background_color(cspd_layer, GColorClear);
	text_layer_set_text_color(cspd_layer, GColorBlack);
	text_layer_set_text_alignment(cspd_layer, GTextAlignmentCenter);
	text_layer_set_font(cspd_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROIDB_18)));
	layer_add_child(window_get_root_layer(window), (Layer *)cspd_layer);

	//trsf_layer (text)
	trsf_layer = text_layer_create (GRect(15, 126, 60, 14));
	text_layer_set_background_color(trsf_layer, GColorClear);
	text_layer_set_text_color(trsf_layer, GColorWhite);
	text_layer_set_text_alignment(trsf_layer, GTextAlignmentCenter);
	text_layer_set_font(trsf_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROIDB_11)));
	layer_add_child(window_get_root_layer(window), (Layer *)trsf_layer);
	
	//ctime_layer (text)
	ctime_layer = text_layer_create (GRect(92, 126, 34, 12));
	text_layer_set_background_color(ctime_layer, GColorClear);
	text_layer_set_text_color(ctime_layer, GColorWhite);
	text_layer_set_text_alignment(ctime_layer, GTextAlignmentCenter);
	text_layer_set_font(ctime_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DROIDB_11)));
	layer_add_child(window_get_root_layer(window), (Layer *)ctime_layer);
	
	//clk_layer (bitmap)
	clk_layer = bitmap_layer_create(GRect(78, 127, 12, 12));
	bitmap_layer_set_alignment(clk_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) clk_layer);
	
	//msd_layer (bitmap)
	msd_layer = bitmap_layer_create(GRect(130, 127, 12, 12));
	bitmap_layer_set_alignment(msd_layer, GAlignCenter);
	layer_add_child(window_get_root_layer(window), (Layer *) msd_layer);
		
}

//windows素材の撤収
void window_unload (Window *window)
	{
	bitmap_layer_destroy(bg_layer);
	
	bitmap_layer_destroy(sig_layer);
	text_layer_destroy(ntype_layer);
	bitmap_layer_destroy(cnct_layer);
	bitmap_layer_destroy(wifi_layer);
	bitmap_layer_destroy(batt_layer);
	bitmap_layer_destroy(ant_layer);
	bitmap_layer_destroy(spdm_layer);
	bitmap_layer_destroy(arw_layer);
	bitmap_layer_destroy(clk_layer);
	text_layer_destroy(crr_layer);
	bitmap_layer_destroy(msd_layer);
	text_layer_destroy(cspd_layer);
	text_layer_destroy(trsf_layer);
	text_layer_destroy(ctime_layer);
}

//windowの表示を構成
void init()
	{
	//コピペ
	window = window_create();
  	window_set_background_color(window, GColorBlack);
 	window_set_fullscreen(window, false);
	
	WindowHandlers handlers = {
		.load = window_load,
		.unload = window_unload,
	};
	window_set_window_handlers(window, handlers);
	
	//appmessage eventsを登録？
	app_message_register_inbox_received(in_received_handler);
	//appmessageの最大入出力数？
	app_message_open (app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	window_stack_push(window, true);
}

void deinit ()
	{
	window_destroy (window);
}

int main (void)
	{
	init();
	app_event_loop();
	deinit();
}