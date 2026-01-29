import web
import time


### Url mappings

urls = (
     '/', 'index',)

### Templates 
render = web.template.render('templates')

credentials = [None, None]

class index:
    form = web.form.Form(
        web.form.Textbox('ssid', web.form.notnull, description="Wifi Name:"),
        web.form.Textbox('passw', web.form.notnull, description="Password:"),
        web.form.Button('Store Credentials'),
    )

    def GET(self):
        """ Show page """
        form = self.form()
        return render.index(form, "")

    def POST(self):
        """ handle button clicked """
        form = self.form()
        if not form.validates():
            return render.index(form, "INPUT ERROR")

        # save data by ur method, or do some task
        
        credentials[0] = form.d.ssid
        credentials[1] = form.d.passw
        
        if None in credentials:
            print("Error, fill in all fields")
        else:
            print("SSID: ")
            print(form.d.ssid)
            print("PASS: ")
            print(form.d.passw)
            app.stop()
        # pyglet.save_data(form.d.fav_name, form.d.cur_name)
        #pyglet.draw(some_pic)
        #os.system(some_cmd)

        form = self.form()
        return render.index(form, "YOUR DATA SAVED")

app = web.application(urls, globals())

if __name__ == '__main__':
    app.run()
    while(True):
        print("Test")
        time.sleep(2)