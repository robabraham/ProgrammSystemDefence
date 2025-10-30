#!/bin/bash

# 1. Ստեղծել նոր տեքստային ֆայլեր
touch file1.txt file2.txt

# 2. Ստեղծել նոր թղթապանակ և տեղափոխել 3 ֆայլ այնտեղ
mkdir new_folder
touch new_folder/{a.txt,b.txt,c.txt}
echo "Ֆայլերը հաջողությամբ ստեղծվեցին new_folder-ում."

# 3. Ստուգել արդյոք 2-րդ քայլում ստեղծված թղթապանակը գոյություն ունի, 
# եթե այո՝ ստեղծել նոր ֆայլ SEMNCNT.txt
if [ -d "new_folder" ]; then
    touch new_folder/SEMNCNT.txt
    echo "SEMNCNT ֆայլը ստեղծվեց new_folder-ի մեջ."
else
    echo "new_folder-ը գոյություն չունի."
fi

# 4. Նույն կերպ ստուգել թղթապանակի գոյությունը և ստեղծել մեկ այլ ֆայլ՝ second.txt
if [ -d "new_folder" ]; then
    touch new_folder/second.txt
    echo "second.txt ֆայլը ևս ստեղծվեց new_folder-ի մեջ."
else
    echo "new_folder-ը չի գտնվել։"
fi
