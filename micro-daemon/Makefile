CC = gcc
OUTPUT_FILE = ce.image.server.daemon.o
SERVICE_NAME = ce-image-server
SERVICE_LOG_FILE = ce-image-server.log
SERVICE_LOG_PATH = /var/log
SERVICE_FILE = ${SERVICE_NAME}.service
SERVICE_PATH_FILE = /etc/systemd/system
CONFIG_FILE_NAME = imageserver.cfg
CONFIG_PAHT_FILE = /etc/ceserver
main: daemon.c
	@${CC} ./server/CEServer.c ./config/config.c daemon.c -o ${OUTPUT_FILE} -lmicrohttpd `pkg-config --libs libconfig`
install: 	

	cp ${OUTPUT_FILE} /usr/bin/${OUTPUT_FILE}
	cp ${SERVICE_FILE} ${SERVICE_PATH_FILE}/${SERVICE_FILE}
	cp ${SERVICE_LOG_FILE} ${SERVICE_LOG_PATH}/${SERVICE_LOG_FILE}
	cp config/${CONFIG_FILE_NAME} ${CONFIG_PAHT_FILE}/${CONFIG_FILE_NAME}
clean: 
	rm  *.o
	rm /usr/bin/${OUTPUT_FILE} 
	rm ${SERVICE_PATH_FILE}/${SERVICE_FILE}
	rm ${SERVICE_LOG_PATH}/${SERVICE_LOG_FILE}
	rm ${CONFIG_PAHT_FILE}/${CONFIG_FILE_NAME}
open_log:
	code  ${SERVICE_LOG_PATH}/${SERVICE_LOG_FILE}

sys_start: 
	systemctl start ce-image-server
sys_status:
	systemctl  status ${SERVICE_NAME} 
sys_stop: 
	systemctl stop ${SERVICE_NAME}
	
ser_start:
	service ${SERVICE_NAME} start 
ser_status:
	service ${SERVICE_NAME} status 
ser_stop:
	service ${SERVICE_NAME} stop 
journal: 
	journalctl -f -a -u ${SERVICE_NAME}