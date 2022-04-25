FILES="server client aesd-application"

make CROSS_COMPILE=arm-linux-gnueabihf- ${FILES}

scp ${FILES} ip update_ip.sh root@128.138.189.42:/usr/bin/aesd-project/