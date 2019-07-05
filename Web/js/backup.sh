#!/usr/bin/expect -f

#/bin/echo "Try login UDS100"
spawn ssh root@128.129.17.37
expect "password: "
send "Root_123\r"
expect "# "
send "ls\r"
expect "# "
send "cd /IDE0/ZTE_HLR/hlrserver_1_130/log\r"
expect "# "
send "pwd\r"
expect "# "
send "ls\r"
expect "# "
send "DBIO_FILE=`ls -t dbiosrv_1_130_*.log | head -1`\r"
#send "ls -t dbiosrv_1_130_*.log | head -1\r"
expect "# "
spawn scp *.log root@128.129.17.174:/home/backup/ProvLogDBIO

expect "password: "
send "uspproot123\r"


#/bin/echo "Changing the directory"
#spawn cd /IDE0/ZTE_HLR/hlrserver_1_130/log
#interact
expect "# "
send "ls\r"
#spawn ls
#interact
#echo "Find the name of the latest file"
#ls -t dbiosrv_1_130_*.log | head -1 >> ${DBIO_FILE}

#echo "Try downloading the file"

#spawn scp root@128.129.17.164:/home/backup/ProvLogDBIO ./${DBIO_FILE} 

#expect "password"
#send "uspproot123\r"

#interact

#echo "File Succesfully Downloaded"
