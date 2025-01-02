import random
import string

def generate_key(length):
    characters = string.ascii_letters + string.digits
    key = ''.join(random.choice(characters) for i in range(length))
    return key

def save_keys(filename, num_keys, key_length):
    with open(filename, 'w') as file:
        for _ in range(num_keys):
            key = generate_key(key_length)
            file.write(key + '\n')

# Example usage
save_keys('key.txt', 100, 16)
