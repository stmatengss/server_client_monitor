import tornado.web
import json
import os

all_client = set()

class MonitorHandler(tornado.web.RequestHandler):
    def get(self):
        global all_client
        items = ["running " + i for i in all_client]
        self.render("monitor.html", title = 'Monitor', items = items)

class StartHandler(tornado.web.RequestHandler):
    def get(self, id):
        idStr = str(id)
        global all_client
        all_client.add(idStr)

        # for i in all_client:
        #     print i
        self.write('add ' + idStr)

class FinishHandler(tornado.web.RequestHandler):
    def get(self, id):
        idStr = str(id)
        global all_client
        if idStr in all_client:
            all_client.remove(idStr)
        else:
            raise Exception('illegal id')
        # for i in all_client:
        #     print i
        self.write('delete ' + idStr)

if __name__ == "__main__":
    application = tornado.web.Application(
        handlers = [
            (r"/monitor", MonitorHandler),
            (r"/start/([0-9]+)", StartHandler),
            (r"/finish/([0-9]+)", FinishHandler)
        ],
    )
    application.listen(8888)
    tornado.ioloop.IOLoop.current().start()
