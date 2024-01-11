from farmbot import Farmbot, FarmbotToken
import threading

# PYTHON MULTITHREAD EXAMPLE.
# ==========================================================
# The main thread has a blocking loop that waits for user
# input. The W/A/S/D keys are used to move FarmBot. Commands
# are entered in a queue that are processed in a background
# thread so as to not be blocked when waiting for keyboard
# input.
# ==========================================================



class MyHandler:
    

    def __init__(self, bot):
        # Store "W", "A", "S", "D" in a queue
        self.queue = []
        # Maintain a flag that lets us know if the bot is
        # ready for more commands.
        self.busy = True
        self.bot = bot
        self.bot_x = 0
        self.bot_y = 0
        self.bot_z = 0

    def add_job(self, direction):
        d = direction.capitalize()
        if d in ["W", "A", "S", "D"]:
            self.queue.append(d)
            self.bot.read_status()

    def try_next_job(self):
        if (len(self.queue) > 0) and (not self.busy):
            command = self.queue.pop(0)
            print("sending " + command)
            self.busy = True
            if command == "W":
                self.bot_x += 10
                return self.bot.move_relative(10, 0, 0)
            if command == "A":
                self.bot_y += -10
                return self.bot.move_relative(0, -10, 0)
            if command == "S":
                self.bot_x += -10
                return self.bot.move_relative(-10, 0, 0)
            if command == "D":
                self.bot_y += 10
                return self.bot.move_relative(0, 10, 0)

    def on_connect(self, bot, mqtt_client):
        self.bot.read_status()
        pass

    def on_change(self, bot, state):
        is_busy = state['informational_settings']['busy']
        if is_busy != self.busy:
            if is_busy:
                print("Device is busy")
            else:
                print("Device is idle")

        self.busy = is_busy
        self.try_next_job()

    def on_log(self, _bot, log):
        print("LOG: " + log['message'] + f" total is ({self.bot_x},{self.bot_y},{self.bot_z})", )

    def on_response(self, _bot, _response):
        pass

    def on_error(self, _bot, response):
        print("ERROR: " + response.id)
        print("Reason(s) for failure: " + str(response.errors))


if __name__ == '__main__':
    # import Farmbot Web Account credentials
    fileFarmbotWebAccount = open("FarmbotWebAccount.txt", "r")
    usernameFarmbotWebAccount = fileFarmbotWebAccount.readline()
    passwordFarmbotWebAccount = fileFarmbotWebAccount.readline()

    # Before we begin, we must download an access token from the
    # API. To avoid copy/pasting passwords, it is best to create
    # an access token and then store that token securely:
    raw_token = FarmbotToken.download_token(usernameFarmbotWebAccount,
                                            passwordFarmbotWebAccount,
                                            "https://my.farm.bot")

    # This token is then passed to the Farmbot constructor:
    fb = Farmbot(raw_token)
    handler = MyHandler(fb)
    threading.Thread(target=fb.connect, name="foo", args=[handler]).start()
    print("ENTER A DIRECTION VIA WASD:")
    print("           ^")
    print("           W")
    print("       < A   S >")
    print("           D")
    print("           v")

    while(True):
        direction = input("> ")
        handler.add_job(direction)
        handler.try_next_job()