set -ve
openssl ecparam -genkey -name P-256 -out key-p256-priv.pem
openssl ec -in key-p256-priv.pem -pubout -out key-p256-pub.pem
echo "sign me" | openssl pkeyutl -inkey key-p256-priv.pem -sign -rawin -digest sha256 -out sig-p256.der
echo "sign me" | openssl pkeyutl -pubin -inkey key-p256-pub.pem -verify -rawin -digest sha256 -sigfile sig-p256.der
./convert 256 < sig-p256.der > sig-p256.raw
./convert < sig-p256.raw > sig-p256.der1

echo "sign me" | openssl pkeyutl -pubin -inkey key-p256-pub.pem -verify -rawin -digest sha256 -sigfile sig-p256.der1
openssl ecparam -genkey -name P-384 -out key-p384-priv.pem
openssl ec -in key-p384-priv.pem -pubout -out key-p384-pub.pem
echo "sign me" | openssl pkeyutl -inkey key-p384-priv.pem -sign -rawin -digest sha384 -out sig-p384.der
echo "sign me" | openssl pkeyutl -pubin -inkey key-p384-pub.pem -verify -rawin -digest sha384 -sigfile sig-p384.der
./convert 384 < sig-p384.der > sig-p384.raw
./convert < sig-p384.raw > sig-p384.der1
echo "sign me" | openssl pkeyutl -pubin -inkey key-p384-pub.pem -verify -rawin -digest sha384 -sigfile sig-p384.der1

openssl ecparam -genkey -name brainpoolP256r1 -out key-brainpoolP256-priv.pem
openssl ec -in key-brainpoolP256-priv.pem -pubout -out key-brainpoolP256-pub.pem
echo "sign me" | openssl pkeyutl -inkey key-brainpoolP256-priv.pem -sign -rawin -digest sha256 -out sig-brainpoolP256.der
echo "sign me" | openssl pkeyutl -pubin -inkey key-brainpoolP256-pub.pem -verify -rawin -digest sha256 -sigfile sig-brainpoolP256.der
./convert 256 < sig-brainpoolP256.der > sig-brainpoolP256.raw
./convert < sig-brainpoolP256.raw > sig-brainpoolP256.der1
echo "sign me" | openssl pkeyutl -pubin -inkey key-brainpoolP256-pub.pem -verify -rawin -digest sha256 -sigfile sig-brainpoolP256.der1

openssl ecparam -genkey -name brainpoolP384r1 -out key-brainpoolP384-priv.pem
openssl ec -in key-brainpoolP384-priv.pem -pubout -out key-brainpoolP384-pub.pem
echo "sign me" | openssl pkeyutl -inkey key-brainpoolP384-priv.pem -sign -rawin -digest sha384 -out sig-brainpoolP384.der
echo "sign me" | openssl pkeyutl -pubin -inkey key-brainpoolP384-pub.pem -verify -rawin -digest sha384 -sigfile sig-brainpoolP384.der
./convert 384 < sig-brainpoolP384.der > sig-brainpoolP384.raw
./convert < sig-brainpoolP384.raw > sig-brainpoolP384.der1
echo "sign me" | openssl pkeyutl -pubin -inkey key-brainpoolP384-pub.pem -verify -rawin -digest sha384 -sigfile sig-brainpoolP384.der1
