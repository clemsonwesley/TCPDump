import random
def fuzzer(max_length=100, char_start=32, char_range=32):
    """A string of up to `max_length` characters
    in the range [`char_start`, `char_start` + `char_range`]"""
    string_length = random.randrange(0, max_length + 1)
    out = ""
    for i in range(0, string_length):
        out += chr(random.randrange(char_start, char_start + char_range))
     #   out2 = chr(random.randrange(char_start, char_start + char_range))
     #   out2 = '\n' +  out2[0:5] + " IP " + out2[5:]
     #   out += out2
    return out

def create_file():
    out_file = open('fuzzed.txt', 'w')
    for i in range(1000):
        out_file.write(fuzzer()+'\n')
    out_file.close()

def main():
    create_file()
            

main()
