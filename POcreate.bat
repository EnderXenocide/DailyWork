dir /B *.cpp > files.txt
"C:\Program Files (x86)\GnuWin32\bin\xgettext" --from-code=utf-8  -d app_name -s --keyword=_ -p ./lang -o dailywork.pot -ffiles.txt