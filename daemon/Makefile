CC = gcc
OUTPUT_FILE = ce.image.server.daemon.o
SERVICE_NAME = ce-image-server
SERVICE_LOG_FILE = ce-image-server.log
SERVICE_LOG_PATH = /var/log
SERVICE_FILE = ${SERVICE_NAME}.service
SERVICE_PATH_FILE = /etc/systemd/system
main: daemon.c
	@${CC} ./server/CEServer.c daemon.c -o ${OUTPUT_FILE} 
install: 	

	cp ${OUTPUT_FILE} /usr/bin/${OUTPUT_FILE}
	cp ${SERVICE_FILE} ${SERVICE_PATH_FILE}/${SERVICE_FILE}
	cp ${SERVICE_LOG_FILE} ${SERVICE_LOG_PATH}/${SERVICE_LOG_FILE}
clean: 
	rm -rf *.o
	rm /usr/bin/${OUTPUT_FILE} 
	rm ${SERVICE_PATH_FILE}/${SERVICE_FILE}
	rm -rf ${SERVICE_LOG_PATH}/${SERVICE_LOG_FILE}
service_start: 
	systemctl start ce-image-server
service_status:
	systemctl  status ${SERVICE_NAME} 
service_stop: 
	systemctl stop ${SERVICE_NAME}
