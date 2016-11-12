import tornado.ioloop
import tornado.web
import json
import os

class MainHandler(tornado.web.RequestHandler):
    def get(self):
    	jsonStr = json.dumps([
    		{'isok':1}, 
    		{'addr':'/static/CCSP.zip'}
    		])
        self.write(jsonStr)

if __name__ == "__main__":
    application = tornado.web.Application(
        handlers = [(r"/", MainHandler)],
        static_path = os.path.join(os.path.dirname(__file__), "static")
    )
    application.listen(8888)
    tornado.ioloop.IOLoop.current().start()
