#!/usr/bin/env python

import os
import sys
import SimpleHTTPServer
import SocketServer

os.chdir('site')

if sys.argv[1:]:
    port = int(sys.argv[1])
else:
    port = 8000

handler = SimpleHTTPServer.SimpleHTTPRequestHandler
httpd = SocketServer.TCPServer(('127.0.0.1', port), handler)

print "serving at port", port
httpd.serve_forever()
