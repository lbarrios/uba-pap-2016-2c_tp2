DEBUG = False

def debug(*args):
    pass
if __debug__ and DEBUG:
    def debug(*args):
        print(*args)
