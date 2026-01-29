import web



render = web.template.render('templates/')


urls = (
    '/(.*)', 'index'
)


class index:
    def GET(self, name):
        # i = web.input(name=None)
        # name = "bob"
        return render.index(name)        
        # return render.index()        
        # return "Hello world!"
    
    
    
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()