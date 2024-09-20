#include "../include/utilities.hpp"

OneginStatusCode FillerDebugPrinter(const String* string) {

	static size_t str_num = 1;

	printf("\t\t\t<tr class='string_inf'>\n");

	printf("\t\t\t\t<td class='string_number' style='text-align: center;'><tt>%zu</tt></td>\n", str_num);

	printf("\t\t\t\t<td class='struct_pointer'><tt>%p</tt></td>\n", string);

	printf("\t\t\t\t<td class='string_pointer'><tt>%p</tt></td>\n", string->cur_str);

	printf("\t\t\t\t<td class='string'><tt>('%d')", *(string->cur_str));
	printf("%s", string->cur_str);
	printf("('%d')</tt></td>\n", *(string->cur_str + string->cur_str_size - 2));

	printf("\t\t\t\t<td class='string_size' style='text-align: center;'><tt>%zu</tt></td>\n", string->cur_str_size);

	printf("\t\t\t</tr>\n");

	printf("\n");

	str_num++;

	return ONEGIN_NO_ERROR;
}

OneginStatusCode HtmlLogStarter() {

	printf("<!DOCTYPE HTML PUBLIC>\n");
	printf("<html>\n");

	printf("\t<head>\n");
	printf("\t\t<title>Onegin log file</title>\n");
	printf("\t</head>\n");

	printf("\t<style>\n");
	printf("\t\t.anchor { \n\t\t\toutline: none; \n\t\t\ttext-decoration: none; \
			\n\t\t\tpadding: 2px 1px 0; \n\t\t}\n");
	printf("\t\t.anchor:link { \n\t\t\tcolor: #fff; \n\t\t}\n");
	printf("\t\t.anchor:visited { \n\t\t\tcolor: #fff; \n\t\t}\n");
	printf("\t\t.anchor:focused { \n\t\t\tborder-bottom: 1px solid; \n\t\t\tbackground: #bae498; \n\t\t}\n");

	printf("\t\t.table_header > td > h3{ \n\t\t\tpadding: 10px 20px; \n\t\t}\n");
	printf("\t\t.string_number { \n\t\t\tcolor: blue; \n\t\t}\n");
	printf("\t\t.struct_pointer { \n\t\t\tcolor: red; \n\t\t}\n");
	printf("\t\t.string_pointer { \n\t\t\tcolor: brown; \n\t\t}\n");
	printf("\t\t.string { \n\t\t\tcolor: green; \n\t\t}\n");
	printf("\t\t.string_size { \n\t\t\tcolor: violet; \n\t\t}\n");

	printf("\t\t.tb_str { \n\t\t\twidth: 80%%; \n\t\t\tborder: 15px solid #F2F8F8; \
			\n\t\t\tborder-collapse: collapse; \n\t\t\tmargin: auto; \
			\n\t\t\ttable-layout: auto; \n\t\t\tmargin-bottom: 20px; \
			\n\t\t\tborder-top: 5px solid #F2F8F8; \n\t\t}\n");
	printf("\t\t.tb_str th { \n\t\t\tfont-weight: bold; \n\t\t\tpadding: 5px; \
			\n\t\t\tbackground: #F2F8F8; \n\t\t\tborder: none; \
			\n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	printf("\t\t.tb_str td { \n\t\t\tpadding: 10px; \n\t\t\tborder: none; \
			\n\t\t\ttext-align: left; \n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	printf("\t\t.table_header > td { \n\t\t\ttext-align: center; \n\t\t}\n");
	printf("\t\t.tb_str tbody tr:nth-child(odd) { \n\t\t\tbackground: #fff; \n\t\t}\n");
	printf("\t\t.tb_str tbody tr:nth-child(even) { \n\t\t\tbackground: #F7F7F7; \n\t\t}\n");

	printf("\t\t.time { \n\t\t\tcolor: #4A235A; \n\t\t\tfont-size: 30px; \
			\n\t\t\tmargin: center; \n\t\t}\n");

	printf("\t\t.btn { \n\t\t\tborder: none; \n\t\t\tborder-radius: 15px; \n\t\t\ttext-decoration: none; \
    		\n\t\t\tcolor: white; \n\t\t\tbackground: #0B63F6; \n\t\t\tbox-shadow: 0 5px 0 #003CC5; \
			\n\t\t\tfont-size: 16px; \n\t\t\tpadding-block: 8px; \n\t\t\tpadding-inline: 15px; \n\t\t}\n");
	printf("\t\t.btn:hover { \n\t\t\tbackground: #003CC5; \n\t\t\tbox-shadow: none; \n\t\t\tposition: relative; \
    		\n\t\t\ttop: 5px; \n\t\t}\n");

	printf("\t\th1[name='top'] { \n\t\t\tcolor: #4B0082; \n\t\t\tfont-style: italic; \
			\n\t\t\ttext-decoration: underline; \n\t\t}\n");
	printf("\t</style>\n");

	printf("\t<body>\n");
	printf("\t\t<h1 align='center' name='top'><tt>If BedaDedBeda go suda</tt></h1>\n");
	printf("\t\t<p><a href='#time' class='anchor'><button class='btn'><tt>Working time of program</tt></button></a></p><br>\n");

	printf("\t\t<table class='tb_str'>\n");
	printf("\t\t\t<tr class='table_header'>\n");
	printf("\t\t\t\t<td><tt><h3>Number</tt></h3></td>\n");
	printf("\t\t\t\t<td><tt><h3>Struct pointer</tt></h3></td>\n");
	printf("\t\t\t\t<td><tt><h3>String pointer</tt></h3></td>\n");
	printf("\t\t\t\t<td><tt><h3>String</tt></h3></td>\n");
	printf("\t\t\t\t<td><tt><h3>String size</h3></tt></td>\n");
	printf("\t\t\t</tr>\n");

	return ONEGIN_NO_ERROR;
}

OneginStatusCode WorkTime(double time, const char* sort_type) {

	printf("\t\t</table>\n");
	printf("\t\t<p class='time'><a name='time'><tt>Working Time with %s: %lf ms</tt></a></p>\n",
			sort_type, time / CLOCKS_PER_SEC);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode HtmlLogFinisher() {

	printf("\t\t<p><a href='#top' class='anchor'><button class='btn'><tt>TOP</tt></button></a></p>\n");
	printf("\t</body>\n");
	printf("</html>\n");

	system("open log_eblan.html");

	return ONEGIN_NO_ERROR;
}

const char* ErrorsMessenger(OneginStatusCode status) {
	switch(status) {
		case ONEGIN_NO_ERROR:		 return "NO ERROR";
		case ONEGIN_FILE_OPEN_ERROR: return "FILE OPEN ERROR";
		case ONEGIN_FILE_READ_ERROR: return "FILE READ ERROR";
		case ONEGIN_ALLOC_ERROR: 	 return "ALLOCATION ERROR";
		case ONEGIN_SORT_MODE_ERROR: return "SORT MODE ERROR";
		default: 					 return "UNDEFINED ERROR";
	}
}
