import urllib2
import os
import json
import time
import sys
from urllib2 import urlopen, URLError, HTTPError

def dlfile(url):
    # Open the url
    try:
        f = urlopen(url)
        print "downloading from " + url

        # Open our local file for writing
        print url.split('/')[-1]
        with open(os.path.basename(url.split('/')[-1]), "wb") as local_file:
            local_file.write(f.read())

    #handle errors
    except HTTPError, e:
        print "HTTP Error:", e.code, url
    except URLError, e:
        print "URL Error:", e.reason, url

def main(server_ip = '166.111.131.132', s_port = '8888', monitor_ip = 'localhost', m_port = '8888'):
	import socket
	localIP = socket.gethostbyname(socket.gethostname())
	client_id = localIP.split('.')[-1]
	while True:
		text = None
		try:
			addr = 'http://' + server_ip + ':' + s_port
			print addr
			text = urllib2.urlopen(addr)
		except Exception as e:
			print e
		if not text:
			raise Exception("error")
		jsonStr = text.read()
		jsonData = json.loads(jsonStr)
		print jsonData[0]['isok']
		print jsonData[1]['addr']
		if jsonData[0]['isok'] == 1:
			add_addr = 'http://' + server_ip + ':' + m_port + '/start/' + client_id
			urllib2.urlopen(add_addr)
			dlfile(addr + jsonData[1]['addr'])
			add_addr = 'http://' + server_ip + ':' + m_port + '/finish/' + client_id
			urllib2.urlopen(add_addr)
			# TODO finish the extra processes
			return 
		time.sleep(1)

if __name__ == '__main__':
	if len(sys.argv) == 5:
		main(sys.argv[1:])
	else:
		main()