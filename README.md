# Probe
The set of often used tools[COMBINED] in order to manage many useful operations

PocoConnection - Simple interface for MySQL connection using POCO and was created to the needs of the SEth.
Database pre-defined consists of 5 colmuns(UserID, Name, Surname, IP, City).
Available operations :
-ShowAll
-Insert
-GetIDFromIP
-SelectOne

As the name of the TCPServer-Client implies, it's simple class for creating TCP Server and Client asa per POCO.

Lotto.cpp - Short project which computes the most common numbers from the ALL(since 1975(?)) Lotto's lotteries and then shows it's occur.
All data are derived from the Lotto_data.txt file.

updownloader.sh - Script which allows us to uploading and downloading file(s) from the command line to the https://bashupload.com servers.
Examples:
updownloader.sh /home/Mateusz/scrip1.sh
updownloader.sh -d /home/Mateusz/dumps
updownloader.sh 'file1.sh' 'file2.sh' 'file3.sh'

script.sh - Simple garbage cleaning script which is based on the given pattern.
