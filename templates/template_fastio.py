import sys
# import io, os

def fast_io():
    input = sys.stdin.readline

    # # reads bytes
    # # use input().decode().strip() for strings, otherwise just cast
    # input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

    print = sys.stdout.write # can only output strings

    return input, print

def main():
    input, print = fast_io()




if __name__ == "__main__":
    main()

