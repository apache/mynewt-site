#!/usr/bin/env python

import os
import sys

is_python3 = sys.version_info[0] >= 3

if is_python3:
    from http.server import HTTPServer, SimpleHTTPRequestHandler
else:
    import SimpleHTTPServer
    import SocketServer

os.chdir('site')

if sys.argv[1:]:
    port = int(sys.argv[1])
else:
    port = 8000

server_address = ('', 8000)
print("serving at port {}".format(port))

if is_python3:
    httpd = HTTPServer(server_address, SimpleHTTPRequestHandler)
else:
    handler = SimpleHTTPServer.SimpleHTTPRequestHandler
    httpd = SocketServer.TCPServer(('127.0.0.1', port), handler)

httpd.serve_forever()
