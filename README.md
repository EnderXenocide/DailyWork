# DailyWork
This is a simple daily notepad application. 
Written in c++ with [wxWidgets](https://www.wxwidgets.org/) under [CodeLite](http://codelite.org/).
It uses json file to store data (see in docs folder for his shema).
Based on Julian Smart's wxWidgets rich text editor sample and STC test module, maintained by Wyo. You chose one editor between them with #define USE_RICH_EDIT TRUE.
Rich Edit fonctions are disabled because there is no wxRichTextHTMLHandler's load fonction. 

Librairies :
[RapidJSON GitHub](https://github.com/miloyip/rapidjson/)
[wxWidgets](https://www.wxwidgets.org/)
