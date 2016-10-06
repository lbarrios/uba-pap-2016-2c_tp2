def debug(*args):
    pass
if __debug__:
    def debug(*args):
        print(*args)
