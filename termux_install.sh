#!/data/data/com.termux/files/usr/bin/bash
set -e

INSTALL_DIR="$PREFIX/bin"
BINARY_NAME="tmin"
VERSION="v0.1.0"

echo "Installing $BINARY_NAME $VERSION (alpha build, not stable)..."

# Download archive
curl -L "https://github.com/lordryns/tmin/releases/download/$VERSION/${BINARY_NAME}-termux-arm64.tar.gz" -o /tmp/${BINARY_NAME}.tar.gz

# Extract
tar -xvzf /tmp/${BINARY_NAME}.tar.gz -C /tmp

# Install
chmod +x /tmp/$BINARY_NAME
mv /tmp/$BINARY_NAME "$INSTALL_DIR/$BINARY_NAME"

# Cleanup
rm /tmp/${BINARY_NAME}.tar.gz

echo "$BINARY_NAME $VERSION installed!"
echo "Note: This is an alpha build (not yet stable)."
echo "Run it with: $BINARY_NAME <filename>"

echo "Happy hacking :)"
