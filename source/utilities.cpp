#include "../include/utilities.hpp"

FilePaths file_paths = {};

OneginStatusCode FillerDebugPrinter(const String* string) {

	FILE* log_file = fopen(file_paths.log_html, "a");
	if (!log_file)
		ONEGIN_ERROR_CHECK(ONEGIN_FILE_OPEN_ERROR);

	static size_t str_num = 1;

	fprintf(log_file, "\t\t\t<tr class='string_inf'>\n");

	fprintf(log_file, "\t\t\t\t<td class='string_number' style='text-align: center;'><tt>%zu</tt></td>\n", str_num);

	fprintf(log_file, "\t\t\t\t<td class='struct_pointer'><tt>%p</tt></td>\n", string);

	fprintf(log_file, "\t\t\t\t<td class='string_pointer'><tt>%p</tt></td>\n", string->cur_str);

	fprintf(log_file, "\t\t\t\t<td class='string'><tt>('%d')", *(string->cur_str));
	fprintf(log_file, "%s", string->cur_str);
	fprintf(log_file, "('%d')</tt></td>\n", *(string->cur_str + string->cur_str_size - 2));

	fprintf(log_file, "\t\t\t\t<td class='string_size' style='text-align: center;'><tt>%zu</tt></td>\n", string->cur_str_size);

	fprintf(log_file, "\t\t\t</tr>\n");

	fprintf(log_file, "\n");

	str_num++;

	fclose(log_file);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode HtmlLogStarter() {

	FILE* log_file = fopen(file_paths.log_html, "w");
	if (!log_file)
		ONEGIN_ERROR_CHECK(ONEGIN_FILE_OPEN_ERROR);

	fprintf(log_file, "<!DOCTYPE HTML PUBLIC>\n");
	fprintf(log_file, "<html>\n");

	fprintf(log_file, "\t<head>\n");
	fprintf(log_file, "\t\t<title>Onegin log file</title>\n");
	fprintf(log_file, "\t</head>\n");

	fprintf(log_file, "\t<style>\n");
	fprintf(log_file, "\t\t.anchor { \n\t\t\toutline: none; \n\t\t\ttext-decoration: none; \
			\n\t\t\tpadding: 2px 1px 0; \n\t\t}\n");
	fprintf(log_file, "\t\t.anchor:link { \n\t\t\tcolor: #fff; \n\t\t}\n");
	fprintf(log_file, "\t\t.anchor:visited { \n\t\t\tcolor: #fff; \n\t\t}\n");
	fprintf(log_file, "\t\t.anchor:focused { \n\t\t\tborder-bottom: 1px solid; \n\t\t\tbackground: #bae498; \n\t\t}\n");

	fprintf(log_file, "\t\t.table_header > td > h3{ \n\t\t\tpadding: 10px 20px; \n\t\t}\n");
	fprintf(log_file, "\t\t.string_number { \n\t\t\tcolor: blue; \n\t\t}\n");
	fprintf(log_file, "\t\t.struct_pointer { \n\t\t\tcolor: red; \n\t\t}\n");
	fprintf(log_file, "\t\t.string_pointer { \n\t\t\tcolor: brown; \n\t\t}\n");
	fprintf(log_file, "\t\t.string { \n\t\t\tcolor: green; \n\t\t}\n");
	fprintf(log_file, "\t\t.string_size { \n\t\t\tcolor: violet; \n\t\t}\n");

	fprintf(log_file, "\t\t.tb_str { \n\t\t\twidth: 80%%; \n\t\t\tborder: 15px solid #F2F8F8; \
			\n\t\t\tborder-collapse: collapse; \n\t\t\tmargin: auto; \
			\n\t\t\ttable-layout: auto; \n\t\t\tmargin-bottom: 20px; \
			\n\t\t\tborder-top: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_str th { \n\t\t\tfont-weight: bold; \n\t\t\tpadding: 5px; \
			\n\t\t\tbackground: #F2F8F8; \n\t\t\tborder: none; \
			\n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_str td { \n\t\t\tpadding: 10px; \n\t\t\tborder: none; \
			\n\t\t\ttext-align: left; \n\t\t\tborder-bottom: 5px solid #F2F8F8; \n\t\t}\n");
	fprintf(log_file, "\t\t.table_header > td { \n\t\t\ttext-align: center; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_str tbody tr:nth-child(odd) { \n\t\t\tbackground: #fff; \n\t\t}\n");
	fprintf(log_file, "\t\t.tb_str tbody tr:nth-child(even) { \n\t\t\tbackground: #F7F7F7; \n\t\t}\n");

	fprintf(log_file, "\t\t.time { \n\t\t\tcolor: #4A235A; \n\t\t\tfont-size: 30px; \
			\n\t\t\tmargin: center; \n\t\t}\n");

	fprintf(log_file, "\t\t.btn { \n\t\t\tborder: none; \n\t\t\tborder-radius: 15px; \n\t\t\ttext-decoration: none; \
    		\n\t\t\tcolor: white; \n\t\t\tbackground: #0B63F6; \n\t\t\tbox-shadow: 0 5px 0 #003CC5; \
			\n\t\t\tfont-size: 16px; \n\t\t\tpadding-block: 8px; \n\t\t\tpadding-inline: 15px; \n\t\t}\n");
	fprintf(log_file, "\t\t.btn:hover { \n\t\t\tbackground: #003CC5; \n\t\t\tbox-shadow: none; \n\t\t\tposition: relative; \
    		\n\t\t\ttop: 5px; \n\t\t}\n");

	fprintf(log_file, "\t\th1[name='top'] { \n\t\t\tcolor: #4B0082; \n\t\t\tfont-style: italic; \
			\n\t\t\ttext-decoration: underline; \n\t\t}\n");
	fprintf(log_file, "\t</style>\n");

	fprintf(log_file, "\t<body>\n");
	fprintf(log_file, "\t\t<h1 align='center' name='top'><tt>If BedaDedBeda go suda</tt></h1>\n");
	fprintf(log_file, "\t\t<p><a href='#time' class='anchor'><button class='btn'><tt>Working time of program</tt></button></a></p><br>\n");

	fprintf(log_file, "\t\t<table class='tb_str'>\n");
	fprintf(log_file, "\t\t\t<tr class='table_header'>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Number</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>Struct pointer</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>String pointer</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>String</tt></h3></td>\n");
	fprintf(log_file, "\t\t\t\t<td><tt><h3>String size</h3></tt></td>\n");
	fprintf(log_file, "\t\t\t</tr>\n");

	fclose(log_file);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode WorkTime(double time, const char* sort_type) {

	FILE* log_file = fopen(file_paths.log_html, "a");
	if (!log_file)
		ONEGIN_ERROR_CHECK(ONEGIN_FILE_OPEN_ERROR);

	fprintf(log_file, "\t\t</table>\n");
	fprintf(log_file, "\t\t<p class='time'><a name='time'><tt>Working Time with %s: %lf ms</tt></a></p>\n",
			sort_type, time / CLOCKS_PER_SEC);

	fclose(log_file);

	return ONEGIN_NO_ERROR;
}

OneginStatusCode HtmlLogFinisher() {

	FILE* log_file = fopen(file_paths.log_html, "a");
	if (!log_file)
		ONEGIN_ERROR_CHECK(ONEGIN_FILE_OPEN_ERROR);

	fprintf(log_file, "\t\t<p><a href='#top' class='anchor'><button class='btn'><tt>TOP</tt></button></a></p>\n");
	fprintf(log_file, "\t</body>\n");
	fprintf(log_file, "</html>\n");

	fclose(log_file);

	system("open log_eblan.html");

	return ONEGIN_NO_ERROR;
}

const char* ErrorsMessenger(OneginStatusCode status) {
	switch(status) {
		case ONEGIN_NO_ERROR:		  return "NO ERROR";
		case ONEGIN_FILE_OPEN_ERROR:  return "FILE OPEN ERROR";
		case ONEGIN_FILE_READ_ERROR:  return "FILE READ ERROR";
		case ONEGIN_ALLOC_ERROR: 	  return "MEMORY ALLOCATION ERROR";
		case ONEGIN_SORT_MODE_ERROR:  return "SORT MODE ERROR";
		case ONEGIN_INPUT_FILE_ERROR: return "INPUT FILE ERROR";
		case ONEGIN_FEW_ARG_ERROR:	  return "FEW ARGUMENTS ERROR";
		default: 					  return "UNDEFINED ERROR";
	}
}
