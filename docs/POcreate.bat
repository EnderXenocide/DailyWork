cd..
dir /B *.cpp *.h > listecppfiles.txt
"C:\Program Files\gettext-iconv\xgettext" --from-code=utf-8  -d app_name -s --keyword=_ -p ./docs -o dailywork.pot -flistecppfiles.txt