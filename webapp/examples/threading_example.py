import threading
import time

foo = None

def thread_f():
    while True:
        print("thread ", "NONE" if foo == None else foo)
        time.sleep(2)

if __name__ == "__main__":
    x = threading.Thread(target=thread_f, daemon=True)
    x.start()
    for x in range(10):
        print("main")
        time.sleep(1)
    foo = "zelda"
    for x in range(10):
        print("main")
        time.sleep(1)

    