# Author: RickaPrincy <rckprincy@gmail.com>
pkgname=cpp_inquirer
pkgver=0.0.1
pkgrel=1
pkgdesc="C++ inquirer"
arch=('x86_64')
depends=()
url="https://github.com/RickaPrincy/cpp_inquirer"
license=('MIT')
source=("cpp_inquirer@$pkgver.tar.gz::https://github.com/RickaPrincy/cpp_inquirer/releases/download/v0.0.1/cpp_inquirer@$pkgver.tar.gz")

sha256sums=("1014298edf7b17be0218a8f36f733224b982ddbcf7c4352cca8b3971c5b29a81")

package() {
    echo "Installing to \"$pkgdir/usr/\""
    mkdir -p "$pkgdir/usr/include"
    mkdir -p "$pkgdir/usr/lib"
    cp -r "cpp_inquirer@$pkgver/include" "$pkgdir/usr"
    cp -r "cpp_inquirer@$pkgver/lib" "$pkgdir/usr"
}
