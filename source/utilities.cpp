#include "../include/utilities.hpp"

OneginStatusCode HtmlLogStarter() {

	printf("<!DOCTYPE HTML PUBLIC>\n");
	printf("<html>\n");

	printf("\t<head>\n");
	printf("\t\t<title>Onegin log file</title>\n");
	printf("\t</head>\n");

	printf("\t<style>\n");
	printf("\t\t.anchor { \n\t\t\toutline: none; \n\t\t\ttext-decoration: none; \n\t\t\tpadding: 2px 1px 0; \n\t\t}\n");
	printf("\t\t.anchor:link { \n\t\t\tcolor: #265301; \n\t\t}\n");
	printf("\t\t.anchor:visited { \n\t\t\tcolor: #437a16; \n\t\t}\n");
	printf("\t\t.anchor:focused { \n\t\t\tborder-bottom: 1px solid; \n\t\t\tbackground: #bae498; \n\t\t}\n");
	printf("\t\t.anchor:hover { \n\t\t\tborder-bottom: 1px solid; \n\t\t\tbackground: #cdfeaa; \n\t\t}\n");
	printf("\t\t.string_inf > td { \n\t\t\ttext-align: center; \n\t\t}\n");
	printf("\t\t.string_number { \n\t\t\tcolor: blue; \n\t\t}\n");
	printf("\t\t.struct_pointer { \n\t\t\tcolor: red; \n\t\t}\n");
	printf("\t\t.string_pointer { \n\t\t\tcolor: brown; \n\t\t}\n");
	printf("\t\t.string { \n\t\t\tcolor: green; \n\t\t}\n");
	printf("\t\t.string_size { \n\t\t\tcolor: pink; \n\t\t}\n");
	printf("\t\t.tb_str { \n\t\t\twidth: 100%%; \n\t\t}\n");
	printf("\t</style>\n");

	printf("\t<body>\n");
	printf("\t\t<h1 align='center' name='top'>Onegin file for debug</h1>\n");
	printf("\t\t<p><a href='#time' class='anchor'>Working time of program</a></p>\n");

	printf("\t\t<table class='tb_str'>\n");
	printf("\t\t\t<tr class='string_inf'>\n");
	printf("\t\t\t\t<td><h3>String number</h3></td>\n");
	printf("\t\t\t\t<td><h3>Struct pointer</h3></td>\n");
	printf("\t\t\t\t<td><h3>String pointer</h3></td>\n");
	printf("\t\t\t\t<td><h3>String</h3></td>\n");
	printf("\t\t\t\t<td><h3>String size</h3></td>\n");
	printf("\t\t\t</tr>\n");

	return ONEGIN_NO_ERROR;
}

OneginStatusCode HtmlLogFinisher() {

	printf("\t\t<p><a href='#top' class='anchor'>TOP</a></p>\n");
	printf("\t</body>\n");
	printf("</html>\n");

	system("open log_eblan.html");

	return ONEGIN_NO_ERROR;
}
