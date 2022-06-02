# Affine cipher
from math import gcd

# generate alphabets
alphabet = [chr(i) for i in range(97, 97+26)]
letter_to_index = dict(zip(alphabet, range(len(alphabet))))
index_to_letter = dict(zip(range(len(alphabet)), alphabet))


def encrypt(message, a, b):
    """etc"""
    # inv test
    if not gcd(a, len(alphabet)) == 1:
        print("lambda and 26 are not co-prime")
        exit(1)

    # format message if need be
    message = message.replace(' ', '').replace('.', '').replace(',', '').lower()

    # y = (ax + b)(mod 26)
    cipher = ''
    for letter in message:
        y = (a*letter_to_index[letter] + b) % len(alphabet)
        cipher += index_to_letter[y]

    return cipher.upper()


def decrypt(cipher, a, b):
    """etc"""
    # format cipher if need be
    cipher = cipher.lower()

    # y = (inv(a)*y - b)(mod 26)
    if gcd(a, len(alphabet)) != 1:
        print("Error")
        exit(1)
    # let inv(a) be z
    # u can use euler phi function to get a's inverse
    z = pow(a, -1, len(alphabet))

    # x = (z*(y - b))(mod 26)
    plain = ''
    for letter in cipher:
        y = (z * (letter_to_index[letter] - b)) % len(alphabet)
        plain += index_to_letter[y]

    return plain


def main():
    """etc"""
    while True:
        while True:
            a = int(input('Enter Lambda: '))
            b = int(input('Enter K: '))
            if not gcd(a, b) == 1:
                print(f"lambda ({a}) and k ({b}) are not co-prime\n")
                print("Try again\n")
            elif not gcd(a, len(alphabet)) == 1:
                print(f"lambda {a} and m {len(alphabet)} are not co-prime\n")
            else:
                break

        choice = int(input('''What Kind of Input text do you wish to enter?
        1) Plain Text (Encryption)
        2) Cipher Text (Decryption)
        3) Exit (Otherwise)
        '''))

        if choice == 1:
            pt = input('Enter plain text (to encrypt): ')
            ct = encrypt(pt, a, b)
            print('Cipher Text is: ' + ct)

        elif choice == 2:
            ct = input('Enter cipher text (to decrypt): ')
            pt = decrypt(ct, a, b)
            print('Plain Text is: ' + pt)

        elif choice == 3:
            print("Goodbye")
            exit(0)

        else:
            print("Invalid option")
            main()

        while True:
            cont = int(input('''Would you like to crypt again?
            1) Yes
            2) No
            '''))

            if cont == 1:
                main()
            elif cont == 2:
                print('Goodbye')
                exit(0)


if __name__ == '__main__':
    main()
